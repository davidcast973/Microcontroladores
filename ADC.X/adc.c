/*
 * File:   adc.c
 * Author: david
 *
 * Created on December 6, 2018, 4:49 PM
 */


#include <xc.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000
#pragma config FOSC = INTRC_CLKOUT
#pragma config WDTE = OFF
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config IESO = OFF
#pragma config FCMEN = OFF

void confBusLCD(void);
void comando(unsigned int com);
void dato(unsigned int dat);

void main(void) {
    unsigned char msb, lsb; //, temp;
    // float temp;

    /******* Configuracion de la LCD ********/

    // TRISE=0xF8;    // RE0, RE1 y RE2 como salidas.
    // ANSEL=0;       // Terminales compartidas como digitales.
    // confBusLCD();  // Configura el LCD para usar un bus de 4 bits.
    // comando(0x0C); // Enciende el LCD sin cursor.
    // comando(0x28); // 2 renglones, caracteres de 5 x 8, nuevamente bus de 4 bits.
    // comando(0x01); // Limpia el exhibidor y pone las direcciones a 0.
    // comando(0x80); // Apunta a la cuarta columna del primer rengl?n.
    // printf("%s", "Temperatura:");

    /****** Configuracion para USART ********/

    SPBRG = 25; // Con 6 o 5 de BRGH en 0 habra error porque no se
                // acerca a 9600 que es la velocidad con la que trabaja
                // la computadora.
    TXSTAbits.TXEN = 1;
    TXSTAbits.BRGH = 1; // 0: Baja velocidad, 1: Alta velocidad.
    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;

    /****** Configuracion para ADC ********/

    // TRISA = 0xFF; // Declarar puerto A como  entrada
    // ANSEL = 1; // Declara entradas del puerto A como analogicas
    TRISAbits.TRISA1 = 1;   // Puerto RA 3 analogico como entrada.

    //////// Registro ADCON0 Pag. 387 de "PICmicreo Mid-Range MCU Family"
    //////// Registro ADCON0 Pag. 106 de "PICF1688x"

    // A/D Seleccion de bits del reloj convertidor
    ADCON0bits.ADCS = 0b01; // ADCS1: 0 y ADCS0: 1
                            // Fosc(4MHz)/8 para TAD a 2 microsegundos.
    // Seleccion del canal analogico
    ADCON0bits.CHS = 0b0001;    // CHS3: 0, CHS2: 0, CHS1: 1, CHS0: 1
                                // Canal 3, (AN3) Pin 3 del puerto A
                                // Pin 5 del PIC16F887.
    // A/D en bit
    ADCON0bits.ADON = 1; // A/D Modulo convertidor esta en operacion

    //////// Registro ADCON1 Pag. 388 de "PICmicreo Mid-Range MCU Family"
    //////// Registro ADCON1 Pag. 107 de "PICF1688x"

    // A/D Formato para el resultado
    ADCON1bits.ADFM = 0;    // Justificado a la izquierda.
                            // Los 6 MSB de ADRESH son leidos como '0'.
    // Bit de voltaje de referencia
    ADCON1bits.VCFG1 = 1; // El voltaje de referencia negativo sera VSS.
    ADCON1bits.VCFG0 = 1; // El voltaje de referencia positivo sera VDD.

    while (1) {
        __delay_ms(1000);

        // Estado de la conversion
        ADCON0bits.GO = 1;  // Ciclo de conversion A/D en progreso.
                            // Configuracion de este bit empieza en ciclo
                            // Este bit se limpia automaticamente por el hardware
                            // cuando la conversion A/D fue completada.

        // while(ADCON0bits.nDONE == 1) ;       // No hara nada hasta que finalice el ADC

        while (PIR1bits.ADIF != 1) { // Interruptor de la bandera del convertidor
            NOP();
        }

        // ADRESH: Resultado del ADC en bits
        // temp = ADRESH;
        // temp = ADRESH * 256;
        // temp += ADRESL;

        // Resolusion
        //temp *= 0.004887586;
        //temp *= 100;

        while (PIR1bits.TXIF != 1) ;
        TXREG = ADRESH;

        // comando(0xC0);
        // printf("%3.1f", temp);
        //
        // comando(0xC4);
        // printf("C");

        // PIR1bits.ADIF = 0; // Desabilitar la bandera
    }
}

void confBusLCD(void) {
    int t, estado;

    // Asign? ceros a t para producir retardos peque?os.
    PORTEbits.RE0=0; t=0;  // RS indica comando.
    PORTEbits.RE1=1; t=0;  // RW indica leer del LCD.
    do {
        PORTEbits.RE2=1; t=0; // Sube el habilitador E.
        estado=(PORTD&0x80);  // Lee bandera de ocupado (BF).
        PORTEbits.RE2=0; t=0; // Baja el habilitador E.
    } while (estado!=0);   // Espera a que el LCD est? desocupado.
    PORTEbits.RE1=0;       // RW indica escribir al LCD.
    TRISD=0x0F;            // RD7 a RD3 como salidas.
    PORTD=0x20;            // Ordena usar bus de 4 bits.
    PORTEbits.RE2=1; t=0;  // Sube el habilitador E.
    PORTEbits.RE2=0; t=0;  // Baja el habilitador E.
    TRISD=0xFF;            // Puerto D como entrada.
}

void comando(unsigned int com) {
    int t, estado;

    // Asign? ceros a t para producir retardos peque?os.
    PORTEbits.RE0=0; t=0;  // RS indica comando.
    PORTEbits.RE1=1; t=0;  // RW indica leer del LCD.
    do {
        PORTEbits.RE2=1; t=0; // Sube el habilitador E.
        estado=(PORTD&0x80);  // Lee bandera de ocupado (BF).
        PORTEbits.RE2=0; t=0; // Baja el habilitador E.
        PORTEbits.RE2=1; t=0; // Sube el habilitador E.
        PORTEbits.RE2=0; t=0; // Baja el habilitador E.
    } while (estado!=0);   // Espera a que el LCD est? desocupado.
    PORTEbits.RE1=0;       // RW indica escribir al LCD.
    TRISD=0x0F;            // RD7 a RD3 como salidas.
    PORTD=com;
    PORTEbits.RE2=1; t=0;  // Sube el habilitador E.
    PORTEbits.RE2=0; t=0;  // Baja el habilitador E.
    PORTD=(com<<4);
    PORTEbits.RE2=1; t=0;  // Sube el habilitador E.
    PORTEbits.RE2=0; t=0;  // Baja el habilitador E.
    TRISD=0xFF;            // Puerto D como entrada.
}

void dato(unsigned int dat) {
    int t, estado;

    // Asign? ceros a t para producir retardos peque?os.
    PORTEbits.RE0=0; t=0;  // RS indica comando.
    PORTEbits.RE1=1; t=0;  // RW indica leer del LCD.
    do {
        PORTEbits.RE2=1; t=0; // Sube el habilitador E.
        estado=(PORTD&0x80);  // Lee bandera de ocupado (BF).
        PORTEbits.RE2=0; t=0; // Baja el habilitador E.
        PORTEbits.RE2=1; t=0; // Sube el habilitador E.
        PORTEbits.RE2=0; t=0; // Baja el habilitador E.
    } while (estado!=0);   // Espera a que el LCD est? desocupado.
    PORTEbits.RE0=1; t=0;  // RS indica dato.
    PORTEbits.RE1=0;       // RW indica escribir al LCD.
    TRISD=0x0F;            // RD7 a RD3 como salidas.
    PORTD=dat;
    PORTEbits.RE2=1; t=0;  // Sube el habilitador E.
    PORTEbits.RE2=0; t=0;  // Baja el habilitador E.
    PORTD=(dat<<4);
    PORTEbits.RE2=1; t=0;  // Sube el habilitador E.
    PORTEbits.RE2=0; t=0;  // Baja el habilitador E.
    TRISD=0xFF;            // Puerto D como entrada.
}