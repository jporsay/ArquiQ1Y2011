/*********************************************
kasm.h

************************************************/

#include "defs.h"


unsigned int _read_msw();

void _outb(ushort port, ushort data);
unsigned char _inb(ushort port);

void _lidt (IDTR *idtr);

void _mascaraPIC1 (byte mascara);  /* Escribe mascara de PIC1 */
void _mascaraPIC2 (byte mascara);  /* Escribe mascara de PIC2 */

void _Cli(void);        /* Deshabilita interrupciones  */
void _Sti(void);	 /* Habilita interrupciones  */

void _reset();

void _int_08_hand();	/* Timer tick */
void _int_09_hand();	/* Keyboard */
void _debug (void);

