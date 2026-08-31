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

char *target_specific_target_names(ObjectClass *oc)
{
    TypeIsAvailable *is_available;
    g_autoptr(GSList) targets = NULL;
    g_autoptr(GPtrArray) names = NULL;

    is_available = object_class_get_is_available(oc);
    if (!is_available) {
        return NULL;
    }

    targets = object_class_get_list_sorted(TYPE_TARGET_INFO, false);
    names = g_ptr_array_new();

    for (GSList *elem = targets; elem; elem = elem->next) {
        const TargetInfo *ti = TARGET_INFO_CLASS(elem->data)->target_info;
        bool seen = false;
        guint i;

        for (i = 0; i < names->len; i++) {
            if (!strcmp(names->pdata[i], ti->target_name)) {
                seen = true;
                break;
            }
        }
        if (seen) {
            continue;
        }

        if (is_available(ti)) {
            g_ptr_array_add(names, (gpointer)ti->target_name);
        }
    }

    if (!names->len) {
        return NULL;
    }

    g_ptr_array_add(names, NULL);
    return g_strjoinv(",", (char **)names->pdata);
}

static void list_targets_available(void)
{
    printf("List of targets available:\n");
    g_autoptr(GSList) targets = object_class_get_list_sorted(TYPE_TARGET_INFO, false);
    for (GSList *elem = targets; elem; elem = elem->next) {
        const TargetInfo *ti = TARGET_INFO_CLASS(elem->data)->target_info;
        printf("- %s\n", ti->target_name);
    }
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
            if (!strcmp(name, ti->target_name)) {
                target_info_select(ti);
                return;
            }
        }
        error_setg(errp, "target '%s' is not available, "
                   "use -target ? to list available targets", name);
        return;
    }

    if (num_found == 1) {
        target_info_select(TARGET_INFO_CLASS(targets->data)->target_info);
    }
}
