#include "../include/shell.h"

void excecuteCmd(char* buffer);
int parse_cmd(char* buffer);
int execute(int cmdId);
char** getArguments(char* buffer, int* argc);

char* argv[MAX_ARG_DIM];
int currPos;
char shellBuffer[BUFFER_SIZE];

cmd_table_entry cmd_table[] = {
	{"help", 			HELP_HELP, help_cmd},
	{"restart", 		HELP_RESTART, restart_cmd},
	{"clear", 			HELP_CLEAR, clear_cmd},
	{"getCPUspeed", 	HELP_GETCPUSPEED, getCPUspeed_cmd},
	{"countDown", 		HELP_COUNTDOWN, countDown_cmd},
	{"resetPit", 		HELP_RESETPIT, resetPit_cmd},
	{"setPit", 			HELP_SETPIT, setPit_cmd},
	{"random", 			HELP_RANDOM, random_cmd},
	{"echo", 			HELP_ECHO, echo_cmd},
	{"setAppareance",	HELP_ECHO, setAppearance_cmd},
	{"test", "", test_cmd},
	{"asd", "", asd_cmd},
	{"", "", NULL}
};

void initShell() {
	cleanBuffer();
	printf(SHELL_TEXT);
	int* i = getIrq0CountPointer();
	*i = 0;
	isTesting = FALSE;
}


void updateShell() {
	if (IS_CTRL() && IS_ALT() && IS_DEL()) {
		_reset();
	}
	if (bufferIsEmpty()) {
		return;
	}
	char c = getKeyFromBuffer();
	if (currPos >= BUFFER_SIZE) {
		return;
	}
	if (c == '\n') {
		printf("\n");
		excecuteCmd(shellBuffer);
		printf(SHELL_TEXT);
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
		printf("\n");
	} else if(buffer[0]!='\0') {
		printf("\n\tUnknown command\n");
	}
}


//FIXME: comandos como resetBLABLABVLA se ejecutan ya que matchea con reset.
int parse_cmd(char* buffer) {
	int i, cmdLength = -1, aux;
	int match = -1;

	for(i = 0; cmd_table[i].func != NULL; i++) {
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

cmd_table_entry* getCmdsTable() {
	return cmd_table;
}

int getCmdIndex(char * cmdName) {
	int i;
	for( i=0; cmd_table[i].func != NULL; i++) {
		if (strcmp(cmdName, cmd_table[i].name) == 0) {
			return i;
		}
	}
	return -1;
}


