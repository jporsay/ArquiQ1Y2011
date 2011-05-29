#ifndef _shell_
#define _shell_

#include "defs.h"
#include "io.h"
#include "stdlib.h"
#include "command.h"

#define SHELL_TEXT	"Inutil@OS> "

#define BUFFER_SIZE	1024

#define CMD_FAIL	0
#define CMD_OK		1

#define MAX_ARG_DIM	5

typedef struct cmd_table_entry {
	char* name;
	char* help;
	int (*func)(int argc, char *argv[]);
} cmd_table_entry;

void append(char c);
void cleanBuffer();

#endif

