;Hacer una matriz (arreglo bidimencional) de 64 espacios.
    #include "p16f887.inc"
    __CONFIG _CONFIG1, 03FF5  ;Para apagar el Watchdog
    
    UDATA 020
CONT
    RES 1
NUM RES 1
    
    ORG 0
    CALL PUERTOS ;Cambiar RD0 a RD5 para tener 6 salidas (las necesarias)
    MOVLW .64
    MOVWF CONT
    CLRF NUM
    MOVLW 0x40 ;Guardar los numeros a partir de la dir 0x40
    MOVWF FSR

ASIGNACION    
    MOVF NUM, W ;Poner contenido de NUM en W
    MOVWF INDF ;Mueve el contenido de w a la dir de FSR (con INDF)
    
    INCF FSR, F ;Aumentar en uno para cambiar de una en una direccion
    INCF NUM, F ;Aumentar para ir de 0 a 64
    DECFSZ CONT, F ;Llegar a NUM == 63
    GOTO ASIGNACION

ITERAR    
    MOVLW 040 ;Empezar de nuevo en la dir 0x40
    MOVWF FSR
    MOVLW .64
    MOVWF CONT
FIN
    MOVF INDF, W ;Ponemos en W el contenido de la dir de INDF
    MOVWF PORTD ;Mostramos en PORTD
    INCF FSR, F	;Cambiar de dir
    DECFSZ CONT, F ;Iteramos de 64 a 0
    GOTO FIN
    GOTO ITERAR
    
PUERTOS ;Cambiar RD0 a RD5 para tener 6 salidas (las necesarias)
    BSF STATUS, RP0
    MOVLW 0xC0	    ;1100 0000 utltimos dos como entradas los demás salidas.
    MOVWF TRISD
    BCF STATUS, RP0
    RETURN
    
    END





