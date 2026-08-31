/*
 * QOM type definitions for riscv32 / riscv64 machines
 *
 *  Copyright (c) rev.ng Labs Srl.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef HW_RISCV_MACHINES_QOM_H
#define HW_RISCV_MACHINES_QOM_H

#include "hw/core/boards.h"
#include "qemu/target-info.h"

/*
 * Helper macros for defining machines available in qemu-system-riscv32,
 * qemu-system-riscv64, or both.
 */

#define DEFINE_MACHINE_RISCV32(namestr, machine_initfn) \
        DEFINE_MACHINE_EXTENDED(namestr, MACHINE, MachineState, \
                                machine_initfn, false, target_riscv32, \
                                NULL)

#define DEFINE_MACHINE_RISCV64(namestr, machine_initfn) \
        DEFINE_MACHINE_EXTENDED(namestr, MACHINE, MachineState, \
                                machine_initfn, false, target_riscv64, \
                                NULL)

#define DEFINE_MACHINE_RISCV32_64(namestr, machine_initfn) \
        DEFINE_MACHINE_EXTENDED(namestr, MACHINE, MachineState, \
                                machine_initfn, false, target_base_riscv, \
                                NULL)

#endif
