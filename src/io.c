#include "../include/io.h"
#include "../include/video.h"

void sysRead(int fd, void * buffer, size_t count) {
	//unsigned char c = getKey();
	//_memcpy((void *)&c, buffer, count);
}

void sysWrite(int fd, void * buffer, size_t count) {
	writeInVideo(buffer, count);
}

