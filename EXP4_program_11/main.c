#include <msp430.h> 
#include "clock.h"
#include "pmm.h"
#define TA0_CCR0_INT 53;
#define TA0_CCRN_INT 52;

/**
 * main.c
 */
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD; // Good dog, no barking
  // Increase core voltage so CPU can run at 16Mhz
     // Step 1 allows clocks up to 12MHz, step 2 allows rising MCLK to 16MHz
     pmmVCore(1);
     pmmVCore(2);
     // Configure clock
     // This should make MCLK @16MHz, SMCLK @1MHz and ACLK @32768Hz
     clockInit();

  P4DIR |= BIT7; // Digital out to a LED

  TA1CCTL0 = CCIE; // CRR0 interrupt enable for timer A
  TA1CTL = TASSEL__ACLK + MC__UPDOWN + TACLR + ID_1; //
  TA1CCR0 = 4096;
__bis_SR_register(GIE); // Enable maskable interrupts

  while(1) { // CPU does nothing and thus no harm  }

}
}
#pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
    P4OUT ^= BIT7;
}

