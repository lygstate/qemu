whpx_ss = ss.source_set()
whpx_ss.add(files(
  'whpx-accel-ops.c',
  'whpx-common.c'
))

accel_common_ss.add_all(when: 'CONFIG_WHPX', if_true: whpx_ss)
