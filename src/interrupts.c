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
