/*
 * QEMU target info API (returning QAPI types)
 *
 *  Copyright (c) Linaro
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef QEMU_TARGET_INFO_EXTRA_H
#define QEMU_TARGET_INFO_EXTRA_H

#include "qapi/qapi-types-common.h"
#include "qapi/qapi-types-machine.h"

/*
 * Sentinel when combined qemu-system has not bound a TargetInfo.
 * Not a QAPI SysEmuTarget member and not a heterogeneous VM mode.
 * One past the last generated enumerator.
 */
#define SYS_EMU_TARGET_UNSPECIFIED SYS_EMU_TARGET__MAX

/**
 * target_arch:
 *
 * Returns: QAPI SysEmuTarget enum (e.g. SYS_EMU_TARGET_X86_64), or
 * SYS_EMU_TARGET_UNSPECIFIED when no target is selected.
 */
SysEmuTarget target_arch(void);

/**
 * target_unspecified:
 *
 * Returns true if the process has no single selected TargetInfo
 * (SYS_EMU_TARGET_UNSPECIFIED). Combined qemu-system uses this
 * when argv[0] has no arch suffix and -target is omitted.
 */
static inline bool target_unspecified(void)
{
    return target_arch() == SYS_EMU_TARGET_UNSPECIFIED;
}

/**
 * target_endian_mode:
 *
 * Returns: QAPI EndianMode enum (e.g. ENDIAN_MODE_LITTLE).
 */
EndianMode target_endian_mode(void);

#endif
