'Demostraci¢n del zoom de una imagen
'Por: Jairo Alejandro Duarte Avenda¤o
'Mayo de 1997

SCREEN 13
DIM IMAGEN(11, 11)

LINE (0, 0)-(10, 10), 1, BF
LINE (0, 0)-(10, 10), 7, B
PSET (0, 0), 25
PSET (10, 0), 25
PSET (0, 10), 25
PSET (10, 10), 25
PSET (5, 0), 26
PSET (0, 5), 26
PSET (10, 5), 26
PSET (5, 10), 26
LINE (5, 1)-(5, 9), 9
LINE (1, 5)-(9, 5), 8
CIRCLE (5, 5), 4, 2
PSET (5, 5), 25

COLOR 11
LOCATE 22, 1
PRINT "Imagen original"
COLOR 7
PRINT "Presione una tecla para continuar."
FOR Y = 0 TO 10
  FOR X = 0 TO 10
    IMAGEN(X, Y) = POINT(X, Y)
  NEXT X
NEXT Y
a$ = INPUT$(1)

SCREEN 0
WIDTH 80, 25
PRINT "La imagen esta en memoria."
PRINT
INPUT "Entre el nivel de zoom: "; nivel
SCREEN 13

FOR YP = 0 TO 10 * nivel STEP nivel
  FOR XP = 0 TO 10 * nivel STEP nivel
    CP = IMAGEN(XI, YI)
    FOR YF = YP TO YP + nivel - 1
      FOR XF = XP TO XP + nivel - 1
        PSET (XF, YF), CP
      NEXT XF
    NEXT YF
    XI = XI + 1
  NEXT XP
  XI = 0
  YI = YI + 1
NEXT YP
a$ = INPUT$(1)

