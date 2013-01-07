SCREEN 13
C = 5
B = 2
A:
B = B + 1
FOR A = 0 TO 199 STEP 2
C = C + B - A
LINE (A, B)-(B, A)
'LINE (0, 1)-(319, A),
COLOR A


'LOCATE 25, 1: PRINT "     "
NEXT A
GOTO A

