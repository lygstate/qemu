/*
 * RISC-V Bitmanip Extension Helpers for QEMU.
 *
 * Copyright (c) 2020 Kito Cheng, kito.cheng@sifive.com
 * Copyright (c) 2020 Frank Chang, frank.chang@sifive.com
 * Copyright (c) 2021 Philipp Tomsich, philipp.tomsich@vrull.eu
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2 or later, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu/osdep.h"
#include "qemu/host-utils.h"
#include "cpu.h"
#include "qemu/target-info.h"
#include "exec/helper-proto.h"
#include "tcg/tcg.h"
#include "qemu/crc32.h"
#include "qemu/crc32c.h"

uint64_t HELPER(clmul)(uint64_t rs1, uint64_t rs2)
{
    uint64_t result = 0;

    for (int i = 0; i < target_long_bits(); i++) {
        if ((rs2 >> i) & 1) {
            result ^= (rs1 << i);
        }
    }

    return result;
}

uint64_t HELPER(clmulr)(uint64_t rs1, uint64_t rs2)
{
    uint64_t result = 0;

    for (int i = 0; i < target_long_bits(); i++) {
        if ((rs2 >> i) & 1) {
            result ^= (rs1 >> (target_long_bits() - i - 1));
        }
    }

    return result;
}

static const uint64_t shuf_masks[] = {
    dup_const(MO_8, 0x44),
    dup_const(MO_8, 0x30),
    dup_const(MO_16, 0x0f00),
    dup_const(MO_32, 0xff0000)
};

static inline uint64_t do_shuf_stage(uint64_t src, uint64_t maskL,
                                         uint64_t maskR, int shift)
{
    uint64_t x = src & ~(maskL | maskR);

    x |= ((src << shift) & maskL) | ((src >> shift) & maskR);
    return x;
}

uint64_t HELPER(unzip)(uint64_t rs1)
{
    uint64_t x = rs1;

    x = do_shuf_stage(x, shuf_masks[0], shuf_masks[0] >> 1, 1);
    x = do_shuf_stage(x, shuf_masks[1], shuf_masks[1] >> 2, 2);
    x = do_shuf_stage(x, shuf_masks[2], shuf_masks[2] >> 4, 4);
    x = do_shuf_stage(x, shuf_masks[3], shuf_masks[3] >> 8, 8);
    return x;
}

uint64_t HELPER(zip)(uint64_t rs1)
{
    uint64_t x = rs1;

    x = do_shuf_stage(x, shuf_masks[3], shuf_masks[3] >> 8, 8);
    x = do_shuf_stage(x, shuf_masks[2], shuf_masks[2] >> 4, 4);
    x = do_shuf_stage(x, shuf_masks[1], shuf_masks[1] >> 2, 2);
    x = do_shuf_stage(x, shuf_masks[0], shuf_masks[0] >> 1, 1);
    return x;
}

static inline uint64_t do_xperm(uint64_t rs1, uint64_t rs2,
                                    uint32_t sz_log2)
{
    uint64_t r = 0;
    uint64_t sz = 1LL << sz_log2;
    uint64_t mask = (1LL << sz) - 1;
    uint64_t pos;

    for (int i = 0; i < target_long_bits(); i += sz) {
        pos = ((rs2 >> i) & mask) << sz_log2;
        if (pos < target_long_bits()) {
            r |= ((rs1 >> pos) & mask) << i;
        }
    }
    return r;
}

uint64_t HELPER(xperm4)(uint64_t rs1, uint64_t rs2)
{
    return do_xperm(rs1, rs2, 2);
}

uint64_t HELPER(xperm8)(uint64_t rs1, uint64_t rs2)
{
    return do_xperm(rs1, rs2, 3);
}

uint64_t HELPER(riscv_crc32)(uint64_t rs1, uint64_t sz)
{
    for (uint64_t i = 0; i < sz; i++) {
        rs1 = crc32_table[rs1 & 0xFF] ^ (rs1 >> 8);
    }

    return rs1;
}

uint64_t HELPER(riscv_crc32c)(uint64_t rs1, uint64_t sz)
{
    for (uint64_t i = 0; i < sz; i++) {
        rs1 = crc32c_table[rs1 & 0xFF] ^ (rs1 >> 8);
    }

    return rs1;
}
