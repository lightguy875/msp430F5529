#include <msp430.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int32_t result,num1,num2,auxnum,auxnum2;
volatile unsigned int x = 0,j = 0;
char Result[10];
volatile char operacao,l = 0x30,sinal1,sinal2;
volatile char operacoes[4] = {'*','-','+','/'},signals[2] = {' ','-'};
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
void Write_String(char *String);
void Write_String_no_zeros(char *String);
// Bits para controle do LCD
#define BIT_RS   BIT0
#define BIT_RW   BIT1
#define BIT_E    BIT2
#define BIT_BL   BIT3
#define BIT_D4   BIT4
#define BIT_D5   BIT5
#define BIT_D6   BIT6
#define BIT_D7   BIT7
// valores
int porta=0;    //Úlitmo valor escrito na porta

unsigned char volatile  v = 0;
char String[15] = {'1','2','3','4',' ','*','-','+','/',' ','1','2','3','4',' '};
int main()
{
    //unsigned char c = 0;
    volatile int i = 0;
    volatile int parada = 0;
    unsigned char lcd_linha[2] = {0x80,0xC0};
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    __enable_interrupt();
    I2C_config();
     // LCD_00();
      inicializa();
      config_pinos();
      x =22;
     // lcd_limpa();
      //set_cursor(lcd_linha[0]);
      //Write_String(String);
      while(1)
      {
          if(x == 22)
          {
              P1IE &= ~BIT1;
              P2IE &= ~BIT1;
              lcd_limpa();
              set_cursor(0x80);
                  Write_char('C');
                  TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                  TA0CCR0 = 4096;
                  while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('A');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('L');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('C');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('U');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('L');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('A');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('D');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('O');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('R');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('A');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char(' ');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('L');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('C');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('D');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char(' ');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   set_cursor(0xC2);
                   Write_char('D');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('E');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char(' ');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('I');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('N');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('T');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('E');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('I');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('R');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('O');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   Write_char('S');
                   TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                   TA0CCR0 = 4096;
                   while((TA0CTL & TAIFG) != TAIFG);
                   x = 0;
                   P1IE |= BIT1;
                   P2IE |= BIT1;
                   //while((P2IV & P2IV_P2IFG1) != 0x4);
          }


      }

return 0;
}
#pragma vector = 47
__interrupt void PORT1_VECTOR_ISR(void)
{
    TB0CTL = TBSSEL__ACLK | MC__UP | TBCLR ;
       TB0CCR0 = 8192;
    switch(__even_in_range(P1IV,0x10))
    {
    case 0x0:
        break;
    case 0x2:
        break;
    case 0x4:
        if(x == 1)
        {
            x = 2;
            set_cursor(0x81);
        }
        else if(x == 3)
        {
            x = 4;
            set_cursor(0x82);
        }
        else if(x == 5)
        {
            x = 6;
            set_cursor(0x83);
        }
        else if(x == 7)
        {
            x = 8;
            set_cursor(0x84);
        }
        else if(x == 9)
        {
            x = 10;
            set_cursor(0x86);
        }
        else if(x == 11)
        {
            x = 12;
            set_cursor(0x88);
        }
        else if(x == 13)
        {
            x = 14;
            set_cursor(0x89);
        }
        else if(x == 15)
        {
            x = 16;
            set_cursor(0x8A);
        }
        else if(x == 17)
        {
            x = 18;
            set_cursor(0x8B);
        }
        else if(x == 19)
        {
            x = 20;
            set_cursor(0x8C);
        }
        else if(x == 21)
        {
           if(sinal1 == '-')
               num1 = -num1;
           if(sinal2 == '-')
               num2 = -num2;
           set_cursor(0xC0);
           if(operacao == '+')
           {
               result = num1 + num2;
           }
           else if(operacao == '-')
           {
               result = num1 - num2;
           }
           else if(operacao == '*')
           {
               result = num1 * num2;
           }
           else if(operacao == '/')
           {

              result = num1 / num2;
           }
           if((result & 0x80000000) == 0x80000000)
           {
             result = -result;
             auxnum2 = (char) (result*0.0000001) + 0x30;
             Result[0] = auxnum2;
             auxnum = (result*0.0000001);
             auxnum = auxnum* 10;
             auxnum2 = (result*0.000001) - auxnum;
             Result[1] = (char) auxnum2 + 0x30;
             auxnum = (result*0.000001);
             auxnum = auxnum*10;
             auxnum2 = (result*0.00001) - auxnum;
             Result[2] = (char) auxnum2 + 0x30;
             auxnum = (result*0.00001);
             auxnum = auxnum*10;
             auxnum2 = (result*0.0001) - auxnum;
             Result[3] = (char) auxnum2 + 0x30;
             auxnum = (result*0.0001);
             auxnum = auxnum*10;
             auxnum2 = (result*0.001) - auxnum;
             Result[4] = (char) auxnum2 + 0x30;
             auxnum = (result*0.001);
             auxnum = auxnum*10;
             auxnum2 = (result*0.01) - auxnum;
             Result[5] = (char) auxnum2 + 0x30;
             auxnum = (result*0.01);
             auxnum = auxnum*10;
             auxnum2 = (result*0.1) - auxnum;
             Result[6] = (char) auxnum2 + 0x30;
             auxnum = (result*0.1);
             auxnum = auxnum*10;
             auxnum2 = (result) - auxnum;
             Result[7] = (char) auxnum2 + 0x30;
             Result[8] = '\0';
             Write_String("Result:");
             Write_char('-');
             Write_String_no_zeros(Result);
           }
           else{
               auxnum2 = (char) (result*0.0000001) + 0x30;
               Result[0] = auxnum2;
               auxnum = (result*0.0000001);
               auxnum = auxnum* 10;
               auxnum2 = (result*0.000001) - auxnum;
               Result[1] = (char) auxnum2 + 0x30;
               auxnum = (result*0.000001);
               auxnum = auxnum*10;
               auxnum2 = (result*0.00001) - auxnum;
               Result[2] = (char) auxnum2 + 0x30;
               auxnum = (result*0.00001);
               auxnum = auxnum*10;
               auxnum2 = (result*0.0001) - auxnum;
               Result[3] = (char) auxnum2 + 0x30;
               auxnum = (result*0.0001);
               auxnum = auxnum*10;
               auxnum2 = (result*0.001) - auxnum;
               Result[4] = (char) auxnum2 + 0x30;
               auxnum = (result*0.001);
               auxnum = auxnum*10;
               auxnum2 = (result*0.01) - auxnum;
               Result[5] = (char) auxnum2 + 0x30;
               auxnum = (result*0.01);
               auxnum = auxnum*10;
               auxnum2 = (result*0.1) - auxnum;
               Result[6] = (char) auxnum2 + 0x30;
               auxnum = (result*0.1);
               auxnum = auxnum*10;
               auxnum2 = (result) - auxnum;
               Result[7] = (char) auxnum2 + 0x30;
               Result[8] = '\0';
               Write_String("Result:");
               Write_String_no_zeros(Result);
           }
           while((P2IV & P2IV_P2IFG1) != 0x4);
           x = 22;

        }
    default: break;

    }
    while((TB0CTL & TBIFG) != 1);
    P1IV &= ~BIT2;
}
#pragma vector = 42
__interrupt void PORT2_VECTOR_ISR(void)
{
    TB0CTL = TBSSEL__ACLK | MC__UP | TBCLR ;
    TB0CCR0 = 8192;
    switch(__even_in_range(P2IV,0x10))
    {
    case 0x00:
        break;
    case 0x02:
        break;
    case 0x04:
    if (x == 0)
    {
        x = 1;
        lcd_limpa();
        j = 0;
        set_cursor(0x80);
        while((P1IV & P1IV_P1IFG1) != 0x04)
        {
            TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
            TA0CCR0 = 16384;

            l = signals[j];
            sinal1 = l;
            Write_char(l);
            set_cursor(0x80);
            j++;
            if(j == 2)
                j = 0;

            while((TA0CTL & TAIFG) != TAIFG);
        }
        l = 0x30;
        j = 0;


    }
     if(x == 2)
        {

            x = 3;
           while((P1IV & P1IV_P1IFG1) != 0x04)
           {
              TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
              TA0CCR0 = 8192;
            if(l == 0x3A)
            {
                l = 0x30;
            }
            auxnum = (unsigned int) (l - 0x30);
            Write_char(l);
            set_cursor(0x81);
            l++;
            while((TA0CTL & TAIFG) != TAIFG);
           }
           num1 = auxnum*1000;
           l = 0x30;
        }
     else if(x == 4)
        {
            x = 5;
            while((P1IV & P1IV_P1IFG1) != 0x04)
            {
                TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                TA0CCR0 = 8192;
                if(l == 0x3A)
                 {
                    l = 0x30;
                 }
                Write_char(l);
                auxnum = (unsigned int) (l - 0x30);
                set_cursor(0x82);
                l++;
                while((TA0CTL & TAIFG) != TAIFG);
            }
            auxnum = auxnum*100;
            num1 = num1 + auxnum;
            l = 0x30;
        }
     else if(x == 6)
        {
            x = 7;
           while((P1IV & P1IV_P1IFG1) != 0x04)
           {
               TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
               TA0CCR0 = 8192;
               if(l == 0x3A)
                {
                   l = 0x30;
                }
               Write_char(l);
               auxnum = (unsigned int) (l - 0x30);
               set_cursor(0x83);
               l++;
               while((TA0CTL & TAIFG) != TAIFG);
           }
           auxnum = auxnum*10;
           num1 = num1 + auxnum;
           l = 0x30;
        }
     else if(x == 8)
        {
            x = 9;
            while((P1IV & P1IV_P1IFG1) != 0x04)
            {
                TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                TA0CCR0 = 8192;
                if(l == 0x3A)
                 {
                    l = 0x30;
                 }
                Write_char(l);
                auxnum = (unsigned int) (l - 0x30);
                set_cursor(0x84);
                l++;
                while((TA0CTL & TAIFG) != TAIFG);
            }
            num1 = num1 + auxnum;
            l = 0x30;
        }
     else if(x == 10)
               {
                   x = 11;
                   while((P1IV & P1IV_P1IFG1) != 0x04)
                   {
                       TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
                       TA0CCR0 = 16384;
                       Write_char(operacoes[j]);
                       operacao = operacoes[j];
                       set_cursor(0x86);
                       j++;
                       if(j == 4)
                           j = 0;
                       while((TA0CTL & TAIFG) != TAIFG);
                   }
                   j = 0;
                   l = 0x30;
               }
     else if(x == 12)
     {
         x = 13;
         j = 0;
         while((P1IV & P1IV_P1IFG1) != 0x04)
         {
             TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
             TA0CCR0 = 16384;

             l = signals[j];
             sinal2 = l;
             Write_char(l);
             set_cursor(0x88);
             j++;
             if(j == 2)
                j = 0;
             while((TA0CTL & TAIFG) != TAIFG);

     }
         j = 0;
         l = 0x30;
     }
     else if(x == 14)
     {
         x = 15;
         while((P1IV & P1IV_P1IFG1) != 0x04)
         {
             TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
             TA0CCR0 = 8192;
             if(l == 0x3A)
              {
                 l = 0x30;
              }
             Write_char(l);
             auxnum = (unsigned int) (l - 0x30);
             set_cursor(0x89);
             l++;
             while((TA0CTL & TAIFG) != TAIFG);
         }
         num2 = auxnum * 1000;
         l = 0x30;
     }
     else if(x == 16)
     {
         x = 17;
         while((P1IV & P1IV_P1IFG1) != 0x04)
         {
             TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
             TA0CCR0 = 8192;
             if(l == 0x3A)
              {
                 l = 0x30;
              }
             Write_char(l);
             auxnum = (unsigned int) (l - 0x30);
             set_cursor(0x8A);
             l++;
             while((TA0CTL & TAIFG) != TAIFG);
         }
         auxnum = auxnum*100;
         num2 = num2 + auxnum;
         l = 0x30;
     }
     else if(x == 18)
     {
         x = 19;
         while((P1IV & P1IV_P1IFG1) != 0x04)
         {
             TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
             TA0CCR0 = 8192;
             if(l == 0x3A)
              {
                 l = 0x30;
              }
             Write_char(l);
             auxnum = (unsigned int) (l - 0x30);
             set_cursor(0x8B);
             l++;
             while((TA0CTL & TAIFG) != TAIFG);
         }
         auxnum = auxnum*10;
         num2 = num2 + auxnum;
         l = 0x30;
     }
    else if(x == 20)
    {
        x = 21;
        while((P1IV & P1IV_P1IFG1) != 0x04)
        {
            TA0CTL = TASSEL__ACLK | MC__UP | TACLR;
            TA0CCR0 = 8192;
            if(l == 0x3A)
             {
                l = 0x30;
             }
            Write_char(l);
            auxnum = (unsigned int) (l - 0x30);
            set_cursor(0x8C);
            l++;
            while((TA0CTL & TAIFG) != TAIFG);
    }
        num2 = num2 + auxnum;
        l = 0x30;
    }

        break;
    default:
        break;
    }
    while((TB0CTL & TBIFG) != 1);
    P2IV &= ~BIT2;
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

//    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP);   //Esperar STOP

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
    // P1DIR |= LED1;
    //LED1_OUT &= ~LED1;
    //P4DIR |= LED2;
   // LED2_OUT &= ~LED2;
    // Configuração da porta P1.1 ao lado do led em P4.7
       P1DIR &= ~BIT1; // Como entrada de dados
       P1REN |= BIT1; // Habilita resistor de pull/up ou pull/down
       P1SEL &= ~BIT1; // Define como dispositivo de I/O
       P1OUT |= BIT1; // Seta resistor de pull/up
       P1IES |= BIT1; // Aciona em high->low
       P1IE |= BIT1; // Habilita a interrupção da porta


       // Configuração da porta P2.1 ao lado do led P1.0
       P2DIR &= ~ BIT1; // Como entrada de dados
       P2REN |= BIT1; // Habilita resistor de pull/up ou pull/down
       P2SEL &= ~BIT1; // Define como dispostivo de I/O
       P2OUT |= BIT1; //Seta resistor de pull/up
       P1IES |= BIT1; // Acina em High->low
       P2IE |= BIT1; // Habilita a interrupção da porta
       while((P2IV & P2IV_P2IFG1) != 0x4);


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
    v = 0x38;
    PCF_write(v);
    pulso();
    __delay_cycles(4500);
    v = 0x38;
    PCF_write(v);
    pulso();
    __delay_cycles(150);
    v = 0x38;
    PCF_write(v);
    pulso();
    v = 0x28;
    PCF_write(v);
    pulso();
    v = 0x28;
    PCF_write(v);
    pulso();
    v = 0x88;
   PCF_write(v);
    pulso();
   v = 0x08;
   PCF_write(v);
    pulso();
    v = 0xC8;
    PCF_write(v);
    pulso();
    v = 0x08;
    PCF_write(v);
    pulso();
    v = 0x18;
    PCF_write(v);
    pulso();
    v = 0x08;
    PCF_write(v);
    pulso();
    v = 0x68;
    PCF_write(v);
    pulso();
    v = 0x08;
    PCF_write(v);
    pulso();
    v = 0xC8;
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
void Write_String(char *String)
{
  volatile int i = 0;
  while(String[i] != '\0')
  {
      Write_char(String[i]);
      i++;
  }
}
void Write_String_no_zeros(char *String)
{
    volatile int g = 0;
    volatile int i = 0;
    while(String[i] != '\0')
    {
        if(String[i] != '0')
            g = 1;
        if (g == 1)
        {
            Write_char(String[i]);
        }
        i++;
    }
    if(g == 0)
    {
        Write_char('0');
    }
}



