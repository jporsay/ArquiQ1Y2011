#include "../include/video.h"

void initVideo() {
	video.address = (char*)VIDEO_ADDRESS;
	setVideoColor(BLACK, GREEN);
	cls();
	setOffset(0);
	setCursor(0, 0);
}

void dummyWrite(char ascii) {
	video.address[getOffset()] = ascii;
}

void writeInVideo(char *string, size_t count) {
	int i = 0;
	while (i < count) {
		char ascii = string[i];
		if (!specialAscii(ascii)) {
			dummyWrite(ascii);
		
			if (getOffset() == TOTAL_VIDEO_SIZE - 2) {
				scroll(1);
				setPosition(getCurrRow(), 0);
			}
		
			setOffset(getOffset() + 2);
			setCursor(getCurrRow(), getCurrColumn());
		}
		i++;
	}
	return;
}

void scroll(char lines) {
	
	int i;
	int start = getCurrRow();
	for (i = lines; i <= start; i++) {
		copyRow(i, i - lines);
	}
	
	clearLinesRange(start - lines + 1, start);
	
}

void copyRow(int source, int dest) {
	if (dest < 0) {
		return;
	}
	int posBak = getOffset();
	
	int column;
	for (column = 0; column < COLUMNS; column++) {
		setPosition(source, column);
		int index = getOffset();
		setPosition(dest, column);
		video.address[getOffset()] = video.address[index];
	}
	
	setOffset(posBak);
}

void clearLinesRange(int from, int to) {
	to = to >= ROWS ? ROWS - 1 : to;
	int i;
	for (i = from; i <= to; i++) {
		clearRow(i);
	}
}

void clearToEnd(int from) {
	clearLinesRange(from, ROWS);
}

void clearRow(int row) {
	int i;
	int offsetBackup = getOffset();
	
	for (i = 0; i < COLUMNS; i++) {
		setPosition(row, i);
		video.address[getOffset()] = ' ';
	}
	
	setOffset(offsetBackup);
	
}

void setPosition(int row, int column) {
	int offset;
	if ( 0 <= row && row < ROWS && 0 <= column && column < COLUMNS) {
		offset = (row * COLUMNS) + column;
	} else if (row >= ROWS) {
		row = 24;
		offset = row * COLUMNS;
		scroll(1);
	}
	
	setOffset(offset * 2);
}

/*
	Columns actual de fin de la ultimo caracter
*/
int getCurrRow() {
	return (getOffset() / 2) / COLUMNS; 
}

/*
	Fila actual de fin de la ultimo caracter
*/
int getCurrColumn() {
	return (getOffset() / 2) % COLUMNS; 
}

void setVideoBackground(byte color) {
	video.bgColor = color;
}

void setVideoForeground(byte color) {
	video.fgColor = color;
}

void setVideoColor(byte bg, byte fg) {
	setVideoForeground(fg);
	setVideoBackground(bg);
}

char getVideoColor() {
	return (video.bgColor << 4) | (video.fgColor & 0x0F);
}

int getOffset() {
	return video.offset;
}

void setOffset(int offset) {
	if (offset < 0) {
		offset = 0;
	}
	video.offset = offset;
}

/*
	Setea el cursor en la posicion row, column.
*/
void setCursor(ushort row, ushort column) {
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
void cls() 
{
	unsigned int i = 0;
	while (i < TOTAL_VIDEO_SIZE) {
		video.address[i] = ' ';
		i++;
		video.address[i] = getVideoColor();
		i++;
	};
}

int specialAscii(char ascii) {
	int ret = TRUE;
	switch (ascii) {
		case '\n':
			setPosition(getCurrRow() + 1, 0);
			setCursor(getCurrRow(), getCurrColumn());
			break;
		case '\t': //Tab
			break;
		case '\b': //Backspace
			setOffset(getOffset() - 2);
			dummyWrite(' ');
			setCursor(getCurrRow(), getCurrColumn());
			break;
		default:
			ret = FALSE;
			break;
	}
	
	return ret;
}

