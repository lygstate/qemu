/*
 * QEMU target info API (returning native types)
 *
 *  Copyright (c) Linaro
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef QEMU_TARGET_INFO_H
#define QEMU_TARGET_INFO_H

typedef struct TargetInfo TargetInfo;

/**
 * target_info:
 *
 * Returns: The current TargetInfo. Before target_info_select(), the
 * default uses SYS_EMU_TARGET_NONE.
 */
const TargetInfo *target_info(void);

/**
 * target_info_select:
 * @ti: TargetInfo to select
 *
 * Sets the TargetInfo returned by target_info(). Must be called only
 * once. @ti must not be NULL and must not use SYS_EMU_TARGET_NONE.
 */
void target_info_select(const TargetInfo *ti);

/**
 * target_name:
 *
 * Returns: Canonical target name (i.e. "i386").
 */
const char *target_name(void);

/**
 * target_long_bits:
 *
 * Returns: number of bits in a long type for this target (i.e. 64).
 */
unsigned target_long_bits(void);

/**
 * target_is_long_bits_32:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti uses a 32-bit target long.
 * Usable as TypeInfo.is_available and VMStateField.is_available.
 */
bool target_is_long_bits_32(const TargetInfo *ti);

/**
 * target_is_long_bits_64:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti uses a 64-bit target long.
 * Usable as TypeInfo.is_available and VMStateField.is_available.
 */
bool target_is_long_bits_64(const TargetInfo *ti);

/**
 * target_is_config_kvm:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti was built with CONFIG_KVM.
 * Usable as TypeInfo.is_available and VMStateField.is_available.
 */
bool target_is_config_kvm(const TargetInfo *ti);

/**
 * target_is_config_xen:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti was built with CONFIG_XEN.
 * Usable as TypeInfo.is_available and VMStateField.is_available.
 */
bool target_is_config_xen(const TargetInfo *ti);

/**
 * target_is_config_hvf:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti was built with CONFIG_HVF.
 * Usable as TypeInfo.is_available and VMStateField.is_available.
 */
bool target_is_config_hvf(const TargetInfo *ti);

/**
 * target_is_config_nitro:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti was built with CONFIG_NITRO.
 * Usable as TypeInfo.is_available and VMStateField.is_available.
 */
bool target_is_config_nitro(const TargetInfo *ti);

/**
 * target_is_config_whpx:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti was built with CONFIG_WHPX.
 * Usable as TypeInfo.is_available and VMStateField.is_available.
 */
bool target_is_config_whpx(const TargetInfo *ti);

/**
 * target_is_config_nvmm:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti was built with CONFIG_NVMM.
 * Usable as TypeInfo.is_available and VMStateField.is_available.
 */
bool target_is_config_nvmm(const TargetInfo *ti);

/**
 * target_is_config_mshv:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti was built with CONFIG_MSHV.
 * Usable as TypeInfo.is_available and VMStateField.is_available.
 */
bool target_is_config_mshv(const TargetInfo *ti);

/**
 * target_is_config_tcg:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti was built with CONFIG_TCG.
 * Usable as TypeInfo.is_available and VMStateField.is_available.
 */
bool target_is_config_tcg(const TargetInfo *ti);

/**
 * target_cpu_type:
 *
 * Returns: target CPU base QOM type name (i.e. TYPE_X86_CPU).
 */
const char *target_cpu_type(void);

/**
 * target_big_endian:
 *
 * Returns: %true if the (default) endianness of the target is big endian,
 *          %false otherwise.
 *
 * Common code should normally never need to know about the endianness of
 * the target, so please do *not* use this function unless you  know very
 * well what you are doing!
 */
bool target_big_endian(void);

/**
 * target_base_arm:
 *
 * Returns whether the target architecture is ARM or Aarch64.
 */
bool target_base_arm(void);

/**
 * target_arm:
 *
 * Returns whether the target architecture is ARM (32-bit, not Aarch64).
 */
bool target_arm(void);

/**
 * target_is_aarch64:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti is Aarch64.
 */
bool target_is_aarch64(const TargetInfo *ti);

/**
 * target_aarch64:
 *
 * Returns whether the target architecture is Aarch64.
 */
bool target_aarch64(void);

/**
 * target_is_base_i386:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti is i386 or x86_64.
 */
bool target_is_base_i386(const TargetInfo *ti);

/**
 * target_base_i386:
 *
 * Returns whether the target architecture is i386 or x86_64.
 */
bool target_base_i386(void);

/**
 * target_is_i386:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti is i386 (32-bit, not x86_64).
 */
bool target_is_i386(const TargetInfo *ti);

/**
 * target_i386:
 *
 * Returns whether the target architecture is i386 (32-bit, not x86_64).
 */
bool target_i386(void);

/**
 * target_is_x86_64:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti is x86_64.
 */
bool target_is_x86_64(const TargetInfo *ti);

/**
 * target_x86_64:
 *
 * Returns whether the target architecture is x86_64.
 */
bool target_x86_64(void);

/**
 * target_base_ppc:
 *
 * Returns whether the target architecture is PowerPC 32-bit or 64-bit.
 */
bool target_base_ppc(void);

/**
 * target_ppc:
 *
 * Returns whether the target architecture is PowerPC 32-bit.
 */
bool target_ppc(void);

/**
 * target_ppc64:
 *
 * Returns whether the target architecture is PowerPC 64-bit.
 */
bool target_ppc64(void);

/**
 * target_s390x:
 *
 * Returns whether the target architecture is S390x.
 */
bool target_s390x(void);

/**
 * target_is_base_riscv:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti is RISC-V 32-bit or 64-bit.
 */
bool target_is_base_riscv(const TargetInfo *ti);

/**
 * target_base_riscv:
 *
 * Returns whether the target architecture is RISC-V 32-bit or 64-bit.
 */
bool target_base_riscv(void);

/**
 * target_is_riscv32:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti is RISC-V 32-bit.
 */
bool target_is_riscv32(const TargetInfo *ti);

/**
 * target_riscv32:
 *
 * Returns whether the target architecture is RISC-V 32-bit.
 */
bool target_riscv32(void);

/**
 * target_is_riscv64:
 * @ti: TargetInfo to inspect
 *
 * Returns whether @ti is RISC-V 64-bit.
 */
bool target_is_riscv64(const TargetInfo *ti);

/**
 * target_riscv64:
 *
 * Returns whether the target architecture is RISC-V 64-bit.
 */
bool target_riscv64(void);

#endif
