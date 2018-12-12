#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config IESO = OFF
#pragma config FCMEN = OFF
// Usa la directiva siguiente dependiendo de tu programador y circuito.
// #pragma config LVP = OFF //NO DESACTIVAR

void confBusLCD(void);
void comando(unsigned int com);
void dato(unsigned int dat);
void retardo(int seg);

int main (void) {
    char r_uno[]= "Te amo mucho <3";
    char r_dos[]= "Atte Tu conejito";
    char vacio[]=" ";
    char estela[]="=";
    int n,m;

    TRISE=0xF8;    // RE0, RE1 y RE2 como salidas.
    ANSEL=0;       // Terminales compartidas como digitales.
    confBusLCD();  // Configura el LCD para usar un bus de 4 bits.
    comando(0x0C); // Enciende el LCD sin cursor.
    comando(0x28); // 2 renglones, caracteres de 5 x 8, nuevamente bus de 4 bits.
    comando(0x01); // Limpia el exhibidor y pone las direcciones a 0.
    comando(0x80); // Apunta a la cuarta columna del primer rengl?n.
    for (n=0; n<15; n++) dato(r_uno[n]); // Escribe el contenido de r_uno.
    comando(0xC0); // Apunta a la cuarta columna del primer rengl?n.
    for (n=0; n<16; n++) dato(r_dos[n]); // Escribe el contenido de r_uno.
    while(1) ;
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

void retardo(int seg) {
    int n,m,tiempo;

    tiempo= seg*10;

    for(n=0;n<tiempo;n++)
        for(m=0;m<10;m++);
}
