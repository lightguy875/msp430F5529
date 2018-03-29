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
		call #MAIOR_16
		jmp $
MAIOR_16:
	 	mov	#0x0,R6
		mov	@R5,R10
		mov	R10,R12
		mov	#0x0,R7
		incd	R5
		mov 	R5,R13
		jmp     sub2
sub2:
		mov @R5,R11
		cmp R6,R11
		jhs negativo
		clrn
		incd R5
		dec R10
		jz	sub3
		clrz
		jmp sub2
sub3:
		cmp @R13,R6
		jz zero
		clrz
		dec R12
		jz fim
		clrz
		incd R13
		jmp sub3


zero:
		inc	R7
		dec R12
		jz fim
		clrz
		incd R13
		jmp sub3
negativo:
		mov @R5,R6
		dec R10
		incd R5
		clrn
		jmp sub2
fim:
		ret
;Segmento de vetor
		.data
; Declarar vetor com 19 elementos [LuisEduardoLuzSilva]
vetor: .word 10,'LU','IS','ED','UA','RD','OL','UZ','SI','ZZ','A'
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
            
