accel_i386_ss.add(when: 'CONFIG_SEV', if_true: files('host-cpu.c'))

# x86 cpu type
accel_i386_ss.add(when: 'CONFIG_KVM', if_true: files('xsave_helper.c', 'host-cpu.c'))
accel_i386_ss.add(when: 'CONFIG_HVF', if_true: files('xsave_helper.c', 'host-cpu.c'))
accel_i386_ss.add(when: 'CONFIG_WHPX', if_true: files('xsave_helper.c', 'host-cpu.c'))
accel_i386_ss.add(when: 'CONFIG_NVMM', if_true: files('host-cpu.c'))
accel_i386_ss.add(when: 'CONFIG_MSHV', if_true: files('xsave_helper.c', 'host-cpu.c'))

i386_user_ss = ss.source_set()
i386_stubs_ss = ss.source_set()
i386_common_system_ss = ss.source_set()
i386_common_system_ss.add(files(
  'cpu.c',
  'cpu-dump.c',
  'helper.c',
  'arch_dump.c',
  'arch_memory_mapping.c',
  'gdbstub.c',
  'machine.c',
  'monitor.c',
  'cpu-apic.c',
  'cpu-system.c',
))
accel_i386_ss.add(when: 'CONFIG_SEV', if_true: files(
  'confidential-guest.c',
  'sev.c',
))
i386_stubs_ss.add(files('sev-system-stub.c'))
if igvm.found()
  i386_common_system_ss.add(files('igvm.c'))
endif
i386_common_system_ss.add(when: 'CONFIG_WINDUMP', if_true: files('../../dump/win_dump-x86.c'))

subdir('kvm')
subdir('whpx')
subdir('nvmm')
subdir('hvf')
subdir('tcg')
subdir('emulate')
subdir('mshv')

target_user_arch += {'i386': i386_user_ss}
target_stubs_arch += {'i386': i386_stubs_ss}
target_common_system_arch += {'i386': i386_common_system_ss}
