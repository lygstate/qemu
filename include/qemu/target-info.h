/*
 * QEMU target info API (returning native types)
 *
 *  Copyright (c) Linaro
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef QEMU_TARGET_INFO_H
#define QEMU_TARGET_INFO_H

#include <stdbool.h>

typedef struct TargetInfo TargetInfo;

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
 * @ti: TargetInfo to test.
 *
 * Returns whether @ti is ARM or AArch64.
 */
bool target_base_arm(const TargetInfo *ti);

/**
 * target_arm:
 * @ti: TargetInfo to test.
 *
 * Returns whether @ti is ARM (32-bit, not AArch64).
 */
bool target_arm(const TargetInfo *ti);

/**
 * target_aarch64:
 * @ti: TargetInfo to test.
 *
 * Returns whether @ti is AArch64.
 */
bool target_aarch64(const TargetInfo *ti);

/**
 * target_base_ppc:
 * @ti: TargetInfo to test.
 *
 * Returns whether @ti is PowerPC 32-bit or 64-bit.
 */
bool target_base_ppc(const TargetInfo *ti);

/**
 * target_ppc:
 * @ti: TargetInfo to test.
 *
 * Returns whether @ti is PowerPC 32-bit.
 */
bool target_ppc(const TargetInfo *ti);

/**
 * target_ppc64:
 * @ti: TargetInfo to test.
 *
 * Returns whether @ti is PowerPC 64-bit.
 */
bool target_ppc64(const TargetInfo *ti);

/**
 * target_s390x:
 * @ti: TargetInfo to test.
 *
 * Returns whether @ti is S390x.
 */
bool target_s390x(const TargetInfo *ti);

/**
 * target_base_riscv:
 * @ti: TargetInfo to test.
 *
 * Returns whether @ti is RISC-V 32-bit or 64-bit.
 */
bool target_base_riscv(const TargetInfo *ti);

/**
 * target_riscv32:
 * @ti: TargetInfo to test.
 *
 * Returns whether @ti is RISC-V 32-bit.
 */
bool target_riscv32(const TargetInfo *ti);

/**
 * target_riscv64:
 * @ti: TargetInfo to test.
 *
 * Returns whether @ti is RISC-V 64-bit.
 */
bool target_riscv64(const TargetInfo *ti);

#endif
