#include "../include/interrupts.h"

int counter = 0;
int booool = 0;

//Timer Tick
void int_08() {
	if (counter > 100 && !booool) {
		setPitInterval(100);
		booool = 1;
		counter = 0;
	}
	if (booool == 1) {
		if (counter == 100) {
			putc('s');
			counter = 0;
		}
	} else {
		putc('i');
	}
	counter++;
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
	
	return;
}

