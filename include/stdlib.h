#ifndef STDLIB_H
#define STDLIB_H

#include "defs.h"

#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)

#define STDOUT 1
#define STDIN 2

#define MEM_START (void *)0x1FFE0 //A partir de los 2 MB
#define MEM_LENGTH 8388608 //8 MB de RAM

typedef __builtin_va_list va_list;
typedef struct memoryHeader_t{
	struct memoryHeader_t * next;
	int size;
	int reserved;
} memoryHeader_t;

typedef memoryHeader_t * memoryNode;

void setMemory();
void * malloc(size_t neededMem);
void free(void * pointer);
void printf(const char *fmt, ...);
void putc(char c);
void puti(int n);
void putui(unsigned int n);
void puth(int n, int upperCase);
void puts(char* s);
void putf(double n);
void pute(double n, int upperE);

#endif

