#include "../include/keyboard.h"
#include "../include/video.h"

void handleKeyPress(char scanCode) {
}

void handleKeyRelease(char scanCode) {
	write(scanCode);
}



