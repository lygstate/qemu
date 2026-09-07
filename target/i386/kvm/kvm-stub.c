/*
 * KVM i386 stubs for builds without CONFIG_KVM.
 *
 * Family-common helper.c calls kvm_arch_do_init_vcpu() under kvm_enabled().
 * Per-target compile turns kvm_enabled() into 0 without KVM, so the call
 * is dropped. Common compile keeps a runtime check and needs this symbol.
 */

#include "qemu/osdep.h"
#include "cpu.h"

void kvm_arch_do_init_vcpu(X86CPU *cpu);

void kvm_arch_do_init_vcpu(X86CPU *cpu)
{
}
