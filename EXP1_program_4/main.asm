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
MATR	.set 15013
P3:
		mov #vetor,R5
		call #W16_ASC
		jmp $

W16_ASC:
		mov #MATR,R6
		mov R6,R7

presig4:

		mov #0x0B,R9
		jmp sig4

sig4:
		RRA R7
		dec R9
		jc sig4

analyse4:
		sub #0xA,R7
		jn  addnumber4
		jc	addletter4
		jmp presig3
addnumber4:
		add #0x3A,R7
		mov R7,0(R5)
		jmp presig3
addletter4:
		add #0x41,R7
		mov R7,0(R5)
		jmp presig3
presig3:
		mov R6,R7
		mov #0x05,R10
		mov #0xB,R9
		jmp sig3l

sig3l:
		RLA R7
		dec R10
		jc sig3l
sig3r:
		clrn
		clrc
		RRC R7
		dec R9
		jc sig3r
analyse3:
		sub #0xA,R7
		jn  addnumber3
		jc	addletter3
		jmp presig2
addnumber3:
		add #0x3A,R7
		mov R7,2(R5)
		jmp presig2
addletter3:
		add #0x41,R7
		mov R7,2(R5)
		jmp presig2
presig2:
		mov R6,R7
		mov #0x07,R10
		mov #0xB,R9
		jmp sig2l
sig2l:
		RLA R7
		dec R10
		jc sig2l
		jmp sig2r
sig2r:
		clrn
		clrc
		RRC R7
		dec R9
		jc sig2r
analyse2:
		sub #0xA,R7
		jn  addnumber2
		jc	addletter2
		jmp presig1
addnumber2:
		add #0x3A,R7
		mov R7,4(R5)
		jmp presig1
addletter2:
		add #0x41,R7
		mov R7,4(R5)
		jmp presig1
presig1:
		mov R6,R7
		mov #0x0C,R10
		mov #0xC,R9
		jmp sig1l
sig1l:
		RLA R7
		dec R10
		jc sig1l
		jmp sig1r
sig1r:
		clrn
		clrc
		RRC R7
		dec R9
		jc sig1r
analyse1:
		sub #0xA,R7
		jn  addnumber1
		jc	addletter1
		ret
addnumber1:
		add #0x3A,R7
		mov R7,6(R5)
		ret
addletter1:
		add #0x41,R7
		mov R7,6(R5)
		ret
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
            
