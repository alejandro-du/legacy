1 :
10 '************ CALEIDOSCOPIO *************
20 '
30 KEY OFF: CLS : SCREEN 1
40 '
50 '*** COMIENCIO BUCLE PRINCIPAL ***
60 '
70 U = INT(10 * RND): X = 9 - INT((U + 1) * RND): Y = 9 - INT((U + 1) * RND): C = INT(4 * RND)
80 LINE (16 * X, 10 * Y)-(16 * X + 15, 10 * Y + 9), C, BF
90 LINE (304 - 16 * X, 10 * Y)-(319 - 16 * X, 10 * Y + 9), C, BF
100 LINE (16 * X, 190 - 10 * Y)-(16 * Y + 15, 199 - 10 * Y), C, BF
110 LINE (304 - 16 * X, 190 - 10 * Y)-(319 - 16 * X, 199 - 10 * Y), C, BF
120 LINE (16 * Y, 10 * X)-(16 * Y + 15, 10 * X + 9), C, BF
A$ = INKEY$
IF A$ = " " THEN GOTO 170
IF A$ = "3" THEN GOTO 3
IF A$ = "4" THEN GOTO 4
IF A$ = "2" THEN GOTO 2
130 LINE (16 * Y, 190 - 10 * X)-(16 * Y + 15, 199 - 10 * X), C, BF
140 LINE (304 - 16 * Y, 10 * X)-(319 - 16 * Y, 10 * X + 9), C, BF
150 LINE (304 - 16 * Y, 190 - 10 * X)-(319 - 16 * Y, 199 - 10 * X), C, BF
165 CLS : GOTO 70
170 END
2 :
11 '************ CALEIDOSCOPIO *************
21 '
31 KEY OFF: CLS : SCREEN 7
41 '
51 '*** COMIENCIO BUCLE PRINCIPAL ***
61 '
71 U = INT(10 * RND): X = 9 - INT((U + 1) * RND): Y = 9 - INT((U + 1) * RND): C = INT(15 * RND)
81 LINE (16 * X, 10 * Y)-(16 * X + 15, 10 * Y + 9), C, BF
91 LINE (304 - 16 * X, 10 * Y)-(319 - 16 * X, 10 * Y + 9), C, BF
101 LINE (16 * X, 190 - 10 * Y)-(16 * Y + 15, 199 - 10 * Y), C, BF
111 LINE (304 - 16 * X, 190 - 10 * Y)-(319 - 16 * X, 199 - 10 * Y), C, BF
121 LINE (16 * Y, 10 * X)-(16 * Y + 15, 10 * X + 9), C, BF
A$ = INKEY$
IF A$ = " " THEN GOTO 170
IF A$ = "3" THEN GOTO 3
IF A$ = "4" THEN GOTO 4
IF A$ = "1" THEN GOTO 1
131 LINE (16 * Y, 190 - 10 * X)-(16 * Y + 15, 199 - 10 * X), C, BF
141 LINE (304 - 16 * Y, 10 * X)-(319 - 16 * Y, 10 * X + 9), C, BF
151 LINE (304 - 16 * Y, 190 - 10 * X)-(319 - 16 * Y, 199 - 10 * X), C, BF
166 CLS : GOTO 71
171 END
3 :
12 '************ CALEIDOSCOPIO *************
22 '
32 KEY OFF: CLS : SCREEN 1
42 '
52 '*** COMIENCIO BUCLE PRINCIPAL ***
62 '
72 U = INT(10 * RND): X = 9 - INT((U + 1) * RND): Y = 9 - INT((U + 1) * RND): C = INT(4 * RND)
82 LINE (16 * X, 10 * Y)-(16 * X + 15, 10 * Y + 9), C, BF
92 LINE (304 - 16 * X, 10 * Y)-(319 - 16 * X, 10 * Y + 9), C, BF
102 LINE (16 * X, 190 - 10 * Y)-(16 * Y + 15, 199 - 10 * Y), C, BF
112 LINE (304 - 16 * X, 190 - 10 * Y)-(319 - 16 * X, 199 - 10 * Y), C, BF
122 LINE (16 * Y, 10 * X)-(16 * Y + 15, 10 * X + 9), C, BF
A$ = INKEY$
IF A$ = " " THEN GOTO 170
IF A$ = "2" THEN GOTO 2
IF A$ = "4" THEN GOTO 4
IF A$ = "1" THEN GOTO 1
132 LINE (16 * Y, 190 - 10 * X)-(16 * Y + 15, 199 - 10 * X), C, BF
142 LINE (304 - 16 * Y, 10 * X)-(319 - 16 * Y, 10 * X + 9), C, BF
152 LINE (304 - 16 * Y, 190 - 10 * X)-(319 - 16 * Y, 199 - 10 * X), C, BF
167 GOTO 72
172 END
4 :
13 '************ CALEIDOSCOPIO *************
23 '
33 KEY OFF: CLS : SCREEN 7
43 '
53 '*** COMIENCIO BUCLE PRINCIPAL ***
63 '
73 U = INT(10 * RND): X = 9 - INT((U + 1) * RND): Y = 9 - INT((U + 1) * RND): C = INT(15 * RND)
83 LINE (16 * X, 10 * Y)-(16 * X + 15, 10 * Y + 9), C, BF
93 LINE (304 - 16 * X, 10 * Y)-(319 - 16 * X, 10 * Y + 9), C, BF
103 LINE (16 * X, 190 - 10 * Y)-(16 * Y + 15, 199 - 10 * Y), C, BF
113 LINE (304 - 16 * X, 190 - 10 * Y)-(319 - 16 * X, 199 - 10 * Y), C, BF
123 LINE (16 * Y, 10 * X)-(16 * Y + 15, 10 * X + 9), C, BF
A$ = INKEY$
IF A$ = " " THEN GOTO 170
IF A$ = "3" THEN GOTO 3
IF A$ = "1" THEN GOTO 1
IF A$ = "2" THEN GOTO 2
133 LINE (16 * Y, 190 - 10 * X)-(16 * Y + 15, 199 - 10 * X), C, BF
143 LINE (304 - 16 * Y, 10 * X)-(319 - 16 * Y, 10 * X + 9), C, BF
153 LINE (304 - 16 * Y, 190 - 10 * X)-(319 - 16 * Y, 199 - 10 * X), C, BF
168 GOTO 73
173 END

