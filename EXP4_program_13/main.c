#include <msp430.h> 
#include "clock.h"
#include "pmm.h"
#define TA0_CCR0_INT 53;
#define TA0_CCRN_INT 52;


/**
 * main.c
 */
int volatile aux;
void config();
int main(void)
{
	// Port Mapping // (só funciona após um reset)
	PMAPKEYID = 0x02D52; // Escritas no modulo de mapeamento são protegidas
	// por senha. Escrever 2D52 no registro PMAPKEYID
	// permite reconfiguração de apenas um pino.
	P4MAP7 = PM_TB0CCR1A; // Conecta o pino P4.7 na saída do canal 1
	// do Timer B.
	WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
	    // Increase core voltage so CPU can run at 16Mhz
	    // Step 1 allows clocks up to 12MHz, step 2 allows rising MCLK to 16MHz
	   pmmVCore(1);
	    pmmVCore(2);

	    // Configure clock
	    // This should make MCLK @16MHz, SMCLK @1MHz and ACLK @32768Hz
	    clockInit();
	config();
	__bis_SR_register(GIE); // Enable maskable interrupts
	while(1);
	return 0;
}
void config()
{
    //P4SEL |= BIT7;
    P1DIR |= BIT0; /* Digital out to a LED */
      P1OUT &= ~BIT0;
      P4DIR |= BIT7; /* Digital out to a LED */
      P4OUT &= ~BIT7;
      TB0CCR0 = 10000;//660
       TB0CCR1 = 0;//65
      TB0CTL = TBSSEL__SMCLK + TBCLR + MC__UP + ID__1;
     // TB0EX0 = TBIDEX_0;
      TB0CCTL1 = CCIE | CLLD_3;
      TB0CCTL0 = CCIE | CLLD_1; // CRR0 interrupt enable for timer A
      //TA0CCTL0 = OUTMOD_7;

       __bis_SR_register(GIE); // Enable maskable interrupts


}
#pragma vector =   TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void)
{
// switch (__even_in_range(TB0IV, TB0IV_TB0IFG))
// {
 //case 0x02:
              P1OUT &= ~BIT0;
              P4OUT &= ~BIT7;
   // break;
 //case 0x0E:
   //                   P1OUT |= BIT0;
    //                  P4OUT |= BIT7;

      //                if(TB0CCR1 == TB0CCR0)  aux = -100;//6
          //            if(TB0CCR1 == 0) aux = 100;//6
        //              TB0CCR1 += aux ;
// default: break;
 //}
}
#pragma vector =  TIMER0_B0_VECTOR
__interrupt void TIMER0_B0_ISR(void)
{
    //switch (__even_in_range(TB0IV, TB0IV_TB0IFG))
   // {
    //case 0x02:
     //   P1OUT &= ~BIT0;
      //  P4OUT &= ~BIT7;
      //  break;

   // case 0x0E:


                     TB0CTL &= ~TBIFG;
                     TB0CCTL1 &= ~BIT0;
                     P1OUT |= BIT0;
                     P4OUT |= BIT7;

                     if(TB0CCR1 == TB0CCR0)  aux = -100;//6
                     if(TB0CCR1 == 0) aux = 100;//6
                     TB0CCR1 += aux ;

    //default: break;
  //  }
}
