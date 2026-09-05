/*
 *  AArch64 translation, common definitions.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TARGET_ARM_TRANSLATE_A64_H
#define TARGET_ARM_TRANSLATE_A64_H

#define TCG_ADDRESS_BITS 64
#include "tcg/tcg-op-mem.h"

typedef TCGv_i64 TCGv;
#define tcg_temp_new() tcg_temp_new_i64()
#define tcg_global_mem_new tcg_global_mem_new_i64
#define tcgv_tl_temp tcgv_i64_temp
#define tcg_gen_qemu_ld_tl tcg_gen_qemu_ld_i64
#define tcg_gen_qemu_st_tl tcg_gen_qemu_st_i64
#define tcg_gen_movi_tl tcg_gen_movi_i64
#define tcg_gen_mov_tl tcg_gen_mov_i64
#define tcg_gen_ld8u_tl tcg_gen_ld8u_i64
#define tcg_gen_ld8s_tl tcg_gen_ld8s_i64
#define tcg_gen_ld16u_tl tcg_gen_ld16u_i64
#define tcg_gen_ld16s_tl tcg_gen_ld16s_i64
#define tcg_gen_ld32u_tl tcg_gen_ld32u_i64
#define tcg_gen_ld32s_tl tcg_gen_ld32s_i64
#define tcg_gen_ld_tl tcg_gen_ld_i64
#define tcg_gen_st8_tl tcg_gen_st8_i64
#define tcg_gen_st16_tl tcg_gen_st16_i64
#define tcg_gen_st32_tl tcg_gen_st32_i64
#define tcg_gen_st_tl tcg_gen_st_i64
#define tcg_gen_add_tl tcg_gen_add_i64
#define tcg_gen_addi_tl tcg_gen_addi_i64
#define tcg_gen_sub_tl tcg_gen_sub_i64
#define tcg_gen_neg_tl tcg_gen_neg_i64
#define tcg_gen_abs_tl tcg_gen_abs_i64
#define tcg_gen_subfi_tl tcg_gen_subfi_i64
#define tcg_gen_subi_tl tcg_gen_subi_i64
#define tcg_gen_and_tl tcg_gen_and_i64
#define tcg_gen_andi_tl tcg_gen_andi_i64
#define tcg_gen_or_tl tcg_gen_or_i64
#define tcg_gen_ori_tl tcg_gen_ori_i64
#define tcg_gen_xor_tl tcg_gen_xor_i64
#define tcg_gen_xori_tl tcg_gen_xori_i64
#define tcg_gen_not_tl tcg_gen_not_i64
#define tcg_gen_shl_tl tcg_gen_shl_i64
#define tcg_gen_shli_tl tcg_gen_shli_i64
#define tcg_gen_shr_tl tcg_gen_shr_i64
#define tcg_gen_shri_tl tcg_gen_shri_i64
#define tcg_gen_sar_tl tcg_gen_sar_i64
#define tcg_gen_sari_tl tcg_gen_sari_i64
#define tcg_gen_brcond_tl tcg_gen_brcond_i64
#define tcg_gen_brcondi_tl tcg_gen_brcondi_i64
#define tcg_gen_setcond_tl tcg_gen_setcond_i64
#define tcg_gen_setcondi_tl tcg_gen_setcondi_i64
#define tcg_gen_negsetcond_tl tcg_gen_negsetcond_i64
#define tcg_gen_negsetcondi_tl tcg_gen_negsetcondi_i64
#define tcg_gen_mul_tl tcg_gen_mul_i64
#define tcg_gen_muli_tl tcg_gen_muli_i64
#define tcg_gen_div_tl tcg_gen_div_i64
#define tcg_gen_rem_tl tcg_gen_rem_i64
#define tcg_gen_divu_tl tcg_gen_divu_i64
#define tcg_gen_remu_tl tcg_gen_remu_i64
#define tcg_gen_discard_tl tcg_gen_discard_i64
#define tcg_gen_trunc_tl_i32 tcg_gen_extrl_i64_i32
#define tcg_gen_trunc_i64_tl tcg_gen_mov_i64
#define tcg_gen_extu_i32_tl tcg_gen_extu_i32_i64
#define tcg_gen_ext_i32_tl tcg_gen_ext_i32_i64
#define tcg_gen_extu_tl_i64 tcg_gen_mov_i64
#define tcg_gen_ext_tl_i64 tcg_gen_mov_i64
#define tcg_gen_ext8u_tl tcg_gen_ext8u_i64
#define tcg_gen_ext8s_tl tcg_gen_ext8s_i64
#define tcg_gen_ext16u_tl tcg_gen_ext16u_i64
#define tcg_gen_ext16s_tl tcg_gen_ext16s_i64
#define tcg_gen_ext32u_tl tcg_gen_ext32u_i64
#define tcg_gen_ext32s_tl tcg_gen_ext32s_i64
#define tcg_gen_ext_tl tcg_gen_ext_i64
#define tcg_gen_bswap16_tl tcg_gen_bswap16_i64
#define tcg_gen_bswap32_tl tcg_gen_bswap32_i64
#define tcg_gen_bswap64_tl tcg_gen_bswap64_i64
#define tcg_gen_bswap_tl tcg_gen_bswap64_i64
#define tcg_gen_hswap_tl tcg_gen_hswap_i64
#define tcg_gen_wswap_tl tcg_gen_wswap_i64
#define tcg_gen_revbit8_tl tcg_gen_revbit8_i64
#define tcg_gen_revbit32_tl tcg_gen_revbit32_i64
#define tcg_gen_revbit64_tl tcg_gen_revbit64_i64
#define tcg_gen_revbit_tl tcg_gen_revbit64_i64
#define tcg_gen_concat_tl_i64 tcg_gen_concat32_i64
#define tcg_gen_extr_i64_tl tcg_gen_extr32_i64
#define tcg_gen_andc_tl tcg_gen_andc_i64
#define tcg_gen_eqv_tl tcg_gen_eqv_i64
#define tcg_gen_nand_tl tcg_gen_nand_i64
#define tcg_gen_nor_tl tcg_gen_nor_i64
#define tcg_gen_orc_tl tcg_gen_orc_i64
#define tcg_gen_clz_tl tcg_gen_clz_i64
#define tcg_gen_ctz_tl tcg_gen_ctz_i64
#define tcg_gen_clzi_tl tcg_gen_clzi_i64
#define tcg_gen_ctzi_tl tcg_gen_ctzi_i64
#define tcg_gen_clrsb_tl tcg_gen_clrsb_i64
#define tcg_gen_ctpop_tl tcg_gen_ctpop_i64
#define tcg_gen_rotl_tl tcg_gen_rotl_i64
#define tcg_gen_rotli_tl tcg_gen_rotli_i64
#define tcg_gen_rotr_tl tcg_gen_rotr_i64
#define tcg_gen_rotri_tl tcg_gen_rotri_i64
#define tcg_gen_deposit_tl tcg_gen_deposit_i64
#define tcg_gen_deposit_z_tl tcg_gen_deposit_z_i64
#define tcg_gen_extract_tl tcg_gen_extract_i64
#define tcg_gen_sextract_tl tcg_gen_sextract_i64
#define tcg_gen_extract2_tl tcg_gen_extract2_i64
#define tcg_constant_tl tcg_constant_i64
#define tcg_gen_movcond_tl tcg_gen_movcond_i64
#define tcg_gen_add2_tl tcg_gen_add2_i64
#define tcg_gen_sub2_tl tcg_gen_sub2_i64
#define tcg_gen_addcio_tl tcg_gen_addcio_i64
#define tcg_gen_mulu2_tl tcg_gen_mulu2_i64
#define tcg_gen_muls2_tl tcg_gen_muls2_i64
#define tcg_gen_mulsu2_tl tcg_gen_mulsu2_i64
#define tcg_gen_smin_tl tcg_gen_smin_i64
#define tcg_gen_umin_tl tcg_gen_umin_i64
#define tcg_gen_smax_tl tcg_gen_smax_i64
#define tcg_gen_umax_tl tcg_gen_umax_i64
#define tcg_gen_ussub_tl tcg_gen_ussub_i64
#define tcg_gen_atomic_cmpxchg_tl tcg_gen_atomic_cmpxchg_i64
#define tcg_gen_atomic_xchg_tl tcg_gen_atomic_xchg_i64
#define tcg_gen_atomic_fetch_add_tl tcg_gen_atomic_fetch_add_i64
#define tcg_gen_atomic_fetch_and_tl tcg_gen_atomic_fetch_and_i64
#define tcg_gen_atomic_fetch_or_tl tcg_gen_atomic_fetch_or_i64
#define tcg_gen_atomic_fetch_xor_tl tcg_gen_atomic_fetch_xor_i64
#define tcg_gen_atomic_fetch_smin_tl tcg_gen_atomic_fetch_smin_i64
#define tcg_gen_atomic_fetch_umin_tl tcg_gen_atomic_fetch_umin_i64
#define tcg_gen_atomic_fetch_smax_tl tcg_gen_atomic_fetch_smax_i64
#define tcg_gen_atomic_fetch_umax_tl tcg_gen_atomic_fetch_umax_i64
#define tcg_gen_atomic_add_fetch_tl tcg_gen_atomic_add_fetch_i64
#define tcg_gen_atomic_and_fetch_tl tcg_gen_atomic_and_fetch_i64
#define tcg_gen_atomic_or_fetch_tl tcg_gen_atomic_or_fetch_i64
#define tcg_gen_atomic_xor_fetch_tl tcg_gen_atomic_xor_fetch_i64
#define tcg_gen_atomic_smin_fetch_tl tcg_gen_atomic_smin_fetch_i64
#define tcg_gen_atomic_umin_fetch_tl tcg_gen_atomic_umin_fetch_i64
#define tcg_gen_atomic_smax_fetch_tl tcg_gen_atomic_smax_fetch_i64
#define tcg_gen_atomic_umax_fetch_tl tcg_gen_atomic_umax_fetch_i64
#define tcg_gen_dup_tl_vec  tcg_gen_dup_i64_vec
#define tcg_gen_dup_tl tcg_gen_dup_i64
#define dup_const_tl dup_const

TCGv_i64 cpu_reg(DisasContext *s, int reg);
TCGv_i64 cpu_reg_sp(DisasContext *s, int reg);
TCGv_i64 read_cpu_reg(DisasContext *s, int reg, int sf);
TCGv_i64 read_cpu_reg_sp(DisasContext *s, int reg, int sf);
void write_fp_dreg(DisasContext *s, int reg, TCGv_i64 v);
bool logic_imm_decode_wmask(uint64_t *result, unsigned int immn,
                            unsigned int imms, unsigned int immr);
bool fpmr_access_check(DisasContext *s);
bool sve_access_check(DisasContext *s);
bool sme_enabled_check(DisasContext *s);
bool sme_enabled_check_with_svcr(DisasContext *s, unsigned);
uint64_t make_svemte_desc(DisasContext *s, unsigned vsz, uint32_t nregs,
                          uint32_t msz, bool is_write, uint32_t data);

/* This function corresponds to CheckStreamingSVEEnabled. */
static inline bool sme_sm_enabled_check(DisasContext *s)
{
    return sme_enabled_check_with_svcr(s, R_SVCR_SM_MASK);
}

/* This function corresponds to CheckSMEAndZAEnabled. */
static inline bool sme_za_enabled_check(DisasContext *s)
{
    return sme_enabled_check_with_svcr(s, R_SVCR_ZA_MASK);
}

/* Note that this function corresponds to CheckStreamingSVEAndZAEnabled. */
static inline bool sme_smza_enabled_check(DisasContext *s)
{
    return sme_enabled_check_with_svcr(s, R_SVCR_SM_MASK | R_SVCR_ZA_MASK);
}

TCGv_i64 clean_data_tbi(DisasContext *s, TCGv_i64 addr);
TCGv_i64 gen_mte_check1(DisasContext *s, TCGv_i64 addr, bool is_write,
                        bool tag_checked, MemOp memop);
TCGv_i64 gen_mte_checkN(DisasContext *s, TCGv_i64 addr, bool is_write,
                        bool tag_checked, int total_size, MemOp memop);

/* We should have at some point before trying to access an FP register
 * done the necessary access check, so assert that
 * (a) we did the check and
 * (b) we didn't then just plough ahead anyway if it failed.
 * Print the instruction pattern in the abort message so we can figure
 * out what we need to fix if a user encounters this problem in the wild.
 */
static inline void assert_fp_access_checked(DisasContext *s)
{
#ifdef CONFIG_DEBUG_TCG
    if (unlikely(s->fp_access_checked <= 0)) {
        fprintf(stderr, "target-arm: FP access check missing for "
                "instruction 0x%08x\n", s->insn);
        abort();
    }
#endif
}

/* Return the offset into CPUARMState of an element of specified
 * size, 'element' places in from the least significant end of
 * the FP/vector register Qn.
 */
static inline int vec_reg_offset(DisasContext *s, int regno,
                                 int element, MemOp size)
{
    int element_size = 1 << size;
    int offs = element * element_size;
#if HOST_BIG_ENDIAN
    /* This is complicated slightly because vfp.zregs[n].d[0] is
     * still the lowest and vfp.zregs[n].d[15] the highest of the
     * 256 byte vector, even on big endian systems.
     *
     * Calculate the offset assuming fully little-endian,
     * then XOR to account for the order of the 8-byte units.
     *
     * For 16 byte elements, the two 8 byte halves will not form a
     * host int128 if the host is bigendian, since they're in the
     * wrong order.  However the only 16 byte operation we have is
     * a move, so we can ignore this for the moment.  More complicated
     * operations will have to special case loading and storing from
     * the zregs array.
     */
    if (element_size < 8) {
        offs ^= 8 - element_size;
    }
#endif
    offs += offsetof(CPUARMState, vfp.zregs[regno]);
    assert_fp_access_checked(s);
    return offs;
}

/* Return the offset info CPUARMState of the "whole" vector register Qn.  */
static inline int vec_full_reg_offset(DisasContext *s, int regno)
{
    assert_fp_access_checked(s);
    return offsetof(CPUARMState, vfp.zregs[regno]);
}

/* Return a newly allocated pointer to the vector register.  */
static inline TCGv_ptr vec_full_reg_ptr(DisasContext *s, int regno)
{
    TCGv_ptr ret = tcg_temp_new_ptr();
    tcg_gen_addi_ptr(ret, tcg_env, vec_full_reg_offset(s, regno));
    return ret;
}

/* Return the byte size of the "whole" vector register, VL / 8.  */
static inline int vec_full_reg_size(DisasContext *s)
{
    return s->vl;
}

/* Return the byte size of the vector register, SVL / 8. */
static inline int streaming_vec_reg_size(DisasContext *s)
{
    return s->svl;
}

/*
 * Return the offset info CPUARMState of the predicate vector register Pn.
 * Note for this purpose, FFR is P16.
 */
static inline int pred_full_reg_offset(DisasContext *s, int regno)
{
    return offsetof(CPUARMState, vfp.pregs[regno]);
}

/* Return the byte size of the whole predicate register, VL / 64.  */
static inline int pred_full_reg_size(DisasContext *s)
{
    return s->vl >> 3;
}

/* Return the byte size of the predicate register, SVL / 64.  */
static inline int streaming_pred_reg_size(DisasContext *s)
{
    return s->svl >> 3;
}

/*
 * Round up the size of a register to a size allowed by
 * the tcg vector infrastructure.  Any operation which uses this
 * size may assume that the bits above pred_full_reg_size are zero,
 * and must leave them the same way.
 *
 * Note that this is not needed for the vector registers as they
 * are always properly sized for tcg vectors.
 */
static inline int size_for_gvec(int size)
{
    if (size <= 8) {
        return 8;
    } else {
        return QEMU_ALIGN_UP(size, 16);
    }
}

static inline int pred_gvec_reg_size(DisasContext *s)
{
    return size_for_gvec(pred_full_reg_size(s));
}

/* Return a newly allocated pointer to the predicate register.  */
static inline TCGv_ptr pred_full_reg_ptr(DisasContext *s, int regno)
{
    TCGv_ptr ret = tcg_temp_new_ptr();
    tcg_gen_addi_ptr(ret, tcg_env, pred_full_reg_offset(s, regno));
    return ret;
}

/*
 * Return the ARMFPStatusFlavour to use based on element size and
 * whether FPCR.AH is set.
 */
static inline ARMFPStatusFlavour select_ah_fpst(DisasContext *s, MemOp esz)
{
    if (s->fpcr_ah) {
        return esz == MO_16 ? FPST_AH_F16 : FPST_AH;
    } else {
        return esz == MO_16 ? FPST_A64_F16 : FPST_A64;
    }
}

bool disas_sve(DisasContext *, uint32_t);
bool disas_sme(DisasContext *, uint32_t);

void gen_gvec_rax1(unsigned vece, uint32_t rd_ofs, uint32_t rn_ofs,
                   uint32_t rm_ofs, uint32_t opr_sz, uint32_t max_sz);
void gen_gvec_xar(unsigned vece, uint32_t rd_ofs, uint32_t rn_ofs,
                  uint32_t rm_ofs, int64_t shift,
                  uint32_t opr_sz, uint32_t max_sz);
void gen_gvec_eor3(unsigned vece, uint32_t d, uint32_t n, uint32_t m,
                   uint32_t a, uint32_t oprsz, uint32_t maxsz);
void gen_gvec_bcax(unsigned vece, uint32_t d, uint32_t n, uint32_t m,
                   uint32_t a, uint32_t oprsz, uint32_t maxsz);

void gen_suqadd_bhs(TCGv_i64 res, TCGv_i64 qc,
                    TCGv_i64 a, TCGv_i64 b, MemOp esz);
void gen_suqadd_d(TCGv_i64 res, TCGv_i64 qc, TCGv_i64 a, TCGv_i64 b);
void gen_gvec_suqadd_qc(unsigned vece, uint32_t rd_ofs,
                        uint32_t rn_ofs, uint32_t rm_ofs,
                        uint32_t opr_sz, uint32_t max_sz);

void gen_usqadd_bhs(TCGv_i64 res, TCGv_i64 qc,
                    TCGv_i64 a, TCGv_i64 b, MemOp esz);
void gen_usqadd_d(TCGv_i64 res, TCGv_i64 qc, TCGv_i64 a, TCGv_i64 b);
void gen_gvec_usqadd_qc(unsigned vece, uint32_t rd_ofs,
                        uint32_t rn_ofs, uint32_t rm_ofs,
                        uint32_t opr_sz, uint32_t max_sz);

void gen_gvec_sve2_sqdmulh(unsigned vece, uint32_t rd_ofs,
                           uint32_t rn_ofs, uint32_t rm_ofs,
                           uint32_t opr_sz, uint32_t max_sz);

void gen_sve_ldr(DisasContext *s, TCGv_ptr, int vofs,
                 int len, int rn, int imm, MemOp align);
void gen_sve_str(DisasContext *s, TCGv_ptr, int vofs,
                 int len, int rn, int imm, MemOp align);

#endif /* TARGET_ARM_TRANSLATE_A64_H */
