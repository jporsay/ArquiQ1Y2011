#include "../include/string.h"

size_t strlen(char* string) {
	size_t count = 0;
	while (string[count] != 0) {
		count++;
	}
	
	return count;
}
