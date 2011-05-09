#include "../include/video.h"

void  setCursor(ushort row, ushort col) {
	if (row >= ROWS || row < 0 || col >= COLS || col < 0) {
		return;
	}
	ushort position = (row * 80) + col;

	// cursor LOW port to vga INDEX register
	_outb(0x3D4, 0x0F);
	_outb(0x3D5, (ushort)(position & 0xFF));
	// cursor HIGH port to vga INDEX register
	_outb(0x3D4, 0x0E);
	_outb(0x3D5, (ushort)((position >> 8) & 0xFF));
}

/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen() 
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while (i < TOTAL_VIDEO_SIZE) {
		vidmem[i] = ' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
}
