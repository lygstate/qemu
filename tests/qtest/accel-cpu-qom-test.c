/*
 * AccelCPU QOM parent (shared TYPE_ACCEL_CPU)
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "qemu/osdep.h"

#include "libqtest.h"
#include "qobject/qdict.h"
#include "qobject/qlist.h"

#define TYPE_ACCEL_CPU "accel-cpu"

static bool qemu_binary_is_combined(void)
{
    const char *bin = qtest_qemu_binary(NULL);

    return g_str_has_suffix(bin, "qemu-system") ||
           g_str_has_suffix(bin, "qemu-system.exe");
}

static QList *qom_list_types(QTestState *qts, const char *implements)
{
    QDict *resp;
    QList *ret;
    QDict *args = qdict_new();

    qdict_put_bool(args, "abstract", true);
    qdict_put_str(args, "implements", implements);
    resp = qtest_qmp(qts, "{'execute': 'qom-list-types', 'arguments': %p }",
                     args);
    g_assert(qdict_haskey(resp, "return"));
    ret = qdict_get_qlist(resp, "return");
    qobject_ref(ret);
    qobject_unref(resp);
    return ret;
}

static void test_accel_cpu_parent(void)
{
    QTestState *qts;
    QList *types;
    QListEntry *e;
    bool saw_parent = false;

    qts = qtest_init("-nodefaults -machine none");
    types = qom_list_types(qts, TYPE_ACCEL_CPU);

    QLIST_FOREACH_ENTRY(types, e) {
        QDict *d = qobject_to(QDict, qlist_entry_obj(e));
        const char *name = qdict_get_str(d, "name");

        if (!strcmp(name, TYPE_ACCEL_CPU)) {
            saw_parent = true;
            continue;
        }

        g_assert(qdict_haskey(d, "parent"));
        g_assert_cmpstr(qdict_get_str(d, "parent"), ==, TYPE_ACCEL_CPU);
    }

    g_assert(saw_parent);
    qobject_unref(types);
    qtest_quit(qts);
}

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);

    if (qemu_binary_is_combined()) {
        g_test_add_func("/accel-cpu/qom-parent", test_accel_cpu_parent);
    } else {
        qtest_add_func("accel-cpu/qom-parent", test_accel_cpu_parent);
    }

    return g_test_run();
}
