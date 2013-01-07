'***************************************************************************
'*   Por: Jairo Alejandro Duarte Avenda¤o.                                 *
'*   Redacci¢n: Juan Carlos Duarte Avenda¤o.                               *
'***************************************************************************
ON KEY(1) GOSUB FIN: KEY(1) ON
0 PUNTOSA = 0: PUNTOSB = 0: CLS
LOCATE 3, 50: PRINT "Controles A:"
LOCATE 5, 50: PRINT "Arriba W   Abajo S   Disparo A"
LOCATE 10, 50: PRINT "Controles B"
LOCATE 12, 50: PRINT "Arriba O   Abajo L   Disparo B"
LOCATE 1, 50: PRINT "F1, para parar el juego."
BB = 10: AA = 10
GOTO MP
1 LOCATE AA, 10: PRINT "A"
LOCATE BB, 15: PRINT "B"
A$ = INPUT$(1)
IF A$ = "A" OR A$ = "a" THEN GOTO P
IF A$ = "B" OR A$ = "b" THEN GOTO PB
IF A$ = "W" OR A$ = "w" THEN GOTO MSA
IF A$ = "S" OR A$ = "s" THEN GOTO MAA
IF A$ = "O" OR A$ = "o" THEN GOTO MSB
IF A$ = "L" OR A$ = "l" THEN GOTO MBA ELSE GOTO 1
P:
LOCATE AA, 10: PRINT "-"
FOR A = 1 TO 1000: NEXT A
LOCATE AA, 10: PRINT "A"
IF AA = BB THEN GOTO GA
GOTO 1
PB:
LOCATE BB, 15: PRINT "-"
FOR A = 1 TO 1000: NEXT A
LOCATE BB, 15: PRINT "B"
IF BB = AA THEN GOTO GB
GOTO 1
MAA:
LOCATE AA, 10: PRINT " "
AA = AA + 1
IF AA = 23 THEN AA = 22
GOTO 1
MSA:
LOCATE AA, 10: PRINT " "
AA = AA - 1
IF AA = 0 THEN AA = 1
GOTO 1
MBA:
LOCATE BB, 15: PRINT " "
BB = BB + 1
IF BB = 23 THEN BB = 22
GOTO 1
MSB:
LOCATE BB, 15: PRINT " "
BB = BB - 1
IF BB = 0 THEN BB = 1
GOTO 1
GA:
LOCATE 22, 30: PRINT "Gana: A"
FOR A = 37 TO 45: SOUND A, 1: NEXT A
LOCATE 22, 30: PRINT "       "
PUNTOSA = PUNTOSA + 3: GOTO MP
GB:
LOCATE 22, 30: PRINT "Gana: B"
FOR A = 37 TO 45: SOUND A, 1: NEXT A
LOCATE 22, 30: PRINT "       "
PUNTOSB = PUNTOSB + 3: GOTO MP
MP:
LOCATE 18, 50: PRINT "Puntos A: "; PUNTOSA
LOCATE 19, 50: PRINT "Puntos B: "; PUNTOSB
GOTO 1
FIN:
END

