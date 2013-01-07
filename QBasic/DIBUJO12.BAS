SCREEN 13:  'Adaptador VGA
C = 17
FOR A = 118 TO 132
LINE (0, A)-(319, A - 100), C
C = C + 1
NEXT A
FOR A = 132 TO 147
C = C - 1
LINE (0, A)-(319, A - 100), C
NEXT A

