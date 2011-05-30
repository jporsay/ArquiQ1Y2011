#include "../include/command.h"

int echo_cmd(int argc, char *argv[]) {
	int i;
	if (argc > 0) {
		for( i = 0; i < argc; i++) {
			printf("%s ", argv[i]);
		}
	}
}

int restart_cmd(int argc, char *argv[]) {
	_reset();
}

int clear_cmd(int argc, char *argv[]) {
	cls();
}

int help_cmd(int argc, char *argv[]) {
	int cmdIndex;
	if (argc == 1) {
		cmdIndex = getCmdIndex(argv[0]);
		if (cmdIndex != -1) {
			printf("\n%s\n", getCmdsTable()[cmdIndex].help);
		} else {
			printf("\nCommand not found\n");
		}
	} else if (argc == 0) {
		int i;
		printf("\nAvailable commands:\n\n");
		for( i=0; getCmdsTable()[i].func != NULL; i++) {
			printf("%s\n", getCmdsTable()[i].name);
		}
		printf("\nType in help \"cmdName\" to see the help menu for that command.\n");
	}
}

int setPit_cmd(int argc, char *argv[]) {
}

int resetPit_cmd(int argc, char *argv[]) {
}

int countDown_cmd(int argc, char *argv[]) {
}

int getCPUspeed_cmd(int argc, char *argv[]) {
	printf("Beginning IPS calculation...\n");
	isTesting = TRUE;
	count = 0;
	pos = 0;
	while(isTesting == TRUE) {
		count++;
	}
}

int random_cmd(int argc, char *argv[]) {
	printf("%d", random());
}

void dummyFunc(int eax, int ebx) {
	printf("%d %d\n", eax, ebx);
}

int test_cmd(int argc, char *argv[]) {
	int cpuspeed = _getCpuSpeed();
	printf("Detected CPU speed: %i\n", (int)cpuspeed);
}

int asd_cmd(int argc, char *argv[]) {

}

int setAppearance_cmd(int argc, char *argv[]) {
	if (argc != 2) {
		printf("You need to call this function with 2 colors\n");
	} else {
		char* foreGround = argv[0];
		char* backGround = argv[1];
		
		int fg = parseHexa(foreGround[0]);
		int bg = parseHexa(backGround[0]);
		printf("%d  %d\n", fg, bg);
		if (strlen(foreGround) != 1 || strlen(backGround) != 1 || fg == -1
			|| bg == -1) {
			printf("Both arguments must be a hexadecimal number between 0 \
				and F\n");
			return;
		}
		setVideoColor(bg, fg);
	}
}


