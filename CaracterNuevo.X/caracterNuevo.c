#include <xc.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000

#pragma config FOSC = INTRC_CLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config IESO = OFF
#pragma config FCMEN = OFF

void configurarLCD();
void crearCaracter(unsigned char *pattern, unsigned char address);
void comando(unsigned char command);
void escribirDato(unsigned char data);

/*
 * RE0:PORTEbits.RE0
 * RE1:PORTEbits.RE1
 * RE2:E
 */

int main(void) {
    unsigned char pattern1[] = {0x00, 0x03, 0x07, 0x0E, 0x1D, 0x19, 0x1E, 0x0F}; // tablero ajedrez

    /*
    * 000 00000
    * 000 00011
    * 000 00111
    * 000 01110
    * 000 11101
    * 000 11001
    * 000 11101
    * 000 01111
    */
    unsigned char pattern2[] = {0x00, 0x1F, 0x1F, 0x18, 0x10, 0x10, 0x1F, 0x1F}; // tablero ajedrez

    /*
    * 000 11111
    * 000 11111
    * 000 11000
    * 000 10000
    * 000 10000
    * 000 11111
    * 000 11111
    */
    unsigned char pattern3[] = {0x00, 0x1F, 0x1F, 0x06, 0x03, 0x00, 0x1F, 0x1F}; // tablero ajedrez

    /*
    * 000 11111
    * 000 11111
    * 000 00110
    * 000 00011
    * 000 00000
    * 000 11111
    * 000 11111
    */
    unsigned char pattern4[] = {0x00, 0x18, 0x1E, 0x1E, 0x17, 0x03, 0x07, 0x17}; // tablero ajedrez

    /*
    * 000 11000
    * 000 11110
    * 000 11110
    * 000 10111
    * 000 00011
    * 000 00111
    * 000 10111
    */
    unsigned char pattern5[] = {0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00}; // tablero ajedrez

    /*
    * 000 00111
    * 000 00011
    * 000 00001
    * 000 00000
    * 000 00000
    * 000 00000
    * 000 00000
    */
    unsigned char pattern6[] = {0x00, 0x16, 0x1F, 0x1C, 0x0E, 0x07, 0x03, 0x01}; // tablero ajedrez

    /*
    * 000 00000
    * 000 10110
    * 000 11111
    * 000 11100
    * 000 01110
    * 000 00111
    * 000 00011
    * 000 00001
    */
    unsigned char pattern7[] = {0x01, 0x03, 0x1F, 0x07, 0x0E, 0x1C, 0x18, 0x10}; // tablero ajedrez

    /*
    * 000 00001
    * 000 00011
    * 000 11111
    * 000 00111
    * 000 01110
    * 000 11100
    * 000 11000
    * 000 10000
    */
    unsigned char pattern8[] = {0x1C, 0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00}; // tablero ajedrez

    /*
    * 000 11100
    * 000 11000
    * 000 10000
    * 000 00000
    * 000 00000
    * 000 00000
    * 000 00000
    * 000 00000
    */

    TRISD = 0xFF; // PUERTO D como entrada
    TRISE = 0xF8; // E0, E1 y E2 como salidas
    ANSEL = 0; // Terminales compartidas como digitales
    configurarLCD();
    comando(0x0C); // Enciende el LCD sin cursor.
    comando(0x28); // 8 BITS 2 RENGLONES
    comando(0x01); // Limpia el exhibidor y pone las direcciones a 0.
    crearCaracter(pattern1, 0);
    crearCaracter(pattern2, 1);
    crearCaracter(pattern3, 2);
    crearCaracter(pattern4, 3);
    crearCaracter(pattern5, 4);
    crearCaracter(pattern6, 5);
    crearCaracter(pattern7, 6);
    crearCaracter(pattern8, 7);
    comando(0x01); // Limpia el exhibidor y pone las direcciones a 0. 
    while (1) {       
        comando(0x86); // apunta al primer renglon
        escribirDato(0);
        comando(0x87); // apunta al primer renglon
        escribirDato(1);
        comando(0x88); // apunta al primer renglon
        escribirDato(2);
        comando(0x89); // apunta al primer renglon
        escribirDato(3);
        comando(0xC6); // apunta al primer renglon
        escribirDato(4);
        comando(0xC7); // apunta al primer renglon
        escribirDato(5);
        comando(0xC8); // apunta al primer renglon
        escribirDato(6);
        comando(0xC9); // apunta al primer renglon
        escribirDato(7);
    }
}

void configurarLCD() {
    int t, estado;
    PORTEbits.RE0 = 0; // indica comando.
    t = 0;
    PORTEbits.RE1 = 1; // indica leer del LCD.
    t = 0;
    do {
        PORTEbits.RE2 = 1;
        t = 0;
        estado = (PORTD & 0x80); // Lee bandera de ocupado (BF).
        PORTEbits.RE2 = 0;
        t = 0;
    } while (estado != 0); // Espera a que el LCD est? desocupado.
    PORTEbits.RE1 = 0; // indica escribir al LCD.
    TRISD = 0x0F; // PUERTO D como salidas.
    PORTD=0x20;   // Ordena usar bus de 4 bits.
    PORTEbits.RE2 = 1;
    t = 0;
    PORTEbits.RE2 = 0;
    t = 0;
    TRISD = 0xFF; // Puerto D como entrada
}

void crearCaracter(unsigned char *pattern, unsigned char address) {
    unsigned char i;
    /* establece la direccion a usar en la memoria
     * de generacion de caractereres CGRAM */
    comando(0x40 + (address * 8)); // posision
    for (i = 0; i < 8; i++) {
        escribirDato(pattern[i]);
    }
}

void comando(unsigned char command) {
    int t, estado;
    PORTEbits.RE0 = 0; // indica comando.
    t = 0;
    PORTEbits.RE1 = 1; // indica leer del LCD.
    t = 0;
    do {
        PORTEbits.RE2 = 1;
        t = 0;
        estado = (PORTD & 0x80); // Lee bandera de ocupado (BF)
        PORTEbits.RE2 = 0;
        t = 0;
        PORTEbits.RE2 = 1;
        t = 0;
        PORTEbits.RE2 = 0;
        t = 0;
    } while (estado != 0); // Espera a que el LCD est? desocupado.
    PORTEbits.RE1 = 0; // indica escribir al LCD.
    TRISD=0x0F;            // RD7 a RD3 como salidas.
    PORTD=command;
    PORTEbits.RE2=1; t=0;  // Sube el habilitador E.
    PORTEbits.RE2=0; t=0;  // Baja el habilitador E.
    PORTD=(command<<4);
    PORTEbits.RE2=1; t=0;  // Sube el habilitador E.
    PORTEbits.RE2=0; t=0;  // Baja el habilitador E.
    TRISD=0xFF;            // Puerto D como entrada.
}

void escribirDato(unsigned char data) {
    int t, estado;
    PORTEbits.RE0 = 0; // indica comando.
    t = 0;
    PORTEbits.RE1 = 1; // indica leer del LCD.
    t = 0;
    do {
        PORTEbits.RE2 = 1;
        t = 0;
        estado = (PORTD & 0x80); // Lee bandera de ocupado (BF)
        PORTEbits.RE2 = 0;
        t = 0;
        PORTEbits.RE2 = 1;
        t = 0;
        PORTEbits.RE2 = 0;
        t = 0;
    } while (estado != 0); // Espera a que el LCD est? desocupado.
    /*
     * el procesador entrega un dato al exhibidor.
     * el uso del dato depende si en la operacion anterior
     * se establevi? una direccion para la DDRAM o CGRAM
     */
    PORTEbits.RE0 = 1; // escribir un dato
    PORTEbits.RE1 = 0;
    TRISD=0x0F;            // RD7 a RD3 como salidas.
    PORTD=data;
    PORTEbits.RE2=1; t=0;  // Sube el habilitador E.
    PORTEbits.RE2=0; t=0;  // Baja el habilitador E.
    PORTD=(data<<4);
    PORTEbits.RE2=1; t=0;  // Sube el habilitador E.
    PORTEbits.RE2=0; t=0;  // Baja el habilitador E.
    TRISD=0xFF;            // Puerto D como entrada.
}
