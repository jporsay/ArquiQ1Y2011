#include "../include/command.h"

int echo_cmd(int argc, char *argv[]) {
	int i;
	if (argc > 0) {
		for( i = 0; i < argc; i++) {
			printf("%s ", argv[i]);
		}
	}
	video.offset = 0;
}

int restart_cmd(int argc, char *argv[]) {
	_reset();
}

int clear_cmd(int argc, char *argv[]) {
	cls();
}

int help_cmd(int argc, char *argv[]) {
	puts("Available commands:\n\thelp,\n\treset,\nclear,\n\tCPUspeed,\n\tcountDown,\n\tresetPit,\n\tsetPit,\n\trandom,\n\techo.\n");
}

int setPit_cmd(int argc, char *argv[]) {
}

int resetPit_cmd(int argc, char *argv[]) {
	puts("\nreset Pit!\n");
}

int countDown_cmd(int argc, char *argv[]) {
}

int CPUspeed_cmd(int argc, char *argv[]) {
}

int random_cmd(int argc, char *argv[]) {
	puts("\n583012830921\n");
}

int test_cmd(int argc, char *argv[]) {
	float a = (float)321;
	printf("I have %f years and %s\n", a, "gonzalo is gay!");
}


