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

int test_cmd(int argc, char *argv[]) {
	setPitInterval(100);
	unsigned int low, low1, high, high1;
	setTestConditions(100);
	rdtsc(&low, &high);
	while (getCounter() != 0) {
		printf("test: %d\n", *counter);
	}
	rdtsc(&low1, &high1);
	printf("start: %d%d\n", high, low);
	printf("end: %d%d\n", high1, low1);
	printf("total: %d%d\n", high1 - high, low1 - low);
	setPitInterval(0);
}

int asd_cmd(int argc, char *argv[]) {
	printf("\nIngrese un caracter: ");
	printf("%c", getchar());
}


