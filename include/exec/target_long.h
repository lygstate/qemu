/*
 * Target Long Definitions
 *
 * Copyright (c) 2003 Fabrice Bellard
 * Copyright (c) 2023 Linaro Ltd
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef _TARGET_LONG_H_
#define _TARGET_LONG_H_

#ifdef COMPILING_PER_TARGET
/*
 * Usually this should only be included via cpu-defs.h however for
 * certain cases where we want to build only two versions of a binary
 * object we can include directly. However the build-system must
 * ensure TARGET_LONG_BITS is defined directly.
 */
#ifndef TARGET_LONG_BITS
#error TARGET_LONG_BITS not defined
#endif

#define TARGET_LONG_SIZE (TARGET_LONG_BITS / 8)

/* target_ulong is the type of a virtual address */
#if TARGET_LONG_SIZE == 4
typedef int32_t target_long;
typedef uint32_t target_ulong;
#define TARGET_FMT_lx "%08x"
#define TARGET_FMT_ld "%d"
#define TARGET_FMT_lu "%u"
#define MO_TL MO_32
#elif TARGET_LONG_SIZE == 8
typedef int64_t target_long;
typedef uint64_t target_ulong;
#define TARGET_FMT_lx "%016" PRIx64
#define TARGET_FMT_ld "%" PRId64
#define TARGET_FMT_lu "%" PRIu64
#define MO_TL MO_64
#else
#error TARGET_LONG_SIZE undefined
#endif
#else
typedef uint64_t target_ulong;
#endif

#include "qemu/target-info.h"

/*
 * 1-element view of a packed target_long array. Pass as
 * target_long_array_t *; index i with the packed s32/s64 view and
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

#endif /* _TARGET_LONG_H_ */
