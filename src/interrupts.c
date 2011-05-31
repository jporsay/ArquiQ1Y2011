#include "../include/interrupts.h"

void prtAvg();

int getIrq0Count() {
	int count2 = count;
	return count2;
}

int *getIrq0CountPointer() {
	return &count;
}

//Timer Tick
void int_08() {
	if (isTesting == TRUE) {
		if (pos < TT_MEDITIONS) {
			int speed = count / 182.0;
			resp[pos++] = speed;
			count = 0;
		} else {
			prtAvg();
			isTesting = FALSE;
		}
	}
}

void prtAvg() {
	int total = 0;
	int i;
	for (i=0; i < 100; i++) {
		total += resp[i];
	}
	printf("TOTAL: %d\n", (total / TT_MEDITIONS));
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

