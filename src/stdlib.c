#include "../include/stdlib.h"

void putc(char c) {
	__write(STDOUT, &c, 1);
}

