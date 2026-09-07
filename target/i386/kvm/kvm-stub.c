/*
 * KVM i386 stubs for builds without CONFIG_KVM.
 *
 * Family-common code calls kvm_* under kvm_enabled(). Per-target compile
 * turns kvm_enabled() into 0 without KVM, so those calls are dropped.
 * Common compile keeps a runtime check and needs these symbols.
 */

#include "qemu/osdep.h"
#include "cpu.h"
#include "migration/vmstate.h"
#include "qapi/error.h"
#include "qapi/qapi-types-run-state.h"
#include "system/kvm.h"
#include "kvm_i386.h"
#include "hw/i386/kvm/clock.h"

void kvm_arch_do_init_vcpu(X86CPU *cpu)
{
}

bool is_tdx_vm(void)
{
    return false;
}

bool kvm_has_exception_payload(void)
{
    return false;
}

bool kvm_nested_guest_mode_consistent(CPUX86State *env)
{
    return true;
}

GuestPanicInformation *kvm_arch_get_crash_info(CPUState *cs)
{
    return NULL;
}

uint32_t kvm_arch_get_supported_cpuid(KVMState *env, uint32_t function,
                                      uint32_t index, int reg)
{
    return 0;
}

uint64_t kvm_arch_get_supported_msr_feature(KVMState *s, uint32_t index)
{
    return 0;
}

bool kvm_enable_sgx_provisioning(KVMState *s)
{
    return false;
}

void kvm_arch_reset_vcpu(X86CPU *cpu)
{
}

void kvm_arch_after_reset_vcpu(X86CPU *cpu)
{
}

void kvm_request_xsave_components(X86CPU *cpu, uint64_t mask)
{
}

bool kvm_hyperv_expand_features(X86CPU *cpu, Error **errp)
{
    return true;
}

bool kvm_has_smm(void)
{
    return false;
}

bool kvm_enable_x2apic(void)
{
    return false;
}

int kvm_get_vm_type(MachineState *ms)
{
    return 0;
}

void kvmclock_create(bool create_always)
{
}

static bool nested_state_never(void *opaque)
{
    return false;
}

const VMStateDescription vmstate_nested_state = {
    .name = "cpu/nested_state",
    .needed = nested_state_never,
    .fields = (const VMStateField[]) {
        VMSTATE_END_OF_LIST()
    }
};
