#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/kernel.h"

DESCR_INT idt[0x81];			/* IDT de 81h entradas*/
IDTR idtr;						/* IDTR */

/**********************************************
kmain() 
Punto de entrada de código C.
*************************************************/

kmain() 
{

	int i,num;

	/* Borra la pantalla. */ 
	initVideo();

	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */
	setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x09], 0x09, (dword)&_int_09_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x80], 0x80, (dword)&_int_80_hand, ACS_INT, 0);
	/* Carga de IDTR    */
	idtr.base = 0;
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;

	_lidt (&idtr);

	_Cli();

	/* Habilito interrupcion de timer tick*/
	//_mascaraPIC1(INT_08 & INT_09 & INT_80);
	_mascaraPIC1(0x00);
	_mascaraPIC2(NONE);
	_Sti();

	while (1) {
	}
	
}

size_t __read(int fd, void * buffer, size_t count) {
	_SysCall(SYSTEM_READ,fd, buffer, count);
	return count;
}

size_t __write(int fd, const void * buffer, size_t count) {
	_SysCall(SYSTEM_WRITE,fd, buffer, count);
	return count;
}

void _memcpy(void* from, void* to, size_t nbytes) {
	size_t i;
	for (i = 0; i < nbytes; i++) {
		* ((char *)to + i) = * ((char *)from + i);
	}
}

