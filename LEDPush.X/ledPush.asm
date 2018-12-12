    #include "p16f887.inc"
    
    ORG 0
    CLRF PORTD
    BSF STATUS, RP0 ;Pasar al banco 1
    MOVLW 0x01	;Momever un '0000 0001' poner el b1 en modo input
    MOVWF TRISD
    BCF STATUS, RP0 ;Pasar al banco 0
PULSO
    BTFSS PORTD, 0
    BCF PORTD,1
    BTFSC PORTD, 0
    BSF PORTD,1
    GOTO PULSO
    END