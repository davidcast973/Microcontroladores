/*
 * File:   TxRx.c
 * Author: david
 *
 * Created on November 5, 2018, 5:15 PM
 */

#include <xc.h>
#pragma config WDTE = OFF
#pragma config FOSC = INTRC_CLKOUT      // Se utilizará el oscilador interno

void main(void) {
    unsigned char dato;
    
                /****** Configuracion para USART ********/
    
    SPBRG= 25;          // Con 6 o 5 de BRGH en 0 habra error porque no se
                        // acerca a 9600 que es la velocidad con la que trabaja
                        // la computadora.
    TXSTAbits.TXEN= 1;
    TXSTAbits.BRGH= 1;  // 0: Baja velocidad, 1: Alta velocidad.
    RCSTAbits.SPEN= 1;
    RCSTAbits.CREN= 1;
    
    while(1) {
        if(PIR1bits.RCIF == 1) {       //Pregunta si ya se recibio el dato
            dato= RCREG;
            dato++;     // Se incrementa en uno para enviar el sig caracter.
            while(PIR1bits.TXIF == 0);     // Pregunta si se puede poner algo
                                           // en TXREG para poder enviar.
            TXREG= dato;
        }
    }
}
