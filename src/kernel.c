#include "../include/kasm.h"
#include "../include/defs.h"
DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

int tickpos=-2;

void int_08() {

    char *video = (char *) 0xb8000;
    video[(tickpos+=2) % (25 * 80 * 2)]=65 + (tickpos/2) % 27;

}

void  setCursor(ushort row, ushort col)
{
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

        _mascaraPIC1(0xFE);
        _mascaraPIC2(0xFF);
        
	_Sti();

        while(1)
        {
        }
	
}

