#include "../include/shell.h"

void excecuteCmd(char* buffer);
int parse_cmd(char* buffer);
int execute(int cmdId);
void myPrint(char * s);

int currPos;

void initShell() {
	cleanBuffer();
	myPrint(SHELL_TEXT);
}


void append(char c) {
	if (currPos >= BUFFER_SIZE) {
		return;
	}
	
	if (c == '\n') {
		excecuteCmd(shellBuffer);
		cleanBuffer();
		writeInVideo(&c, 1);
		//currPos = strlen(SHELL_TEXT);
		myPrint(SHELL_TEXT);
	} else if (c == '\b') {
		if (currPos > strlen(SHELL_TEXT)) {
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
	int cmdId = parse_cmd(buffer);
	if (cmdId != -1) {
		execute(cmdId);
	}
}

int parse_cmd(char* buffer) {
	int i;
	for( i = 0; i < ROUTINES_SIZE; i++) {
		if(substr(cmd_table[i].name, buffer)) {
			return i;
		}
	}
	return -1;
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

int execute(int cmdId) {
	cmd_table[cmdId].func(0, NULL);
}

void cleanBuffer() {
	currPos = 0;
	shellBuffer[0] = '\0';
}

//-----CMD IMPLEMTATIONS------------------------

int echo_cmd(int argc, char *argv[]) {
	myPrint("\necho execution!\n");
}

int reset_cmd(int argc, char *argv[]) {
	myPrint("\nreset execution!\n");
}

int clear_cmd(int argc, char *argv[]) {
	myPrint("\nclear execution!\n");
}

int help_cmd(int argc, char *argv[]) {
	myPrint("\nhelp execution!\n");
}

//----------------------------------------------

void myPrint(char * s) {
	int length = strlen(s);
	writeInVideo(s, length);
}



