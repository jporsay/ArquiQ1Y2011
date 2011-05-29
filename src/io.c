#include "../include/io.h"

void sysRead(int fd, void * buffer, size_t count) {
	memcpy((void *) fd, (void*) buffer, count);
}

void sysWrite(int fd, void * buffer, size_t count) {
	writeInVideo(buffer, count);
}

