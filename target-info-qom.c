/*
 * QEMU binary/target API (QOM types)
 *
 *  Copyright (c) Linaro
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qom/object.h"
#include "qemu/target-info-impl.h"
#include "qemu/target-info-init.h"
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

void target_info_qom_set_target(void)
{
    g_autoptr(GSList) targets = object_class_get_list(TYPE_TARGET_INFO, false);

    size_t num_found = g_slist_length(targets);
    if (num_found != 1) {
        error_setg(&error_fatal, num_found == 0 ?
                                 "no target-info is available" :
                                 "more than one target-info is available");
    }

    target_info_select(TARGET_INFO_CLASS(targets->data)->target_info);
}
