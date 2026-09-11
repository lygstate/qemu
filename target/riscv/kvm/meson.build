# Add only when the host build has KVM, so all_sources() does not compile
# kvm-cpu.c without linux/kvm.h. when: still limits extract_objects to
# kvm_targets (riscv64-softmmu).
if 'CONFIG_KVM' in config_all_accel
  riscv_common_system_ss.add(when: 'CONFIG_KVM', if_true: files('kvm-cpu.c'))
endif
riscv_stubs_ss.add(files('kvm-stub.c'))
