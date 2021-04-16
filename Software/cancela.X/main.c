/*
 * File:   main.c
 * Author: Eduardo Viniciu Hahn (17102329) e Lucas Felippe Mateus (17103449)
 * Created on 10 de Abril de 2021, 09:04
 */

#include <xc.h>
#include <pic16f877a.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000

//Definindo os pinos de entrada
#define ST PORTBbits.RB0
#define SA PORTBbits.RB1
#define SCA PORTBbits.RB2
#define SCF PORTBbits.RB3

//Definindo os pinos de saída
#define LED_ABRINDO PORTCbits.RC7
#define LED_FECHANDO PORTCbits.RC6
#define SIRENE PORTCbits.RC5
#define SENTIDO_MOTOR PORTCbits.RC4
#define MOTOR PORTCbits.RC3

void __interrupt() TratarInterrupcao();
void trata_entrada();

void main(void) {
   //configura quais pinos serao entrada e quais serao saida
   TRISBbits.TRISB0 = 1;
   TRISBbits.TRISB1 = 1;
   TRISBbits.TRISB2 = 1;
   TRISBbits.TRISB3 = 1;
   
   TRISCbits.TRISC3 = 0;
   TRISCbits.TRISC4 = 0;
   TRISCbits.TRISC5 = 0;
   TRISCbits.TRISC6 = 0;
   TRISCbits.TRISC7 = 0;
   //ativa resistores de pull up
   OPTION_REG = 0b01111111;
   
   OPTION_REGbits.INTEDG = 1;
   INTCONbits.GIE = 1;
   INTCONbits.INTE = 1;
   //Inicializando as saídas
   LED_ABRINDO = 0;
   LED_FECHANDO = 0;
   SIRENE = 0; 
   SENTIDO_MOTOR = 0;
   MOTOR = 0;
   
   while(1){
      if(SA == 0 && SCA != 0 && ST != 0){
         LED_ABRINDO = 1;
         MOTOR = 1;
         SENTIDO_MOTOR = 1; 
      }
      
      if (SA != 0 && SCF != 0 && SCA != 0){
         LED_FECHANDO = 1;
         MOTOR = 1;
         SENTIDO_MOTOR = 0; 
      }
       
      if(SCA == 0){
         MOTOR = 0;
         LED_ABRINDO = 0;
      }
      
      if(SCF == 0 && SA != 0){
         MOTOR = 0;
         LED_FECHANDO = 0;
      }
   }
   
   return;
}

void __interrupt() TratarInterrupcao() {
   if (INTF){
      if (SCF != 0){
         SIRENE = 1;
         LED_FECHANDO = 1;
         MOTOR = 1;
         SENTIDO_MOTOR = 0; 
         __delay_ms(2000);
         SIRENE = 0;
         LED_FECHANDO = 0;
         MOTOR = 0;
      }else{
         SIRENE = 1;
         __delay_ms(2000);
      }   
      
      SIRENE = 0;
      INTF = 0;
    
   }
   
   return;
}
