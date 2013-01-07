CONST tamano = 10
DIM array(tamano)

CLS
FOR i = 1 TO 10
        PRINT "Array("; i; ") = ";
        INPUT array(i)
NEXT i

FOR p = 1 TO tamano - 1
        menor = array(p)
        FOR i = p + 1 TO tamano
                IF array(i) < menor THEN
                        menor = array(i)
                        pt = i
                END IF
        NEXT i
        temp = a(p)
        a(p) = menor
        a(pt) = temp
NEXT

CLS
FOR i = 1 TO 10
        PRINT "Array("; i; ") = ";
        PRINT array(i)
NEXT i

