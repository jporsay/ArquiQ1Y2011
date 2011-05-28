#ifndef STDLIB_H
#define STDLIB_H

#include "defs.h"

#define STDOUT 1

#define STDIN 2
#define MEM_START (void *)0x1FFE0 //A partir de los 2 MB
#define MEM_LENGTH 8388608 //8 MB de RAM

typedef struct memoryHeader_t{
	struct memoryHeader_t * next;
	int size;
	int reserved;
} memoryHeader_t;

typedef memoryHeader_t * memoryNode;


void putc(char c);
void setMemory();
void * malloc(size_t neededMem);
void free(void * pointer);
void myPrint(char * s);

#endif

