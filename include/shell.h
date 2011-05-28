#ifndef SHELL_H
#define SHELL_H

#include "defs.h"
#include "io.h"
#include "stdlib.h"

#define SHELL_TEXT		"InutilOs> "

#define BUFFER_SIZE	1024
#define ROUTINES_SIZE	4

//#define CMD_ENTRY(cmd) {#cmd, "help", cmd}

#define CMD_FAIL	0
#define CMD_OK		1

typedef struct cmd_table_entry {
	char* name;
	char* help;
	int (*func)(int argc, char *argv[]);
} cmd_table_entry;

int echo_cmd(int argc, char *argv[]);
int reset_cmd(int argc, char *argv[]);
int clear_cmd(int argc, char *argv[]);
int help_cmd(int argc, char *argv[]);

char shellBuffer[BUFFER_SIZE];
void echo();
void append(char c);
void cleanBuffer();
void excecuteCmd();

char shellBuffer[BUFFER_SIZE];

#endif

