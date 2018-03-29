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
P1:
		mov	#vetor,R5
		call #Menor
		jmp $
Menor:
	 	mov.b	#0x7F,R6
		mov.b	#0x01,R8
		mov.b	@R5,R10
		mov.b	R10,R12
		mov.b 	#0x0,R7
		inc		R5
		mov 	R5,R13
		jmp     sub2
sub2:
		mov.b @R5,R11
		cmp.b R6,R11
		jn negativo
		clrz
		inc R5
		dec R10
		jz	sub3
		jmp sub2
sub3:
		cmp.b @R13,R6
		jz zero
		clrz
		dec R12
		jz fim
		clrz
		inc R13
		jmp sub3


zero:
		inc	R7
		dec R12
		jz fim
		clrz
		inc R13
		jmp sub3
negativo:
		mov.b @R5,R6
		dec R10
		inc R5
		clrn
		jmp sub2
fim:
		ret
;Segmento de vetor
		.data
; Declarar vetor com 19 elementos [LuisEduardoLuzSilva]
vetor: .byte 19,"LUISEDUARDOLUZSILVA"
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
            
