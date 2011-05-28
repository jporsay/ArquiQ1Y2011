#include "../include/io.h"
#include "../include/video.h"

void sysRead(int fd, void * buffer, size_t count) {
	//unsigned char c = getKey();
	//_memcpy((void *)&c, buffer, count);
	//TODO: tiene que leer desde una posición de memoria?
}

void sysWrite(int fd, void * buffer, size_t count) {
	writeInVideo(buffer, count);
}

