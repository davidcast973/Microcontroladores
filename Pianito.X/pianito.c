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
#define _XTAL_FREQ 4000000  // nuestro cristal es de 4 MHz
#pragma config FOSC = XT        // Para especificar que es el HS por 8 MHz
#pragma config WDTE = OFF

void sound(int, int, int, int, int);

void main(void) {
    int j= 0, i= 0;
    /******** Configuracion Digital De PORTB *********/

    // ANSELH = 0b000010;      // Sólo deja a RB3 como entrada analogica.
    ANSELHbits.ANS13 = 0; // Pone en digital la patita RB5
    ANSELHbits.ANS12 = 0; // Pone en digital la patita RB0
    ANSELHbits.ANS11 = 0; // Pone en digital la patita RB4
    ANSELHbits.ANS10 = 0; // Pone en digital la patita RB1
    ANSELHbits.ANS8 = 0; // Pone en digital la patita RB2

    TRISB = 0xFF; // PORTB como entrada.
    TRISD = 0xFF;

    OPTION_REGbits.nRBPU = 0; // Habilita las resistencias de pull-up de PORTB.

    TRISC = 0xF7;   // RC3 como salida.
    WPUB = 0xFF;    // Para habilitar las resistencias(por default viene en 1)

    while (1) {

        /******** Configuracion TMR0 ********/

        OPTION_REGbits.T0CS = 0; // oscilador interno
        OPTION_REGbits.T0SE = 1; // para que incremente en flancos de bajada
        OPTION_REGbits.PSA = 0; // asignamos el preescalador al timer0

        // switch (PORTB) {
        //     case 223:
        //         sound(526, 18, 0, 1, 0); // DO 5ta
        //         break;
        //     case 239:
        //         sound(500, 130, 0, 1, 1); // SI
        //         break;
        //     case 251:
        //         sound(435, 112, 0, 1, 1); // LA
        //         break;
        //     case 253:
        //         sound(385, 93, 0, 1, 1); // SOl
        //         break;
        //     case 254:
        //         sound(345, 74, 0, 1, 1); // FA
        //         break;
        //     default:
        //         sound(263, 18, 0, 1, 1); // Nada
        // }
        // switch (PORTD) {
        //     case 127:
        //         sound(333, 162, 1, 0, 0); // MI
        //         break;
        //     case 191:
        //         sound(294, 43, 0, 1, 1); // RE
        //         break;
        //     case 223:
        //         sound(263, 18, 0, 1, 1); // DO
        //         break;
        //     // default:
        //     //     sound(526, 18, 0, 1, 0); // Nada
        // }

        if (PORTBbits.RB5 == 0) {
            // tecla DO 5ta a 256 Hz

            OPTION_REGbits.PS2 = 0;
            OPTION_REGbits.PS1 = 1; // Escala 1:8
            OPTION_REGbits.PS0 = 0;

            TMR0 = 18;

            for (i = 0; i < 526; i++) {
                while (INTCONbits.T0IF != 1) {
                    if (j == 0) {
                        PORTCbits.RC3 = 1;
                    } else {
                        PORTCbits.RC3 = 0;
                    }
                }

                TMR0 = 18;
                INTCONbits.T0IF = 0;

                if (j == 0) {
                    j = 1;
                } else {
                    j = 0;
                }
            }
        } else if (PORTBbits.RB4 == 0) {
            // tecla SI     a 162 Hz
            OPTION_REGbits.PS2 = 0;
            OPTION_REGbits.PS1 = 1; // Escala 1:16
            OPTION_REGbits.PS0 = 1;

            TMR0 = 130;

            for (i = 0; i < 500; i++) {
                while (INTCONbits.T0IF != 1) {
                    if (j == 0) {
                        PORTCbits.RC3 = 1;
                    } else {
                        PORTCbits.RC3 = 0;
                    }
                }

                TMR0 = 130;
                INTCONbits.T0IF = 0;

                if (j == 0) {
                    j = 1;
                } else {
                    j = 0;
                }
            }

            /*for(i = 0; i < 500 ; i++)
            {

                PORTCbits.RC3 = 1;
                __delay_us(1000);
                PORTCbits.RC3 = 0;
                __delay_us(1000);
            }*/
        } else if (PORTBbits.RB2 == 0) { // tecla LA a 434 Hz
            OPTION_REGbits.PS2 = 0;
            OPTION_REGbits.PS1 = 1; // Escala 1:16
            OPTION_REGbits.PS0 = 1;

            TMR0 = 112;

            for (i = 0; i < 435; i++) {
                while (INTCONbits.T0IF != 1) {
                    if (j == 0) {
                        PORTCbits.RC3 = 1;
                    } else {
                        PORTCbits.RC3 = 0;
                    }
                }

                TMR0 = 112;
                INTCONbits.T0IF = 0;

                if (j == 0) {
                    j = 1;
                } else {
                    j = 0;
                }
            }
            /*for(i = 0; i < 435 ; i++)
            {
                PORTCbits.RC3 = 1;
                __delay_us(1150);
                PORTCbits.RC3 = 0;
                __delay_us(1150);
            }*/
        } else if (PORTBbits.RB1 == 0) { // tecla SOL a 383 Hz
            OPTION_REGbits.PS2 = 0;
            OPTION_REGbits.PS1 = 1; // Escala 1:16
            OPTION_REGbits.PS0 = 1;

            TMR0 = 93;

            for (i = 0; i < 385; i++) {
                while (INTCONbits.T0IF != 1) {
                    if (j == 0) {
                        PORTCbits.RC3 = 1;
                    } else {
                        PORTCbits.RC3 = 0;
                    }
                }

                TMR0 = 93;
                INTCONbits.T0IF = 0;

                if (j == 0) {
                    j = 1;
                } else {
                    j = 0;
                }
            }
            /*for(i = 0; i < 385 ; i++)
            {
                PORTCbits.RC3 = 1;
                __delay_us(1300);
                PORTCbits.RC3 = 0;
                __delay_us(1300);
            }*/
        } else if (PORTBbits.RB0 == 0) {
            // tecla FA a 343 Hz
            OPTION_REGbits.PS2 = 0;
            OPTION_REGbits.PS1 = 1; // Escala 1:16
            OPTION_REGbits.PS0 = 1;

            TMR0 = 74;

            for (i = 0; i < 345; i++) {
                while (INTCONbits.T0IF != 1) {
                    if (j == 0) {
                        PORTCbits.RC3 = 1;
                    } else {
                        PORTCbits.RC3 = 0;
                    }
                }

                TMR0 = 74;
                INTCONbits.T0IF = 0;

                if (j == 0) {
                    j = 1;
                } else {
                    j = 0;
                }
            }
            /*for(i = 0; i < 345 ; i++)
            {
                PORTCbits.RC3 = 1;
                __delay_us(1450);
                PORTCbits.RC3 = 0;
                __delay_us(1450);
            }*/
        } else if (PORTDbits.RD7 == 0) { // tecla MI a 664 Hz
            OPTION_REGbits.PS2 = 1;
            OPTION_REGbits.PS1 = 0; // Escala 1:32
            OPTION_REGbits.PS0 = 0;

            TMR0 = 162;

            for (i = 0; i < 333; i++) {
                while (INTCONbits.T0IF != 1) {
                    if (j == 0) {
                        PORTCbits.RC3 = 1;
                    } else {
                        PORTCbits.RC3 = 0;
                    }
                }

                TMR0 = 162;
                INTCONbits.T0IF = 0;

                if (j == 0) {
                    j = 1;
                } else {
                    j = 0;
                }
            }
            /*for(i = 0; i < 333 ; i++)
            {
                PORTCbits.RC3 = 1;
                __delay_us(1500);
                PORTCbits.RC3 = 0;
                __delay_us(1500);
            }*/
        } else if (PORTDbits.RD6 == 0) { // tecla RE a 293 Hz
            OPTION_REGbits.PS2 = 0;
            OPTION_REGbits.PS1 = 1; // Escala 1:16
            OPTION_REGbits.PS0 = 1;

            TMR0 = 43;

            for (i = 0; i < 294; i++) {
                while (INTCONbits.T0IF != 1) {
                    if (j == 0) {
                        PORTCbits.RC3 = 1;
                    } else {
                        PORTCbits.RC3 = 0;
                    }
                }

                TMR0 = 43;
                INTCONbits.T0IF = 0;

                if (j == 0) {
                    j = 1;
                } else {
                    j = 0;
                }
            }
            /*for(i = 0; i < 294 ; i++)
            {
                PORTCbits.RC3 = 1;
                __delay_us(1700);
                PORTCbits.RC3 = 0;
                __delay_us(1700);
            }*/
        } else if (PORTDbits.RD5 == 0) { // tecla DO
            OPTION_REGbits.PS2 = 0;
            OPTION_REGbits.PS1 = 1; // Escala 1:16
            OPTION_REGbits.PS0 = 1;

            TMR0 = 18;

            for (i = 0; i < 263; i++) {
                while (INTCONbits.T0IF != 1) {
                    if (j == 0) {
                        PORTCbits.RC3 = 1;
                    } else {
                        PORTCbits.RC3 = 0;
                    }
                }

                TMR0 = 18;
                INTCONbits.T0IF = 0;

                if (j == 0) {
                    j = 1;
                } else {
                    j = 0;
                }
            }
            /*for(i = 0; i < 263 ; i++)
            {
                PORTCbits.RC3 = 1;
                __delay_us(1900);
                PORTCbits.RC3 = 0;
                __delay_us(1900);
            }*/
        }
    }
}

void sound(int numTMR0, int numComplementoTMR0, int preeS2, int preeS1, int preeS0) {
    int i, j;

    OPTION_REGbits.PS2= preeS2;
    OPTION_REGbits.PS1= preeS1; // Escala 1:8
    OPTION_REGbits.PS0= preeS0;

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
