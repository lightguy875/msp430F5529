#include <msp430.h> 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define ADC12MEM1ADDR (__SFR_FARPTR) 0x0722
#define ADC12MEM2ADDR (__SFR_FARPTR) 0x0724
#define TIMERBADDRESS1 (__SFR_FARPTR) 0x03D4
#define TIMERBADDRESS2 (__SFR_FARPTR) 0x03D6
volatile int adc[2];
void config_adc(void);
void config_pinos(void);
void config_timer(void);
void config_DMA(void);

#define TB0_CTL0_INT 58


int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
  __bis_SR_register(GIE);
  config_pinos();
  config_timer();
  config_DMA();
  config_adc();
  while(1);
  return 0;

}
void config_pinos(void)
{
    P6SEL |= BIT0; // A0 Channel of ADC
    P6SEL |= BIT1; // A1 Channel of ADC

    //Configure Port Mapping
    P4DIR |= BIT3 | BIT7;
    P4SEL |= BIT3 | BIT7; // Mapping P4 for Timer Channel
    PMAPKEYID = 0x02D52;
    P4MAP3 = PM_TB0CCR1A;
    P4MAP7 = PM_TB0CCR2A;

}
void config_adc(void)
{
    ADC12CTL0 &= ~ADC12ENC; //Desabilitar para configurar

    ADC12CTL0 = ADC12SHT0_4 | //ADC tempo amostragem ADCMEM[0-7]
                ADC12MSC | // Proximas conversoes realizadas automaticamente
                ADC12ON; //Ligar ADC


    ADC12CTL1 = ADC12CSTARTADD_0| //Resultado em ADC12MEM0
                ADC12SHS_1 |
                ADC12SHP |   // S/H usar timer interno
                ADC12DIV_0 | //Clock ADC Divisor
                ADC12SSEL_0 | //Clock ADC = SMCLK
                ADC12CONSEQ_3; // Repeat sequencies of channels

     ADC12CTL2 = ADC12TCOFF | // Desligar sensor temperatura
                 ADC12RES_1;  // Resolução 8-bit

     ADC12MCTL1 = ADC12SREF_0 | //VR+ = AVCC e VR- = AVSS
                  ADC12INCH_0;  //(P6.0) A0 = Canal 0
     ADC12MCTL2 = ADC12EOS |  //Fim de sequência
                  ADC12SREF_0 |  //VR+ = AVCC e VR- = AVSS
                  ADC12INCH_1;  //(P6.1) A0 = Canal 1

//     ADC12IE = BIT1 | BIT2;

     ADC12CTL0 |= ADC12ENC; //Habilitar ADC12

}
void config_timer(void)
{
    TB0CTL = TBSSEL__SMCLK | TBCLR | MC__UP | ID__1;

    TB0CCR0 = 5000;
    TB0CCR1 = 1000;
    TB0CCR2 = 1000;

    TB0CCTL1 = OUTMOD_6;
    TB0CCTL2 = OUTMOD_6;

    TA0CTL = TASSEL__SMCLK | TACLR | MC__UP | ID__1;

    TA0CCR0 = 20000;
    TA0CCR1 = 10000;
    TA0CCTL1 = OUTMOD_6;
}
void config_DMA(void)
{

    // Configure Port Mapping
    DMACTL0 = DMA0TSEL__ADC12IFG; //| DMA2TSEL__ADC12IFG;
    DMA0CTL = DMADSTINCR_3 | DMASRCINCR_3 | DMADT_4 | DMAEN;
    DMA0SA = ADC12MEM1ADDR;
    DMA0DA = TIMERBADDRESS1;
    DMA0SZ = 2;
    DMACTL1 = DMA1TSEL__ADC12IFG;
    DMA1CTL = DMADSTINCR_0 | DMASRCINCR_0 | DMADSTBYTE | DMASRCBYTE | DMADT_4  |DMAEN;
    DMA1SA = ADC12MEM2ADDR;
    DMA1DA = TIMERBADDRESS2;
    DMA1SZ = 2;

    DMACTL4 = ROUNDROBIN;
}

/*#pragma vector = 50
__interrupt void DMA_ISR(void){
    volatile int x=0;*/
//    TB0CCR1 = adc[0];
//    TB0CCR2 = adc[1];
//    while(1);
//}
