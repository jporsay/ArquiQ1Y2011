#include "../include/io.h"

void sysRead(int fd, void * buffer, size_t count) {
	__read(fd, buffer, count);
}

void sysWrite(int fd, void * buffer, size_t count) {
	__write(fd, buffer, count);
}


