'Creado el 20 de Noviembre/95
' Por: Jairo ALejandro Duarte Avenda¤o.
5 RANDOMIZE TIMER
DIM LINEA$(11), NUM(14)
COLOR 15, 2: CLS
COLOR 0, 9
FOR B = 10 TO 70
FOR A = 5 TO 20
LOCATE A, B: PRINT " "
NEXT A
NEXT B
FOR A = 6 TO 21
LOCATE A, 72: PRINT "Û"
LOCATE A, 71: PRINT "Û"
NEXT A
FOR A = 12 TO 70
LOCATE 21, A: PRINT "Û"
NEXT A
COLOR 22
LOCATE 5, 10: PRINT " * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
COLOR 2
LOCATE 5, 15: PRINT "  B I N G O  "
COLOR 7
FOR A = 10 TO 70
LOCATE 6, A: PRINT "Ä"
NEXT A
COLOR 3
LOCATE 8, 11
PRINT "Numero de tableros ?"
LOCATE 8, 32
INPUT "", A
LOCATE 10, 11
PRINT "Inserte papel en impresora puerto LPT1."
LOCATE 11, 11
PRINT "Presione ENTER para comenzar la impresi¢n..."
A$ = INPUT$(1)
IF A$ = CHR$(13) THEN GOTO 2
2 FOR B = 1 TO A
LOCATE 14, 11
PRINT "Imprimiendo tablero n£mero:"; B
LPRINT "  "
LPRINT "  "
LPRINT "ÚÄ´ B I N G O ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿"
LPRINT "³                                              ³"
LPRINT "³     "; INT(RND * 100) + 1; "         "; INT(RND * 100) + 1; "          "; INT(RND * 100) + 1; "          ³"
LPRINT "³                                              ³"
LPRINT "³     "; INT(RND * 100) + 1; "         "; INT(RND * 100) + 1; "          "; INT(RND * 100) + 1; "          ³"
LPRINT "³                                              ³"
LPRINT "³     "; INT(RND * 100) + 1; "         "; INT(RND * 100) + 1; "          "; INT(RND * 100) + 1; "          ³"
LPRINT "³                                              ³"
LPRINT "³                                              ³"
LPRINT "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ"
NEXT B
LOCATE 17, 11: PRINT "Impresi¢n Terminada."
A$ = INPUT$(1)
FOR A = 8 TO 17
FOR B = 11 TO 54
LOCATE A, B: PRINT " "
NEXT B
NEXT A
FOR A = 1 TO 9
LOCATE 8, 11: PRINT A; "§ N£mero: "; INT(RND * 100) + 1
A$ = INPUT$(1)
NEXT A
GOTO 5

