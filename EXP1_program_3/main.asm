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
P3:
		mov #vetor,R5
		call #init
		jmp $
		nop
init:
		mov.b @R5+,R10
		mov.b #0,R6
		mov.b #0,R7
		call #M2M4

M2M4:
		jz end
		mov.b @R5,R8
		mov.b @R5+,R9
		jmp mul2
		nop


mul2:
		sub.b #02,R8
		jz contR6
		jc mul2
		jmp mul4
		nop


mul4:
		sub.b #04,R9
		jz contR7
		jc mul4
		sub.b #01,R10
		jmp M2M4
		nop


contR6:
		inc R6
		jmp mul4
		nop
contR7:
		inc R7
		sub #01,R10
		jmp M2M4
		nop
end:
		jmp $
		nop
;----------------------------------------------------------------------------
; Segmento de dados inicializados (0x2400)
;----------------------------------------------------------------------------
					.data
; Declarar vetor
vetor: .byte 19,"LuisEduardoLuzSilva"

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
            
