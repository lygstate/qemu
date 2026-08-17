/*
 * QEMU binary/target API (QOM types)
 *
 *  Copyright (c) Linaro
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "qemu/osdep.h"
#include "qemu/help_option.h"
#include "qapi/error.h"
#include "qom/object.h"
#include "qemu/target-info.h"
#include "qemu/target-info-impl.h"
#include "qemu/target-info-init.h"
#include "qemu/target-info-qapi.h"
#include "qemu/target-info-qom.h"
#include "hw/arm/machines-qom.h"
#include "hw/riscv/machines-qom.h"

static void target_info_qom_class_init(ObjectClass *oc, const void * data)
{
    TargetInfoQomClass *klass = TARGET_INFO_CLASS(oc);
    klass->target_info = data;
}

static const TypeInfo target_info_parent_type = {
    .name = TYPE_TARGET_INFO,
    .parent = TYPE_OBJECT,
    .instance_size = sizeof(TargetInfoQom),
    .class_size = sizeof(TargetInfoQomClass),
    /* use class_base_init so children classes can set class_data accordingly */
    .class_base_init = target_info_qom_class_init,
    /* children classes will be concrete, which allows to easily query them
     * without listing this parent class also */
    .abstract = true,
};

DEFINE_TARGET_INFO_TYPE(target_info_parent_type)

static const TargetInfo *target_info_ptr;

/*
 * Fallback when -target is omitted and argv[0] is qemu-system (no
 * arch suffix). qemu-system-* always gets a name from argv[0]
 * (qemu-system-aarch64 -> aarch64), so it never selects this.
 */
static const TargetInfo target_info_unspecified = {
    .target_name = "unspecified",
    .target_arch = SYS_EMU_TARGET_UNSPECIFIED,
    .long_bits = 64,
    .cpu_type = "",
    .endianness = ENDIAN_MODE_LITTLE,
    .page_bits_init = 12,
    .page_bits_vary = true,
};

const TargetInfo *target_info(void)
{
    return target_info_ptr;
}

static void set_target_info(const TargetInfo *chosen)
{
    target_info_ptr = chosen;
}

static const char *target_endian_suffix(const TargetInfo *ti)
{
    return ti->endianness == ENDIAN_MODE_BIG ? "be" : "le";
}

static void list_targets_available(void)
{
    printf("List of targets available:\n");
    g_autoptr(GSList) targets = object_class_get_list_sorted(TYPE_TARGET_INFO, false);
    for (GSList *elem = targets; elem; elem = elem->next) {
        const TargetInfo *ti = TARGET_INFO_CLASS(elem->data)->target_info;
        const char *end = target_endian_suffix(ti);

        if (ti->is_default) {
            printf("- %s (default %s)\n", ti->target_name, end);
        } else {
            printf("- %s-%s\n", ti->target_name, end);
        }
    }
}

/* Match "aarch64", "aarch64-le", or "aarch64-be". Bare name selects is_default. */
static bool target_info_matches_name(const TargetInfo *ti, const char *name)
{
    size_t len = strlen(ti->target_name);

    if (!strcmp(name, ti->target_name)) {
        return ti->is_default;
    }
    if (strncmp(name, ti->target_name, len) || name[len] != '-') {
        return false;
    }
    return !strcmp(name + len + 1, target_endian_suffix(ti));
}

/* qemu-system-aarch64[.exe] -> aarch64; qemu-system[.exe] -> NULL. */
static const char *target_from_argv0(char *base)
{
    if (g_str_has_prefix(base, "qemu-system-")) {
        return base + strlen("qemu-system-");
    }
    return NULL;
}

void target_info_qom_set_target(const char *name, Error **errp)
{
    g_autoptr(GSList) targets = object_class_get_list(TYPE_TARGET_INFO, false);

    size_t num_found = g_slist_length(targets);
    g_autofree char *prg_base = NULL;

    if (num_found == 0) {
        error_setg(errp, "no target-info is available");
        return;
    }

    if (!name) {
        const char *prg = g_get_prgname();
        if (prg && prg[0]) {
            char *dot;

            prg_base = g_path_get_basename(prg);
            dot = strrchr(prg_base, '.');
            if (dot && g_ascii_strcasecmp(dot, ".exe") == 0) {
                *dot = '\0';
            }
            name = target_from_argv0(prg_base);
        }
    }

    if (name) {
        if (is_help_option(name)) {
            list_targets_available();
            exit(0);
        }
        for (GSList *elem = targets; elem; elem = elem->next) {
            const TargetInfo *ti = TARGET_INFO_CLASS(elem->data)->target_info;
            if (target_info_matches_name(ti, name)) {
                set_target_info(ti);
                return;
            }
        }
        error_setg(errp, "target '%s' is not available, "
                   "use -target ? to list available targets", name);
        return;
    }

    /* Not reached for qemu-system-*: name came from the argv[0] suffix. */
    set_target_info(&target_info_unspecified);
}
