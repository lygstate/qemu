/*
 * QEMU TargetInfo structure definition
 *
 *  Copyright (c) Linaro
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef QEMU_TARGET_INFO_IMPL_H
#define QEMU_TARGET_INFO_IMPL_H

#include "qapi/qapi-types-common.h"
#include "qapi/qapi-types-machine.h"
#include "qemu/target-info.h"

struct TargetInfo {
    /* runtime equivalent of TARGET_NAME definition */
    const char *target_name;
    /* related to TARGET_ARCH definition */
    SysEmuTarget target_arch;
    /* runtime equivalent of TARGET_LONG_BITS definition */
    unsigned long_bits;
    /* runtime equivalent of CPU_RESOLVING_TYPE definition */
    const char *cpu_type;
    /* related to TARGET_BIG_ENDIAN definition */
    EndianMode endianness;
    /*
     * runtime equivalent of
     *   TARGET_PAGE_BITS_VARY ? TARGET_PAGE_BITS_LEGACY : TARGET_PAGE_BITS
     */
    unsigned page_bits_init;
    /* runtime equivalent of TARGET_PAGE_BITS_VARY definition */
    bool page_bits_vary;
    /* runtime equivalent of CONFIG_KVM (compile-time, not kvm_enabled()) */
    bool config_kvm;
    /* runtime equivalent of CONFIG_XEN (compile-time, not xen_enabled()) */
    bool config_xen;
    /* runtime equivalent of CONFIG_HVF (compile-time, not hvf_enabled()) */
    bool config_hvf;
    /* runtime equivalent of CONFIG_NITRO (compile-time, not nitro_enabled()) */
    bool config_nitro;
    /* runtime equivalent of CONFIG_WHPX (compile-time, not whpx_enabled()) */
    bool config_whpx;
    /* runtime equivalent of CONFIG_NVMM (compile-time, not nvmm_enabled()) */
    bool config_nvmm;
    /* runtime equivalent of CONFIG_MSHV (compile-time, not mshv_enabled()) */
    bool config_mshv;
    /* runtime equivalent of CONFIG_TCG (compile-time, not tcg_enabled()) */
    bool config_tcg;
};

#endif
