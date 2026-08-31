/*
 * QEMU target info QOM types
 *
 * Copyright (c) Qualcomm
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef QEMU_TARGET_INFO_QOM_H
#define QEMU_TARGET_INFO_QOM_H

#include "qemu/target-info-impl.h"
#include "qemu/base-arch-defs.h"
#include "qapi/error.h"
#include "qom/object.h"

#include <stddef.h>

typedef struct ArchDumpInfo ArchDumpInfo;
struct GuestPhysBlockList;
typedef struct CPUSemihostingOps CPUSemihostingOps;

typedef struct TargetCpuOps {
    CpuDefinitionInfoList *(*query_cpu_definitions)(Error **errp);
    CpuModelExpansionInfo *(*query_cpu_model_expansion)(
        CpuModelExpansionType type, CpuModelInfo *model, Error **errp);
    int (*get_dump_info)(ArchDumpInfo *info,
                         const struct GuestPhysBlockList *guest_phys_blocks);
    ssize_t (*get_note_size)(int class, int machine, int nr_cpus);
    const CPUSemihostingOps *semihosting;
} TargetCpuOps;

/**
 * target_info_register_cpu_op:
 * @arch_bitmask: QEMU_ARCH_* bitmask of SysEmuTarget slots to fill
 * @offset: offsetof(TargetCpuOps, member) for the slot being filled
 * @impl: handler or ops table stored at that offset
 *
 * Combined binaries merge one member at a time so QMP, dump, and
 * semihosting (or split QMP files) can register independently.
 * Stores into every map[SysEmuTarget] bit set in @arch_bitmask
 * (QEMU_ARCH_ARM fills ARM and AARCH64). Lookup is
 * map[target_arch()].
 */
void target_info_register_cpu_op(uint32_t arch_bitmask, size_t offset,
                                 void *impl);
const TargetCpuOps *target_info_cpu_ops(void);

#define TARGET_INFO_CPU_OP(arch_bitmask, member, impl)                        \
static void glue(target_info_cpu_op_, impl)(void)                             \
{                                                                             \
    target_info_register_cpu_op((arch_bitmask),                               \
                                offsetof(TargetCpuOps, member),               \
                                (void *)&(impl));                             \
}                                                                             \
type_init(glue(target_info_cpu_op_, impl))

#define TYPE_TARGET_INFO "target-info"

typedef struct TargetInfoQom {
    Object parent_obj;
} TargetInfoQom;

typedef struct TargetInfoQomClass {
    ObjectClass parent_class;
    const TargetInfo *target_info;
} TargetInfoQomClass;

OBJECT_DECLARE_TYPE(TargetInfoQom, TargetInfoQomClass, TARGET_INFO)

/*
 * Identify target: first from option, then from argv[0].
 * This happens even before handling --help option, because it may contain
 * entries that are target specific.
 */
void target_info_qom_set_target(const char *name, Error **errp);

#endif /* QEMU_TARGET_INFO_QOM_H */
