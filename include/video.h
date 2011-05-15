#ifndef VIDEO_H
#define VIDEO_H

#include "defs.h"
#include "io.h"

#define VIDEO_ADDRESS 0xb8000

typedef struct video_info {
	char* address;
	byte bgColor;
	byte fgColor;
	int offset;
} videoInfo;

videoInfo video;

#define ROWS 25
#define COLUMNS 80
#define TOTAL_VIDEO_SIZE (ROWS * COLUMNS * 2)

#define WHITE_TXT 0x07 // Atributo de video. Letras blancas, fondo negro
void initVideo();
void write(char ascii);
void setCursor(ushort row, ushort col);
void k_clear_screen();
void k_pushOneline();
int specialAscii(char ascii);
void setPosition(int row, int column);
int getCurrRow();
int getCurrColumn();

void setVideoForeground(byte color);
void setVideoBackground(byte color);
void setVideoColor(byte bg, byte fg);
char getVideoColor();
void scroll(char lines);

void setOffset(int offset);
int getOffset();
void copyRow(int dest, int source);

void clearLinesRange(int from, int to);
void clearToEnd(int from);
void clearRow(int row);
#endif
