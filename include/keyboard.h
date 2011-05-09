#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEY_RELEASE 0x80

void handleKeyPress(char scanCode);
void handleKeyRelease(char scanCode);

#endif
