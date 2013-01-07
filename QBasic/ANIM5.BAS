DIM A(1 TO 600)
B = 0: C = 100
SCREEN 8
LINE (B, 20)-(C, 60), 2, BF
GET (B, 20)-(C, 60), A
1 ' A$ = INPUT$(1)
PUT (B, 20), A
B = B + 20
PUT (B, 20), A, OR
GOTO 1

