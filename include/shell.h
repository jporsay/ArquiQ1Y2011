#ifndef VIDEO_H
#define VIDEO_H

#include "defs.h"
#include "io.h"

#define BUFFER_SIZE	1024

typedef struct shell_cmd {
	char * name;
	void (*f)();
} shellCmd;

shellCmd commands[10];

char shellBuffer[BUFFER_SIZE];
void echo();
void append(char c);
void cleanBuffer();
void excecuteCmd();
#endif

