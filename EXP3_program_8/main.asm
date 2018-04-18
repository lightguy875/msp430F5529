;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
DELAY .equ 5000


;Equate 32768
PS1 .equ 0x2400
PS2	.equ 0x2401
ABT .equ 0
FECH	.equ 1
;Delay: mov R10,#RBT
;LB1: dec R10
;SET:
;	BIS.B #bit0,&P1DIR ; S1-LED1 P1.0 = saída
;	BIC.B #bit0,&P1OUT ; LED1 apagado
;	BIS.B #bit0,&P1OUT ; LED1 aceso
;	BIC.B #bit1,&P2DIR ; S1 P2.1 = entrada
;	BIS.B #bit1,&P2IN ; ler chave
;	jnz LA ; chave aberta = 1, fechada = 0
	;ação ao acionar a chave
;LF: BIT.B #BIT1,&P2IN ; ler chave
	;jz LF ; chave fechada
;	jmp LA
Main:
		BIC.B #BIT1,&P1SEL ; certeza que esta usando GPIO
		BIC.B #BIT1,&P1DIR ; setar p1.1 como entrada
		BIS.B #BIT1,&P1REN ; Ligar pull-up/down resistor
		BIS.B #BIT1,&P1OUT ; Configurar resistor como pull-up
		BIC.B #BIT7,&P4SEL ; certeza que estamos usando GPIO
		BIS.B #BIT7,&P4DIR ; Setar P4.7 como saida
		BIC.B #BIT7,&P4REN ; Desativar resistor na saida
		BIC.B #BIT7,&P4OUT ; setar led do p4.7 com 0

		BIC.B #BIT0,&P1SEL ; certeza de que esta usando GPIO
		BIS.B #BIT0,&P1DIR ; SETAR P1.0 como saida
		BIC.B #BIT0,&P1REN ; Desativar resistor na saida
		BIC.B #BIT0,&P1OUT ; começa com 0 o valor de p1.out
		mov #0,R9
		mov #0,R8

LoopF:
		mov #DELAY,R10
		BIT.B #BIT1,&P1IN
		jnz	cont1
		jz	cont2
		jmp LoopF
		NOP
contdelay:
			dec R10
			jz LoopF
			jmp contdelay

cont1:
		mov #0,R9
		jmp contdelay
		Nop
cont2:
		cmp #0,R9
		jz contefect
		jmp contdelay
contefect:
		inc R8
		mov #1,R9
        jmp	contled
        Nop

contled:
		cmp #1,R8
		jz contled1
		cmp #2,R8
		jz contled2
		cmp #3,R8
		jz contled3
		cmp #4,R8
		jz contled4
contled1:
		bis.b #BIT7,&P4OUT
		bic.b #BIT0,&P1OUT
		jmp contdelay

contled2:
		bic.b #BIT7,&P4OUT
		bis.b #BIT0,&P1OUT
		jmp contdelay
contled3:
		bis.b #BIT7,&P4OUT
		bis.b #BIT0,&P1OUT
		jmp contdelay
contled4:
		bic.b #BIT7,&P4OUT
		bic.b #BIT0,&P1OUT
		mov #0,R8
		jmp contdelay
;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
