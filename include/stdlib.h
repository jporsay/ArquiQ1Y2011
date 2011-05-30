#ifndef STDLIB_H
#define STDLIB_H

#include "defs.h"
#include "video.h"

#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)

#define STDOUT 1
#define STDIN 2

#define F_PRECISION 6

#define MEM_START (void *)0x1FFE0 	//A partir de los 2 MB
#define MEM_LENGTH 8388608 			//8 MB de RAM

typedef __builtin_va_list va_list;
typedef struct memoryHeader_t {
	struct memoryHeader_t * next;
	int size;
	int reserved;
} memoryHeader_t;

typedef memoryHeader_t * memoryNode;

void setMemory();
void * malloc(size_t neededMem);
void free(void * pointer);
void printf(const char *fmt, ...);
void putc(char c, int fd);
char getc(int fd);
void puti(int n);
void putui(unsigned int n);
void puth(int n, int upperCase);
void puts(char* s);
void putf(double n);
void pute(double n, int upperE);
char getchar();
void putchar(char c);

int scanf(const char *format, ...);
int getLongDec(long * ptr);
int getLongInt(long * ptr);
int getLongUDec(long * ptr);
int getLongHex(long * ptr);
int getLongOct(long * ptr);
int getDouble(double * ptr);
void getDoubleDecimals(double * ptr, int i);
int getLongDbl(long double * ptr);
void getLongDblDecimals(long double * ptr, int i);
int getShortDec(short * ptr);
int getShortInt(short * ptr);
int getShortUDec(short * ptr);
int getShortHex(short * ptr);
int getShortOct(short * ptr);
int getDec(int * ptr);
int getInt(int * ptr);
int getUDec(int * ptr);
int getHex(int * ptr);
int getOct(int * ptr);
void getString(char *);
int getFloat(float * ptr);
void getFloatDecimals(float * ptr, int i);
int isdigit(char c);
int isalpha(char c);
int isalnum(char c);
int isupper(char c);
int islower(char c);

#endif

