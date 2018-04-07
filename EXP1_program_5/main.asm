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
MATR		.set 	0x4
P5:
		mov #vetor,R5
		call #ASC_W16
		jmp $
ASC_W16:
		mov @R5,R14
		mov #0x0,R6
		mov #MATR,R7
		mov #0x30,R8 ; variavel com o menor valor representativo para numero
		mov #0x41,R9 ; variavel com o menor valor representativo para letra
		mov #0xA,R10  ; variavel para os valores de numeros
		mov #0x6,R11  ; variavel para os valores de letra maiuscula
		mov #0x4,R12 ; variavel para as rotacoes
		mov #0x0,R13 ; variavel para a contagem de rotacao
		jmp comnumb
comnumb:
		cmp R8,R14
		jz confirmanum
		clrz
		dec R10
		jz comlet
		clrz
		inc R8
		jmp comnumb


confirmanum:
			sub #0x30,R14
			add R14,R6
			jmp rot


comlet:
		cmp R9,R14
		jz confirmalet
		clrz
		dec R11
		jz end1
		clrz
		inc R9
		jmp comlet
confirmalet:
		sub #0x37,R14
		add R14,R6
		jmp rot

rot:
		cmp #0x3,R13
		jz end2
		RLA R6
		dec R12
		jz increme
		clrz
		jmp rot



increme:
		incd R5
		inc R13
		mov #0x30,R8
		mov #0x41,R9
		mov #0x4,R12
		mov #0xA,R10
		mov #0x6,R11
		mov @R5,R14
		jmp comnumb
end1:
		clrc
		ret
end2:
		setc
		ret


;----------------------------------------------------------------------------
; Segmento de dados inicializados (0x2400)
;----------------------------------------------------------------------------
					.data
; Declarar vetor
vetor: .word 0x33,0x41,0x41,0x35

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
            
