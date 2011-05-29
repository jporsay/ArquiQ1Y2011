#include "../include/keyboard.h"

unsigned char lcase[60] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',
  'm', ',', '.', '/',   0, /* Right shift */
  '*',
    0,	/* Alt */
  ' '	/* Space bar */
};

unsigned char ucase[60] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
 '"', '~',   0,		/* Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',
  'M', '<', '>', '?', 0, /* Right shift */
  '*',
    0, /* Alt */
  ' ' /* Space bar */
};


int tickpos = -2;
char handleScanCode(unsigned char scanCode) {
	char c = -1;
	if (!checkSpecialKey(scanCode)) {
		if (IS_MAKE(scanCode)) {
			c = translateSc(CLEAR_BREAK_BIT(scanCode));
		}
	}
	return c;
}

int checkSpecialKey(unsigned char scanCode) {
	int ret = TRUE;
	
	if(IS_ESCAPE()) {
		switch (scanCode) {
			case 0x53:
				kbFlags |= DEL;
				break;
			case 0xD3:
				kbFlags &= ~DEL;
				break;
			default:
				break;
		}
		kbFlags &= ~ESCAPE;
		return TRUE;
	}
	
	switch (scanCode) {
		/* Shifts */
		case 0x2A:
			kbFlags |= UCASE;
			break;
		case 0xAA:
			kbFlags &= ~UCASE;
			break;
		case 0x36:	
			kbFlags |= UCASE;
			break;
		case 0xB6:
			kbFlags &= ~UCASE;
			break;
			
		/* Ctrls */
		case 0x1D:
			kbFlags |= CTRL;
			break;
		case 0x9D:
			kbFlags &= ~CTRL;
			break;
			
		/* Alts */
		case 0x38:
			kbFlags |= ALT;
			break;
		case 0xB8:
			kbFlags &= ~ALT;
			break;
		
		/* Escaped scan codes */
		case 0xE0:
			kbFlags |= ESCAPE;
			break;
		
		default:
			ret = FALSE;
			break;
	}
	
	return ret;
	
}

char translateSc(unsigned char scanCode) {
		return SHIFT_PRESSED() ? ucase[scanCode] : lcase[scanCode];
}

