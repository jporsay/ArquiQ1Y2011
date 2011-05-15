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

/* Inicializa el struct del video */
void initVideo();

/* writes in video a string */
void writeInVideo(char *string, size_t count);

/* Setea el cursor en la posición deseada */
void setCursor(ushort row, ushort col);

void k_clear_screen();

/* Chequea si el parámetro es un ascii especial */
int specialAscii(char ascii);

/* Setea la posición en la cual va escribirse en la pantalla */
void setPosition(int row, int column);

/* Devuelve la columna en la cual se va a escribir */
int getCurrRow();

/* Devuelve la fila en la cual se va a escribir */
int getCurrColumn();

/* Escribe un char directamente en la memoria */
void dummyWrite(char ascii);

/* Setea el color del texto que se escribirá después */
void setVideoForeground(byte color);

/* Setea el color del fondo del caracter siguiente */
void setVideoBackground(byte color);

/* Setea el color de fondo y del texto del próximo caracter */
void setVideoColor(byte bg, byte fg);

/* Devuelve el color de fondo y el texto listo para ser impreso en la memória
 * de la pantalla
 */
char getVideoColor();

/* Sube la pantalla n líneas */
void scroll(char lines);

/* Setea el offset con respecto al inicio de la memoria de video */
void setOffset(int offset);

/* Devuelve el offset con respecto al inicio de la memoria de video */
int getOffset();

/* Copia una linea de "source" a "dest" */
void copyRow(int source, int dest);

/* limpia n líneas en un rango */
void clearLinesRange(int from, int to);

/* limpia desde la línea n hasta el final de la pantalla */
void clearToEnd(int from);

/* limpia una linea */
void clearRow(int row);
#endif
