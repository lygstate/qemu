/* SPDX-License-Identifier: MIT */
/*
 * target_ulong TCG ops. Width follows target_long_bits() at
 * translate time. Does not include exec/target_long.h.
 */

#ifndef TCG_TCG_OP_TL_H
#define TCG_TCG_OP_TL_H

#ifndef TCG_TCG_OP_COMMON_H
#error Include tcg/tcg-op-common.h instead
#endif

#include "qemu/target-info.h"

#ifdef COMPILING_PER_TARGET
static inline bool tcg_tl_is_64(void)
{
    return TARGET_LONG_BITS == 64;
}
#else
static inline bool tcg_tl_is_64(void)
{
    return target_long_bits() == 64;
}
#endif

static inline TCGType tcg_type_tl(void)
{
    return tcg_tl_is_64() ? TCG_TYPE_I64 : TCG_TYPE_I32;
}

/* Runtime TCGType from tcg_type_tl(); not a compile-time constant. */
#define TCG_TYPE_TL tcg_type_tl()

static inline TCGv_i64 tcg_i64_from_tl(TCGv v)
{
    return (TCGv_i64)v;
}

static inline TCGv_i32 tcg_i32_from_tl(TCGv v)
{
    return (TCGv_i32)v;
}

static inline TCGv tcg_tl_from_i64(TCGv_i64 v)
{
    return (TCGv)v;
}

static inline TCGv tcg_tl_from_i32(TCGv_i32 v)
{
    return (TCGv)v;
}

static inline TCGv tcg_temp_new(void)
{
    if (tcg_tl_is_64()) {
        return tcg_tl_from_i64(tcg_temp_new_i64());
    }
    return tcg_tl_from_i32(tcg_temp_new_i32());
}

static inline TCGv tcg_global_mem_new(TCGv_ptr reg, intptr_t off,
                                      const char *name)
{
    if (tcg_tl_is_64()) {
        return tcg_tl_from_i64(tcg_global_mem_new_i64(reg, off, name));
    }
    return tcg_tl_from_i32(tcg_global_mem_new_i32(reg, off, name));
}

static inline TCGv tcg_constant_tl(tcg_imm_tl val)
{
    if (tcg_tl_is_64()) {
        return tcg_tl_from_i64(tcg_constant_i64(val));
    }
    return tcg_tl_from_i32(tcg_constant_i32(val));
}

static inline void tcg_gen_ld_tl(TCGv r, TCGv_ptr b, tcg_target_long o)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ld_i64(tcg_i64_from_tl(r), b, o);
    } else {
        tcg_gen_ld_i32(tcg_i32_from_tl(r), b, o);
    }
}

static inline void tcg_gen_st_tl(TCGv v, TCGv_ptr b, tcg_target_long o)
{
    if (tcg_tl_is_64()) {
        tcg_gen_st_i64(tcg_i64_from_tl(v), b, o);
    } else {
        tcg_gen_st_i32(tcg_i32_from_tl(v), b, o);
    }
}

static inline void tcg_gen_ld8u_tl(TCGv r, TCGv_ptr b, tcg_target_long o)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ld8u_i64(tcg_i64_from_tl(r), b, o);
    } else {
        tcg_gen_ld8u_i32(tcg_i32_from_tl(r), b, o);
    }
}

static inline void tcg_gen_ld8s_tl(TCGv r, TCGv_ptr b, tcg_target_long o)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ld8s_i64(tcg_i64_from_tl(r), b, o);
    } else {
        tcg_gen_ld8s_i32(tcg_i32_from_tl(r), b, o);
    }
}

static inline void tcg_gen_ld16u_tl(TCGv r, TCGv_ptr b, tcg_target_long o)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ld16u_i64(tcg_i64_from_tl(r), b, o);
    } else {
        tcg_gen_ld16u_i32(tcg_i32_from_tl(r), b, o);
    }
}

static inline void tcg_gen_ld16s_tl(TCGv r, TCGv_ptr b, tcg_target_long o)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ld16s_i64(tcg_i64_from_tl(r), b, o);
    } else {
        tcg_gen_ld16s_i32(tcg_i32_from_tl(r), b, o);
    }
}

static inline void tcg_gen_ld32u_tl(TCGv r, TCGv_ptr b, tcg_target_long o)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ld32u_i64(tcg_i64_from_tl(r), b, o);
    } else {
        tcg_gen_ld_i32(tcg_i32_from_tl(r), b, o);
    }
}

static inline void tcg_gen_ld32s_tl(TCGv r, TCGv_ptr b, tcg_target_long o)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ld32s_i64(tcg_i64_from_tl(r), b, o);
    } else {
        tcg_gen_ld_i32(tcg_i32_from_tl(r), b, o);
    }
}

static inline void tcg_gen_st8_tl(TCGv r, TCGv_ptr b, tcg_target_long o)
{
    if (tcg_tl_is_64()) {
        tcg_gen_st8_i64(tcg_i64_from_tl(r), b, o);
    } else {
        tcg_gen_st8_i32(tcg_i32_from_tl(r), b, o);
    }
}

static inline void tcg_gen_st16_tl(TCGv r, TCGv_ptr b, tcg_target_long o)
{
    if (tcg_tl_is_64()) {
        tcg_gen_st16_i64(tcg_i64_from_tl(r), b, o);
    } else {
        tcg_gen_st16_i32(tcg_i32_from_tl(r), b, o);
    }
}

static inline void tcg_gen_st32_tl(TCGv r, TCGv_ptr b, tcg_target_long o)
{
    if (tcg_tl_is_64()) {
        tcg_gen_st32_i64(tcg_i64_from_tl(r), b, o);
    } else {
        tcg_gen_st_i32(tcg_i32_from_tl(r), b, o);
    }
}

static inline void tcg_gen_movi_tl(TCGv r, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_movi_i64(tcg_i64_from_tl(r), i);
    } else {
        tcg_gen_movi_i32(tcg_i32_from_tl(r), i);
    }
}

static inline void tcg_gen_discard_tl(TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_discard_i64(tcg_i64_from_tl(v));
    } else {
        tcg_gen_discard_i32(tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_neg_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_neg_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_neg_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_abs_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_abs_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_abs_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_not_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_not_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_not_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_ext8u_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ext8u_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_ext8u_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_ext8s_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ext8s_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_ext8s_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_ext16u_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ext16u_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_ext16u_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_ext16s_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ext16s_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_ext16s_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_clrsb_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_clrsb_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_clrsb_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_ctpop_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ctpop_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_ctpop_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_mov_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_mov_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_mov_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_add_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_add_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_add_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_sub_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_sub_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_sub_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_and_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_and_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_and_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_or_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_or_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_or_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_xor_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_xor_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_xor_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_andc_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_andc_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_andc_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_eqv_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_eqv_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_eqv_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_nand_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_nand_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_nand_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_nor_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_nor_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_nor_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_orc_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_orc_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_orc_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_shl_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_shl_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_shl_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_shr_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_shr_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_shr_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_sar_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_sar_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_sar_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_mul_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_mul_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_mul_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_div_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_div_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_div_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_rem_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_rem_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_rem_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_divu_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_divu_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_divu_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_remu_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_remu_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_remu_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_clz_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_clz_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_clz_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_ctz_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ctz_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_ctz_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_rotl_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_rotl_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_rotl_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_rotr_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_rotr_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_rotr_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_smin_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_smin_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_smin_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_umin_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_umin_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_umin_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_smax_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_smax_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_smax_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_umax_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_umax_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_umax_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_ussub_tl(TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ussub_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                         tcg_i64_from_tl(y));
    } else {
        tcg_gen_ussub_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                         tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_addi_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_addi_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_addi_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_subfi_tl(TCGv r, tcg_imm_tl i, TCGv x)
{
    if (tcg_tl_is_64()) {
        tcg_gen_subfi_i64(tcg_i64_from_tl(r), i, tcg_i64_from_tl(x));
    } else {
        tcg_gen_subfi_i32(tcg_i32_from_tl(r), i, tcg_i32_from_tl(x));
    }
}

static inline void tcg_gen_subi_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_subi_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_subi_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_andi_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_andi_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_andi_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_ori_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ori_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_ori_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_xori_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_xori_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_xori_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_muli_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_muli_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_muli_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_shli_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_shli_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_shli_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_shri_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_shri_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_shri_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_sari_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_sari_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_sari_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_clzi_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_clzi_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_clzi_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_ctzi_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ctzi_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_ctzi_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_rotli_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_rotli_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_rotli_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_rotri_tl(TCGv r, TCGv x, tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_rotri_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_rotri_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_brcond_tl(TCGCond cond, TCGv x, TCGv y,
                                     TCGLabel *l)
{
    if (tcg_tl_is_64()) {
        tcg_gen_brcond_i64(cond, tcg_i64_from_tl(x), tcg_i64_from_tl(y), l);
    } else {
        tcg_gen_brcond_i32(cond, tcg_i32_from_tl(x), tcg_i32_from_tl(y), l);
    }
}

static inline void tcg_gen_brcondi_tl(TCGCond cond, TCGv x, tcg_imm_tl i,
                                      TCGLabel *l)
{
    if (tcg_tl_is_64()) {
        tcg_gen_brcondi_i64(cond, tcg_i64_from_tl(x), i, l);
    } else {
        tcg_gen_brcondi_i32(cond, tcg_i32_from_tl(x), i, l);
    }
}

static inline void tcg_gen_setcond_tl(TCGCond cond, TCGv r, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_setcond_i64(cond, tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                            tcg_i64_from_tl(y));
    } else {
        tcg_gen_setcond_i32(cond, tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                            tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_setcondi_tl(TCGCond cond, TCGv r, TCGv x,
                                       tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_setcondi_i64(cond, tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                             i);
    } else {
        tcg_gen_setcondi_i32(cond, tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                             i);
    }
}

static inline void tcg_gen_negsetcond_tl(TCGCond cond, TCGv r, TCGv x,
                                         TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_negsetcond_i64(cond, tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                               tcg_i64_from_tl(y));
    } else {
        tcg_gen_negsetcond_i32(cond, tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                               tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_negsetcondi_tl(TCGCond cond, TCGv r, TCGv x,
                                          tcg_imm_tl i)
{
    if (tcg_tl_is_64()) {
        tcg_gen_negsetcondi_i64(cond, tcg_i64_from_tl(r),
                                tcg_i64_from_tl(x), i);
    } else {
        tcg_gen_negsetcondi_i32(cond, tcg_i32_from_tl(r),
                                tcg_i32_from_tl(x), i);
    }
}

static inline void tcg_gen_movcond_tl(TCGCond cond, TCGv r, TCGv c1,
                                      TCGv c2, TCGv v1, TCGv v2)
{
    if (tcg_tl_is_64()) {
        tcg_gen_movcond_i64(cond, tcg_i64_from_tl(r), tcg_i64_from_tl(c1),
                            tcg_i64_from_tl(c2), tcg_i64_from_tl(v1),
                            tcg_i64_from_tl(v2));
    } else {
        tcg_gen_movcond_i32(cond, tcg_i32_from_tl(r), tcg_i32_from_tl(c1),
                            tcg_i32_from_tl(c2), tcg_i32_from_tl(v1),
                            tcg_i32_from_tl(v2));
    }
}

static inline void tcg_gen_trunc_tl_i32(TCGv_i32 r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_extrl_i64_i32(r, tcg_i64_from_tl(v));
    } else {
        tcg_gen_mov_i32(r, tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_trunc_i64_tl(TCGv r, TCGv_i64 v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_mov_i64(tcg_i64_from_tl(r), v);
    } else {
        tcg_gen_extrl_i64_i32(tcg_i32_from_tl(r), v);
    }
}

static inline void tcg_gen_extu_i32_tl(TCGv r, TCGv_i32 v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_extu_i32_i64(tcg_i64_from_tl(r), v);
    } else {
        tcg_gen_mov_i32(tcg_i32_from_tl(r), v);
    }
}

static inline void tcg_gen_ext_i32_tl(TCGv r, TCGv_i32 v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ext_i32_i64(tcg_i64_from_tl(r), v);
    } else {
        tcg_gen_mov_i32(tcg_i32_from_tl(r), v);
    }
}

static inline void tcg_gen_extu_tl_i64(TCGv_i64 r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_mov_i64(r, tcg_i64_from_tl(v));
    } else {
        tcg_gen_extu_i32_i64(r, tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_ext_tl_i64(TCGv_i64 r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_mov_i64(r, tcg_i64_from_tl(v));
    } else {
        tcg_gen_ext_i32_i64(r, tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_ext32u_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ext32u_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_mov_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_ext32s_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ext32s_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_mov_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_ext_tl(TCGv r, TCGv v, MemOp opc)
{
    if (tcg_tl_is_64()) {
        tcg_gen_ext_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v), opc);
    } else {
        tcg_gen_ext_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v), opc);
    }
}

static inline void tcg_gen_bswap16_tl(TCGv r, TCGv v, int flags)
{
    if (tcg_tl_is_64()) {
        tcg_gen_bswap16_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v), flags);
    } else {
        tcg_gen_bswap16_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v), flags);
    }
}

static inline void tcg_gen_bswap32_tl(TCGv r, TCGv v, int flags)
{
    if (tcg_tl_is_64()) {
        tcg_gen_bswap32_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v), flags);
    } else {
        tcg_gen_bswap32_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_bswap64_tl(TCGv r, TCGv v)
{
    tcg_debug_assert(tcg_tl_is_64());
    tcg_gen_bswap64_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
}

static inline void tcg_gen_bswap_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_bswap64_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_bswap32_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_hswap_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_hswap_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_hswap_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_wswap_tl(TCGv r, TCGv v)
{
    tcg_debug_assert(tcg_tl_is_64());
    tcg_gen_wswap_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
}

static inline void tcg_gen_revbit8_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_revbit8_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_revbit8_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_revbit32_tl(TCGv r, TCGv v, int flags)
{
    if (tcg_tl_is_64()) {
        tcg_gen_revbit32_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v), flags);
    } else {
        tcg_gen_revbit32_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_revbit64_tl(TCGv r, TCGv v)
{
    tcg_debug_assert(tcg_tl_is_64());
    tcg_gen_revbit64_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
}

static inline void tcg_gen_revbit_tl(TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_revbit64_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_revbit32_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_concat_tl_i64(TCGv_i64 r, TCGv lo, TCGv hi)
{
    if (tcg_tl_is_64()) {
        tcg_gen_concat32_i64(r, tcg_i64_from_tl(lo), tcg_i64_from_tl(hi));
    } else {
        tcg_gen_concat_i32_i64(r, tcg_i32_from_tl(lo), tcg_i32_from_tl(hi));
    }
}

static inline void tcg_gen_extr_i64_tl(TCGv lo, TCGv hi, TCGv_i64 v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_extr32_i64(tcg_i64_from_tl(lo), tcg_i64_from_tl(hi), v);
    } else {
        tcg_gen_extr_i64_i32(tcg_i32_from_tl(lo), tcg_i32_from_tl(hi), v);
    }
}

static inline void tcg_gen_deposit_tl(TCGv r, TCGv x, TCGv y, unsigned pos,
                                      unsigned len)
{
    if (tcg_tl_is_64()) {
        tcg_gen_deposit_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(x),
                            tcg_i64_from_tl(y), pos, len);
    } else {
        tcg_gen_deposit_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(x),
                            tcg_i32_from_tl(y), pos, len);
    }
}

static inline void tcg_gen_deposit_z_tl(TCGv r, TCGv v, unsigned pos,
                                        unsigned len)
{
    if (tcg_tl_is_64()) {
        tcg_gen_deposit_z_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v), pos,
                              len);
    } else {
        tcg_gen_deposit_z_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v), pos,
                              len);
    }
}

static inline void tcg_gen_extract_tl(TCGv r, TCGv v, unsigned pos,
                                     unsigned len)
{
    if (tcg_tl_is_64()) {
        tcg_gen_extract_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v), pos,
                            len);
    } else {
        tcg_gen_extract_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v), pos,
                            len);
    }
}

static inline void tcg_gen_sextract_tl(TCGv r, TCGv v, unsigned pos,
                                      unsigned len)
{
    if (tcg_tl_is_64()) {
        tcg_gen_sextract_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(v), pos,
                             len);
    } else {
        tcg_gen_sextract_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(v), pos,
                             len);
    }
}

static inline void tcg_gen_extract2_tl(TCGv r, TCGv lo, TCGv hi,
                                      unsigned ofs)
{
    if (tcg_tl_is_64()) {
        tcg_gen_extract2_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(lo),
                             tcg_i64_from_tl(hi), ofs);
    } else {
        tcg_gen_extract2_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(lo),
                             tcg_i32_from_tl(hi), ofs);
    }
}

static inline void tcg_gen_add2_tl(TCGv rl, TCGv rh, TCGv al, TCGv ah,
                                  TCGv bl, TCGv bh)
{
    if (tcg_tl_is_64()) {
        tcg_gen_add2_i64(tcg_i64_from_tl(rl), tcg_i64_from_tl(rh),
                         tcg_i64_from_tl(al), tcg_i64_from_tl(ah),
                         tcg_i64_from_tl(bl), tcg_i64_from_tl(bh));
    } else {
        tcg_gen_add2_i32(tcg_i32_from_tl(rl), tcg_i32_from_tl(rh),
                         tcg_i32_from_tl(al), tcg_i32_from_tl(ah),
                         tcg_i32_from_tl(bl), tcg_i32_from_tl(bh));
    }
}

static inline void tcg_gen_sub2_tl(TCGv rl, TCGv rh, TCGv al, TCGv ah,
                                  TCGv bl, TCGv bh)
{
    if (tcg_tl_is_64()) {
        tcg_gen_sub2_i64(tcg_i64_from_tl(rl), tcg_i64_from_tl(rh),
                         tcg_i64_from_tl(al), tcg_i64_from_tl(ah),
                         tcg_i64_from_tl(bl), tcg_i64_from_tl(bh));
    } else {
        tcg_gen_sub2_i32(tcg_i32_from_tl(rl), tcg_i32_from_tl(rh),
                         tcg_i32_from_tl(al), tcg_i32_from_tl(ah),
                         tcg_i32_from_tl(bl), tcg_i32_from_tl(bh));
    }
}

static inline void tcg_gen_mulu2_tl(TCGv rl, TCGv rh, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_mulu2_i64(tcg_i64_from_tl(rl), tcg_i64_from_tl(rh),
                         tcg_i64_from_tl(x), tcg_i64_from_tl(y));
    } else {
        tcg_gen_mulu2_i32(tcg_i32_from_tl(rl), tcg_i32_from_tl(rh),
                         tcg_i32_from_tl(x), tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_muls2_tl(TCGv rl, TCGv rh, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_muls2_i64(tcg_i64_from_tl(rl), tcg_i64_from_tl(rh),
                         tcg_i64_from_tl(x), tcg_i64_from_tl(y));
    } else {
        tcg_gen_muls2_i32(tcg_i32_from_tl(rl), tcg_i32_from_tl(rh),
                         tcg_i32_from_tl(x), tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_mulsu2_tl(TCGv rl, TCGv rh, TCGv x, TCGv y)
{
    if (tcg_tl_is_64()) {
        tcg_gen_mulsu2_i64(tcg_i64_from_tl(rl), tcg_i64_from_tl(rh),
                         tcg_i64_from_tl(x), tcg_i64_from_tl(y));
    } else {
        tcg_gen_mulsu2_i32(tcg_i32_from_tl(rl), tcg_i32_from_tl(rh),
                         tcg_i32_from_tl(x), tcg_i32_from_tl(y));
    }
}

static inline void tcg_gen_addcio_tl(TCGv r, TCGv co, TCGv x, TCGv y,
                                     TCGv ci)
{
    if (tcg_tl_is_64()) {
        tcg_gen_addcio_i64(tcg_i64_from_tl(r), tcg_i64_from_tl(co),
                           tcg_i64_from_tl(x), tcg_i64_from_tl(y),
                           tcg_i64_from_tl(ci));
    } else {
        tcg_gen_addcio_i32(tcg_i32_from_tl(r), tcg_i32_from_tl(co),
                           tcg_i32_from_tl(x), tcg_i32_from_tl(y),
                           tcg_i32_from_tl(ci));
    }
}

static inline void tcg_gen_dup_tl_vec(unsigned vece, TCGv_vec r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_dup_i64_vec(vece, r, tcg_i64_from_tl(v));
    } else {
        tcg_gen_dup_i32_vec(vece, r, tcg_i32_from_tl(v));
    }
}

static inline void tcg_gen_dup_tl(unsigned vece, TCGv r, TCGv v)
{
    if (tcg_tl_is_64()) {
        tcg_gen_dup_i64(vece, tcg_i64_from_tl(r), tcg_i64_from_tl(v));
    } else {
        tcg_gen_dup_i32(vece, tcg_i32_from_tl(r), tcg_i32_from_tl(v));
    }
}

static inline tcg_imm_tl dup_const_tl(unsigned vece, uint64_t c)
{
    if (tcg_tl_is_64()) {
        return dup_const(vece, c);
    }
    if (__builtin_constant_p(vece)) {
        switch (vece) {
        case MO_8:
            return 0x01010101ul * (uint8_t)c;
        case MO_16:
            return 0x00010001ul * (uint16_t)c;
        case MO_32:
            return 0x00000001ul * (uint32_t)c;
        default:
            qemu_build_not_reached();
        }
    }
    return (uint32_t)dup_const(vece, c);
}

#endif /* TCG_TCG_OP_TL_H */
