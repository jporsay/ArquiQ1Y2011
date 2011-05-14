#include "../include/video.h"

int position=0;

void write(char ascii) {
	char *video = (char *) VIDEO_ADDRESS;
	video[position] = ascii;
	position+=2;
	if (position == TOTAL_VIDEO_SIZE) {
		k_pushOneline();
	}
	setCursor(getCurrRow(), getCurrColumn());
}

void k_pushOneline() {
    char *video = (char *) VIDEO_ADDRESS;
	int row, column;
	for (row = 0; row < ROWS - 1; row++) {
		for (column = 0; column < COLUMNS ; column++) {
			setPosition(row, column);
			int newIndex = position;
			setPosition(row + 1, column);
			video[newIndex] = video[position];
		}
	}
	for(column = 0; column < COLUMNS; column++) {
		setPosition(ROWS - 1, column);
		video[position] = ' ';
	}
	setPosition(ROWS - 1, 0);
}

void setPosition(int row, int column) {
	if ( 0 <= row && row < ROWS && 0 <= column && column < COLUMNS) {
		position = (row * COLUMNS) + column;
		position *= 2;
	} else {
		position = 0;
	}
}

/*
	Columns actual de fin de la ultimo caracter
*/
int getCurrRow() {
	return (position/2) / COLUMNS; 
}

/*
	Fila actual de fin de la ultimo caracter
*/
int getCurrColumn() {
	return (position/2) % COLUMNS; 
}


/*
	Setea el cursor en la posicion row, column.
*/
void  setCursor(ushort row, ushort column) {
	if (row >= ROWS || row < 0 || column >= COLUMNS || column < 0) {
		return;
	}
	ushort position = (row * COLUMNS) + column;

	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (ushort)(position & 0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (ushort)((position >> 8) & 0xFF));
}

/*
Borra la pantalla en modo texto color.
*/
void k_clear_screen() 
{
	char *vidmem = (char *) VIDEO_ADDRESS;
	unsigned int i = 0;
	while (i < TOTAL_VIDEO_SIZE) {
		vidmem[i] = ' ';
		i++;
		vidmem[i] = WHITE_TXT;
		i++;
	};
}

