#include <xc.h>
#define _XTAL_FREQ 4000000 // nuestro cristal es de 8 MHz
#pragma config FOSC = XT // Para especificar que es el high speed por 8 MHz
// #pragma config FOSC = INTRC_CLKOUT
#pragma config WDTE = OFF // Apagamos al perro guardi?n xd

/*
 * T0IF para checar si ya paso el tiempo de cada medio periodo
 * TMR1IF para checar si ya paso un segundo
 * //OPTION_REGbits.T0CS = 0; // para instrucciones internas
 * //OPTION_REGbits.PSA = 0; // Asignamos al timer0 el preescalador
 * //OPTION_REGbits.PS2 = 0; 
 * //OPTION_REGbits.PS1 = 1; // Estos bits son para configurar el preescalador a 1:8
 * //OPTION_REGbits.PS0 = 0;
 * //TMR0 = 18;
 */

void main() {
    // RC3 funciona como la salida de audio
    // de RB0 a RB7 funciona como entradas de los push buttons

    int i = 0;
    int j = 0;
    ANSELHbits.ANS13 = 0; // Pone en digital la patita RB5
    ANSELHbits.ANS11 = 0; // Pone en digital la patita RB4
    ANSELHbits.ANS8 = 0; // Pone en digital la patita RB2
    ANSELHbits.ANS10 = 0; // Pone en digital la patita RB1
    ANSELHbits.ANS12 = 0; // Pone en digital la patita RB0
    TRISB = 0xFF; // coloca todas las patitas de PORTB como entradas(por default viene en 1)
    TRISD = 0xFF; // coloca todas las patitas de PORTD como entradas
    OPTION_REGbits.nRBPU = 0; // habilita las resistencias de pull-up de PORTB
    TRISC = 0xF7; // Habilitamos la pata RC3 como salida
    WPUB = 0xFF; // Para habilitar las resistencias(por default viene en 1)

    while (1) {
        // Para usar el timer0

        OPTION_REGbits.T0CS = 0; // oscilador interno
        OPTION_REGbits.T0SE = 1; // para que incremente en flancos de bajada
        OPTION_REGbits.PSA = 0; // asignamos el preescalador al timer0

        if (PORTBbits.RB5 == 0) {
            // tecla DO 5ta   

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
            // tecla SI
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
        } else if (PORTBbits.RB2 == 0) { // tecla LA
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
        } else if (PORTBbits.RB1 == 0) { // tecla SOL
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
            // tecla FA
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
        } else if (PORTDbits.RD7 == 0) { // tecla MI
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
        } else if (PORTDbits.RD6 == 0) { // tecla RE
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