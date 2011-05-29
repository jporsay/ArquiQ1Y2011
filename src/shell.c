#include "../include/shell.h"

void excecuteCmd(char* buffer);
int parse_cmd(char* buffer);
int execute(int cmdId);
char** getArguments(char* buffer, int* argc);

char* argv[MAX_ARG_DIM];
int currPos;
char shellBuffer[BUFFER_SIZE];
cmd_table_entry cmd_table[] = {
	{"help", "this is the help help function", help_cmd},
	{"reset", "this is the reset help function", reset_cmd},
	{"clear", "this is the clear screen help function", clear_cmd},
	{"CPUspeed", "this is the CPUspeed help function", CPUspeed_cmd},
	{"countDown", "this is the countDown help function", countDown_cmd},
	{"resetPit", "this is the resetPit help function", resetPit_cmd},
	{"setPit", "this is the setPit help function", setPit_cmd},
	{"random", "this is the random help function", random_cmd},
	{"echo", "this is the echo help function", echo_cmd},
	{"test", "this is test help function", test_cmd}
};

void initShell() {
	cleanBuffer();
	myPrint(SHELL_TEXT);
}


void append(char c) {
	if (currPos >= BUFFER_SIZE) {
		return;
	}
	
	if (c == '\n') {
		myPrint("\n");
		excecuteCmd(shellBuffer);
		myPrint("\n");
		myPrint(SHELL_TEXT);
		cleanBuffer();
	} else if (c == '\b') {
		if (currPos > 0) {
			writeInVideo(&c, 1);
			currPos--;
			shellBuffer[currPos] = '\0';
		}
	} else {
		writeInVideo(&c, 1);
		shellBuffer[currPos] = c;
		shellBuffer[currPos + 1] = '\0';
		currPos++;
	}
}

void excecuteCmd(char* buffer) {
	int cmdLen, argc;
	char ** arguments;
	
	int cmdIndex = parse_cmd(buffer);
	if (cmdIndex != -1) {
		cmdLen = strlen(cmd_table[cmdIndex].name);
		arguments = getArguments(buffer + cmdLen, &argc);
		cmd_table[cmdIndex].func(argc, arguments);
	}
}

//FIXME: no tiene que depender del valor de ROUTINES_SIZE!
int parse_cmd(char* buffer) {
	int i, cmdLength = -1, aux;
	int match = -1;

	for( i = 0; i < ROUTINES_SIZE; i++) {
		if (substr(cmd_table[i].name, buffer)) {
			aux = strlen(cmd_table[i].name);
			if (aux > cmdLength) {
				match = i;
				cmdLength = aux;
			}
		}
	}
	return match;
}


char** getArguments(char* buffer, int* argc) {
	int i = 0, arg = 0;
	while(buffer[i] != '\0' && arg < MAX_ARG_DIM) {
		if (buffer[i] == ' ') {
			argv[arg++] = buffer + i + 1;
			buffer[i] = '\0';
		}
		i++;
	}
	*argc = arg;
	return argv;
}

/*Retorna true si s1 es subString de s2*/
int substr(const char * s1, const char *s2) {
	int i = 0, isSubstr = TRUE;
	while(isSubstr && s1[i] != '\0') {
		if(s1[i] != s2[i]) {
			isSubstr = FALSE;
		}
		i++;
	}
	return isSubstr;
}

void cleanBuffer() {
	currPos = 0;
	shellBuffer[0] = '\0';
}



