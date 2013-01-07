SCREEN 13: CLS : COLOR 2
PAINT (1, 1), 23
pi = 3.14159265#
c = 40
FOR a = 0 TO 60
CIRCLE (160, 100 + dy), 160, c, 0, 3, .5
d = d + 1
IF d MOD 3 = 0 THEN c = c + 1
dy = dy + 1
NEXT a
c = 1
r = 58
FOR a = 0 TO 10
1 LINE (100, 120)-(100, 150), c
CIRCLE (100, 135), 18, c, 1.5 * pi, pi / 2: PAINT (101, 137), r, c
LINE (125, 120)-(130, 150), c, B:
CIRCLE (135, 128), 10, c, (pi * 240 / 180), (pi * 120 / 180): PAINT (136, 128), r, c
LINE (135, 136)-(145, 150), c: LINE (130, 136)-(140, 150), c: LINE (145, 150)-(140, 150), c
PAINT (127, 140), r, c
PAINT (141, 149), r, c
CIRCLE (160, 150), 30, c, 0, pi, 3: LINE (151, 135)-(169, 135), c: PAINT (160, 126), r, c
LINE (170, 120)-(180, 150), c: LINE -(190, 120), c: LINE -(200, 150), c: LINE (210, 120)-(200, 150), c
LINE (175, 135)-(185, 135), c: LINE (195, 135)-(205, 135), c
PAINT (177, 136), r, c: PAINT (197, 136), r, c
FOR b = 0 TO 300: NEXT b
r = r + 1
NEXT a
LOCATE 20, 17: PRINT "Pixel"
DO
FOR x = 0 TO 359
CIRCLE (152, 130), 70, c, (x * pi / 180), 0, .5
CIRCLE (152, 130), 70, 15, 0, (x * pi / 180), .5
a$ = INKEY$
IF a$ <> "" THEN RUN "draw"
NEXT x
FOR x = 0 TO 359
CIRCLE (152, 130), 70, c, 0, (x * pi / 180), .5
a$ = INKEY$
IF a$ <> "" THEN RUN "draw"
NEXT x
LOOP



