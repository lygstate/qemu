#include "qemu/osdep.h"

uint32_t mshv_get_supported_cpuid(uint32_t func, uint32_t idx, int reg);

uint32_t mshv_get_supported_cpuid(uint32_t func, uint32_t idx, int reg)
{
    return 0;
}
