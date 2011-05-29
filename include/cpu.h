#ifndef CPU_H
#define CPU_H

int detect_cpu(void);
__inline__ void rdtsc(unsigned int* low, unsigned int* high);
#endif
