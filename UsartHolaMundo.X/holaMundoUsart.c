/*
 * File:   holaMundoUsart.c
 * Author: david
 *
 * Created on November 25, 2018, 5:19 AM
 */

#include <xc.h>
#pragma config FOSC = INTRC_CLKOUT
#pragma config WDTE = OFF

void main(void) {
    unsigned char cadena[] = "Hola mundo. Ya me quedo la practica. :3 <3\n";
    unsigned char i;
    
                /****** Configuracion para USART ********/
    
    SPBRG= 25;          // Con 6 o 5 de BRGH en 0 habra error porque no se
                        // acerca a 9600 que es la velocidad con la que trabaja
                        // la computadora.
    TXSTAbits.TXEN= 1;
    TXSTAbits.BRGH= 1;  // 0: Baja velocidad, 1: Alta velocidad.
    RCSTAbits.SPEN= 1;
    RCSTAbits.CREN= 1;

    
    while(1) {
        for(i = 0; i < 42 ; i++) {
            while(PIR1bits.TXIF == 0);     // Pregunta si se puede poner algo
                                           // en TXREG para poder enviar.
            TXREG= cadena[i];
            /*
             * Para leer de la PC es con RCREG y preguntar si ya 
             * llego el dato con RCIF ver pagina 347.
             */
        }
    }
}
