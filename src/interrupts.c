#include "../include/interrupts.h"

static inline
unsigned char inb( unsigned short port )
{
    unsigned char ret;
    asm volatile( "inb %1, %0"
                  : "=a"(ret) : "Nd"(port) );
    return ret;
}

//Timer Tick
void int_08() {
}

//Keyboard
void int_09() {
    char *video = (char *) 0xb8000;
	char i = inb(0x60);
	if (i & KEY_RELEASE) {
		i &= 0x7F; //Reset release bit;
		handleKeyRelease(i);
	} else {
		handleKeyPress(i);
	}
	return;
}
