#include "../include/interrupts.h"

int getIrq0Count() {
	int count2 = count;
	return count2;
}

int *getIrq0CountPointer() {
	return &count;
}

//Timer Tick
void int_08() {
	count++;
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

