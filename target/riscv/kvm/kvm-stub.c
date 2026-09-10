/*
 * QEMU KVM RISC-V specific function stubs
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 */

#include "qemu/osdep.h"
#include "cpu-qom.h"
#include "kvm/kvm_riscv.h"
#include "hw/core/boards.h"

/*
 * Safe to call without KVM. Return "not supported".
 */
bool kvm_riscv_has_mp_state(void)
{
    return false;
}

/*
 * These functions should never actually be called without KVM support.
 */
void kvm_riscv_reset_vcpu(RISCVCPU *cpu)
{
    g_assert_not_reached();
}

void kvm_riscv_set_irq(RISCVCPU *cpu, int irq, int level)
{
    g_assert_not_reached();
}

void riscv_kvm_cpu_finalize_features(RISCVCPU *cpu, Error **errp)
{
    g_assert_not_reached();
}

uint64_t kvm_riscv_get_timebase_frequency(RISCVCPU *cpu)
{
    g_assert_not_reached();
}

void kvm_riscv_aia_create(MachineState *machine, uint64_t group_shift,
                          uint64_t aia_irq_num, uint64_t aia_msi_num,
                          uint64_t aplic_base, uint64_t imsic_base,
                          uint64_t guest_num)
{
    g_assert_not_reached();
}

void riscv_kvm_aplic_request(void *opaque, int irq, int level)
{
    g_assert_not_reached();
}
