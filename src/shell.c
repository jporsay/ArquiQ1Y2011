#include "../include/shell.h"

int currPos;

void initShell() {
	currPos = 0;
	
	shellCmd echoCmd = {"echo"};
	echoCmd.f = &echo;
	
	commands[0] = echoCmd;
	//commands[1] = NULL;
}


void append(char c) {
	if (currPos < BUFFER_SIZE) {
		shellBuffer[currPos++] = c;
		writeInVideo(&c, 1);
		if (c == '\n') {
			//excecuteCmd();
			cleanBuffer();
		}
	}
}

void excecuteCmd() {

}

void cleanBuffer() {
	currPos = 0;
	shellBuffer[0] = '\0';
}

void echo() {
}
