/*
 * File:   main.c
 * Author: Eduardo
 * Created on 10 de Abril de 2021, 09:04
 */

#include <xc.h>
#include <pic16f877a.h>

#define ST PORTDbits.RB0
#define SA PORTDbits.RB4
#define SCA PORTDbits.RB5
#define SCF PORTDbits.RB6

#define LED_L PORTDbits.RD5
#define LED_D PORTDbits.RD6
#define SIRENE PORTDbits.RD7

void __interrupt() TratarInterrupcao(void){
   if (INTF){
      //
   }
}

void main(void) {
   //configura quais pinos serao entrada e quais serao saida
   TRISB = 0b00000111;
   //ativa resistores de pull up
   OPTION_REG = 0b01111111;
   
   OPTION_REGbits.INTEDG = 0;
   INTCONbits.GIE = 1;
   INTCONbits.INTE = 1;
   return;
}
