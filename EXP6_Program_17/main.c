#include <msp430.h>

#define TRUE        1
#define FALSE       0

#define LED1        BIT0
#define LED1_OUT    P1OUT
#define LED2        BIT7
#define LED2_OUT    P4OUT

// I2C pins
#define SDA_SEL     P3SEL
#define SDA_BIT     BIT0
#define SDA_REN     P3REN
#define SDA_OUT     P3OUT

#define SCL_SEL     P3SEL
#define SCL_BIT     BIT1
#define SCL_REN     P3REN
#define SCL_OUT     P3OUT

#define BR100K      10      //100 kbps
#define BR50K       20      // 50 kbps
#define BR10K       100     // 10 kbps

/////////////////////////////////////////////
#define PCF 0x3f    //Endereço PCF8574AT
//#define PCF 0x27    //Endereço PCF8574T
////////////////////////////////////////////

void config_pinos(void);
void config_I2C(void);
void LCD_BL_on(void);
void LCD_BL_off(void);
void LCD_00(void);
int  PCF_read(void);
void PCF_write(char dado);
void delay(long limite);


// Bits para controle do LCD
#define BIT_RS   BIT0
#define BIT_RW   BIT1
#define BIT_E    BIT2
#define BIT_BL   BIT3
#define BIT_D4   BIT4
#define BIT_D5   BIT5
#define BIT_D6   BIT6
#define BIT_D7   BIT7

int porta=0;    //Úlitmo valor escrito na porta

int main(void) {
    volatile int zz=0;
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    config_pinos();
    config_I2C();
    LCD_00();

    while(TRUE){
        LCD_BL_on();
        delay(10000);
        LCD_BL_off();
        delay(10000);
    }
    return 0;
}

// Ligar Back Light
void LCD_BL_on(void){
  porta = porta | BIT_BL;
  PCF_write(porta);
}

// Desligar Back Light
void LCD_BL_off(void){
  porta = porta & ~BIT_BL;
  PCF_write(porta);
}

// Zerar toda a porta
void LCD_00(void){
    porta=0;
    PCF_write(porta);
}

// Escrever dado na porta
void PCF_write(char dado){
    UCB0I2CSA = PCF;                            //Endereço do Escravo

    UCB0CTL1 |= UCTR    |                       //Mestre transmissor
                UCTXSTT;                        //Gerar START e envia endereço

    while ( (UCB0IFG & UCTXIFG) == 0);          //Esperar TXIFG (completar transm.)

    if ( (UCB0IFG & UCNACKIFG) == UCNACKIFG){   //NACK?
        LED1_OUT |= LED1;                       //Acender LED Vermelho
        while(1);                               //Se NACK, prender
    }

    UCB0TXBUF = dado;                           //Dado a ser escrito

    while ( (UCB0IFG & UCTXIFG) == 0);          //Esperar Transmitir

    UCB0CTL1 |= UCTXSTP;                        //Gerar STOP

    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP);   //Esperar STOP

    delay(50);                                  //Atraso p/ escravo perceber stop
}

// Configurar Pinos I2C - UCSB0
// P3.0 —> SDA
// P3.1 —> SCL
void config_I2C(void){
    SDA_SEL |=  SDA_BIT;    // Usar módulo dedicado
    SDA_REN |=  SDA_BIT;    // Habilitar resistor
    SDA_OUT |=  SDA_BIT;    // Pull-up

    SCL_SEL |=  SCL_BIT;    // Usar módulo dedicado
    SCL_REN |=  SCL_BIT;    // Habilitar resistor
    SCL_OUT |=  SCL_BIT;    // Pull-up

    UCB0CTL1 |= UCSWRST;    // UCSI B0 em ressete

    UCB0CTL0 = UCSYNC |     //Síncrono
               UCMODE_3 |   //Modo I2C
               UCMST;       //Mestre

    UCB0BRW = BR100K;       //100 kbps
    //UCB0BRW = BR20K;      // 20 kbps
    //UCB0BRW = BR10K;      // 10 kbps
    UCB0CTL1 = UCSSEL_2;   //SMCLK e remove ressete
}

// Configurar portas
void config_pinos(void){
     P1DIR |= LED1;
    LED1_OUT &= ~LED1;
    P4DIR |= LED2;
    LED2_OUT &= ~LED2;
}

void delay(long limite){
    volatile long cont=0;
    while (cont++ < limite) ;
}
