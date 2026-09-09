#include "qemu/osdep.h"
#include "cpu.h"
#include "system/kvm.h"
#include "system/tcg.h"
#include "helper_regs.h"
#include "mmu-hash64.h"
#include "migration/vmstate.h"
#include "migration/qemu-file-types.h"
#include "qapi/error.h"
#include "kvm_ppc.h"
#include "power8-pmu.h"
#include "system/replay.h"

static void post_load_update_msr(CPUPPCState *env)
{
    target_ulong msr = target_ulong_val(&env->msr);

    /*
     * Invalidate all supported msr bits except MSR_TGPR/MSR_HVB
     * before restoring.  Note that this recomputes hflags.
     */
    target_ulong_set(&env->msr, target_ulong_val(&env->msr) ^ (env->msr_mask & ~((1ULL << MSR_TGPR) | MSR_HVB)));
    ppc_store_msr(env, msr);
}

static int get_avr(QEMUFile *f, void *pv, size_t size,
                   const VMStateField *field)
{
    ppc_avr_t *v = pv;

    v->u64[0] = qemu_get_be64(f);
    v->u64[1] = qemu_get_be64(f);

    return 0;
}

static int put_avr(QEMUFile *f, void *pv, size_t size,
                   const VMStateField *field, JSONWriter *vmdesc)
{
    ppc_avr_t *v = pv;

    qemu_put_be64(f, v->u64[0]);
    qemu_put_be64(f, v->u64[1]);
    return 0;
}

static const VMStateInfo vmstate_info_avr = {
    .name = "avr",
    .get  = get_avr,
    .put  = put_avr,
};

#define VMSTATE_AVR_ARRAY_V(_f, _s, _n, _v)                       \
    VMSTATE_SUB_ARRAY(_f, _s, 32, _n, _v, vmstate_info_avr, ppc_avr_t)

#define VMSTATE_AVR_ARRAY(_f, _s, _n)                             \
    VMSTATE_AVR_ARRAY_V(_f, _s, _n, 0)

static int get_fpr(QEMUFile *f, void *pv, size_t size,
                   const VMStateField *field)
{
    ppc_vsr_t *v = pv;

    v->VsrD(0) = qemu_get_be64(f);

    return 0;
}

static int put_fpr(QEMUFile *f, void *pv, size_t size,
                   const VMStateField *field, JSONWriter *vmdesc)
{
    ppc_vsr_t *v = pv;

    qemu_put_be64(f, v->VsrD(0));
    return 0;
}

static const VMStateInfo vmstate_info_fpr = {
    .name = "fpr",
    .get  = get_fpr,
    .put  = put_fpr,
};

#define VMSTATE_FPR_ARRAY_V(_f, _s, _n, _v)                       \
    VMSTATE_SUB_ARRAY(_f, _s, 0, _n, _v, vmstate_info_fpr, ppc_vsr_t)

#define VMSTATE_FPR_ARRAY(_f, _s, _n)                             \
    VMSTATE_FPR_ARRAY_V(_f, _s, _n, 0)

static int get_vsr(QEMUFile *f, void *pv, size_t size,
                   const VMStateField *field)
{
    ppc_vsr_t *v = pv;

    v->VsrD(1) = qemu_get_be64(f);

    return 0;
}

static int put_vsr(QEMUFile *f, void *pv, size_t size,
                   const VMStateField *field, JSONWriter *vmdesc)
{
    ppc_vsr_t *v = pv;

    qemu_put_be64(f, v->VsrD(1));
    return 0;
}

static const VMStateInfo vmstate_info_vsr = {
    .name = "vsr",
    .get  = get_vsr,
    .put  = put_vsr,
};

#define VMSTATE_VSR_ARRAY_V(_f, _s, _n, _v)                       \
    VMSTATE_SUB_ARRAY(_f, _s, 0, _n, _v, vmstate_info_vsr, ppc_vsr_t)

#define VMSTATE_VSR_ARRAY(_f, _s, _n)                             \
    VMSTATE_VSR_ARRAY_V(_f, _s, _n, 0)

static int cpu_pre_save(void *opaque)
{
    PowerPCCPU *cpu = opaque;
    CPUPPCState *env = &cpu->env;
    int i;

    target_ulong_array_set(&env->spr.rec, SPR_LR, env->lr);
    target_ulong_array_set(&env->spr.rec, SPR_CTR, env->ctr);
    target_ulong_array_set(&env->spr.rec, SPR_XER, cpu_read_xer(env));
#if defined(TARGET_PPC64)
    target_ulong_array_set(&env->spr.rec, SPR_CFAR, env->cfar);
#endif
    target_ulong_array_set(&env->spr.rec, SPR_BOOKE_SPEFSCR, env->spe_fscr);

    for (i = 0; (i < 4) && (i < env->nb_BATs); i++) {
        target_ulong_array_set(&env->spr.rec, SPR_DBAT0U + 2 * i, env->DBAT[0][i]);
        target_ulong_array_set(&env->spr.rec, SPR_DBAT0U + 2 * i + 1, env->DBAT[1][i]);
        target_ulong_array_set(&env->spr.rec, SPR_IBAT0U + 2 * i, env->IBAT[0][i]);
        target_ulong_array_set(&env->spr.rec, SPR_IBAT0U + 2 * i + 1, env->IBAT[1][i]);
    }
    for (i = 0; (i < 4) && ((i + 4) < env->nb_BATs); i++) {
        target_ulong_array_set(&env->spr.rec, SPR_DBAT4U + 2 * i, env->DBAT[0][i + 4]);
        target_ulong_array_set(&env->spr.rec, SPR_DBAT4U + 2 * i + 1, env->DBAT[1][i + 4]);
        target_ulong_array_set(&env->spr.rec, SPR_IBAT4U + 2 * i, env->IBAT[0][i + 4]);
        target_ulong_array_set(&env->spr.rec, SPR_IBAT4U + 2 * i + 1, env->IBAT[1][i + 4]);
    }

    /* Used to retain migration compatibility for pre 6.0 for 601 machines. */
    target_ulong_set(&env->hflags_compat_nmsr, 0);

    if (tcg_enabled()) {
        /*
         * TCG does not maintain the DECR spr (unlike KVM) so have to save
         * it here.
         */
        target_ulong_array_set(&env->spr.rec, SPR_DECR, cpu_ppc_load_decr(env));
    }

    return 0;
}

/*
 * Determine if a given PVR is a "close enough" match to the CPU
 * object.  For TCG and KVM PR it would probably be sufficient to
 * require an exact PVR match.  However for KVM HV the user is
 * restricted to a PVR exactly matching the host CPU.  The correct way
 * to handle this is to put the guest into an architected
 * compatibility mode.  However, to allow a more forgiving transition
 * and migration from before this was widely done, we allow migration
 * between sufficiently similar PVRs, as determined by the CPU class's
 * pvr_match() hook.
 */
static bool pvr_match(PowerPCCPU *cpu, uint32_t pvr)
{
    PowerPCCPUClass *pcc = POWERPC_CPU_GET_CLASS(cpu);

    if (pvr == pcc->pvr) {
        return true;
    }
    return pcc->pvr_match(pcc, pvr, true);
}

static int cpu_post_load(void *opaque, int version_id)
{
    PowerPCCPU *cpu = opaque;
    CPUPPCState *env = &cpu->env;
    int i;

    /*
     * If we're operating in compat mode, we should be ok as long as
     * the destination supports the same compatibility mode.
     *
     * Otherwise, however, we require that the destination has exactly
     * the same CPU model as the source.
     */

#if defined(TARGET_PPC64)
    if (cpu->compat_pvr) {
        uint32_t compat_pvr = cpu->compat_pvr;
        Error *local_err = NULL;
        int ret;

        cpu->compat_pvr = 0;
        ret = ppc_set_compat(cpu, compat_pvr, &local_err);
        if (ret < 0) {
            error_report_err(local_err);
            return ret;
        }
    } else
#endif
    {
        if (!pvr_match(cpu, target_ulong_array_val(&env->spr.rec, SPR_PVR))) {
            return -EINVAL;
        }
    }

    /*
     * If we're running with KVM HV, there is a chance that the guest
     * is running with KVM HV and its kernel does not have the
     * capability of dealing with a different PVR other than this
     * exact host PVR in KVM_SET_SREGS. If that happens, the
     * guest freezes after migration.
     *
     * The function kvmppc_pvr_workaround_required does this verification
     * by first checking if the kernel has the cap, returning true immediately
     * if that is the case. Otherwise, it checks if we're running in KVM PR.
     * If the guest kernel does not have the cap and we're not running KVM-PR
     * (so, it is running KVM-HV), we need to ensure that KVM_SET_SREGS will
     * receive the PVR it expects as a workaround.
     *
     */
    if (kvmppc_pvr_workaround_required(cpu)) {
        target_ulong_array_set(&env->spr.rec, SPR_PVR, env->spr_cb[SPR_PVR].default_value);
    }

    env->lr = target_ulong_array_val(&env->spr.rec, SPR_LR);
    env->ctr = target_ulong_array_val(&env->spr.rec, SPR_CTR);
    cpu_write_xer(env, target_ulong_array_val(&env->spr.rec, SPR_XER));
#if defined(TARGET_PPC64)
    env->cfar = target_ulong_array_val(&env->spr.rec, SPR_CFAR);
#endif
    env->spe_fscr = target_ulong_array_val(&env->spr.rec, SPR_BOOKE_SPEFSCR);

    for (i = 0; (i < 4) && (i < env->nb_BATs); i++) {
        env->DBAT[0][i] = target_ulong_array_val(&env->spr.rec, SPR_DBAT0U + 2 * i);
        env->DBAT[1][i] = target_ulong_array_val(&env->spr.rec, SPR_DBAT0U + 2 * i + 1);
        env->IBAT[0][i] = target_ulong_array_val(&env->spr.rec, SPR_IBAT0U + 2 * i);
        env->IBAT[1][i] = target_ulong_array_val(&env->spr.rec, SPR_IBAT0U + 2 * i + 1);
    }
    for (i = 0; (i < 4) && ((i + 4) < env->nb_BATs); i++) {
        env->DBAT[0][i + 4] = target_ulong_array_val(&env->spr.rec, SPR_DBAT4U + 2 * i);
        env->DBAT[1][i + 4] = target_ulong_array_val(&env->spr.rec, SPR_DBAT4U + 2 * i + 1);
        env->IBAT[0][i + 4] = target_ulong_array_val(&env->spr.rec, SPR_IBAT4U + 2 * i);
        env->IBAT[1][i + 4] = target_ulong_array_val(&env->spr.rec, SPR_IBAT4U + 2 * i + 1);
    }

    if (!cpu->vhyp) {
        ppc_store_sdr1(env, target_ulong_array_val(&env->spr.rec, SPR_SDR1));
    }

    if (!cpu->rtas_stopped_state) {
        /*
         * The source QEMU doesn't have fb802acdc8 and still uses halt +
         * PM bits in LPCR to implement RTAS stopped state. The new (this)
         * QEMU will have put the secondary vcpus in stopped state,
         * waiting for the start-cpu RTAS call. That call will never come
         * if the source cpus were already running. Try to infer the cpus
         * state and set env->quiesced accordingly.
         *
         * env->quiesced = true  ==> the cpu is waiting to start
         * env->quiesced = false ==> the cpu is running (unless halted)
         */

        /*
         * Halted _could_ mean quiesced, but it could also be cede,
         * confer_self, power management, etc.
         */
        if (CPU(cpu)->halted) {
            PowerPCCPUClass *pcc = POWERPC_CPU_GET_CLASS(cpu);
            /*
             * Both the PSSCR_EC bit and LPCR PM bits set at cpu reset
             * and rtas_stop and cleared at rtas_start, it's a good
             * heuristic.
             */
            if ((target_ulong_array_val(&env->spr.rec, SPR_PSSCR) & PSSCR_EC) &&
                (target_ulong_array_val(&env->spr.rec, SPR_LPCR) & pcc->lpcr_pm)) {
                env->quiesced = true;
            } else {
                env->quiesced = false;
            }
        } else {
            /*
             * Old QEMU sets halted during rtas_stop_self. Not halted,
             * therefore definitely not quiesced.
             */
            env->quiesced = false;
        }
    }

    post_load_update_msr(env);

    if (tcg_enabled()) {
        /* Re-set breaks based on regs */
#if defined(TARGET_PPC64)
        ppc_update_ciabr(env);
        ppc_update_daw(env, 0);
        ppc_update_daw(env, 1);
#endif
        /*
         * TCG needs to re-start the decrementer timer and/or raise the
         * interrupt. This works for level-triggered decrementer. Edge
         * triggered types (including HDEC) would need to carry more state.
         */
        cpu_ppc_store_decr(env, target_ulong_array_val(&env->spr.rec, SPR_DECR));
        pmu_mmcr01a_updated(env);
    }

    return 0;
}

static bool fpu_needed(void *opaque)
{
    PowerPCCPU *cpu = opaque;

    return cpu->env.insns_flags & PPC_FLOAT;
}

static const VMStateDescription vmstate_fpu = {
    .name = "cpu/fpu",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = fpu_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_FPR_ARRAY(env.vsr, PowerPCCPU, 32),
        VMSTATE_UINT32_AVAILABLE(env.fpscr.u32, PowerPCCPU, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(env.fpscr.u64, PowerPCCPU, target_is_long_bits_64),
        VMSTATE_END_OF_LIST()
    },
};

static bool altivec_needed(void *opaque)
{
    PowerPCCPU *cpu = opaque;

    return cpu->env.insns_flags & PPC_ALTIVEC;
}

static int get_vscr(QEMUFile *f, void *opaque, size_t size,
                    const VMStateField *field)
{
    PowerPCCPU *cpu = opaque;
    ppc_store_vscr(&cpu->env, qemu_get_be32(f));
    return 0;
}

static int put_vscr(QEMUFile *f, void *opaque, size_t size,
                    const VMStateField *field, JSONWriter *vmdesc)
{
    PowerPCCPU *cpu = opaque;
    qemu_put_be32(f, ppc_get_vscr(&cpu->env));
    return 0;
}

static const VMStateInfo vmstate_vscr = {
    .name = "cpu/altivec/vscr",
    .get = get_vscr,
    .put = put_vscr,
};

static const VMStateDescription vmstate_altivec = {
    .name = "cpu/altivec",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = altivec_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_AVR_ARRAY(env.vsr, PowerPCCPU, 32),
        /*
         * Save the architecture value of the vscr, not the internally
         * expanded version.  Since this architecture value does not
         * exist in memory to be stored, this requires a but of hoop
         * jumping.  We want OFFSET=0 so that we effectively pass CPU
         * to the helper functions.
         */
        {
            .name = "vscr",
            .version_id = 0,
            .size = sizeof(uint32_t),
            .info = &vmstate_vscr,
            .flags = VMS_SINGLE,
            .offset = 0
        },
        VMSTATE_END_OF_LIST()
    },
};

static bool vsx_needed(void *opaque)
{
    PowerPCCPU *cpu = opaque;

    return cpu->env.insns_flags2 & PPC2_VSX;
}

static const VMStateDescription vmstate_vsx = {
    .name = "cpu/vsx",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = vsx_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_VSR_ARRAY(env.vsr, PowerPCCPU, 32),
        VMSTATE_END_OF_LIST()
    },
};

#ifdef TARGET_PPC64
/* Transactional memory state */
static bool tm_needed(void *opaque)
{
    PowerPCCPU *cpu = opaque;
    CPUPPCState *env = &cpu->env;
    return FIELD_EX64(target_ulong_val(&env->msr), MSR, TS);
}

static const VMStateDescription vmstate_tm = {
    .name = "cpu/tm",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = tm_needed,
    .fields = (const VMStateField []) {
        VMSTATE_UINT32_ARRAY_AVAILABLE(env.tm_gpr.u32, PowerPCCPU, 32,
                                       target_is_long_bits_32),
        VMSTATE_UINT64_ARRAY_AVAILABLE(env.tm_gpr.u64, PowerPCCPU, 32,
                                       target_is_long_bits_64),
        VMSTATE_AVR_ARRAY(env.tm_vsr, PowerPCCPU, 64),
        VMSTATE_UINT64(env.tm_cr, PowerPCCPU),
        VMSTATE_UINT64(env.tm_lr, PowerPCCPU),
        VMSTATE_UINT64(env.tm_ctr, PowerPCCPU),
        VMSTATE_UINT64(env.tm_fpscr, PowerPCCPU),
        VMSTATE_UINT64(env.tm_amr, PowerPCCPU),
        VMSTATE_UINT64(env.tm_ppr, PowerPCCPU),
        VMSTATE_UINT64(env.tm_vrsave, PowerPCCPU),
        VMSTATE_UINT32(env.tm_vscr, PowerPCCPU),
        VMSTATE_UINT64(env.tm_dscr, PowerPCCPU),
        VMSTATE_UINT64(env.tm_tar, PowerPCCPU),
        VMSTATE_END_OF_LIST()
    },
};
#endif

static bool sr_needed(void *opaque)
{
#ifdef TARGET_PPC64
    PowerPCCPU *cpu = opaque;

    return !mmu_is_64bit(cpu->env.mmu_model);
#else
    return true;
#endif
}

static const VMStateDescription vmstate_sr = {
    .name = "cpu/sr",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = sr_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_UINT32_ARRAY_AVAILABLE(env.sr.u32, PowerPCCPU, 32,
                                       target_is_long_bits_32),
        VMSTATE_UINT64_ARRAY_AVAILABLE(env.sr.u64, PowerPCCPU, 32,
                                       target_is_long_bits_64),
        VMSTATE_END_OF_LIST()
    },
};

#ifdef TARGET_PPC64
static int get_slbe(QEMUFile *f, void *pv, size_t size,
                    const VMStateField *field)
{
    ppc_slb_t *v = pv;

    v->esid = qemu_get_be64(f);
    v->vsid = qemu_get_be64(f);

    return 0;
}

static int put_slbe(QEMUFile *f, void *pv, size_t size,
                    const VMStateField *field, JSONWriter *vmdesc)
{
    ppc_slb_t *v = pv;

    qemu_put_be64(f, v->esid);
    qemu_put_be64(f, v->vsid);
    return 0;
}

static const VMStateInfo vmstate_info_slbe = {
    .name = "slbe",
    .get  = get_slbe,
    .put  = put_slbe,
};

#define VMSTATE_SLB_ARRAY_V(_f, _s, _n, _v)                       \
    VMSTATE_ARRAY(_f, _s, _n, _v, vmstate_info_slbe, ppc_slb_t)

#define VMSTATE_SLB_ARRAY(_f, _s, _n)                             \
    VMSTATE_SLB_ARRAY_V(_f, _s, _n, 0)

static bool slb_needed(void *opaque)
{
    PowerPCCPU *cpu = opaque;

    /* We don't support any of the old segment table based 64-bit CPUs */
    return mmu_is_64bit(cpu->env.mmu_model);
}

static int slb_post_load(void *opaque, int version_id)
{
    PowerPCCPU *cpu = opaque;
    CPUPPCState *env = &cpu->env;
    int i;

    /*
     * We've pulled in the raw esid and vsid values from the migration
     * stream, but we need to recompute the page size pointers
     */
    for (i = 0; i < cpu->hash64_opts->slb_size; i++) {
        if (ppc_store_slb(cpu, i, env->slb[i].esid, env->slb[i].vsid) < 0) {
            /* Migration source had bad values in its SLB */
            return -1;
        }
    }

    return 0;
}

static const VMStateDescription vmstate_slb = {
    .name = "cpu/slb",
    .version_id = 2,
    .minimum_version_id = 1,
    .needed = slb_needed,
    .post_load = slb_post_load,
    .fields = (const VMStateField[]) {
        VMSTATE_SLB_ARRAY(env.slb, PowerPCCPU, MAX_SLB_ENTRIES),
        VMSTATE_END_OF_LIST()
    }
};
#endif /* TARGET_PPC64 */

static const VMStateDescription vmstate_tlb6xx_entry = {
    .name = "cpu/tlb6xx_entry",
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (const VMStateField[]) {
        VMSTATE_UINT32_AVAILABLE(pte0.u32, ppc6xx_tlb_t, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(pte0.u64, ppc6xx_tlb_t, target_is_long_bits_64),
        VMSTATE_UINT32_AVAILABLE(pte1.u32, ppc6xx_tlb_t, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(pte1.u64, ppc6xx_tlb_t, target_is_long_bits_64),
        VMSTATE_UINT32_AVAILABLE(EPN.u32, ppc6xx_tlb_t, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(EPN.u64, ppc6xx_tlb_t, target_is_long_bits_64),
        VMSTATE_END_OF_LIST()
    },
};

static bool tlb6xx_needed(void *opaque)
{
    PowerPCCPU *cpu = opaque;
    CPUPPCState *env = &cpu->env;

    return env->nb_tlb && (env->tlb_type == TLB_6XX);
}

static const VMStateDescription vmstate_tlb6xx = {
    .name = "cpu/tlb6xx",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = tlb6xx_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_INT32_EQUAL(env.nb_tlb, PowerPCCPU),
        VMSTATE_STRUCT_VARRAY_POINTER_INT32(env.tlb.tlb6, PowerPCCPU,
                                            env.nb_tlb,
                                            vmstate_tlb6xx_entry,
                                            ppc6xx_tlb_t),
        VMSTATE_UINT32_ARRAY_AVAILABLE(env.tgpr.u32, PowerPCCPU, 4,
                                       target_is_long_bits_32),
        VMSTATE_UINT64_ARRAY_AVAILABLE(env.tgpr.u64, PowerPCCPU, 4,
                                       target_is_long_bits_64),
        VMSTATE_END_OF_LIST()
    }
};

static const VMStateDescription vmstate_tlbemb_entry = {
    .name = "cpu/tlbemb_entry",
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (const VMStateField[]) {
        VMSTATE_UINT64(RPN, ppcemb_tlb_t),
        VMSTATE_UINT32_AVAILABLE(EPN.u32, ppcemb_tlb_t, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(EPN.u64, ppcemb_tlb_t, target_is_long_bits_64),
        VMSTATE_UINT32_AVAILABLE(PID.u32, ppcemb_tlb_t, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(PID.u64, ppcemb_tlb_t, target_is_long_bits_64),
        VMSTATE_UINT32_AVAILABLE(size.u32, ppcemb_tlb_t, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(size.u64, ppcemb_tlb_t, target_is_long_bits_64),
        VMSTATE_UINT32(prot, ppcemb_tlb_t),
        VMSTATE_UINT32(attr, ppcemb_tlb_t),
        VMSTATE_END_OF_LIST()
    },
};

static bool tlbemb_needed(void *opaque)
{
    PowerPCCPU *cpu = opaque;
    CPUPPCState *env = &cpu->env;

    return env->nb_tlb && (env->tlb_type == TLB_EMB);
}

static const VMStateDescription vmstate_tlbemb = {
    .name = "cpu/tlbemb",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = tlbemb_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_INT32_EQUAL(env.nb_tlb, PowerPCCPU),
        VMSTATE_STRUCT_VARRAY_POINTER_INT32(env.tlb.tlbe, PowerPCCPU,
                                            env.nb_tlb,
                                            vmstate_tlbemb_entry,
                                            ppcemb_tlb_t),
        VMSTATE_END_OF_LIST()
    },
};

static const VMStateDescription vmstate_tlbmas_entry = {
    .name = "cpu/tlbmas_entry",
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (const VMStateField[]) {
        VMSTATE_UINT32(mas8, ppcmas_tlb_t),
        VMSTATE_UINT32(mas1, ppcmas_tlb_t),
        VMSTATE_UINT64(mas2, ppcmas_tlb_t),
        VMSTATE_UINT64(mas7_3, ppcmas_tlb_t),
        VMSTATE_END_OF_LIST()
    },
};

static bool tlbmas_needed(void *opaque)
{
    PowerPCCPU *cpu = opaque;
    CPUPPCState *env = &cpu->env;

    return env->nb_tlb && (env->tlb_type == TLB_MAS);
}

static const VMStateDescription vmstate_tlbmas = {
    .name = "cpu/tlbmas",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = tlbmas_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_INT32_EQUAL(env.nb_tlb, PowerPCCPU),
        VMSTATE_STRUCT_VARRAY_POINTER_INT32(env.tlb.tlbm, PowerPCCPU,
                                            env.nb_tlb,
                                            vmstate_tlbmas_entry,
                                            ppcmas_tlb_t),
        VMSTATE_END_OF_LIST()
    }
};

static bool compat_needed(void *opaque)
{
    PowerPCCPU *cpu = opaque;

    assert(!(cpu->compat_pvr && !cpu->vhyp));
    return cpu->compat_pvr != 0;
}

static const VMStateDescription vmstate_compat = {
    .name = "cpu/compat",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = compat_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_UINT32(compat_pvr, PowerPCCPU),
        VMSTATE_END_OF_LIST()
    }
};

static bool reservation_needed(void *opaque)
{
    return (replay_mode != REPLAY_MODE_NONE);
}

static const VMStateDescription vmstate_reservation = {
    .name = "cpu/reservation",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = reservation_needed,
    .fields = (const VMStateField[]) {
        VMSTATE_UINT32_AVAILABLE(env.reserve_addr.u32, PowerPCCPU, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(env.reserve_addr.u64, PowerPCCPU, target_is_long_bits_64),
        VMSTATE_UINT32_AVAILABLE(env.reserve_length.u32, PowerPCCPU, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(env.reserve_length.u64, PowerPCCPU, target_is_long_bits_64),
        VMSTATE_UINT32_AVAILABLE(env.reserve_val.u32, PowerPCCPU, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(env.reserve_val.u64, PowerPCCPU, target_is_long_bits_64),
#if defined(TARGET_PPC64)
        VMSTATE_UINT32_AVAILABLE(env.reserve_val2.u32, PowerPCCPU, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(env.reserve_val2.u64, PowerPCCPU, target_is_long_bits_64),
#endif
        VMSTATE_END_OF_LIST()
    }
};

static bool rtas_stopped_needed(void *opaque)
{
    PowerPCCPU *cpu = opaque;

    return cpu->rtas_stopped_state;
}

static const VMStateDescription vmstate_rtas_stopped = {
    .name = "cpu/rtas_stopped",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = rtas_stopped_needed,
    .fields = (const VMStateField[]) {
        /*
         * "RTAS stopped" state, independent of halted state. For QEMU
         * < 10.0, this is taken from cpu->halted at cpu_post_load()
         */
        VMSTATE_BOOL(env.quiesced, PowerPCCPU),
        VMSTATE_END_OF_LIST()
    }
};

#ifdef TARGET_PPC64
static bool bhrb_needed(void *opaque)
{
    PowerPCCPU *cpu = opaque;
    return (cpu->env.flags & POWERPC_FLAG_BHRB) != 0;
}

static const VMStateDescription vmstate_bhrb = {
    .name = "cpu/bhrb",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = bhrb_needed,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32_AVAILABLE(env.bhrb_offset.u32, PowerPCCPU, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(env.bhrb_offset.u64, PowerPCCPU, target_is_long_bits_64),
        VMSTATE_UINT64_ARRAY(env.bhrb, PowerPCCPU, BHRB_MAX_NUM_ENTRIES),
        VMSTATE_END_OF_LIST()
    }
};
#endif

const VMStateDescription vmstate_ppc_cpu = {
    .name = "cpu",
    .version_id = 5,
    .minimum_version_id = 5,
    .pre_save = cpu_pre_save,
    .post_load = cpu_post_load,
    .fields = (const VMStateField[]) {
        VMSTATE_UNUSED(sizeof(target_ulong)), /* was _EQUAL(env.spr[SPR_PVR]) */

        /* User mode architected state */
        VMSTATE_UINT32_ARRAY_AVAILABLE(env.gpr.u32, PowerPCCPU, 32,
                                       target_is_long_bits_32),
        VMSTATE_UINT64_ARRAY_AVAILABLE(env.gpr.u64, PowerPCCPU, 32,
                                       target_is_long_bits_64),
#if !defined(TARGET_PPC64)
        VMSTATE_UINT32_ARRAY_AVAILABLE(env.gprh.u32, PowerPCCPU, 32,
                                       target_is_long_bits_32),
        VMSTATE_UINT64_ARRAY_AVAILABLE(env.gprh.u64, PowerPCCPU, 32,
                                       target_is_long_bits_64),
#endif
        VMSTATE_UINT32_ARRAY(env.crf, PowerPCCPU, 8),
        VMSTATE_UINT32_AVAILABLE(env.nip.u32, PowerPCCPU, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(env.nip.u64, PowerPCCPU, target_is_long_bits_64),

        /* SPRs */
        VMSTATE_UINT32_ARRAY_AVAILABLE(env.spr.u32, PowerPCCPU, 1024,
                                       target_is_long_bits_32),
        VMSTATE_UINT64_ARRAY_AVAILABLE(env.spr.u64, PowerPCCPU, 1024,
                                       target_is_long_bits_64),
        VMSTATE_UINT64(env.spe_acc, PowerPCCPU),

        VMSTATE_UNUSED(sizeof(target_ulong)), /* was env.reserve_addr */

        /* Supervisor mode architected state */
        VMSTATE_UINT32_AVAILABLE(env.msr.u32, PowerPCCPU, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(env.msr.u64, PowerPCCPU, target_is_long_bits_64),

        /* Backward compatible internal state */
        VMSTATE_UINT32_AVAILABLE(env.hflags_compat_nmsr.u32, PowerPCCPU, target_is_long_bits_32),
        VMSTATE_UINT64_AVAILABLE(env.hflags_compat_nmsr.u64, PowerPCCPU, target_is_long_bits_64),

        VMSTATE_END_OF_LIST()
    },
    .subsections = (const VMStateDescription * const []) {
        &vmstate_fpu,
        &vmstate_altivec,
        &vmstate_vsx,
        &vmstate_sr,
#ifdef TARGET_PPC64
        &vmstate_tm,
        &vmstate_slb,
        &vmstate_bhrb,
#endif /* TARGET_PPC64 */
        &vmstate_tlb6xx,
        &vmstate_tlbemb,
        &vmstate_tlbmas,
        &vmstate_compat,
        &vmstate_reservation,
        &vmstate_rtas_stopped,
        NULL
    }
};
