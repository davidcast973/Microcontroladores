;Oscilador interno
    #include "p16f887.inc"
    __CONFIG _CONFIG1, 0x3FF5 ;Usar Osc. interno y  y apagar el WD

    ORG 0
    BSF STATUS, RP0
    BCF TRISD, 0
    BCF STATUS, RP0

CICLO
    BSF PORTD, 0
    NOP
    NOP
    BCF PORTD, 0
    GOTO CICLO

    END