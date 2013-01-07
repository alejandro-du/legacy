SCREEN 13

FOR a = 1 TO 256
LINE (a, 0)-(a, 115), a
IF a$ = "S" OR a$ = "s" THEN END
NEXT a

b = 256
FOR a = 1 TO 256
LINE (a, 116)-(a, 230), b
IF a$ = "S" OR a$ = "s" THEN END
b = b - 1
NEXT a
a$ = INPUT$(1)

