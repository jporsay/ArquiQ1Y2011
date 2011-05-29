#include "../include/command.h"

int echo_cmd(int argc, char *argv[]) {
	puts("\necho execution!\n");
}

int reset_cmd(int argc, char *argv[]) {
	puts("\nreset execution!\n");
}

int clear_cmd(int argc, char *argv[]) {
	puts("\nclear execution!\n");
}

int help_cmd(int argc, char *argv[]) {
	myPrint("Comandos: ");
	char c = argc + '0';
	putc(c);
	myPrint("\n---\n");
	int i;
	for( i = 0; i < argc; i++) {
		myPrint(argv[i]);
		myPrint("\n");
	}
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


