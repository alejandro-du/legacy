    'Este ejemplo requiere las teclas Bloq May£s y Bloq Num desactivadas.
    CONST ESC = 27
    KEY 15, CHR$(4) + CHR$(31)                'Define Ctrl+S como KEY 15.
    ON KEY(15) GOSUB PauseHandler
    KEY(15) ON
    WHILE INKEY$ <> CHR$(ESC)
        PRINT "Presione Esc para parar, Ctrl+S para hacer una pausa."
        PRINT
    WEND
    END

PauseHandler:
        SLEEP 1
        RETURN

