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
	puts("\nAvailable commands:\n\thelp,\n\treset,\nclear,\n\tCPUspeed,\n\tcountDown,\n\tresetPit,\n\tsetPit,\n\trandom,\n\techo.\n");
}

int setPit_cmd(int argc, char *argv[]) {
}

int resetPit_cmd(int argc, char *argv[]) {
}

int countDown_cmd(int argc, char *argv[]) {
}

int CPUspeed_cmd(int argc, char *argv[]) {
}

int random_cmd(int argc, char *argv[]) {
	printf("%d", random());
}

void dummyFunc(int eax, int ebx) {
	printf("%d %d\n", eax, ebx);
}

int test_cmd(int argc, char *argv[]) {
	double cpuspeed = getCpuSpeed();
	printf("Detected CPU speed: %u\n", (unsigned int)cpuspeed);
	
}

int asd_cmd(int argc, char *argv[]) {
	printf("\nIngrese un caracter: ");
	printf("%c", getchar());
}


