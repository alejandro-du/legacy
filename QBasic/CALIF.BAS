CLS : SCREEN 0: WIDTH 80, 25
LOCATE 1, 17: PRINT "Programa para administrar notas de alumnos"
LOCATE 8, 1: PRINT "1. Introducci¢n de notas."
LOCATE 10, 1: PRINT "2. Consultar calificaciones."
1 a$ = INPUT$(1)
IF a$ = "1" THEN GOTO idn
IF a$ = "2" THEN GOTO cc ELSE GOTO 1

idn:
CLS
LOCATE 1, 20: PRINT "Introducci¢n de notas"
LOCATE 4, 1: INPUT "N£mero de alumnos"; nda
INPUT "N£mero de notas"; ndn

