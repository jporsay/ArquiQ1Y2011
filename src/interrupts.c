#include "../include/interrupts.h"

int tickpos=-2;
int ticks = 0;

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
int par = 0;
void int_09() {
    char *video = (char *) 0xb8000;
	char i = inb(0x60);
	par++; //For some reason i'm reading twice
	if (par % 2) {
    	video[(tickpos+=2) % (25 * 80 * 2)]=65 + (tickpos/2) % 26;
	}
	return;
}
