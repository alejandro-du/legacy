INPUT x
INPUT y
CLS

FOR a = 2 TO x - 1
LOCATE 1, a: PRINT "*"
LOCATE y, a: PRINT "*"
NEXT a

FOR a = 1 TO y
LOCATE a, 1: PRINT "*"
LOCATE a, x: PRINT "*"
NEXT a

