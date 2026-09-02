if 'CONFIG_TCG' not in config_all_accel
  subdir_done()
endif

riscv_common_system_ss.add(files(
  'bitmanip_helper.c',
  'crypto_helper.c',
  'fpu_helper.c',
  'm128_helper.c',
  'op_helper.c',
  'translate.c',
  'vcrypto_helper.c',
  'vector_helper.c',
  'vector_internals.c',
  'zce_helper.c',
  'cpu_helper.c',
  'csr.c',
  'tcg-cpu.c',
  'mips_csr.c',
  'pmp.c',
  'pmu.c',
  'th_csr.c',
  'debug.c',
))


