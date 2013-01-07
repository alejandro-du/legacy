SCREEN 9, 0
COLOR 2, 9: CLS
DIM C(10000)
LINE (40, 70)-(80, 90), 11, BF
LINE (80, 70)-(100, 65), 3
LINE (80, 90)-(100, 85), 3
LINE (80, 70)-(80, 90), 3
LINE (100, 65)-(100, 85), 3
PAINT (90, 80), 3
LINE (40, 70)-(60, 65), 11
LINE (60, 65)-(100, 65), 11
LINE (40, 70)-(80, 70), 11
LINE (80, 70)-(100, 65), 11
PAINT (45, 69), 11
FOR A = 40 TO 80 STEP 3
FOR B = 70 TO 90 STEP 2
PSET (A, B), 3
NEXT B
NEXT A
GET (40, 65)-(100, 90), C
A = 40: B = 65
1 A$ = INPUT$(1)
PUT (A, B), C, XOR
A = A + 5
PUT (A, B), C, XOR
GOTO 1

 '   AND        Combina la imagen almacenada con una imagen
 '              existente.
 '   OR         Superpone la imagen almacenada en una imagen
 '              existente.
 '   PSET       Traza una imagen almacenada, borrando una
 '              imagen existente.
 '   PRESET     Traza una imagen almacenada en colores
 '              inversos, borrando una imagen existente.
 '   XOR        Traza una imagen almacenada o borra una imagen

