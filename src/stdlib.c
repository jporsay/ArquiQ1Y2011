#include "../include/stdlib.h"

//@deprecated
void myPrint(char * s) {
	int length = strlen(s);
	writeInVideo(s, length);
}

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
	
	do{
		if(node->reserved == FALSE && node->size >= neededMem){
			chunkFound = TRUE;
			node->reserved = TRUE;
			if(node->size > neededMem){
				memoryNode newNode = (memoryNode)(node + sizeof(memoryHeader_t)
					 + neededMem);
				
				newNode->next = node->next;
				newNode->size = node->size - neededMem - sizeof(memoryHeader_t);
				newNode->reserved = FALSE;
				
				node->next = newNode;
				node->size = neededMem;
			}
		
		}else{
			node = node->next;
		}
	}while(!chunkFound && node != firstNode);
	
	if(chunkFound)
		return (void *)(node + 1);
	
	return NULL;
}

void free(void * pointer) {
	
	memoryNode node = (memoryNode)(pointer - sizeof(memoryHeader_t));
	
	node->reserved = FALSE;

	memoryNode startingNode = node;
	
	while(node->next != startingNode && node->next->reserved == FALSE){
		node->size = node->size + node->next->size + sizeof(memoryHeader_t);
		node->next = node->next->next;
	}
	
}

void putc(char c) {
	__write(STDOUT, &c, 1);
}

void puti(int n) {
	if (n < 0) {
		putc('-');
		n = 0 - n;
	}
	putui(n);
}

void putui(unsigned int n) {
	if (n <= 0) {
		return;
	}
	putui(n / 10);
	putc((n % 10) + '0');
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
	putc(c);
}

void puts(char* s) {
	char c;
	while ((c = *s++) != 0) {
		putc(c);
	}
}

void putf(double n) {
	putc((int)(3) + '0');
	putc('.');
	/*
	n = n - (int)n;
	if (n == 0) return;
	n = n * pow(10, F_PRECISION);
	puti((int)n);
	*/
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
			putc(c);
		} else {
			c = *fmt++;
			switch(c) {
				case '%':
					putc('%');
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
					t = va_arg(args, double);
					puti((int)t);
					//putf(va_arg(args, double));
					break;
				case 'e':
					pute(va_arg(args, double), FALSE);
					break;
				case 'E':
					pute(va_arg(args, double), TRUE);
					break;
				default:
					break;
			}
		}
	}
	va_end(args);
}
