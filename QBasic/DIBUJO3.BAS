ON KEY(1) GOSUB FIN
KEY(1) ON
SCREEN 8
B = 0: C = 639: D = 199
FOR A = 1 TO 100
LINE (B, B)-(C, D), 4, B
B = B + 2: C = C - 2: D = D - 2
NEXT A










FIN:
END

