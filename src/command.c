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
	char * helpMenu = "\nList of commands:\n  clear\n  echo\n  reset\n  help\n";
	myPrint(helpMenu);
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
}

