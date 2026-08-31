/*
 * QEMU target info helpers
 *
 *  Copyright (c) Linaro
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "qemu/osdep.h"
#include "qemu/error-report.h"
#include "qemu/target-info.h"
#include "qemu/target-info-qapi.h"
#include "qemu/target-info-impl.h"
#include "qemu/target-info-qom.h"
#include "qapi/error.h"

const char *target_name(void)
{
    return target_info()->target_name;
}

unsigned target_long_bits(void)
{
    return target_info()->long_bits;
}

SysEmuTarget target_arch(void)
{
    return target_info()->target_arch;
}

const char *target_cpu_type(void)
{
    return target_info()->cpu_type;
}

EndianMode target_endian_mode(void)
{
    return target_info()->endianness;
}

bool target_big_endian(void)
{
    return target_endian_mode() == ENDIAN_MODE_BIG;
}

bool target_config_cxl(void)
{
    return target_info()->config_cxl;
}

bool target_config_dpcd(void)
{
    return target_info()->config_dpcd;
}

bool target_config_multiprocess(void)
{
    return target_info()->config_multiprocess;
}

bool target_config_nitro(void)
{
    return target_info()->config_nitro;
}

bool target_base_arm(void)
{
    switch (target_arch()) {
    case SYS_EMU_TARGET_ARM:
    case SYS_EMU_TARGET_AARCH64:
        return true;
    default:
        return false;
    }
}

bool target_arm(void)
{
    return target_arch() == SYS_EMU_TARGET_ARM;
}

bool target_aarch64(void)
{
    return target_arch() == SYS_EMU_TARGET_AARCH64;
}

bool target_microblaze(void)
{
    return target_arch() == SYS_EMU_TARGET_MICROBLAZE;
}


bool target_base_ppc(void)
{
    switch (target_arch()) {
    case SYS_EMU_TARGET_PPC:
    case SYS_EMU_TARGET_PPC64:
        return true;
    default:
        return false;
    }
}

bool target_ppc(void)
{
    return target_arch() == SYS_EMU_TARGET_PPC;
}

bool target_ppc64(void)
{
    return target_arch() == SYS_EMU_TARGET_PPC64;
}

bool target_s390x(void)
{
    return target_arch() == SYS_EMU_TARGET_S390X;
}

bool target_base_riscv(void)
{
    switch (target_arch()) {
    case SYS_EMU_TARGET_RISCV32:
    case SYS_EMU_TARGET_RISCV64:
        return true;
    default:
        return false;
    }
}

bool target_riscv32(void)
{
    return target_arch() == SYS_EMU_TARGET_RISCV32;
}

bool target_riscv64(void)
{
    return target_arch() == SYS_EMU_TARGET_RISCV64;
}

/*
 * SYS_EMU_TARGET_UNSPECIFIED is SYS_EMU_TARGET__MAX, so +1 makes
 * that sentinel a valid index. Registration still fills 0 .. MAX-1.
 */
static TargetCpuOps target_cpu_ops[SYS_EMU_TARGET__MAX + 1];

static void target_cpu_ops_store(SysEmuTarget arch, size_t offset, void *impl)
{
    void **slot;

    g_assert((unsigned)arch < SYS_EMU_TARGET__MAX);
    slot = (void **)((char *)&target_cpu_ops[arch] + offset);
    if (*slot && *slot != impl) {
        error_report("TargetCpuOps already registered for %s (offset %zu)",
                     SysEmuTarget_str(arch), offset);
        exit(1);
    }
    *slot = impl;
}

void target_info_register_cpu_op(uint32_t arch_bitmask, size_t offset,
                                 void *impl)
{
    int i;

    g_assert(offset + sizeof(void *) <= sizeof(TargetCpuOps));
    g_assert((offset % sizeof(void *)) == 0);
    g_assert(arch_bitmask);

    for (i = 0; i < SYS_EMU_TARGET__MAX; i++) {
        if (arch_bitmask & (1UL << i)) {
            target_cpu_ops_store(i, offset, impl);
        }
    }
}

const TargetCpuOps *target_info_cpu_ops(void)
{
    SysEmuTarget arch = target_arch();

    g_assert((unsigned)arch <= SYS_EMU_TARGET__MAX);
    return &target_cpu_ops[arch];
}
