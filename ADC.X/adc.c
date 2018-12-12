/*
 * File:   adc.c
 * Author: david
 *
 * Created on December 6, 2018, 4:49 PM
 */


#include <xc.h>
#include <stdio.h>

#pragma config FOSC = INTRC_CLKOUT
#pragma config WDTE = OFF
#define _XTAL_FREQ 4000000

void initUSART(void);
void initADC(void);
void escribeUSART(unsigned char dato);

void main(void) {
    unsigned char msb, lsb, res;

    /****** Configuracion para USART ********/

    SPBRG = 25; // Con 6 o 5 de BRGH en 0 habra error porque no se
                // acerca a 9600 que es la velocidad con la que trabaja
                // la computadora.
    TXSTAbits.TXEN = 1;
    TXSTAbits.BRGH = 1; // 0: Baja velocidad, 1: Alta velocidad.
    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;

    /****** Configuracion para ADC ********/

    TRISA = 0xFF; // Declarar puerto A como  entrada
    ANSEL = 1; // Declara entradas del puerto A como analogicas

    //////// Registro ADCON0 Pag. 387 de "PICmicreo Mid-Range MCU Family"
    //////// Registro ADCON0 Pag. 106 de "PICF1688x"

    // A/D Seleccion de bits del reloj convertidor
    ADCON0bits.ADCS = 0b01; // ADCS0: 0 y ADCS1: 1
                            // Fosc(4MHz)/8 para TAD a 2 microsegundos.
    // Seleccion del canal analogico
    ADCON0bits.CHS = 0b0011;    // CHS3: 0, CHS2: 0, CHS1: 0, CHS0: 1
                                // Canal 3, (AN3) Pin 3 del puerto A
                                // Pin 5 del PIC16F887.
    // A/D en bit
    ADCON0bits.ADON = 1; // A/D Modulo convertidor esta en operacion

    //////// Registro ADCON1 Pag. 388 de "PICmicreo Mid-Range MCU Family"
    //////// Registro ADCON1 Pag. 107 de "PICF1688x"

    // A/D Formato para el resultado
    ADCON1bits.ADFM = 1;    // Justificado a la derecha.
                            // Los 6 MSB de ADRESH son leidos como '0'.
    // Bit de voltaje de referencia
    ADCON1bits.VCFG1 = 0; // El voltaje de referencia negativo será VSS.
    ADCON1bits.VCFG0 = 0; // El voltaje de referencia positivo será VDD.

    while (1) {
        __delay_ms(1000);

        // Estado de la conversion
        ADCON0bits.GO = 1;  // Ciclo de conversion A/D en progreso.
                            // Configuracion de este bit empieza en ciclo
                            // Este bit se limpia automaticamente por el hardware
                            // cuando la conversion A/D fue completada.

        // while(ADCON0bits.nDONE == 1) ;       // No hará nada hasta que finalice el ADC

        while (PIR1bits.ADIF != 1) { // Interruptor de la bandera del convertidor
            NOP();
        }

        // ADRESH: Resultado del ADC en bits        
        res = ADRESH * 256;
        res += ADRESL;
        
        // Resolución
        res *= 0.004887586;
        res *= 100;
        
        while (PIR1bits.TXIF != 1) ;
        TXREG = res;

        PIR1bits.ADIF = 0; // Desabilitar la bandera
    }
}