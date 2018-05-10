#include <msp430.h> 
#include "clock.h"
#include "pmm.h"
#define TB0_CCR0_INT 53;
#define TB0_CCRN_INT 52;

/**
 * main.c
 */
    int volatile aux;
void config();
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    // Increase core voltage so CPU can run at 16Mhz
    // Step 1 allows clocks up to 12MHz, step 2 allows rising MCLK to 16MHz
   pmmVCore(1);
    pmmVCore(2);

    // Configure clock
    // This should make MCLK @16MHz, SMCLK @1MHz and ACLK @32768Hz
    clockInit();

	config();
	 while(1){
	     while(!(TB0CCTL1 & CCIFG));

	             TB0CCTL1 &= ~BIT0;
	             P1OUT &= ~BIT0;

	     while(!(TB0CCTL0 & CCIFG));

	        TB0CCTL0 &= ~BIT0;
	        P1OUT |= BIT0;



	        if(TB0CCR1 == TB0CCR0)
	            aux = -6;
	        if(TB0CCR1==0)
	            aux = 6;
	        TB0CCR1 += aux ;

	 }
	}
void config()
{
    P1DIR |= BIT0; /* Digital out to a LED */
    P1OUT &= ~BIT0;
    P4DIR |= BIT7; /* Digital out to a LED */
    P4OUT &= ~BIT7;
    TB0CTL = TBSSEL__ACLK + TBCLR + MC__UP + ID__1;
    TB0EX0 = TBIDEX_0;
    TB0CCTL1 = CCIE;
    TB0CCTL0 = CCIE; // CRR0 interrupt enable for timer A
    //TA0CCTL0 = OUTMOD_7;
    TB0CCR0 = 654;//654
    TB0CCR1 = 0;//65
     //__bis_SR_register(GIE); // Enable maskable interrupts



}

/*#pragma vector =   TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{

              TA0CTL &= ~TAIFG;
              TA0CCTL1 &= ~BIT0;
              P1OUT |= BIT0;
              P4OUT |= BIT7;


}
#pragma vector =  TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
                     TA0CCTL1 &= ~BIT0;
                     TA0CTL &= ~TAIFG;
                     P1OUT &= ~BIT0;
                     P4OUT &= ~BIT7;
                     if(TA0CCR1 == TA0CCR0)  aux = -6;//6
                     if(TA0CCR1==0) aux = 6;//6
                     TA0CCR1 += aux ;
}
*/
