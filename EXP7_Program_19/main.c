#include <msp430.h> 
/**
 * main.c
 */
int adc;
void config_adc(void);
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P6SEL |= BIT0;
	config_adc();
	int x[500];
	int i = 0;;
	while(1)
	{
	    ADC12CTL0 &= ~ADC12SC;
	    ADC12CTL0 |= ADC12SC + ADC12ENC;
	    while((ADC12IFG & ADC12IFG0) == 0);
	   if(i < 500)
	   {
	    x[i]   = ADC12MEM0;
	   }
	   i++;
	}
	return 0;
}
void config_adc(void)
{                           //Pulsar ADC12SC para iniciar uma conversão
    ADC12CTL0 &= ~ADC12ENC; //Desabilitar para configurar
    ADC12CTL0 = ADC12SHT0_3 | //ADC tempo amostragem ADCMEM[0-7]
            ADC12ON; //Ligar ADC
    ADC12CTL1 = ADC12CSTARTADD_0 | //Resultado em ADC12MEM0
            ADC12SHS_0 | // Selecionar ADC12SC bit
            ADC12SHP | // S/H usar timer
            ADC12DIV_0 | //Clock ADC Divisor
            ADC12SSEL_3 | //Clock ADC = SMCLK
            ADC12CONSEQ_2; //Modo Single
    ADC12CTL2 = ADC12TCOFF | // Desligar sensor temperatura
            ADC12RES_2; // Resolução 12-bit
    ADC12MCTL0 = ADC12EOS | //Fim de sequência
            ADC12SREF_0 | //VR+ = AVCC e VR- = AVSS
            ADC12INCH_0; //(P6.0) A0 = Canal 0 (?P6SEL |= BIT0?)
    ADC12CTL0 |= ADC12ENC; //Habilitar ADC12
}


