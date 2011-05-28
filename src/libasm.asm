GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand
GLOBAL	_int_09_hand
GLOBAL _int_80_hand
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug
GLOBAL	_outb
GLOBAL	_inb
GLOBAL _reset
GLOBAL _cpuIdTest
GLOBAL _SysCall
EXTERN  int_08
EXTERN	int_09
EXTERN	int_80

SECTION .text


_Cli:
	cli	; limpia flag de interrupciones
	ret

_Sti:

	sti	; habilita interrupciones por flag
	ret

_outb:
	push	ebp
	mov		ebp, esp
	mov		edx, [ss:ebp+8] ;Grab data
	mov		eax, [ss:ebp+12] ;Grab port
	out		dx, ax
	pop		ebp
	retn

_inb:
	push	ebp
	mov		ebp, esp
	mov		dx, [ss:ebp+8] ;Grab port
	in		ax, dx
	mov		esp, ebp
	pop		ebp
	retn

_mascaraPIC1:			; Escribe mascara del PIC 1
	push	ebp
	mov		ebp, esp
	mov		ax, [ss:ebp+8]  ; ax = mascara de 16 bits
	out		21h,al
	pop		ebp
	retn

_mascaraPIC2:			; Escribe mascara del PIC 2
	push	ebp
	mov		ebp, esp
	mov		ax, [ss:ebp+8]  ; ax = mascara de 16 bits
	out		0A1h,al
	pop		ebp
	retn

_read_msw:
	smsw	ax		; Obtiene la Machine Status Word
	retn


_lidt:				; Carga el IDTR
	push	ebp
	mov		ebp, esp
	push	ebx
	mov		ebx, [ss: ebp + 6] ; ds:bx = puntero a IDTR
	rol		ebx,16
	lidt	[ds: ebx]          ; carga IDTR
	pop		ebx
	pop		ebp
	retn


_int_08_hand:				; Handler de INT 8 ( Timer tick)
	push	ds
	push	es                      ; Se salvan los registros
	pusha                           ; Carga de DS y ES con el valor del selector
	mov		ax, 10h			; a utilizar.
	mov		ds, ax
	mov		es, ax
	call	int_08
	mov		al,20h			; Envio de EOI generico al PIC
	out		20h,al
	popa
	pop		es
	pop		ds
	iret

_int_09_hand:				; Handler de INT 9 ( Teclado )
	push	ds
	push	es
	pusha
	call	int_09
	mov		al,20h			; Envio de EOI generico al PIC
	out		20h,al
	popa
	pop		es
	pop		ds
	iret

_int_80_hand:				; Handler de INT 80h
	push ebp
	mov ebp, esp			;StackFrame
	
	push edx
	push ecx
	push ebx
	
	push esp				; Puntero al array de argumentos
	push eax				; Numero de Systemcall
	call int_80
	mov	al,20h			; Envio de EOI generico al PIC
	out	20h,al
	pop eax
	pop esp

	pop ebx
	pop ecx
	pop edx
	
	mov esp, ebp
	pop ebp
	iret

_SysCall:
	push ebp
	mov ebp, esp
	pusha

	mov eax, [ebp + 8] ; Syscall number
	mov ebx, [ebp + 12]; file descriptor
	mov ecx, [ebp + 16]; buffer
	mov edx, [ebp + 20]; count
	
	int 80h

	popa
	mov esp, ebp
	pop ebp
	ret

_reset:
.wait1:
	in		al, 64h
	test	al, 02h
	jne		.wait1
	mov		al, 0FEh
	out		64h, al
	ret

_cpuIdTest:
	pushfd ; get
	pop eax
	mov ecx, eax ; save
	xor eax, 0x200000 ; flip
	push eax ; set
	popfd
	pushfd ; and test
	pop eax
	xor eax, ecx ; mask changed bits
	shr eax, 21 ; move bit 21 to bit 0
	and eax, 1 ; and mask others
	push ecx
	popfd ; restore original flags
	ret

; Debug para el BOCHS, detiene la ejecución
; Para continuar colocar en el BOCHSDBG: set $eax=0


_debug:
	push    bp
	mov     bp, sp
	push	ax
vuelve:
	mov     ax, 1
	cmp	ax, 0
	jne	vuelve
	pop	ax
	pop     bp
	retn


