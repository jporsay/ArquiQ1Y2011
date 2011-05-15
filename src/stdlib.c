#include "../include/stdlib.h"

void putc(char c) {
	__write(STD_OUT, &c, 1);
}

