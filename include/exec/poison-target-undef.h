/* #undef the same TARGET_* names that poison-target-arch.h poisons.
   COMPILING_PER_TARGET_BASE includes this after CONFIG_TARGET, then
   poison-target-arch.h.
   poison.h does not include this. Keep the two lists in lockstep. */

#ifndef POISON_TARGET_UNDEF_H
#define POISON_TARGET_UNDEF_H

#undef TARGET_I386
#undef TARGET_X86_64
#undef TARGET_AARCH64
#undef TARGET_ALPHA
#undef TARGET_ARM
#undef TARGET_HEXAGON
#undef TARGET_HPPA
#undef TARGET_LOONGARCH64
#undef TARGET_M68K
#undef TARGET_MICROBLAZE
#undef TARGET_MIPS
#undef TARGET_ABI_MIPSN32
#undef TARGET_ABI_MIPSO32
#undef TARGET_MIPS64
#undef TARGET_ABI_MIPSN64
#undef TARGET_OR1K
#undef TARGET_PPC
#undef TARGET_PPC64
#undef TARGET_ABI32
#undef TARGET_RX
#undef TARGET_S390X
#undef TARGET_SH4
#undef TARGET_SPARC
#undef TARGET_SPARC64
#undef TARGET_TRICORE
#undef TARGET_XTENSA

#undef TARGET_NAME
#undef TARGET_BIG_ENDIAN

#undef TARGET_LONG_BITS
#undef TARGET_FMT_lx
#undef TARGET_FMT_ld
#undef TARGET_FMT_lu

#endif
