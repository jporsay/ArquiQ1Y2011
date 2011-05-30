#ifndef _shell_
#define _shell_

#include "kernel.h"
#include "defs.h"
#include "io.h"
#include "stdlib.h"
#include "command.h"

#define SHELL_TEXT	"gatOS> "

#define BUFFER_SIZE	1024

#define CMD_FAIL	0
#define CMD_OK		1

#define MAX_ARG_DIM	5

typedef struct cmd_table_entry {
	char* name;
	char* help;
	int (*func)(int argc, char *argv[]);
} cmd_table_entry;

void updateShell();
void cleanBuffer();

#endif

