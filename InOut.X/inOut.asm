;Programa que saca por RD0 lo que haya en RD1
    #include "p16f887.inc"
    __CONFIG _CONFIG1, 0x3FF5
    ORG 0
    BSF STATUS, RP0	;Cambiar al banco 1
    BCF TRISD, RD0	;Configuramos RD0 para que este en modo salida.
    BCF STATUS, RP0	;Cambiar al banco 0
    
CICLO
    BTFSC PORTD, RD1	;Prende a RD0 si esta apagado RD1
    BSF PORTD, RD0
    BTFSS PORTD, RD1	;Apaga a RD0 si esta prendido RD1
    BCF PORTD, RD0
    GOTO CICLO
    END


