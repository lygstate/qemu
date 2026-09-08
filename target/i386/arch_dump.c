/*
 * i386 memory mapping
 *
 * Copyright Fujitsu, Corp. 2011, 2012
 *
 * Authors:
 *     Wen Congyang <wency@cn.fujitsu.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#include "qemu/osdep.h"
#include "cpu.h"
#include "system/dump.h"
#include "elf.h"
#include "system/memory_mapping.h"
#include "qemu/target-info-qom.h"

#define ELF_NOTE_SIZE(hdr_size, name_size, desc_size)   \
    ((DIV_ROUND_UP((hdr_size), 4)                       \
      + DIV_ROUND_UP((name_size), 4)                    \
      + DIV_ROUND_UP((desc_size), 4)) * 4)

#ifdef TARGET_X86_64
typedef struct {
    target_ulong r15, r14, r13, r12, rbp, rbx, r11, r10;
    target_ulong r9, r8, rax, rcx, rdx, rsi, rdi, orig_rax;
    target_ulong rip, cs, eflags;
    target_ulong rsp, ss;
    target_ulong fs_base, gs_base;
    target_ulong ds, es, fs, gs;
} x86_64_user_regs_struct;

typedef struct {
    char pad1[32];
    uint32_t pid;
    char pad2[76];
    x86_64_user_regs_struct regs;
    char pad3[8];
} x86_64_elf_prstatus;

static int x86_64_write_elf64_note(WriteCoreDumpFunction f,
                                   CPUX86State *env, int id,
                                   DumpState *s)
{
    x86_64_user_regs_struct regs;
    Elf64_Nhdr *note;
    char *buf;
    int descsz, note_size, name_size = 5;
    const char *name = "CORE";
    int ret;

    regs.r15 = target_ulong_array_val(&env->regs.rec, 15);
    regs.r14 = target_ulong_array_val(&env->regs.rec, 14);
    regs.r13 = target_ulong_array_val(&env->regs.rec, 13);
    regs.r12 = target_ulong_array_val(&env->regs.rec, 12);
    regs.r11 = target_ulong_array_val(&env->regs.rec, 11);
    regs.r10 = target_ulong_array_val(&env->regs.rec, 10);
    regs.r9  = target_ulong_array_val(&env->regs.rec, 9);
    regs.r8  = target_ulong_array_val(&env->regs.rec, 8);
    regs.rbp = target_ulong_array_val(&env->regs.rec, R_EBP);
    regs.rsp = target_ulong_array_val(&env->regs.rec, R_ESP);
    regs.rdi = target_ulong_array_val(&env->regs.rec, R_EDI);
    regs.rsi = target_ulong_array_val(&env->regs.rec, R_ESI);
    regs.rdx = target_ulong_array_val(&env->regs.rec, R_EDX);
    regs.rcx = target_ulong_array_val(&env->regs.rec, R_ECX);
    regs.rbx = target_ulong_array_val(&env->regs.rec, R_EBX);
    regs.rax = target_ulong_array_val(&env->regs.rec, R_EAX);
    regs.rip = target_ulong_val(&(env)->eip);
    regs.eflags = target_ulong_val(&(env)->eflags);

    regs.orig_rax = 0; /* FIXME */
    regs.cs = env->segs[R_CS].selector;
    regs.ss = env->segs[R_SS].selector;
    regs.fs_base = target_ulong_val(&(env->segs[R_FS]).base);
    regs.gs_base = target_ulong_val(&(env->segs[R_GS]).base);
    regs.ds = env->segs[R_DS].selector;
    regs.es = env->segs[R_ES].selector;
    regs.fs = env->segs[R_FS].selector;
    regs.gs = env->segs[R_GS].selector;

    descsz = sizeof(x86_64_elf_prstatus);
    note_size = ELF_NOTE_SIZE(sizeof(Elf64_Nhdr), name_size, descsz);
    note = g_malloc0(note_size);
    note->n_namesz = cpu_to_le32(name_size);
    note->n_descsz = cpu_to_le32(descsz);
    note->n_type = cpu_to_le32(NT_PRSTATUS);
    buf = (char *)note;
    buf += ROUND_UP(sizeof(Elf64_Nhdr), 4);
    memcpy(buf, name, name_size);
    buf += ROUND_UP(name_size, 4);
    memcpy(buf + 32, &id, 4); /* pr_pid */
    buf += descsz - sizeof(x86_64_user_regs_struct)-sizeof(target_ulong);
    memcpy(buf, &regs, sizeof(x86_64_user_regs_struct));

    ret = f(note, note_size, s);
    g_free(note);
    if (ret < 0) {
        return -1;
    }

    return 0;
}
#endif

typedef struct {
    uint32_t ebx, ecx, edx, esi, edi, ebp, eax;
    unsigned short ds, __ds, es, __es;
    unsigned short fs, __fs, gs, __gs;
    uint32_t orig_eax, eip;
    unsigned short cs, __cs;
    uint32_t eflags, esp;
    unsigned short ss, __ss;
} x86_user_regs_struct;

typedef struct {
    char pad1[24];
    uint32_t pid;
    char pad2[44];
    x86_user_regs_struct regs;
    char pad3[4];
} x86_elf_prstatus;

static void x86_fill_elf_prstatus(x86_elf_prstatus *prstatus, CPUX86State *env,
                                  int id)
{
    memset(prstatus, 0, sizeof(x86_elf_prstatus));
    prstatus->regs.ebp = target_ulong_array_val(&env->regs.rec, R_EBP) & 0xffffffff;
    prstatus->regs.esp = target_ulong_array_val(&env->regs.rec, R_ESP) & 0xffffffff;
    prstatus->regs.edi = target_ulong_array_val(&env->regs.rec, R_EDI) & 0xffffffff;
    prstatus->regs.esi = target_ulong_array_val(&env->regs.rec, R_ESI) & 0xffffffff;
    prstatus->regs.edx = target_ulong_array_val(&env->regs.rec, R_EDX) & 0xffffffff;
    prstatus->regs.ecx = target_ulong_array_val(&env->regs.rec, R_ECX) & 0xffffffff;
    prstatus->regs.ebx = target_ulong_array_val(&env->regs.rec, R_EBX) & 0xffffffff;
    prstatus->regs.eax = target_ulong_array_val(&env->regs.rec, R_EAX) & 0xffffffff;
    prstatus->regs.eip = target_ulong_val(&(env)->eip) & 0xffffffff;
    prstatus->regs.eflags = target_ulong_val(&(env)->eflags) & 0xffffffff;

    prstatus->regs.cs = env->segs[R_CS].selector;
    prstatus->regs.ss = env->segs[R_SS].selector;
    prstatus->regs.ds = env->segs[R_DS].selector;
    prstatus->regs.es = env->segs[R_ES].selector;
    prstatus->regs.fs = env->segs[R_FS].selector;
    prstatus->regs.gs = env->segs[R_GS].selector;

    prstatus->pid = id;
}

static int x86_write_elf64_note(WriteCoreDumpFunction f, CPUX86State *env,
                                int id, DumpState *s)
{
    x86_elf_prstatus prstatus;
    Elf64_Nhdr *note;
    char *buf;
    int descsz, note_size, name_size = 5;
    const char *name = "CORE";
    int ret;

    x86_fill_elf_prstatus(&prstatus, env, id);
    descsz = sizeof(x86_elf_prstatus);
    note_size = ELF_NOTE_SIZE(sizeof(Elf64_Nhdr), name_size, descsz);
    note = g_malloc0(note_size);
    note->n_namesz = cpu_to_le32(name_size);
    note->n_descsz = cpu_to_le32(descsz);
    note->n_type = cpu_to_le32(NT_PRSTATUS);
    buf = (char *)note;
    buf += ROUND_UP(sizeof(Elf64_Nhdr), 4);
    memcpy(buf, name, name_size);
    buf += ROUND_UP(name_size, 4);
    memcpy(buf, &prstatus, sizeof(prstatus));

    ret = f(note, note_size, s);
    g_free(note);
    if (ret < 0) {
        return -1;
    }

    return 0;
}

int x86_cpu_write_elf64_note(WriteCoreDumpFunction f, CPUState *cs,
                             int cpuid, DumpState *s)
{
    X86CPU *cpu = X86_CPU(cs);
    int ret;
#ifdef TARGET_X86_64
    X86CPU *first_x86_cpu = X86_CPU(first_cpu);
    bool lma = !!(first_x86_cpu->env.hflags & HF_LMA_MASK);

    if (lma) {
        ret = x86_64_write_elf64_note(f, &cpu->env, cpuid, s);
    } else {
#endif
        ret = x86_write_elf64_note(f, &cpu->env, cpuid, s);
#ifdef TARGET_X86_64
    }
#endif

    return ret;
}

int x86_cpu_write_elf32_note(WriteCoreDumpFunction f, CPUState *cs,
                             int cpuid, DumpState *s)
{
    X86CPU *cpu = X86_CPU(cs);
    x86_elf_prstatus prstatus;
    Elf32_Nhdr *note;
    char *buf;
    int descsz, note_size, name_size = 5;
    const char *name = "CORE";
    int ret;

    x86_fill_elf_prstatus(&prstatus, &cpu->env, cpuid);
    descsz = sizeof(x86_elf_prstatus);
    note_size = ELF_NOTE_SIZE(sizeof(Elf32_Nhdr), name_size, descsz);
    note = g_malloc0(note_size);
    note->n_namesz = cpu_to_le32(name_size);
    note->n_descsz = cpu_to_le32(descsz);
    note->n_type = cpu_to_le32(NT_PRSTATUS);
    buf = (char *)note;
    buf += ROUND_UP(sizeof(Elf32_Nhdr), 4);
    memcpy(buf, name, name_size);
    buf += ROUND_UP(name_size, 4);
    memcpy(buf, &prstatus, sizeof(prstatus));

    ret = f(note, note_size, s);
    g_free(note);
    if (ret < 0) {
        return -1;
    }

    return 0;
}

/*
 * please count up QEMUCPUSTATE_VERSION if you have changed definition of
 * QEMUCPUState, and modify the tools using this information accordingly.
 */
#define QEMUCPUSTATE_VERSION (1)

struct QEMUCPUSegment {
    uint32_t selector;
    uint32_t limit;
    uint32_t flags;
    uint32_t pad;
    uint64_t base;
};

typedef struct QEMUCPUSegment QEMUCPUSegment;

struct QEMUCPUState {
    uint32_t version;
    uint32_t size;
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rsp, rbp;
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
    uint64_t rip, rflags;
    QEMUCPUSegment cs, ds, es, fs, gs, ss;
    QEMUCPUSegment ldt, tr, gdt, idt;
    uint64_t cr[5];
    /*
     * Fields below are optional and are being added at the end without
     * changing the version. External tools may identify their presence
     * by checking 'size' field.
     */
    uint64_t kernel_gs_base;
};

typedef struct QEMUCPUState QEMUCPUState;

static void copy_segment(QEMUCPUSegment *d, SegmentCache *s)
{
    d->pad = 0;
    d->selector = s->selector;
    d->limit = s->limit;
    d->flags = s->flags;
    d->base = target_ulong_val(&s->base);
}

static void qemu_get_cpustate(QEMUCPUState *s, CPUX86State *env)
{
    memset(s, 0, sizeof(QEMUCPUState));

    s->version = QEMUCPUSTATE_VERSION;
    s->size = sizeof(QEMUCPUState);

    s->rax = target_ulong_array_val(&env->regs.rec, R_EAX);
    s->rbx = target_ulong_array_val(&env->regs.rec, R_EBX);
    s->rcx = target_ulong_array_val(&env->regs.rec, R_ECX);
    s->rdx = target_ulong_array_val(&env->regs.rec, R_EDX);
    s->rsi = target_ulong_array_val(&env->regs.rec, R_ESI);
    s->rdi = target_ulong_array_val(&env->regs.rec, R_EDI);
    s->rsp = target_ulong_array_val(&env->regs.rec, R_ESP);
    s->rbp = target_ulong_array_val(&env->regs.rec, R_EBP);
#ifdef TARGET_X86_64
    s->r8  = target_ulong_array_val(&env->regs.rec, 8);
    s->r9  = target_ulong_array_val(&env->regs.rec, 9);
    s->r10 = target_ulong_array_val(&env->regs.rec, 10);
    s->r11 = target_ulong_array_val(&env->regs.rec, 11);
    s->r12 = target_ulong_array_val(&env->regs.rec, 12);
    s->r13 = target_ulong_array_val(&env->regs.rec, 13);
    s->r14 = target_ulong_array_val(&env->regs.rec, 14);
    s->r15 = target_ulong_array_val(&env->regs.rec, 15);
#endif
    s->rip = target_ulong_val(&(env)->eip);
    s->rflags = target_ulong_val(&(env)->eflags);

    copy_segment(&s->cs, &env->segs[R_CS]);
    copy_segment(&s->ds, &env->segs[R_DS]);
    copy_segment(&s->es, &env->segs[R_ES]);
    copy_segment(&s->fs, &env->segs[R_FS]);
    copy_segment(&s->gs, &env->segs[R_GS]);
    copy_segment(&s->ss, &env->segs[R_SS]);
    copy_segment(&s->ldt, &env->ldt);
    copy_segment(&s->tr, &env->tr);
    copy_segment(&s->gdt, &env->gdt);
    copy_segment(&s->idt, &env->idt);

    s->cr[0] = target_ulong_array_val(&env->cr.rec, 0);
    s->cr[1] = target_ulong_array_val(&env->cr.rec, 1);
    s->cr[2] = target_ulong_array_val(&env->cr.rec, 2);
    s->cr[3] = target_ulong_array_val(&env->cr.rec, 3);
    s->cr[4] = target_ulong_array_val(&env->cr.rec, 4);

#ifdef TARGET_X86_64
    s->kernel_gs_base = env->kernelgsbase;
#endif
}

static inline int cpu_write_qemu_note(WriteCoreDumpFunction f,
                                      CPUX86State *env,
                                      DumpState *s,
                                      int type)
{
    QEMUCPUState state;
    Elf64_Nhdr *note64;
    Elf32_Nhdr *note32;
    void *note;
    char *buf;
    int descsz, note_size, name_size = 5, note_head_size;
    const char *name = "QEMU";
    int ret;

    qemu_get_cpustate(&state, env);

    descsz = sizeof(state);
    if (type == 0) {
        note_head_size = sizeof(Elf32_Nhdr);
    } else {
        note_head_size = sizeof(Elf64_Nhdr);
    }
    note_size = (DIV_ROUND_UP(note_head_size, 4) + DIV_ROUND_UP(name_size, 4) +
                DIV_ROUND_UP(descsz, 4)) * 4;
    note = g_malloc0(note_size);
    if (type == 0) {
        note32 = note;
        note32->n_namesz = cpu_to_le32(name_size);
        note32->n_descsz = cpu_to_le32(descsz);
        note32->n_type = 0;
    } else {
        note64 = note;
        note64->n_namesz = cpu_to_le32(name_size);
        note64->n_descsz = cpu_to_le32(descsz);
        note64->n_type = 0;
    }
    buf = note;
    buf += ROUND_UP(note_head_size, 4);
    memcpy(buf, name, name_size);
    buf += ROUND_UP(name_size, 4);
    memcpy(buf, &state, sizeof(state));

    ret = f(note, note_size, s);
    g_free(note);
    if (ret < 0) {
        return -1;
    }

    return 0;
}

int x86_cpu_write_elf64_qemunote(WriteCoreDumpFunction f, CPUState *cs,
                                 DumpState *s)
{
    X86CPU *cpu = X86_CPU(cs);

    return cpu_write_qemu_note(f, &cpu->env, s, 1);
}

int x86_cpu_write_elf32_qemunote(WriteCoreDumpFunction f, CPUState *cs,
                                 DumpState *s)
{
    X86CPU *cpu = X86_CPU(cs);

    return cpu_write_qemu_note(f, &cpu->env, s, 0);
}

static int x86_get_dump_info(ArchDumpInfo *info,
                      const GuestPhysBlockList *guest_phys_blocks)
{
    bool lma = false;
    GuestPhysBlock *block;

#ifdef TARGET_X86_64
    X86CPU *first_x86_cpu = X86_CPU(first_cpu);
    lma = first_cpu && (first_x86_cpu->env.hflags & HF_LMA_MASK);
#endif

    if (lma) {
        info->d_machine = EM_X86_64;
    } else {
        info->d_machine = EM_386;
    }
    info->d_endian = ELFDATA2LSB;

    if (lma) {
        info->d_class = ELFCLASS64;
    } else {
        info->d_class = ELFCLASS32;

        QTAILQ_FOREACH(block, &guest_phys_blocks->head, next) {
            if (block->target_end > UINT_MAX) {
                /* The memory size is greater than 4G */
                info->d_class = ELFCLASS64;
                break;
            }
        }
    }

    return 0;
}

static ssize_t x86_get_note_size(int class, int machine, int nr_cpus)
{
    int name_size = 5; /* "CORE" or "QEMU" */
    size_t elf_note_size = 0;
    size_t qemu_note_size = 0;
    int elf_desc_size = 0;
    int qemu_desc_size = 0;
    int note_head_size;

    if (class == ELFCLASS32) {
        note_head_size = sizeof(Elf32_Nhdr);
    } else {
        note_head_size = sizeof(Elf64_Nhdr);
    }

    if (machine == EM_386) {
        elf_desc_size = sizeof(x86_elf_prstatus);
    }
#ifdef TARGET_X86_64
    else {
        elf_desc_size = sizeof(x86_64_elf_prstatus);
    }
#endif
    qemu_desc_size = sizeof(QEMUCPUState);

    elf_note_size = ELF_NOTE_SIZE(note_head_size, name_size, elf_desc_size);
    qemu_note_size = ELF_NOTE_SIZE(note_head_size, name_size, qemu_desc_size);

    return (elf_note_size + qemu_note_size) * nr_cpus;
}

TARGET_INFO_CPU_OP(QEMU_ARCH_I386, get_dump_info, x86_get_dump_info);
TARGET_INFO_CPU_OP(QEMU_ARCH_I386, get_note_size, x86_get_note_size);
