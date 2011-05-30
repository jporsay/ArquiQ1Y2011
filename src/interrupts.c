#include "../include/interrupts.h"

void prtProm();

int getIrq0Count() {
	int count2 = count;
	return count2;
}

int *getIrq0CountPointer() {
	return &count;
}

//Timer Tick
void int_08() {
	if (pos < 100) {
		int speed = count / 18.2;
		printf("%d\n", speed);
		resp[pos] = speed;
		count = 0;
		pos++;
	} else {
		prtProm();
	}
}

void prtProm() {
	int total = 0;
	int i;
	for (i=0; i < 100; i++) {
		total += resp[i];
	}
	printf("TOTAL: %d\n", (total / 100));
}

//Keyboard
void int_09() {
	handleScanCode(inb(0x60));
}

void int_80(int sysCallNumber, void ** args) {
	switch(sysCallNumber) {
		case SYSTEM_WRITE:
			sysWrite((int) args[0], args[1], (int)args[2]);
			break;
		case SYSTEM_READ:
			sysRead((int) args[0], args[1],(int)args[2]);
			break;
	}
}

