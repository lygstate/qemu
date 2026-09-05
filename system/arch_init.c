/*
 * QEMU System Emulator
 *
 * Copyright (c) 2003-2008 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "qemu/osdep.h"
#include "qemu/base-arch-defs.h"
#include "qemu/bitops.h"
#include "qemu/target-info-qapi.h"

bool qemu_arch_available(uint32_t arch_bitmask)
{
    if (target_arch() == SYS_EMU_TARGET_NONE) {
        return true;
    }
    return extract32(arch_bitmask, target_arch(), 1);
}

SysEmuTarget qemu_host_arch(void)
{
#if defined(HOST_X86_64)
    return SYS_EMU_TARGET_X86_64;
#elif defined(HOST_AARCH64)
    return SYS_EMU_TARGET_AARCH64;
#elif defined(HOST_S390X)
    return SYS_EMU_TARGET_S390X;
#elif defined(HOST_PPC64)
    return SYS_EMU_TARGET_PPC64;
#elif defined(HOST_RISCV64)
    return SYS_EMU_TARGET_RISCV64;
#elif defined(HOST_LOONGARCH64)
    return SYS_EMU_TARGET_LOONGARCH64;
#else
    return SYS_EMU_TARGET_NONE;
#endif
}

bool qemu_host_kvm_supports(SysEmuTarget guest)
{
    switch (qemu_host_arch()) {
    case SYS_EMU_TARGET_X86_64:
        return guest == SYS_EMU_TARGET_I386 ||
               guest == SYS_EMU_TARGET_X86_64;
    case SYS_EMU_TARGET_AARCH64:
        return guest == SYS_EMU_TARGET_AARCH64;
    case SYS_EMU_TARGET_S390X:
        return guest == SYS_EMU_TARGET_S390X;
    case SYS_EMU_TARGET_PPC64:
        return guest == SYS_EMU_TARGET_PPC ||
               guest == SYS_EMU_TARGET_PPC64;
    case SYS_EMU_TARGET_RISCV64:
        return guest == SYS_EMU_TARGET_RISCV64;
    case SYS_EMU_TARGET_LOONGARCH64:
        return guest == SYS_EMU_TARGET_LOONGARCH64;
    default:
        return false;
    }
}
