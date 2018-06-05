#include <msp430.h> 
#include <stdint.h>


/**
 * main.c
 */
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

#define delay_en    4 // delay do enable

/////////////////////////////////////////////
#define PCF 0x3f    //Endereço PCF8574AT
//#define PCF 0x27    //Endereço PCF8574T
////////////////////////////////////////////
void pulso(void);
void inicializa(void);
void config_pinos(void);
void I2C_config(void);
void LCD_BL_on(void);
void LCD_BL_off(void);
void LCD_00(void);
int  PCF_read(void);
void PCF_write(unsigned char dado);
void delay(long limite);
void Write_char(char c);
void set_cursor(char c);
void rs_rw(void);
void lcd_limpa(void);
void set_cursor(char c);
void escreve_A(void);
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
unsigned char volatile  v = 0;

int main()
{
    unsigned char c = 0;
    volatile int i = 0;
    volatile int parada = 0;
    unsigned char lcd_linha[2] = {0x80,0xC0};
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    config_pinos();
    I2C_config();
     // LCD_00();
      inicializa();
      while(parada < 128)
      {
          Write_char(c);
          __delay_cycles(60000);
          c++;
          i++;
          parada++;
          if(i == 16)
          {
             set_cursor(lcd_linha[1]);
          }
          else if(i == 32)
          {
           if(parada != 128)
           {
             __delay_cycles(100000);
              lcd_limpa();
              __delay_cycles(500);
              set_cursor(lcd_linha[0]);
              __delay_cycles(500);
              i = 0;
           }
          }

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
void PCF_write(unsigned char dado){
    UCB0I2CSA = PCF;                            //Endereço do Escravo

  //  while(UCB0STAT & UCBBUSY);                 // verifica se a linha esta ocupada

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
void I2C_config(void)
{
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
void lcd_high(void)
{
v |= BIT_E;
PCF_write(v);

}
void lcd_low(void)
{
 v  &= ~BIT_E; 
 PCF_write(v);
}
void pulso(void)
{
    __delay_cycles(100);
    lcd_high();__delay_cycles(300);
    lcd_low(); __delay_cycles(100);
}
void inicializa(void)
{
    PCF_write(0x00);
    PCF_write(0x08); // BL = 1
    rs_rw();
    __delay_cycles(20000);
    v = 0x30;
    PCF_write(v);
    pulso();
    __delay_cycles(4500);
    v = 0x30;
    PCF_write(v);
    pulso();
    __delay_cycles(150);
    v = 0x30;
    PCF_write(v);
    pulso();
    v = 0x20;
    PCF_write(v);
    pulso();
    v = 0x20;
    PCF_write(v);
    pulso();
    v = 0x80;
   PCF_write(v);
    pulso();
   v = 0x00;
   PCF_write(v);
    pulso();
    v = 0xC0;
    PCF_write(v);
    pulso();
    v = 0x00;
    PCF_write(v);
    pulso();
    v = 0x10;
    PCF_write(v);
    pulso();
    v = 0x00;
    PCF_write(v);
    pulso();
    v = 0x60;
    PCF_write(v);
    pulso();
    v = 0x00;
    PCF_write(v);
    pulso();
    v = 0xC0;
    PCF_write(v);
    pulso();

}

void Write_char(char c)
{
 v = 0;
 v |= (c & 0xF0);
 v |= 0x9;
 PCF_write(v);
 pulso();
 v = 0;
 v |= (c << 4);
 v |= 0x9;
 PCF_write(v);
 pulso();
}
void set_cursor(char c)
{
   v = 0;
   v = (c & 0xF0);
   v |= 0x08; // BL = 1
    PCF_write(v);
    pulso();
    __delay_cycles(500);
    v = c << 4;
    v |= 0x08;
    PCF_write(v);
    pulso();
    __delay_cycles(500);
}
void rs_rw(void)
{
    v = v &= ~BIT_RS;
    v = v &= ~BIT_RW;
    PCF_write(v);
}

void lcd_limpa(void)
{
    v = 0x08;
    PCF_write(v);
    pulso();
    __delay_cycles(450);
    v = 0x18;
    PCF_write(v);
    pulso();
    __delay_cycles(450);
}
//      Write_char('C');
//      __delay_cycles(300000);
//      Write_char('A');
//      __delay_cycles(300000);
//      Write_char('L');
//      __delay_cycles(300000);
//      Write_char('C');
//      __delay_cycles(300000);
//      Write_char('U');
//      __delay_cycles(300000);
//      Write_char('L');
//      __delay_cycles(300000);
//      Write_char('A');
//      __delay_cycles(300000);
//      Write_char('D');
//      __delay_cycles(300000);
//      Write_char('O');
//      __delay_cycles(300000);
//      Write_char('R');
//      __delay_cycles(300000);
//      Write_char('A');
//      __delay_cycles(300000);
//      Write_char(' ');
//      __delay_cycles(300000);
//      Write_char('L');
//      __delay_cycles(300000);
//      Write_char('C');
//      __delay_cycles(300000);
//      Write_char('D');
//      __delay_cycles(300000);
//      Write_char(' ');
//      __delay_cycles(300000);

