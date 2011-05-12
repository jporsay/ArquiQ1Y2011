#ifndef VIDEO_H
#define VIDEO_H

#include "defs.h"
#include "io.h"

#define ROWS 25
#define COLS 80
#define TOTAL_VIDEO_SIZE ROWS * COLS * 2

#define WHITE_TXT 0x07 // Atributo de video. Letras blancas, fondo negro

void setCursor(ushort row, ushort col);
void k_clear_screen();

#endif
