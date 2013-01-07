SCREEN 13:  'Adaptador VGA
X = 0
C = 17
FOR B = 1 TO 8
FOR A = X TO X + 13
LINE (0, A)-(319, A), C
C = C + 1
NEXT A
FOR A = X + 13 TO X + 26
C = C - 1
LINE (0, A)-(319, A), C
NEXT A
X = X + 26
NEXT B
SLEEP

