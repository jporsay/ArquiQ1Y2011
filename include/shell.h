#ifndef VIDEO_H
#define VIDEO_H

#include "defs.h"
#include "io.h"

#define BUFFER_SIZE	1024

shellCmd commands[10];

char shellBuffer[BUFFER_SIZE];
void echo();
void cleanBuffer();
void excecuteCmd();
#endif

