#ifndef ROUTINES_H
#define ROUTINES_H

#include "defs.h"
#include "stdlib.h"

typedef struct retStruct{
	int returnValue;
	void * returnEnviroment;
	char * msg;
} retStruct;

void echo(char * args);
void restart(char * args);
void help(char * args);

#endif
