#include "../include/kasm.h"
#include "../include/defs.h"
DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

/**********************************************
kmain() 
Punto de entrada de código C.
*************************************************/

kmain() 
{

	int i,num;

	/* Borra la pantalla. */ 
	k_clear_screen();
	setCursor(13,40);

	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */
	setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);

	/* Carga de IDTR    */
	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;

	_lidt (&idtr);	

	_Cli();

	/* Habilito interrupcion de timer tick*/
	_mascaraPIC1(NONE & INT_08);
	_mascaraPIC2(NONE);
	_Sti();

	while (1) {
	}
	
}

