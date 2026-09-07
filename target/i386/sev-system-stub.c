/*
 * QEMU SEV system stub
 *
 * Copyright Advanced Micro Devices 2018
 *
 * Authors:
 *      Brijesh Singh <brijesh.singh@amd.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#include "qemu/osdep.h"
#include "monitor/monitor.h"
#include "monitor/hmp.h"
#include "qapi/error.h"
#include "sev.h"

bool sev_enabled(void)
{
    return false;
}

bool sev_es_enabled(void)
{
    return false;
}

bool sev_snp_enabled(void)
{
    return false;
}

uint32_t sev_get_cbit_position(void)
{
    return 0;
}

uint32_t sev_get_reduced_phys_bits(void)
{
    return 0;
}

bool sev_add_kernel_loader_hashes(SevKernelLoaderContext *ctx, Error **errp)
{
    return false;
}

int sev_encrypt_flash(hwaddr gpa, uint8_t *ptr, uint64_t len, Error **errp)
{
    g_assert_not_reached();
}

void sev_es_set_reset_vector(CPUState *cpu)
{
}

int sev_es_save_reset_vector(void *flash_ptr, uint64_t flash_size)
{
    g_assert_not_reached();
}

void pc_system_parse_sev_metadata(uint8_t *flash_ptr, size_t flash_size)
{
}
