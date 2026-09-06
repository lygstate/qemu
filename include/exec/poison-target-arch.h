/* TARGET_* poisons moved out of exec/poison.h.
   Use target_x86_64() / target_aarch64() / target_riscv64() /
   target_name() / target_big_endian() / target_long_bits(). */

#ifndef POISON_TARGET_ARCH_H
#define POISON_TARGET_ARCH_H

#pragma GCC poison TARGET_I386
#pragma GCC poison TARGET_X86_64
#pragma GCC poison TARGET_AARCH64
#pragma GCC poison TARGET_ALPHA
#pragma GCC poison TARGET_ARM
#pragma GCC poison TARGET_HEXAGON
#pragma GCC poison TARGET_HPPA
#pragma GCC poison TARGET_LOONGARCH64
#pragma GCC poison TARGET_M68K
#pragma GCC poison TARGET_MICROBLAZE
#pragma GCC poison TARGET_MIPS
#pragma GCC poison TARGET_ABI_MIPSN32
#pragma GCC poison TARGET_ABI_MIPSO32
#pragma GCC poison TARGET_MIPS64
#pragma GCC poison TARGET_ABI_MIPSN64
#pragma GCC poison TARGET_OR1K
#pragma GCC poison TARGET_PPC
#pragma GCC poison TARGET_PPC64
#pragma GCC poison TARGET_ABI32
#pragma GCC poison TARGET_RX
#pragma GCC poison TARGET_S390X
#pragma GCC poison TARGET_SH4
#pragma GCC poison TARGET_SPARC
#pragma GCC poison TARGET_SPARC64
#pragma GCC poison TARGET_TRICORE
#pragma GCC poison TARGET_XTENSA

#pragma GCC poison TARGET_NAME
#pragma GCC poison TARGET_BIG_ENDIAN

#pragma GCC poison TARGET_LONG_BITS
#pragma GCC poison TARGET_FMT_lx
#pragma GCC poison TARGET_FMT_ld
#pragma GCC poison TARGET_FMT_lu

#endif
