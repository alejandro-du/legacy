'Autor: Juan Carlos Duarte Avenda�o

INI:
RANDOMIZE TIMER
ON KEY(1) GOSUB SAL: KEY(1) ON
SCREEN 9
COLORF = INT(RND * 15) + 0
COLOR 0, COLORF: CLS
1 A = INT(RND * 639) + 0
B = INT(RND * 329) + 0
C = INT(RND * 60) + 1
D = INT(RND * 15) + 0
E = RND * 5 + 1
F = RND * 4 + 1
G = RND * 6 + 0
CIRCLE (A, B), C, D, E, F, G
A$ = INKEY$
IF A$ = CHR$(78) OR A$ = CHR$(110) THEN GOTO INI
IF A$ = CHR$(50) THEN RUN "ANIM17.BAS"
IF A$ = CHR$(27) THEN GOTO SAL
GOTO 1
SAL:
SCREEN 0
END

