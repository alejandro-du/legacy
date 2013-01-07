' NAF:  No A la Fluctuaci¢n.

SCREEN 13
3 x = 1
GOTO 2
1 LINE (x, 60)-(x + 39, 80), 14, BF
LINE (x, 81)-(x + 39, 101), 9, BF
RETURN

2
DO
GOSUB 1
FOR z = 1 TO 600: NEXT z
x = x + 1
GOSUB 1
LINE (x - 1, 60)-(x - 1, 101), 0
IF x > 320 GOTO 3
LOOP

