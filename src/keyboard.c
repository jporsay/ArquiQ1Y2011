#include "../include/keyboard.h"

int tickpos=-2;

void handleKeyPress(char scanCode) {
    char *video = (char *) 0xb8000;
	video[(tickpos+=2) % (25 * 80 * 2)]=65 + (tickpos/2) % 26;
}

void handleKeyRelease(char scanCode) {
}
