/* Poison identifiers that should not be used when building
   target independent device code.  */

#ifndef HW_POISON_H
#define HW_POISON_H

#include "config-poison.h"
#include "exec/poison-target-arch.h"

#pragma GCC poison TARGET_HAS_BFLT
#pragma GCC poison TCG_GUEST_DEFAULT_MO

#pragma GCC poison TARGET_PHYS_ADDR_SPACE_BITS

#pragma GCC poison CONFIG_ALPHA_DIS
#pragma GCC poison CONFIG_HPPA_DIS
#pragma GCC poison CONFIG_I386_DIS
#pragma GCC poison CONFIG_HEXAGON_DIS
#pragma GCC poison CONFIG_LOONGARCH_DIS
#pragma GCC poison CONFIG_M68K_DIS
#pragma GCC poison CONFIG_MICROBLAZE_DIS
#pragma GCC poison CONFIG_MIPS_DIS
#pragma GCC poison CONFIG_PPC_DIS
#pragma GCC poison CONFIG_RISCV_DIS
#pragma GCC poison CONFIG_S390_DIS
#pragma GCC poison CONFIG_SH4_DIS
#pragma GCC poison CONFIG_SPARC_DIS
#pragma GCC poison CONFIG_XTENSA_DIS

#pragma GCC poison CONFIG_HVF
#pragma GCC poison CONFIG_LINUX_USER
#pragma GCC poison CONFIG_KVM
#pragma GCC poison CONFIG_WHPX
#pragma GCC poison CONFIG_XEN

#ifndef COMPILING_SYSTEM_VS_USER
#pragma GCC poison CONFIG_USER_ONLY
#pragma GCC poison CONFIG_SOFTMMU
#endif

#pragma GCC poison KVM_HAVE_MCE_INJECTION

#endif
