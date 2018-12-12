/*
 * File:   pianito.c
 * Author: David
 *
 * Created on October 24, 2018, 4:49 PM
 *
 * Pianito
 *
 * Se necesitaran 2 temporizadores, uno para el tiempo que sonara la tecla y el
 *      otro es para la frecuencia.
 *
 * T0IF: Checar� si ya paso el tiempo de cada medio periodo.
 * TMR1IF: Checar� si ya paso un segundo.
 * T0CS = 0; // para instrucciones internas
 * PSA = 0; // Asignamos al timer0 el preescalador
 * PS2 = 0;
 * PS1 = 1; // Estos bits son para configurar el preescalador a 1:8
 * PS0 = 0;
 * TMR0 = 18;
 */

#include <xc.h>
#define _XTAL_FREQ 8000000  // nuestro cristal es de 8 MHz
#pragma config FOSC = HS        // Para especificar que es el HS por 8 MHz
#pragma config WDTE = OFF

void sound(int, int);

void main(void) {
    /******** Configuracion Digital De PORTB *********/

    ANSELH = 0b000010;      // Sólo deja a RB3 como entrada analogica.

    TRISB = 0xFF; // PORTB como entrada.
    TRISD = 0xFF;

    OPTION_REGbits.nRBPU = 0; // Habilita las resistencias de pull-up de PORTB.

    TRISC = 0xF7; // RC3 como salida.
    WPUB = 0xFF; // Para habilitar las resistencias(por default viene en 1)

    while (1) {

        /******** Configuracion TMR0 ********/

        OPTION_REGbits.T0CS = 0; // oscilador interno
        OPTION_REGbits.T0SE = 1; // para que incremente en flancos de bajada
        OPTION_REGbits.PSA = 0; // asignamos el preescalador al timer0


        switch (PORTB) {
            case 16:
                sound(526, 18); // DO
                break;
            case 8:
                sound(500, 130); // SI
                break;
            case 2:
                sound(435, 112); // LA
                break;
            case 1:
                sound(385, 93); // SOl
                break;
            case 0:
                sound(345, 74); // FA
                break;
            default:
                sound(0, 0); // Nada
        }
        switch (PORTD) {
            case 64:
                sound(333, 162); // MI
                break;
            case 32:
                sound(294, 43); // RE
                break;
            case 2:
                sound(263, 18); // DO
                break;
            case 1:
                sound(385, 93); //Fa
                break;
            default:
                sound(0, 0); // Nada
        }
    }
}

void sound(int numTMR0, int numComplementoTMR0) {
    int i, j;

    OPTION_REGbits.PS2 = 0;
    OPTION_REGbits.PS1 = 1; // Escala 1:8
    OPTION_REGbits.PS0 = 0;

    TMR0 = numComplementoTMR0; // Para que pueda somar correctamente hasta los 255.

    for (i = 0; i < numTMR0; i++) {
        while (INTCONbits.T0IF != 1) {
            // if (j)
            if (j == 0)
                PORTCbits.RC3 = 1;
            else
                PORTCbits.RC3 = 0;
        }
    }

    TMR0 = numComplementoTMR0; // Para que pueda somar correctamente hasta los 255.
    INTCONbits.T0IF = 0; // Se apaga la bandera manualmente.

    // j = !j;
    if (j == 0)
        j = 1;
    else
        j = 0;
}
