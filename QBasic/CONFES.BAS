
' ***************************************************************************
' *       C O N F E S I O N A R I O    P O R    C O M P U T A D O R         *
' *       ---------------------------------------------------------         *
' *                                                                         *
' *                                                                         *
' *  - Para iniciar el programa presione SHIFT + F5.                        *
' *  - Para avandonar el programa presione F4.                              *
' *  - Para avandonar QUICK BASIC presione ALT + A, L                       *
' *                                                                         *
' *                                                                         *
' *   Para registrar el programa, consulte el archivo REGP.TXT.             *
' *                                                                         *
' *                                                                         *
' *                                                                         *
' *                                          Todos los derechos reservados. *
' *                                                                         *
' ***************************************************************************

'---------------------------------------------------------------------------

REM * * * * * * * *  CONFESIONARIO POR COMPUTADOR  * * * * * * * * *
REM *  AUTOR: Jairo Alejandro Duarte                               *
REM *  HISTORIA: Jairo Duarte Rodriguez, Jonathan Avenda¤o         *
REM *  SONIDO: Jairo Alejandro Duarte                              *
REM *  GRAFICAS: Jairo Alejandro Duarte, Juan Carlos Duarte        *
REM *  REDACCION: Jairo Alejandro Duarte                           *
REM * **************************************************************

'----------------------------------------------------------------------------
CLEAR
1 DIM LINEA$(100), PEN$(17)
PUNTUAC = 0
DATOS = 0
ON KEY(1) GOSUB AYUDA: KEY(1) ON
ON KEY(4) GOSUB FIN: KEY(4) ON
SCREEN 7
'OPEN "C:\DOS\PROGOR.CFS" FOR INPUT AS #1: CLOSE
PAINT (60, 60), 7
B = 0: C = 319: D = 199
FOR A = 1 TO 15
LINE (B, B)-(C, B), A
LINE (C, B)-(C, D), A
LINE (B, 1)-(B, D), A
LINE (B, D)-(C, D), A
B = B + 1: C = C + 1: D = D + 1
NEXT A
GOSUB CUADROS
GOSUB BLANQUIAR
LINE (16, 185)-(311, 185), 8
LINE (313, 24)-(313, 185), 8
COLOR 12
LOCATE 4, 4: PRINT "CONFESIONARIO POR COMPUTADOR"
COLOR 11, 0
PLAY "ML<FC7D7C7P7FC7D7C7P7"
COLOR 11
LOCATE 6, 4: PRINT "Dice mentiras:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
COLOR 11
LOCATE 6, 4: PRINT "Pelea:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
COLOR 11
LOCATE 6, 4: PRINT "Dice grocerias:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Asiste a misa:"
COLOR 15
LOCATE 8, 6: PRINT "1= Nunca"
LOCATE 9, 6: PRINT "2= Muy poco"
LOCATE 10, 6: PRINT "3= Poco"
LOCATE 11, 6: PRINT "4= De vez en cuando"
LOCATE 12, 6: PRINT "5= Alguito"
LOCATE 13, 6: PRINT "6= Mucho"
LOCATE 14, 6: PRINT "7= Muchisimo"
LOCATE 15, 6: PRINT "8= Demaciado"
LOCATE 16, 6: PRINT "9= Exagerado"
COLOR 13
LOCATE 22, 5: PRINT "Cual es su caso ???"
GOSUB RESPUESTA
GOSUB RESBIEN
GOSUB CUADROS
GOSUB BLANQUIAR
COLOR 11
LOCATE 6, 4: PRINT "A robado:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "A matado:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Se ha drogado:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Malos pensamientos:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Mal hermano:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Trafica con drogas:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Perdona a los demas:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB RESBIEN
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Ama a DIOS sobre TODAS las cosas:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB RESBIEN
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Honrra a padre y madre:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB RESBIEN
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Santifica las fiestas:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB RESBIEN
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Comete actos impuros:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Jura el nombre de DIOS en vano:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Siente envidia:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "Es egoista:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 6, 4: PRINT "A deseado la mujer del projimo:"
GOSUB YASABE
GOSUB RESPUESTA
GOSUB PUNTUACION
GOSUB CUADROS
GOSUB BLANQUIAR
COLOR 4
LOCATE 6, 7: PRINT "RESULTADO DE LA CONFESION"
COLOR 3
LOCATE 9, 4: PRINT "Puntuaci¢n: "; PUNTUAC
LOCATE 11, 4: PRINT "N£mero de pecados: "; PECADO
COLOR 2
LOCATE 13, 5: PRINT "1= Penitencias..."
LOCATE 15, 5: PRINT "2= Imprimir resultados..."
PEN$(1) = "Eres un buen cristiano, puedes ir en paz. "
PEN$(2) = "Resa 10 Padres nuestros."
PEN$(3) = "Resar 50 Padres nuestros."
PEN$(4) = "Resar 400 Padres nuestros."
PEN$(5) = "Has alguna obra de caridad."
PEN$(6) = "Has 10 obras de caridad esta semana."
PEN$(7) = "Has muchas obras de caridad durante este a¤o y el que sigue."
PEN$(8) = "Se humilde y trabaja solo para los dem s."
PEN$(9) = "Resa todos lo d¡as durante una hora."
PEN$(10) = "Resa 50 Rosarios."
PEN$(11) = "Resa 200 Rosarios."
PEN$(12) = "Visita este confecionario todos los d¡as a partir de ma¤ana."
PEN$(13) = "Ve a cualquier hospital y dona 1000 cm. c£bicos de sangre."
PEN$(14) = "Lee cinco veces la Santa Biblia y quedar s absuelto."
PEN$(15) = "Dona TODOS tus bienes."
PEN$(16) = "Cumple TODOS los mandamientos y obras de caridad durante TODA tu vida."
IF PUNTUAC <= 2 THEN PENF$ = PEN$(1)
IF PUNTUAC <= 45 AND PUNTUAC > 2 THEN PENF$ = PEN$(2)
IF PUNTUAC <= 85 AND PUNTUAC > 45 THEN PENF$ = PEN$(3)
IF PUNTUAC <= 125 AND PUNTUAC > 85 THEN PENF$ = PEN$(4)
IF PUNTUAC <= 165 AND PUNTUAC > 125 THEN PENF$ = PEN$(5)
IF PUNTUAC <= 195 AND PUNTUAC > 165 THEN PENF$ = PEN$(6)
IF PUNTUAC <= 225 AND PUNTUAC > 195 THEN PENF$ = PEN$(7)
IF PUNTUAC <= 245 AND PUNTUAC > 225 THEN PENF$ = PEN$(8)
IF PUNTUAC <= 285 AND PUNTUAC > 245 THEN PENF$ = PEN$(9)
IF PUNTUAC <= 305 AND PUNTUAC > 285 THEN PENF$ = PEN$(10)
IF PUNTUAC <= 315 AND PUNTUAC > 305 THEN PENF$ = PEN$(11)
IF PUNTUAC <= 335 AND PUNTUAC > 315 THEN PENF$ = PEN$(12)
IF PUNTUAC <= 355 AND PUNTUAC > 335 THEN PENF$ = PEN$(13)
IF PUNTUAC <= 375 AND PUNTUAC > 355 THEN PENF$ = PEN$(14)
IF PUNTUAC <= 395 AND PUNTUAC > 375 THEN PENF$ = PEN$(15)
IF PUNTUAC <= 418 AND PUNTUAC > 395 THEN PENF$ = PEN$(16)
GOSUB RESPUESTA
IF RES$ = "2" THEN GOTO IMPRIMIR
IF RES$ = "1" THEN GOTO PENITENCIAS
PENITENCIAS:
GOSUB CUADROS: GOSUB BLANQUIAR
COLOR 14
LOCATE 6, 10: PRINT "PENITENCIA:"
COLOR 11
LOCATE 10, 4: PRINT PENF$
COLOR 7
LOCATE 16, 6: PRINT "Presione una tecla y contin£e ..."
123 A$ = "": A$ = INKEY$: IF A$ = "" THEN 123
GOTO FIN
YASABE:
COLOR 15
LOCATE 8, 6: PRINT "1= Nunca"
LOCATE 9, 6: PRINT "2= Muy poco"
LOCATE 10, 6: PRINT "3= Poco"
LOCATE 11, 6: PRINT "4= De vez en cuando"
LOCATE 12, 6: PRINT "5= Alguito"
LOCATE 13, 6: PRINT "6= Mucho"
LOCATE 14, 6: PRINT "7= Muchisimo"
LOCATE 15, 6: PRINT "8= Demaciado"
LOCATE 16, 6: PRINT "9= Exagerado"
COLOR 13
LOCATE 22, 5: PRINT "Cual es su caso ???"
COLOR 11
RETURN
CUADROS:
FOR A = 16 TO 318 STEP 4
LINE (A, 16)-(A, 198), 8
NEXT A
FOR A = 16 TO 198 STEP 4
LINE (16, A)-(318, A), 8
NEXT A
RETURN
RESPUESTA:
100 RES$ = "": RES$ = INKEY$: IF RES$ = "" THEN 100
RETURN
ALELUYA:
PLAY "MNMBFC7D7C7P7"
RETURN
PUNTUACION:
IF RES$ = "1" THEN GOSUB ALELUYA: RETURN
IF RES$ = "2" THEN PUNTUAC = PUNTUAC + 1: GOTO DATOS
IF RES$ = "3" THEN PUNTUAC = PUNTUAC + 4: GOTO DATOS
IF RES$ = "4" THEN PUNTUAC = PUNTUAC + 7: GOTO DATOS
IF RES$ = "5" THEN PUNTUAC = PUNTUAC + 9: GOTO DATOS
IF RES$ = "6" THEN PUNTUAC = PUNTUAC + 12: GOTO DATOS
IF RES$ = "7" THEN PUNTUAC = PUNTUAC + 16: GOTO DATOS
IF RES$ = "8" THEN PUNTUAC = PUNTUAC + 19: GOTO DATOS
IF RES$ = "9" THEN PUNTUAC = PUNTUAC + 22: GOTO DATOS
RETURN
BLANQUIAR:
FOR A = 4 TO 23
FOR B = 3 TO 39
LOCATE A, B: PRINT " "
NEXT B
NEXT A
RETURN
RESBIEN:
IF RES$ = "1" THEN PUNTUAC = PUNTUAC + 22: GOTO DATOS
IF RES$ = "2" THEN PUNTUAC = PUNTUAC + 19: GOTO DATOS
IF RES$ = "3" THEN PUNTUAC = PUNTUAC + 16: GOTO DATOS
IF RES$ = "4" THEN PUNTUAC = PUNTUAC + 12: GOTO DATOS
IF RES$ = "5" THEN PUNTUAC = PUNTUAC + 9: GOTO DATOS
IF RES$ = "6" THEN PUNTUAC = PUNTUAC + 7: GOTO DATOS
IF RES$ = "7" THEN PUNTUAC = PUNTUAC + 4: GOTO DATOS
IF RES$ = "8" THEN PUNTUAC = PUNTUAC + 1: GOTO DATOS
IF RES$ = "9" THEN GOSUB ALELUYA
RETURN
DATOS:
PECADO = PECADO + 1
RETURN
IMPRIMIR:
OPEN "C:\DOS\EAQHQ.PSO" FOR INPUT AS #1
CLOSE
GOSUB CUADROS
GOSUB BLANQUIAR
LINE (20, 25)-(300, 182), 3, B
COLOR 11, 6
LOCATE 4, 4: PRINT " IMPRIMIR "
COLOR 7
LOCATE 8, 5: PRINT " Imprimir en impresora LPT1 ???"
LINE (40, 75)-(110, 92), 4, B
PAINT (90, 78), 4
LOCATE 11, 7: PRINT "ACEPTAR"
COLOR 15: LOCATE 11, 7: PRINT "A"
LINE (42, 93)-(112, 95), 8, BF
LINE (111, 77)-(113, 95), 8, BF
LINE (152 + 20, 75)-(243, 92), 4, B
PAINT (220, 78), 4
COLOR 7
LOCATE 11, 23: PRINT "CANCELAR"
COLOR 15: LOCATE 11, 23: PRINT "C"
LINE (172, 93)-(246, 95), 8, BF
LINE (244, 77)-(246, 95), 8, BF
300 GOSUB RESPUESTA
IF RES$ = "A" OR RES$ = "a" THEN GOTO IMPRIMIRLPT1
IF RES$ = "C" OR RESP$ = "c" THEN GOTO FIN ELSE GOSUB ALELUYA: GOTO 300
IMPRIMIRLPT1:
COLOR 15, 0
GOSUB CUADROS
GOSUB BLANQUIAR
LOCATE 10, 5: PRINT "Imprimiendo resultados en LPT1..."
FOR A = 1 TO 1000: NEXT A
RESULTADO$ = "           * * * * * * CONFESIONARIO POR COMPUTADOR * * * * * *"
LINEA$(1) = "      -------------- RESULTADOS FINALES DE LA CONFESION --------------"
LINEA$(2) = "                                                       "
LINEA$(3) = "                                                       "
LINEA$(4) = "  Confesado via RED Internet directamente desde el Baticano,"
LINEA$(5) = "  por el Papa Juan Pablo II.                           "
LINEA$(6) = "                                                       "
LINEA$(7) = "                                                       "
LINEA$(8) = "                                                       "
LINEA$(9) = "   PENITENCIA:                                         "
LINEA$(10) = "                                                      "
LPRINT RESULTADO$
FOR IMPR = 1 TO 10
LPRINT LINEA$(IMPR)
NEXT IMPR
LPRINT LINEA$(10)
LPRINT PENF$
LPRINT "  Puntuaci¢n= "; PUNTUAC
LPRINT "  N£mero de pecados= "; PECADO
10 '************ CALEIDOSCOPIO *************
20 '
30 KEY OFF: CLS : SCREEN 7
40 '
50 '*** COMIENCIO BUCLE PRINCIPAL ***
60 '
FOR CICLO = 1 TO 130
70 U = INT(10 * RND): X = 9 - INT((U + 1) * RND): Y = 9 - INT((U + 1) * RND): C = INT(15 * RND)
80 LINE (16 * X, 10 * Y)-(16 * X + 15, 10 * Y + 9), C, BF
90 LINE (304 - 16 * X, 10 * Y)-(319 - 16 * X, 10 * Y + 9), C, BF
95 LINE (16 * X, 190 - 10 * Y)-(16 * Y + 15, 199 - 10 * Y), C, BF
110 LINE (304 - 16 * X, 190 - 10 * Y)-(319 - 16 * X, 199 - 10 * Y), C, BF
120 LINE (16 * Y, 10 * X)-(16 * Y + 15, 10 * X + 9), C, BF
130 LINE (16 * Y, 190 - 10 * X)-(16 * Y + 15, 199 - 10 * X), C, BF
140 LINE (304 - 16 * Y, 10 * X)-(319 - 16 * Y, 10 * X + 9), C, BF
150 LINE (304 - 16 * Y, 190 - 10 * X)-(319 - 16 * Y, 199 - 10 * X), C, BF
165 NEXT CICLO
VELOCIDAD = 75
31 CLS
C = 3
51 P = 0: Q = -45
FOR CICLO = 1 TO 100
91 LINE (160 - 1.6 * P, 100 - P)-(160 + 1.6 * P, 100 + P), C, B
101 IF 1 >= 0 THEN LINE (160 - 1.6 * Q, 100 - Q)-(160 + 1.6 * Q, 100 + Q), 0, B
111 P = P + 5: IF P > 95 THEN P = 0: C = 1 + INT(32 * RND)
121 Q = Q + 5: IF Q > 95 THEN Q = 0
131 IF P = 0 OR Q = 0 THEN GOTO 141
132 FOR VEL = 1 TO VELOCIDAD: NEXT VEL
141
151 NEXT CICLO
102 REM ********************  LINEAS  *********************
202 '
302 SCREEN 7
402 DEFINT A-Z
502 DIM X1(150), Y1(150), X2(150), Y2(150)
602 RANDOMIZE TIMER
702 KEY OFF
802 X1 = 120: Y1 = 70: X2 = 200: Y2 = 130
902 CONTCOLOR = 0
1002 '
1102 ' ********* BUCLE PRINCIPAL ********
1202 '
1302 '*** BORRADO DE LINEA ANTERIOR ***
1402 '
FOR ASD = 1 TO 1040
O = INT(2 * RND)
1502 LINE (X1(I), Y1(I))-(X2(I), Y2(I)), 0
1602 '
1702 '*** GENERACION DE VALORES NUEVOS PARA CONTADORES ***
1802 '
1902 IF CONTCOLOR = 0 THEN CONTCOLOR = 5 * (1 + INT(10 * RND)): CLR = 1 + INT(15 * RND)
2002 IF CONPUNT = 0 THEN CONTPUT = 5 * (1 + INT(9 * RND)): DX1 = INT(9 * RND) - 4: DY1 = INT(9 * RND) - 4: DX2 = INT(9 * RND) - 4: DY2 = INT(9 * RND) - 4
2102 '
2202 '*** PUNTOS FINALES NUEVA LINEA ***
2302 '
2402 X1 = X1 + DX1: IF X1 < 0 OR X1 > 319 THEN X1 = X1 - 2 * DX1
2502 Y1 = Y1 + DY1: IF Y1 < 0 OR Y1 > 199 THEN Y1 = Y1 - 2 * DY1
2602 X2 = X2 + DX2: IF X2 < 0 OR X2 > 310 THEN X2 = X2 - 2 + DX2
2702 Y2 = Y2 + DY2: IF Y2 < 0 OR Y2 > 199 THEN Y2 = Y2 - 2 * DY2
2802 '
2902 '*** LINEA NUEVA ***
3002 '
3102 LINE (X1, Y1)-(X2, Y2), CLR
3202 X1(I) = X1(I): Y1(I) = Y1: X2(I) = X2: Y2(I) = Y2
3302 '
3402 '*** AJUSTE CONTADORES Y REPETICIOIN ***
3502 '
3602 I = I + 1
3702 IF I > 150 THEN I = 1
3802 CONTCOLOR = CONTCOLOR - 1: CONTPUNT = CONPUT - 1
3902 NEXT ASD
'************ REBOTE DE PELOTA ************
KEY OFF: CLS
DEFINT A-Z
RANDOMIZE TIMER
SCREEN 2
701 DIM PELOTA(34)
801 LINE (0, 0)-(639, 199), , B
901 LINE (10, 5)-(629, 194), , B
1001 PAINT (5, 2)
1101 X = 20 + INT(600 * RND): Y = 20 + INT(160 * RND)
1201 DX = 1 + INT(10 * RND): DY = 1 + INT(10 * RND)
1301 CIRCLE (X, Y), 10
1401 PAINT (X, Y)
1501 GET (X - 10, Y - 10)-(X + 10, Y + 10), PELOTA
1601 '
1701 '*** COMIENZO BUCLE ***
1801 '
FOR CICLO = 1 TO 200
1901 PUT (X - 10, Y - 10), PELOTA
2001 X1 = X + DX: Y1 = Y + DY
2101 IF X1 < 21 THEN X1 = 21: DX = -DX: GOTO 2301
2201 IF X1 > 618 THEN X1 = 618: DX = -DX
2301 IF Y1 < 10 THEN Y1 = 10: DY = -DY: GOTO 2501
2401 IF Y1 > 189 THEN Y1 = 10: DY = -DY
2501 PUT (X1 - 10, Y1 - 10), PELOTA
2601 X = X1: Y = Y1
2701 FOR C = 1 TO 10000: NEXT C
2801 NEXT CICLO
SCREEN 7
FIN:
COLOR 7, 0: CLS
FOR C = 1 TO 15
D = INT(RND * 30) + 3
FOR A = 1 TO 319 STEP D
FOR B = 1 TO 199 STEP D
PSET (A, B), C
NEXT B
NEXT A
NEXT C
FOR A = 0 TO 319
LINE (A, 1)-(A, 199), 9
FOR B = 1 TO 490: NEXT B
NEXT A
LOCATE 10, 5: PRINT " NUEVA CONFESION (S/N) ??? "
1000 A$ = "": A$ = INKEY$: IF A$ = "" THEN 1000
IF A$ = "S" OR A$ = "s" THEN GOTO 1
IF A$ = "n" OR A$ = "N" THEN GOTO SALIR ELSE GOSUB ALELUYA: GOTO 1000
SALIR:
FOR A = 1 TO 25
FOR B = 1 TO 40
LOCATE A, B: PRINT " "
NEXT B
NEXT A
PAINT (100, 100), 4
PLAY "MLMB>FC7D7C7P7"
SLEEP 1
B = 0: C = 319: D = 199
FOR A = 1 TO 100
FOR E = 1 TO 500: NEXT E
LINE (B, B)-(C, D), 0, B
B = B + 1: C = C - 1: D = D - 1
NEXT A
END
AYUDA:
OPEN "C:\DOS\INST.CFS" FOR INPUT AS #1
CLOSE
OPEN "C:\DOS\CON.CFS" FOR INPUT AS #1
CLOSE
DIM PANTA1(10000), PANTA2(10000)
GET (10, 40)-(300, 170), PANTA1
LINE (10, 40)-(300, 170), 3, BF
LINE (10, 40)-(300, 170), 4, B
LINE (11, 41)-(299, 169), 12, B
FOR A = 7 TO 20
FOR B = 4 TO 36
LOCATE A, B: PRINT " "
NEXT B: NEXT A
COLOR 12
LOCATE 7, 6: PRINT "Confesionario por computador."
LOCATE 8, 6: PRINT "      Versi¢n: 1.0           "
COLOR 10
LOCATE 10, 5: PRINT "Autor: Jairo Alejandro Duarte."
COLOR 11
LOCATE 13, 5: PRINT "Historia: "
COLOR 15
LOCATE 14, 5: PRINT "         Jairo Duarte Rodriguez."
LOCATE 15, 5: PRINT "         Jonathan Avenda¤o."
COLOR 11
LOCATE 17, 5: PRINT "Colaboraci¢n Gr ficas:"
COLOR 15
LOCATE 19, 5: PRINT "         Juan Carlos Duarte."
GET (10, 40)-(300, 170), PANTA2
10101 A$ = "": A$ = INKEY$: IF A$ = "" THEN 10101
PUT (10, 40), PANTA2
PUT (10, 40), PANTA1
RETURN

