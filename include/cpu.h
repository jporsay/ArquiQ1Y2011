#ifndef CPU_H
#define CPU_H

#include "defs.h"
#include "interrupts.h"

int detect_cpu(void);
__inline__ uint64_t rdtsc();
#endif
