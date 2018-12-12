/*
 * File:   usart.c
 * Author: david
 *
 * Created on November 5, 2018, 5:15 PM
 */

#include <xc.h>
#pragma config FOSC = INTRC_CLKOUT
#pragma config WDTE = OFF

void main(void) {
                /****** Configuracion para USART ********/
    
    SPBRG= 25;          // Con 6 o 5 de BRGH en 0 habra error porque no se
                        // acerca a 9600 que es la velocidad con la que trabaja
                        // la computadora.
    TXSTAbits.TXEN= 1;
    TXSTAbits.BRGH= 1;  // 0: Baja velocidad, 1: Alta velocidad.
    RCSTAbits.SPEN= 1;
    RCSTAbits.CREN= 1;

    while(1) {
        while(PIR1bits.TXIF == 0);     // Pregunta si se puede poner algo
                                       // en TXREG para poder enviar.
        TXREG = 'U';
    } 
}
