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
P6:
		mov #vetor,R5
		call #Ordena1
		jmp $
		nop
Ordena1:

		mov.b @R5+,R6; Move para a quantidade de dados que o vetor tem
		mov R5,R8 ; Aponta para o inicio dos dados
		sub.b #0x1,R6; Desconta um dado por causa do jump do carry
		mov.b R6,R7
		mov.b R7,R12 ; Valor de repetições incluindo zero
		jmp sub2 ; Inicio da subrotina que efetuará a contagem realmente
Ordena2:
		dec R6
		jz end
		mov.b R12,R7
		mov R8,R5
		jmp sub2

sub2:
		mov R5,R11
		mov.b @R5+,R9
		mov.b @R5,R10
		cmp.b R10,R9
		jge Trocadados
		dec R7
		jz Ordena2
		jmp sub2

Trocadados:
		mov.b R10,0(R11)
		mov.b R9,1(R11)
		dec R7
		jz Ordena2
		jmp sub2
end:
		ret

                                            
;----------------------------------------------------------------------------
; Segmento de dados inicializados (0x2400)
;----------------------------------------------------------------------------
					.data
; Declarar vetor
vetor: .byte 36,"LuisEduardoLuzSilvaLuisFelipeFreitas"
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
            
