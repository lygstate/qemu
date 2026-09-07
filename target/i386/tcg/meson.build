i386_ss.add(when: 'CONFIG_TCG', if_false: files('tcg-stub.c'))

if 'CONFIG_TCG' not in config_all_accel
  subdir_done()
endif

i386_common_system_ss.add(files(
  'access.c',
  'bpt_helper.c',
  'cc_helper.c',
  'excp_helper.c',
  'fpu_helper.c',
  'int_helper.c',
  'mem_helper.c',
  'misc_helper.c',
  'mpx_helper.c',
  'seg_helper.c',
  'tcg-cpu.c',
  'translate.c',
))

subdir('system')
subdir('user')
