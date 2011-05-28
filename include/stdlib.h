#ifndef STDLIB_H
#define STDLIB_H

#include "defs.h"

#define STDOUT 1
#define STDIN 2

void putc(char c);
void setMemory();
void * malloc(size_t neededMem);
void free(void * pointer);

#endif

