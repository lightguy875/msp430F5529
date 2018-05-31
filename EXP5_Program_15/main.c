#include <msp430.h> 
#include <stdint.h>
#define DELAY1 8192
//

/**
 * main.c
 */

uint8_t P1_on = 0xA0;
uint8_t P2_on = 0x0A;
int volatile x = 0;
int volatile y = 0;
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	config();
while(1)
{
	  if(P1IN & BIT1)
	        {
	          if(x == 0)
	          {
	              x = 1;
	          __delay_cycles(DELAY1);

	            if(P1_on == 0x10)
	            {
	                P1_on = 0xA0;
	            }
	            else if(P1_on == 0xA0)
	            {
	                P1_on = 0x10;
	            }

	        }
	        }
	        else if(!(P1IN & BIT1))
	         {
	            x = 0;
	           // __delay_cycles(DELAY1);
	            UCA0TXBUF = P1_on;
	         }
	  if(P2IN & BIT1)
	  {
	     if(y == 0)
	     {
	        y = 1;
	      __delay_cycles(DELAY1);
	      if(P2_on == 0x01)
	      {
	         P2_on = 0x0A;
	      }
	      else if(P2_on == 0x0A)
	      {
	          P2_on = 0x01;
	      }
	  }
	  }
	  else if(!(P2IN & BIT1))

	  {
	      y = 0;
	      //__delay_cycles(DELAY1);
	      UCA0TXBUF = P2_on;
	  }


}
return 0;
}

config(){
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
//setando a chave do baudrate
P3SEL |= BIT3+BIT4; // P3.3,4 = USCI_A0 TXD/RXD
UCA0CTL1 |= UCSWRST; // **Put state machine in reset**
UCA0CTL1 |= UCSSEL__ACLK; // ACLK
UCA0BR0 = 27; // User GuideW
UCA0MCTL |= UCBRS_1 + UCBRF_0; // Modulation UCBRSx=1, UCBRFx=0
UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
UCA0IE |= UCRXIE; // Enable USCI_A0 RX interrupt
//__bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled
__bis_SR_register(GIE); // Enter LPM0, interrupts enabled
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

}
// Echo back RXed character, confirm TX buffer is ready first
#pragma vector= USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
switch(UCA0RXBUF)
{
case 0x01:
    P1OUT |= BIT0;
    break;
case 0xA:
    P1OUT &= ~BIT0;
    break;
case 0x10:
    P4OUT |= BIT7;
    break;
case 0xA0:
    P4OUT &= ~BIT7;
    break;
default:
    break;
}
}




























/*#pragma vector = TA0_CCR0
__interrupt void TA0_CCR0_ISR(){
    switch(rx_state)
    {
    case start:
        rx_bit = ((P1IN & BIT4)) >> 4);
        if(!rx = bit)
            rx_state = rx;
            TA1CCR0 = 27; // Tb
         if(!rx_bit)
             rx_state = rx;
         else{
             rx_state = start(erro);
             P1IE |= BIT4;
             }
    case rx:
        rx_bit = (P1IN & BIT4)>>3;
        rx_buffer = (rx_buffer << 1) | rx_bit;
        if(bit_Cnt ++ == 7)
            rx_state = Stop;
    case Stop:
        if(P1IN & BIT4)
            rx_State = ended;


         }
    }



}
sendByte(uint8 byte)
{
    tx_buffer = byte ;
    TA0CTL |=MC__UP | TACLR;
    P1OUT = ~BIT3;
    while(Tx_state != ended);
}
#pragma TA0CCR3
    if(tx_buffer & BIT0)
        P1OUT |= BIT3;
    else
        P1OUT & = ~BIT3;
    txbuffer = txbuffer >> 1;
    if(!txCnt__)
        tx_State = ended;
        TA0CTL &= ~(MC_3);
}
*/
