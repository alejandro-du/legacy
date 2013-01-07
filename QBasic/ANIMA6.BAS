ON KEY(1) GOSUB FIN
KEY(1) ON
RANDOMIZE TIMER
SCREEN 9
A = 0: B = 639: C = 349
FOR A = 0 TO 684 STEP 2
1 LINE (A, A)-(B, C), INT(RND * 15) + 1, B
B = B - 2: C = C - 2
COLOR 11: LOCATE 25, 1: PRINT "                                                                           "; A
NEXT A
FIN:
END

