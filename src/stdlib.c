#include "../include/stdlib.h"


void setMemory() {
	memoryNode firstMemoryNode = MEM_START;
	firstMemoryNode->next = firstMemoryNode;
	firstMemoryNode->size = MEM_LENGTH;
	firstMemoryNode->reserved = FALSE;
}

void * malloc(size_t neededMem) {
	memoryNode node, firstNode;
	int chunkFound = FALSE;
	node = firstNode = MEM_START;
	do {
		if (node->reserved == FALSE && node->size >= neededMem) {
			chunkFound = TRUE;
			node->reserved = TRUE;
			if (node->size > neededMem) {
				memoryNode newNode = (memoryNode)(node + sizeof(memoryHeader_t)
					 + neededMem);
				newNode->next = node->next;
				newNode->size = node->size - neededMem - sizeof(memoryHeader_t);
				newNode->reserved = FALSE;
				node->next = newNode;
				node->size = neededMem;
			}
		} else {
			node = node->next;
		}
	} while (!chunkFound && node != firstNode);
	
	if (chunkFound) {
		return (void *)(node + 1);
	}
	return NULL;
}

void free(void * pointer) {
	memoryNode node = (memoryNode)(pointer - sizeof(memoryHeader_t));
	node->reserved = FALSE;
	memoryNode startingNode = node;
	while(node->next != startingNode && node->next->reserved == FALSE) {
		node->size = node->size + node->next->size + sizeof(memoryHeader_t);
		node->next = node->next->next;
	}
}

char getchar() {
	return getc(STD_IN);
}

char getc(int fd) {
	char c;
	while(bufferIsEmpty()) {
	}
	__read(fd, &c, 1);
	return c;
}

void putchar(char c) {
	putc(c, STD_OUT);
}

void putc(char c, int fd) {
	__write(STD_OUT, &c, 1);
}

void puti(int n) {
	if (n < 0) {
		putchar('-');
		n = 0 - n;
	}
	putui(n);
}

void putui(unsigned int n) {
	if (n <= 0) {
		return;
	}
	putui(n / 10);
	putchar((n % 10) + '0');
}

void puth(int n, int upperCase) {
	char *letters = upperCase ? "ABCDEF" : "abcdef";
	char c;
	int num;
	if (n <= 0) {
		return;
	}
	num = n % 16;
	c = num > 9 ? letters[num - 10] : (num + '0');
	
	puth(n / 16, upperCase);
	putchar(c);
}

void puts(char* s) {
	char c;
	while ((c = *s++) != 0) {
		putchar(c);
	}
}

void putf(double n) {
	putchar((int)(3) + '0');
	n = n - (int)n;
	if (n == 0) return;
	putchar('.');
	int precision = 0;
	while (n != 0 && precision < F_PRECISION) {
		n *= 10;
		puti((int)n);
		n = n - (int)n;
		precision++;
	}
		
}

void pute(double n, int upperE) {
}

void printf(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	double t;
	char c;
	while ((c = *fmt++) != 0) {
		if (c != '%') {
			putchar(c);
		} else {
			c = *fmt++;
			switch(c) {
				case '%':
					putchar('%');
					break;
				case 'i':
				case 'd':
					puti(va_arg(args, int));
					break;
				case 'u':
					putui(va_arg(args, int));
				case 'x':
					puth(va_arg(args, int), FALSE);
					break;
				case 'X':
					puth(va_arg(args, int), TRUE);
					break;
				case 's':
					puts(va_arg(args, char*));
					break;
				case 'f':
					putf(va_arg(args, double));
					break;
				case 'e':
					pute(va_arg(args, double), FALSE);
					break;
				case 'E':
					pute(va_arg(args, double), TRUE);
					break;
				case 'c':
					c = (char)va_arg(args, int);
					putchar(c);
					break;
				default:
					break;
			}
		}
	}
	va_end(args);
}

void memcpy(void* from, void* src, size_t count) {
	size_t i;
	for (i = 0; i < count; i++) {
		*((char *)src + i) = *((char *)from + i);
	}
}

int scanf(const char *format, ...) {
	va_list(args);
	va_start(args, format);
	int c;
	int varCount = 0;
	char * cPtr;
	long * lPtr;
	short * sPtr;
	int * iPtr;
	
	while((c = getchar()) == ' ' || c == '\t');
	
	while((c = getchar()) != '\n' && *format != '\0') {
		if(*format++ == '%'){
			switch(*format){
				case 'l':
					switch(*(++format)){
						case 'd':
							getLongDec(va_arg(args, long *));
							break;
						case 'i':
							getLongInt(va_arg(args, long *));
							break;
						case 'o':
							getLongOct(va_arg(args, long *));
							break;
						case 'u':
							getLongUDec(va_arg(args, long *));
							break;
						case 'x':
							getLongHex(va_arg(args, long *));
							break;
						case 'e':
						case 'f':
						case 'g':
							getDouble(va_arg(args, double *));
							break;
						case 'n':
							lPtr = (long *)va_arg(args, long *);
							*lPtr = varCount;
							break;
						default:
							break;
					}
					break;
				case 'L':
					switch(*(++format)){
						case 'e':
						case 'f':
						case 'g':
							getLongDouble(va_arg(args, long double *));
							break;
						default:
							break;
					}
					break;
				case 'h':
					switch(*(++format)){
						case 'd':
							getShortDec(va_arg(args, short *));
							break;
						case 'i':
							getShortInt(va_arg(args, short *));
							break;
						case 'o':
							getShortOct(va_arg(args, short *));
							break;
						case 'u':
							getShortUDec(va_arg(args, short *));
							break;
						case 'x':
							getShortHex(va_arg(args, short *));
							break;
						case 'n':
							sPtr = (short *)va_arg(args, short *);
							*sPtr = varCount;
							break;
						default:
							break;
					}
					break;
				case 'd':
					getDec(va_arg(args, int *));
					break;
				case 'i':
					getInt(va_arg(args, int *));
					break;
				case 'o':
					getOct(va_arg(args, int *));
					break;
				case 'u':
					getUDec(va_arg(args, int *));
					break;
				case 'x':
					getHex(va_arg(args, int *));
					break;
				case 'c':
					cPtr = (char *)va_arg(args, char *); 
					*cPtr = getchar();
					break;
				case 's':
					getString(va_arg(args, char *));
					break;
				case 'e':
				case 'f':
				case 'g':
					getFloat(va_arg(args, float *));
					break;
				case 'n':
					iPtr = (int *)va_arg(args, int *);
					*iPtr = varCount;
					break;
				case '%':
				default:
					break;					
			}
		}
		format++;
	}
	va_end(args);
}

void getString(char * s) {
	int c;
	int stop = FALSE;
	int quotes = FALSE;
	
	while(!stop){
		c = getchar();
		switch(c){
			case '"':
				quotes = !quotes;
				*s = c;
				break;
			case ' ':
				if(!quotes)
					stop = TRUE;
				else
					*s = c;
				break;
			case '\0':
				stop = TRUE;
			default:
				*s = c;
				break;
		}
		s++;
	}
}

int isdigit(char c) {
	return ( c >= '0' && c <= '9');
}

int islower(char c) {
	return ( c >= 'a' && c <= 'z');
}

int isupper(char c) {
	return ( c >= 'A' && c <= 'Z');
}

int isalpha(char c) {
	return (islower(c) || isupper(c));
}

int isalnum(char c) {
	return (isalpha(c) || islower(c));
}

int getShortInt(short * ptr) {
	return getShortDec(ptr);
}

int getShortDec(short * ptr) {
	short c;
	int i;
	int sign = 1;
	if(!isdigit(c = getchar())) {
		switch(c){
			case '-':
				c = getchar();
				sign = -1;
				break;
			default:
			*ptr = 0;
			return 0;
		}
	}
	
	
	*ptr = sign * c * pow(10, i = getShortDec(ptr)) + *ptr;
	
	return i+1;
}

int getShortUDec(short * ptr) {
	short c;
	int i;
	if(!isdigit(c = getchar())) {
		*ptr = 0;
		return 0;
	}
	
	*ptr = c * pow(10, i = getShortUDec(ptr)) + *ptr;
	
	return i+1;
}

int getShortHex(short * ptr) {
	short c;
	int i;
	int sign = 1;
	if(!isdigit(c = getchar())) {
		switch(c){
			case '-':
				c = getchar();
				sign = -1;
				break;
			case 'x':
			case 'X':
				c = getchar();
				break;
			case 'a':
			case 'A':
				c = 10;
				break;
			case 'b':
			case 'B':
				c = 11;
				break;
			case 'c':
			case 'C':
				c = 12;
				break;
			case 'd':
			case 'D':
				c = 13;
				break;
			case 'e':
			case 'E':
				c = 14;
				break;
			case 'f':
			case 'F':
				c = 15;
				break;
			default:
			*ptr = 0;
			return 0;
		}
	}
	
	if( c = '-')
		sign = -1;
	
	*ptr = sign * c * pow(16, i = getShortHex(ptr)) + *ptr;
	
	return i+1;
}

int getShortOct(short * ptr) {
	short c;
	int i;
	int sign = 1;
	if(!isdigit(c = getchar())) {
		switch(c){
			case '-':
				c = getchar();
				sign = -1;
				break;
			default:
			*ptr = 0;
			return 0;
		}
	}
	
	*ptr = sign * c * pow(8, i = getShortOct(ptr)) + *ptr;
	
	return i+1;
	
}

int getInt(int * ptr) {
	return getDec(ptr);
}

int getDec(int * ptr) {
	int c;
	int i;
	int sign = 1;
	if(!isdigit(c = getchar())) {
		switch(c){
			case '-':
				c = getchar();
				sign = -1;
				break;
			default:
			*ptr = 0;
			return 0;
		}
	}
	
	
	*ptr = sign * c * pow(10, i = getDec(ptr)) + *ptr;
	
	return i+1;
}

int getUDec(int * ptr) {
	int c;
	int i;
	if(!isdigit(c = getchar())) {
		*ptr = 0;
		return 0;
	}
	
	*ptr = c * pow(10, i = getUDec(ptr)) + *ptr;
	
	return i+1;
}

int getHex(int * ptr) {
	int c;
	int i;
	int sign = 1;
	if(!isdigit(c = getchar())) {
		switch(c){
			case '-':
				c = getchar();
				sign = -1;
				break;
			case 'x':
			case 'X':
				c = getchar();
				break;
			case 'a':
			case 'A':
				c = 10;
				break;
			case 'b':
			case 'B':
				c = 11;
				break;
			case 'c':
			case 'C':
				c = 12;
				break;
			case 'd':
			case 'D':
				c = 13;
				break;
			case 'e':
			case 'E':
				c = 14;
				break;
			case 'f':
			case 'F':
				c = 15;
				break;
			default:
			*ptr = 0;
			return 0;
		}
	}
	
	if( c = '-')
		sign = -1;
	
	*ptr = sign * c * pow(16, i = getHex(ptr)) + *ptr;
	
	return i+1;
}

int getOct(int * ptr){
	int c;
	int i;
	int sign = 1;
	if(!isdigit(c = getchar())) {
		switch(c){
			case '-':
				c = getchar();
				sign = -1;
				break;
			default:
			*ptr = 0;
			return 0;
		}
	}
		
	*ptr = sign * c * pow(8, i = getOct(ptr)) + *ptr;
	
	return i+1;
}

int getLongInt(long * ptr) {
	//TODO: hacerlo bien
	return getLongDec(ptr);
}

int getLongUDec(long * ptr) {
	long c;
	int i;
	if(!isdigit(c = getchar())) {
		*ptr = 0;
		return 0;
	}
	
	*ptr = c * pow(10, i = getLongUDec(ptr)) + *ptr;
	
	return i+1;
}

int getLongDec(long * ptr) {
	long c;
	int i;
	int sign = 1;
	if(!isdigit(c = getchar())) {
		switch(c){
			case '-':
				c = getchar();
				sign = -1;
				break;
			default:
			*ptr = 0;
			return 0;
		}
	}
	
	
	*ptr = sign * c * pow(10, i = getLongDec(ptr)) + *ptr;
	
	return i+1;
}

int getLongHex(long * ptr) {
	long c;
	int i;
	int sign = 1;
	if(!isdigit(c = getchar())) {
		switch(c){
			case '-':
				c = getchar();
				sign = -1;
				break;
			case 'x':
			case 'X':
				c = getchar();
				break;
			case 'a':
			case 'A':
				c = 10;
				break;
			case 'b':
			case 'B':
				c = 11;
				break;
			case 'c':
			case 'C':
				c = 12;
				break;
			case 'd':
			case 'D':
				c = 13;
				break;
			case 'e':
			case 'E':
				c = 14;
				break;
			case 'f':
			case 'F':
				c = 15;
				break;
			default:
			*ptr = 0;
			return 0;
		}
	}
		
	*ptr = sign * c * pow(16, i = getLongHex(ptr)) + *ptr;
	
	return i+1;
}

int getLongOct(long * ptr) {
	long c;
	int i;
	int sign = 1;
	if(!isdigit(c = getchar())) {
		switch(c){
			case '-':
				c = getchar();
				sign = -1;
				break;
			default:
			*ptr = 0;
			return 0;
		}
	}
	
	*ptr = sign * c * pow(8, i = getLongOct(ptr)) + *ptr;
	
	return i+1;
}

void getDoubleDecimals(double * ptr, int i) {
	int c = getchar();
	
	if(!isdigit(c)){
		*ptr = 0;
		return;
	}
	
	getDoubleDecimals(ptr, i+1);
	*ptr = (double)(c * 1/pow(10, i)) + *ptr;
}

int getDouble(double * ptr) {
	int c;
	int i;
	int sign = 1;
	
	if(!isdigit(c = getchar())){
		switch(c){
			case '-':
				c = getchar();
				sign = -1;
				break;
			case '.':
			case ',':
				getDoubleDecimals(ptr, 0);
				return 0;
				break;
			default:
				*ptr = 0;
				return 0;
				break;
		}
	}
	
	*ptr = (double)(sign * c * pow(10, i = getDouble(ptr))) + *ptr;
	
	return i+1;
}

void getLongDblDecimals(long double * ptr, int i) {
	int c = getchar();
	
	if(!isdigit(c)){
		*ptr = 0;
		return;
	}
	
	getLongDblDecimals(ptr, i+1);
	*ptr = (double)(c * 1/pow(10, i)) + *ptr;
}

int getLongDouble(long double * ptr) {
	int c;
	int i;
	int sign = 1;
	
	if(!isdigit(c = getchar())){
		switch(c){
			case '-':
				c = getchar();
				sign = -1;
				break;
			case '.':
			case ',':
				getLongDblDecimals(ptr, 0);
				return 0;
				break;
			default:
				*ptr = 0;
				return 0;
				break;
		}
	}
	
	*ptr = (double)(sign * c * pow(10, i = getLongDouble(ptr))) + *ptr;
	
	return i+1;
}

void getFloatDecimals(float * ptr, int i) {
	int c = getchar();
	
	if(!isdigit(c)){
		*ptr = 0;
		return;
	}
	getFloatDecimals(ptr, i+1);
	*ptr = (double)(c * 1/pow(10, i)) + *ptr;
}

int getFloat(float * ptr) {
	int c;
	int i;
	int sign = 1;
	
	if(!isdigit(c = getchar())){
		switch(c){
			case '-':
				c = getchar();
				sign = -1;
				break;
			case '.':
			case ',':
				getFloatDecimals(ptr, 0);
				return 0;
				break;
			default:
				*ptr = 0;
				return 0;
				break;
		}
	}
	
	*ptr = (double)(sign * c * pow(10, i = getFloat(ptr))) + *ptr;
	
	return i+1;
}


