/*
 * Stubs for CONFIG_HYPERV=n
 *
 * Copyright (c) 2015-2018 Virtuozzo International GmbH.
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 */

#include "qemu/osdep.h"
#include "hyperv.h"

int hyperv_x86_synic_add(X86CPU *cpu)
{
    return -ENOSYS;
}

void hyperv_x86_synic_reset(X86CPU *cpu)
{
}

void hyperv_x86_synic_update(X86CPU *cpu)
{
}

void hyperv_x86_set_vmbus_recommended_features_enabled(void)
{
}

uint64_t hyperv_syndbg_query_options(void)
{
    return 0;
}

int hyperv_enable_synic(X86CPU *cpu)
{
    return 0;
}
