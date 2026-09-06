/*
 * QEMU target info helpers
 *
 *  Copyright (c) Linaro
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "qemu/osdep.h"
#include "qemu/target-info.h"
#include "qemu/target-info-qapi.h"
#include "qemu/target-info-impl.h"
#include "qapi/error.h"

static const TargetInfo target_info_none = {
    .target_arch = SYS_EMU_TARGET_NONE,
    .target_name = "none",
    .long_bits = 64,
    .endianness = ENDIAN_MODE_LITTLE,
};

static const TargetInfo *target_info_ptr = &target_info_none;

const TargetInfo *target_info(void)
{
    return target_info_ptr;
}

void target_info_select(const TargetInfo *ti)
{
    g_assert(target_info_ptr->target_arch == SYS_EMU_TARGET_NONE);
    g_assert(ti != NULL);
    g_assert(ti->target_arch != SYS_EMU_TARGET_NONE);

    target_info_ptr = ti;
}

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

bool target_is_aarch64(const TargetInfo *ti)
{
    return ti->target_arch == SYS_EMU_TARGET_AARCH64;
}

bool target_aarch64(void)
{
    return target_is_aarch64(target_info());
}

bool target_is_base_i386(const TargetInfo *ti)
{
    switch (ti->target_arch) {
    case SYS_EMU_TARGET_I386:
    case SYS_EMU_TARGET_X86_64:
        return true;
    default:
        return false;
    }
}

bool target_base_i386(void)
{
    return target_is_base_i386(target_info());
}

bool target_is_i386(const TargetInfo *ti)
{
    return ti->target_arch == SYS_EMU_TARGET_I386;
}

bool target_i386(void)
{
    return target_is_i386(target_info());
}

bool target_is_x86_64(const TargetInfo *ti)
{
    return ti->target_arch == SYS_EMU_TARGET_X86_64;
}

bool target_x86_64(void)
{
    return target_is_x86_64(target_info());
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

bool target_is_base_riscv(const TargetInfo *ti)
{
    switch (ti->target_arch) {
    case SYS_EMU_TARGET_RISCV32:
    case SYS_EMU_TARGET_RISCV64:
        return true;
    default:
        return false;
    }
}

bool target_base_riscv(void)
{
    return target_is_base_riscv(target_info());
}

bool target_is_riscv32(const TargetInfo *ti)
{
    return ti->target_arch == SYS_EMU_TARGET_RISCV32;
}

bool target_riscv32(void)
{
    return target_is_riscv32(target_info());
}

bool target_is_riscv64(const TargetInfo *ti)
{
    return ti->target_arch == SYS_EMU_TARGET_RISCV64;
}

bool target_riscv64(void)
{
    return target_is_riscv64(target_info());
}
