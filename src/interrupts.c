#include "../include/interrupts.h"

int tickpos=-2;
int ticks = 0;

//Timer Tick
void int_08() {
    char *video = (char *) 0xb8000;
	ticks++;
	if(ticks == 18) {
	    video[(tickpos+=2) % (25 * 80 * 2)]=65 + (tickpos/2) % 26;
		ticks = 0;
	}
}

//Keyboard
void int_09() {

}
