
#include <msp430.h>
#include "pmm.h"
#include "clock.h"

#define ECHO_PIN BIT3  // P1.3
#define LED_PIN BIT0   // P1.0
#define distancia_minima 20  // cm
#define intervalo_de_medida 2048  // ~250 ms

void Espera_trigger() 
{
    // Espera um tempo de 10 micro_segundos    
    __delay_cycles(10);
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;
   int volatile Ultima_conta = 0;
    int volatile distancia = 0;

    
    // Configura led e desliga
    P1DIR |= LED_PIN;
    P1OUT &= ~LED_PIN;

    // configura echo como captura do pino 1.2
    P1DIR &= ~ECHO_PIN;
    P1SEL |= ECHO_PIN;

    // Configura o pino
    TA0CCTL2 = CM_3 | CCIS_0 | SCS | CAP | CCIE;

    // inicia com o intervalo de medida
    TA0CCR0 = intervalo_de_medida;
    TA0CCTL0 = CCIE;

    // ACLOCK CONTÍNUO
    TA0CTL = TASSEL__ACLK | ID__1 | MC__CONTINUOUS | TACLR;



    for (;;)
    {
        Espera_trigger();

        //espera flanco de subida
        while(!(TA0CCTL2 & CCIFG));
        TA0CCTL2 &= ~ CCIFG;

        Ultima_conta = TA0CCR2;

        //espera flanco de decida
        while(!(TA0CCTL2 & CCIFG));
        TA0CCTL2 &= ~ CCIFG;


        distancia = TA0CCR2 - Ultima_conta;

        if (distancia <= distancia_minima)
        {
           // liga o led
            P1OUT |= LED_PIN;
        }
        else
        {/
            // Desliga o led
            P1OUT &= ~LED_PIN;
        }

        // Espera a medida do proximo intervalo
        while(!(TA0CCTL0 & CCIFG));
            TA0CCTL0 &= ~CCIFG;
    }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void) {
    // Medida do intervalo
    TA0CCR0 += intervalo_de_medida;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR (void) {
    // Altera o estado do pino
    TA0IV = 0;
}
