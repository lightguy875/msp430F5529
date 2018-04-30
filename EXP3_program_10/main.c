#include <msp430.h> 
#define DELAY1 32768
#define DELAY2 833333

/**
 * main.c
 */
//DELAY1 32768
//DELAY2 25000000
//P2OUT &= ~BIT1;    /* Pin P2.1 = 0 */
//P2OUT |= BIT1;     /* Pin P2.1 = 1 */
//P2OUT ^= BIT1;     /* Toggle Pin P2.1 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
	    //setando a chave P1.1
	    P1SEL &= ~BIT1;
	    P1DIR &= ~BIT1;
	    P1REN |=  BIT1;
	    P1OUT |=  BIT1;
	    // setando a chave P2.1
	    P2SEL &= ~BIT1;
	    P2DIR &= ~BIT1;
	    P2REN |=  BIT1;
	    P2OUT |=  BIT1;
	    //setando o led P4.7
	    P4OUT &= ~BIT7;
	    P4SEL &= ~BIT7;
	    P4DIR |= BIT7;
	    P4REN &= ~BIT7;
	    //setando o led P1.0
	    P1OUT &= ~BIT0;
	    P1SEL &= ~BIT0;
	    P1DIR |= BIT0;
	    P1REN &= ~BIT0;
	   volatile int  estadoS1 = 0;
	   volatile int  estadoS2 = 0;
	   volatile int x;
	   volatile int y;

while(1)
{
    if(!(P2IN & BIT1) && !(P1IN & BIT1))
                  {
                    x = P1OUT;
                    y = P4OUT;
                      while(!(P1IN & BIT1) || !(P2IN & BIT1))
                      {
                          P1OUT &= ~BIT0;
                          P4OUT |= BIT7;
                          __delay_cycles(DELAY2);
                       if(!(P1IN & BIT1) || !(P2IN & BIT1))
                       {
                          P4OUT &= ~BIT7;
                          P1OUT |= BIT0;
                          __delay_cycles(DELAY2);
                       }
                     }
                      P1OUT = x;
                      P4OUT = y;
                  }
    if(P1IN & BIT1)
    {
        estadoS2 = 0;
        __delay_cycles(DELAY1);
    }
    else if(!(P1IN & BIT1))
    {

            if(estadoS2 == 0)
            {
              estadoS2 = 1;
              P4OUT ^= BIT7;
              __delay_cycles(DELAY1);
            }
    }

    if(P2IN & BIT1)
    {
        estadoS1 = 0;
        __delay_cycles(DELAY1);
    }
    else if(!(P2IN & BIT1))
    {
        if(estadoS1 == 0)
        {
            estadoS1 = 1;
            P1OUT ^= BIT0;
            __delay_cycles(DELAY1);
        }
    }
 }
return 0;
}
