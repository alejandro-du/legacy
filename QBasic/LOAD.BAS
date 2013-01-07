ON ERROR GOTO errores
CLS
DIM X(6000), Y(6000), c(5000), A(100)
OPEN "e:\dpasoft\QBasic\imagenes\barco2.DRW" FOR INPUT AS #1
A = 0
LOCATE 13, 30: PRINT "Abriendo la imagen..."
DO
A = A + 1
INPUT #1, X(A), Y(A), c(A)
LOOP

1 CLS : PRINT "Ya esta en memoria el dibujo."
PRINT
PRINT "(Presione un tecla para presentar el dibujo)"
A$ = INPUT$(1)

SCREEN 13

FOR b = 1 TO A
PSET (X(b), Y(b)), c(b)
NEXT b
END

errores:
IF ERR = 62 THEN RESUME 1:
RESUME 1

