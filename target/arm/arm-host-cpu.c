/*
 * AArch64 -cpu host (KVM / HVF / WHPX)
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "qemu/osdep.h"
#include "cpu.h"
#include "cpregs.h"
#include "qemu/module.h"
#include "system/kvm.h"
#include "system/hvf.h"
#include "system/whpx.h"
#include "system/nitro-accel.h"
#include "kvm_arm.h"
#include "hvf_arm.h"
#include "whpx_arm.h"
#include "internals.h"

#if defined(CONFIG_KVM)
static void kvm_arm_set_cpreg_mig_tolerances(ARMCPU *cpu)
{
    /*
     * Registers that may be in the incoming stream and not exposed
     * on the destination
     */

    /*
     * TCR_EL1 was erroneously unconditionally exposed before linux v6.13.
     * See commit 0fcb4eea5345 ("KVM: arm64: Hide TCR2_EL1 from userspace
     * when disabled for guests")
     */
    arm_register_cpreg_mig_tolerance(cpu, ARM64_SYS_REG(3, 0, 2, 0, 3),
                                     0, 0, ToleranceNotOnBothEnds);
    /*
     * PIRE0_EL1 and PIR_EL1 were erroneously unconditionally exposed
     * before linux v6.13. See commit a68cddbe47ef ("KVM: arm64: Hide
     * S1PIE registers from userspace when disabled for guests")
     */
    arm_register_cpreg_mig_tolerance(cpu, ARM64_SYS_REG(3, 0, 10, 2, 2),
                                     0, 0, ToleranceNotOnBothEnds);
    arm_register_cpreg_mig_tolerance(cpu, ARM64_SYS_REG(3, 0, 10, 2, 3),
                                     0, 0, ToleranceNotOnBothEnds);

    /*
     * KVM_REG_ARM_VENDOR_HYP_BMAP_2 pseudo FW register is exposed
     * from v6.15 onwards. Backward migration from a >= v6.15 to an older
     * kernel would fail without cpreg migration tolerance definition.
     * If the register is present on source but not on destination, make
     * sure it has its reset value, ie. 0, meaning no service is exposed
     * to the guest.
     */
    arm_register_cpreg_mig_tolerance(cpu, KVM_REG_ARM_FW_FEAT_BMAP_REG(3),
                                     UINT64_MAX, 0, ToleranceOnlySrcTestValue);
}
#endif

void aarch64_host_initfn(Object *obj)
{
    ARMCPU *cpu = ARM_CPU(obj);

#if defined(CONFIG_NITRO)
    if (nitro_enabled()) {
        /* The nitro accel uses -cpu host, but does not actually consume it */
        return;
    }
#endif

#if defined(CONFIG_KVM)
    kvm_arm_set_cpreg_mig_tolerances(cpu);
    kvm_arm_set_cpu_features_from_host(cpu);
    aarch64_add_sve_properties(obj);
#elif defined(CONFIG_HVF)
    hvf_arm_set_cpu_features_from_host(cpu);
#elif defined(CONFIG_WHPX)
    whpx_arm_set_cpu_features_from_host(cpu);
#else
    g_assert_not_reached();
#endif
    if (arm_feature(&cpu->env, ARM_FEATURE_AARCH64)) {
        aarch64_add_pauth_properties(obj);
    }
}

static const ARMCPUInfo aarch64_host_cpu = {
    .name = "host",
    .initfn = aarch64_host_initfn,
};

static void aarch64_host_cpu_register_types(void)
{
    arm_cpu_register(&aarch64_host_cpu);
}

type_init(aarch64_host_cpu_register_types)
