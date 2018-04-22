#define DELAY 30000

#include <msp430.h> 

//P2OUT &= ~BIT1;    /* Pin P2.1 = 0 */
//P2OUT |= BIT1;     /* Pin P2.1 = 1 */
//P2OUT ^= BIT1;     /* Toggle Pin P2.1 */
 /* main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	//setando a chave
	P1SEL &= ~BIT1;
	P1DIR &= ~BIT1;
	P1REN |=  BIT1;
	P1OUT |=  BIT1;
	//setando o led menos significativo
	P4SEL &= ~BIT7;
	P4DIR |= BIT7;
	P4REN &= ~BIT7;
	P4OUT &= ~BIT7;
	//setando o led mais signficativo
	P1SEL &= ~BIT0;
	P1DIR |= BIT0;
	P1REN &= ~BIT0;
	P1OUT &= ~BIT0;
	volatile int contadorpino = 0;
	volatile int estado = 0;
while(1)
{

    if(P1IN & BIT1)
    {
        estado = 0;
        __delay_cycles(DELAY);
        }
    else if(!(P1IN & BIT1))
    {
        if(estado == 0)
        {
            contadorpino++;
            estado = 1;
        switch(contadorpino)
        {
        case 1:
            P4OUT |= BIT7;
            P1OUT &= ~BIT0;
            __delay_cycles(DELAY);
            break;
        case 2:
            P4OUT &= ~BIT7;
            P1OUT |= BIT0;
            __delay_cycles(DELAY);
            break;
        case 3:
            P4OUT |= BIT7;
            P1OUT |= BIT0;
            __delay_cycles(DELAY);
            break;
        case 4:
            P4OUT &= ~BIT7;
            P1OUT &= ~BIT0;
            contadorpino = 0;
            __delay_cycles(DELAY);
        }
        }
        }
    }


return 0;
}
