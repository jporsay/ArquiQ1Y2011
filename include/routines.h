#include "defs.h"
#include "stdlib.h"
#include "interpreter.h"

typedef struct retStruct{
	int returnValue;
	void * returnEnviroment;
	char * msg;
} retStruct;
