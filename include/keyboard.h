#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "kasm.h"
#include "defs.h"

#define IS_MAKE(A) ((A) & 0x80)
#define CLEAR_BREAK_BIT(A) ((A) & 0x7F)
#define ESCAPE	0x01
#define UCASE	0x02
#define CTRL	0x04
#define ALT		0x08
#define DEL		0x10
#define SHIFT_PRESSED() (kbFlags & UCASE)

char kbFlags;

void handleScanCode(unsigned char scanCode);
int checkSpecialKey(unsigned char scanCode);
int specialAscii(char ascii);
char translateSc(unsigned char scanCode);
#endif
