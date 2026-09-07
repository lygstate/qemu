#include "qemu/osdep.h"
#include "cpu.h"
#include "hvf-i386.h"

uint32_t hvf_get_supported_cpuid(uint32_t func, uint32_t idx, int reg)
{
    return 0;
}
