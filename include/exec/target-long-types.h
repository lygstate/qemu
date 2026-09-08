/*
 * Target long union types that do not need TARGET_LONG_BITS.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef EXEC_TARGET_LONG_TYPES_H
#define EXEC_TARGET_LONG_TYPES_H

#include "qemu/target-info.h"

typedef union {
    int32_t s32;
    int64_t s64;
} target_long_t;

typedef union {
    uint32_t u32;
    uint64_t u64;
} target_ulong_t;

/*
 * 1-element view of a packed target_long array. Pass as
 * target_long_array_t *; index i with the packed u32/u64 view and
 * target_long_bits(). Do not use sizeof(*p) as length or stride.
 */
typedef union {
    int32_t s32[1];
    int64_t s64[1];
} target_long_array_t;

typedef union {
    uint32_t u32[1];
    uint64_t u64[1];
} target_ulong_array_t;

#define TARGET_LONG_ARRAY(n) \
    union { \
        int32_t s32[n]; \
        int64_t s64[n]; \
        target_long_array_t rec; \
    }
#define TARGET_ULONG_ARRAY(n) \
    union { \
        uint32_t u32[n]; \
        uint64_t u64[n]; \
        target_ulong_array_t rec; \
    }

static inline uint64_t target_ulong_val(const target_ulong_t *p)
{
    if (target_long_bits() == 64) {
        return p->u64;
    }
    return p->u32;
}

static inline void target_ulong_set(target_ulong_t *p, uint64_t v)
{
    if (target_long_bits() == 64) {
        p->u64 = v;
    } else {
        p->u32 = (uint32_t)v;
    }
}

static inline int64_t target_long_val(const target_long_t *p)
{
    if (target_long_bits() == 64) {
        return p->s64;
    }
    return p->s32;
}

static inline void target_long_set(target_long_t *p, int64_t v)
{
    if (target_long_bits() == 64) {
        p->s64 = v;
    } else {
        p->s32 = (int32_t)v;
    }
}

static inline uint64_t target_ulong_array_val(const target_ulong_array_t *p,
                                              unsigned i)
{
    if (target_long_bits() == 64) {
        return p->u64[i];
    }
    return p->u32[i];
}

static inline uint64_t target_ulong_array_set(target_ulong_array_t *p,
                                              unsigned i, uint64_t v)
{
    if (target_long_bits() == 64) {
        p->u64[i] = v;
        return v;
    }
    p->u32[i] = (uint32_t)v;
    return p->u32[i];
}

static inline int64_t target_long_array_val(const target_long_array_t *p,
                                            unsigned i)
{
    if (target_long_bits() == 64) {
        return p->s64[i];
    }
    return p->s32[i];
}

static inline void target_long_array_set(target_long_array_t *p, unsigned i,
                                         int64_t v)
{
    if (target_long_bits() == 64) {
        p->s64[i] = v;
    } else {
        p->s32[i] = (int32_t)v;
    }
}

/* Packed element i; stride is target_long_bits()/8. */
static inline void *target_ulong_array_elem(const target_ulong_array_t *p,
                                            unsigned i)
{
    if (target_long_bits() == 64) {
        return (void *)&p->u64[i];
    }
    return (void *)&p->u32[i];
}

#endif /* EXEC_TARGET_LONG_TYPES_H */
