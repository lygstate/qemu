/*
 * Guest memory accessors for i386 TCG compiled into libsystem_i386.
 * accel/tcg/cpu-ldst.h uses abi_ptr / target_ulong and cannot be included.
 */

#ifndef I386_TCG_CPU_LDST_I386_H
#define I386_TCG_CPU_LDST_I386_H

#include "accel/tcg/cpu-ldst-common.h"
#include "accel/tcg/cpu-mmu-index.h"

static inline uint32_t
cpu_ldub_mmuidx_ra(CPUArchState *env, vaddr addr, int mmu_idx, uintptr_t ra)
{
    MemOpIdx oi = make_memop_idx(MO_UB, mmu_idx);
    return cpu_ldb_mmu(env, addr, oi, ra);
}

static inline uint32_t
cpu_lduw_le_mmuidx_ra(CPUArchState *env, vaddr addr, int mmu_idx, uintptr_t ra)
{
    MemOpIdx oi = make_memop_idx(MO_LEUW | MO_UNALN, mmu_idx);
    return cpu_ldw_mmu(env, addr, oi, ra);
}

static inline int
cpu_ldsw_le_mmuidx_ra(CPUArchState *env, vaddr addr, int mmu_idx, uintptr_t ra)
{
    return (int16_t)cpu_lduw_le_mmuidx_ra(env, addr, mmu_idx, ra);
}

static inline uint32_t
cpu_ldl_le_mmuidx_ra(CPUArchState *env, vaddr addr, int mmu_idx, uintptr_t ra)
{
    MemOpIdx oi = make_memop_idx(MO_LEUL | MO_UNALN, mmu_idx);
    return cpu_ldl_mmu(env, addr, oi, ra);
}

static inline uint64_t
cpu_ldq_le_mmuidx_ra(CPUArchState *env, vaddr addr, int mmu_idx, uintptr_t ra)
{
    MemOpIdx oi = make_memop_idx(MO_LEUQ | MO_UNALN, mmu_idx);
    return cpu_ldq_mmu(env, addr, oi, ra);
}

static inline void
cpu_stb_mmuidx_ra(CPUArchState *env, vaddr addr, uint32_t val,
                  int mmu_idx, uintptr_t ra)
{
    MemOpIdx oi = make_memop_idx(MO_UB, mmu_idx);
    cpu_stb_mmu(env, addr, val, oi, ra);
}

static inline void
cpu_stw_le_mmuidx_ra(CPUArchState *env, vaddr addr, uint32_t val,
                     int mmu_idx, uintptr_t ra)
{
    MemOpIdx oi = make_memop_idx(MO_LEUW | MO_UNALN, mmu_idx);
    cpu_stw_mmu(env, addr, val, oi, ra);
}

static inline void
cpu_stl_le_mmuidx_ra(CPUArchState *env, vaddr addr, uint32_t val,
                     int mmu_idx, uintptr_t ra)
{
    MemOpIdx oi = make_memop_idx(MO_LEUL | MO_UNALN, mmu_idx);
    cpu_stl_mmu(env, addr, val, oi, ra);
}

static inline void
cpu_stq_le_mmuidx_ra(CPUArchState *env, vaddr addr, uint64_t val,
                     int mmu_idx, uintptr_t ra)
{
    MemOpIdx oi = make_memop_idx(MO_LEUQ | MO_UNALN, mmu_idx);
    cpu_stq_mmu(env, addr, val, oi, ra);
}

static inline uint32_t
cpu_lduw_le_data_ra(CPUArchState *env, vaddr addr, uintptr_t ra)
{
    int mmu_index = cpu_mmu_index(env_cpu(env), false);
    return cpu_lduw_le_mmuidx_ra(env, addr, mmu_index, ra);
}

static inline int
cpu_ldsw_le_data_ra(CPUArchState *env, vaddr addr, uintptr_t ra)
{
    return (int16_t)cpu_lduw_le_data_ra(env, addr, ra);
}

static inline uint32_t
cpu_ldl_le_data_ra(CPUArchState *env, vaddr addr, uintptr_t ra)
{
    int mmu_index = cpu_mmu_index(env_cpu(env), false);
    return cpu_ldl_le_mmuidx_ra(env, addr, mmu_index, ra);
}

static inline uint64_t
cpu_ldq_le_data_ra(CPUArchState *env, vaddr addr, uintptr_t ra)
{
    int mmu_index = cpu_mmu_index(env_cpu(env), false);
    return cpu_ldq_le_mmuidx_ra(env, addr, mmu_index, ra);
}

static inline void
cpu_stb_data_ra(CPUArchState *env, vaddr addr, uint32_t val, uintptr_t ra)
{
    int mmu_index = cpu_mmu_index(env_cpu(env), false);
    cpu_stb_mmuidx_ra(env, addr, val, mmu_index, ra);
}

static inline void
cpu_stw_le_data_ra(CPUArchState *env, vaddr addr, uint32_t val, uintptr_t ra)
{
    int mmu_index = cpu_mmu_index(env_cpu(env), false);
    cpu_stw_le_mmuidx_ra(env, addr, val, mmu_index, ra);
}

static inline void
cpu_stl_le_data_ra(CPUArchState *env, vaddr addr, uint32_t val, uintptr_t ra)
{
    int mmu_index = cpu_mmu_index(env_cpu(env), false);
    cpu_stl_le_mmuidx_ra(env, addr, val, mmu_index, ra);
}

static inline void
cpu_stq_le_data_ra(CPUArchState *env, vaddr addr, uint64_t val, uintptr_t ra)
{
    int mmu_index = cpu_mmu_index(env_cpu(env), false);
    cpu_stq_le_mmuidx_ra(env, addr, val, mmu_index, ra);
}

#endif /* I386_TCG_CPU_LDST_I386_H */
