#include "../include/interrupts.h"

//Timer Tick
void int_08() {
}

//Keyboard
void int_09() {
	handleScanCode(inb(0x60));
	if (IS_CTRL() && IS_ALT() && IS_DEL()) {
		_reset();
	}
	return;
}

void int_80(int sysCallNumber, void ** args) {
	switch(sysCallNumber) {
		case SYSTEM_WRITE:
			sysWrite((int) args[0], args[1], (int)args[2]);
			break;
		case SYSTEM_READ:
			sysRead((int) args[0], args[1],(int)args[2]);
			break;
		default:
			break;
	}
}

