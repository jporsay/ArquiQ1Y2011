#include "../include/command.h"

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
	/*myPrint("\nComandos: ");
	char c = argc + '0';
	putc(c);
	myPrint("\n---\n");
	int i;
	for( i = 0; i < argc; i++) {
		myPrint(argv[i]);
		myPrint("\n");
	}*/
}

int setPit_cmd(int argc, char *argv[]) {
}

int resetPit_cmd(int argc, char *argv[]) {
	myPrint("\nreset Pit!\n");
}

int countDown_cmd(int argc, char *argv[]) {
}

int CPUspeed_cmd(int argc, char *argv[]) {
}

int random_cmd(int argc, char *argv[]) {
	myPrint("\n583012830921\n");
}

