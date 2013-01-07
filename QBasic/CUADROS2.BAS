INPUT x
INPUT y
INPUT x1
INPUT y1
CLS


FOR a = x1 + 1 TO x1 + x - 2
LOCATE y1, a: PRINT "*"
LOCATE y1 + y - 1, a: PRINT "*"
NEXT a

FOR a = y1 TO y1 + y - 1
LOCATE a, x1: PRINT "*"
LOCATE a, x1 + x - 1: PRINT "*"
NEXT a

