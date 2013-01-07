'*************************************************+¥ IMPROBAS PICTURES √+****
'*                                                                          *
'*         I N S T A L A C I O N   D E   I B - P I C T U R E S              *
'*                                                                          *
'* ˙ Para iniciar la instalaci¢n del programa presione SHIFT+F5.            *
'*                                                                          *
'* La instalaci¢n de Pictures sera r†pida y sensilla, recuerde que el       *
'* programa de instalaci¢n requiere de algunos archivos:                    *
'*      - IBAP.TXT                                                          *
'*      - REGIBP.DOC                                                        *
'*      - INSTALAR.BAS                                                      *
'*      - IOP.LFR                                                           *
'*      - ORIBPIC.IN_                                                       *
'*      - PICDATA.FRL                                                       *
'*  Si los anteriores archivos no existen la instalaci¢n de pictures no     *
'*  sera efectuada.                                                         *
'*                                                                          *
'****************************************************************************
' Comienza la instalaci¢n.
' Del programa
' Pictures
COLOR 15, 1: CLS : KEY OFF
COLOR 15, 4
FOR A = 1 TO 80
LOCATE 1, A: PRINT CHR$(196): NEXT A
LOCATE 1, 1: PRINT "Instalaci¢n de Pictures.  Versi¢n 1.21"
COLOR 7, 1
LOCATE 4, 2: PRINT "  Por favor espere un momento..."
' Cerrado de archivos
CLOSE
OPEN "PICDATA.FRL" FOR APPEND AS #1: CLOSE
OPEN "EAQHQ.PSO" FOR INPUT AS #1: CLOSE
FOR A = 1 TO 70
LOCATE 4, A: PRINT CHR$(32)
NEXT A
COLOR 1, 1: CLS
COLOR 0, 3
LOCATE 25, 1: PRINT "     F1 = Avandonar      F2 = Iniciar la instalaci¢n                            "
COLOR 15, 4
FOR A = 1 TO 80
LOCATE 1, A: PRINT CHR$(196): NEXT A
LOCATE 1, 1: PRINT "Instalaci¢n de Pictures.  Versi¢n 1.21 "
COLOR 7, 1
LOCATE 7, 1
PRINT "       Para inicializar la instalacion de Pictures en su disco duro,"
PRINT "       presione F2."
PRINT "       El programa de instalaci¢n de Pictures version 1,21, copiara en"
PRINT "       su disco duro los componentes necesarios para el funcionamiento"
PRINT "       del programa."
PRINT
PRINT
PRINT "       Para avandonar el programa, presione F1."
' TECLAS DE FUNCION
ON KEY(1) GOSUB AVANDONAR
ON KEY(2) GOSUB INICIAR
KEY(1) ON
KEY(2) ON
SEGUIROSALIR:
GOTO SEGUIROSALIR
AVANDONAR:
COLOR 0, 4
FOR A = 8 TO 50
FOR B = 8 TO 13
LOCATE B, A: PRINT CHR$(32)
NEXT B
NEXT A
COLOR 14
LOCATE 8, 13
PRINT "*** INSTALACION NO TERMINADA ***"
COLOR 0, 4
LOCATE 10, 9
PRINT "El programa no termin¢ de copiar Picures."
COLOR 15, 4
LOCATE 12, 11: PRINT "Presione una tecla y continue..."
A$ = INPUT$(1)
COLOR 7, 8: CLS : CLOSE : END
INICIAR:
KEY(2) OFF
COLOR 7, 8: CLS
COLOR 0, 3
LOCATE 25, 1
PRINT "    F1 = Salir                                                                  "
COLOR 15, 4
LOCATE 1, 1
PRINT "    Instalaci¢n de IB-Pictures versi¢n 1.21                                     "
COLOR 7, 1
FOR A = 5 TO 22
FOR B = 1 TO 80
LOCATE A, B: PRINT CHR$(32)
NEXT B
NEXT A
LOCATE 7, 4
PRINT " Leyendo:                           Escribiendo:"
COLOR 0, 3
FOR A = 11 TO 16
FOR B = 5 TO 75
LOCATE A, B: PRINT CHR$(32)
NEXT B
NEXT A
COLOR 0
LOCATE 11, 10
PRINT "  Porcentaje instalado"
LOCATE 14, 6: PRINT "0%"
LOCATE 14, 71: PRINT "100%"
COLOR 14
P$ = CHR$(219)
LOCATE 14, 9: PRINT P$
COLOR 15, 1
LOCATE 7, 14: PRINT "PICDATA.FRL"
CLOSE
OPEN "PICDATA.FRL" FOR INPUT AS #1
CLOSE
LOCATE 7, 53: PRINT "C:\PICTURES\PICDATA.FRL"
COLOR 7
LOCATE 7, 14: PRINT "PICDATA.FRL"
MKDIR "C:\PICTURES"
COLOR 14
LOCATE 14, 10: PRINT "€€"
LOCATE 8, 1
FOR A = 1 TO 226
OPEN "C:\PICTURES\PICDATA.FRL" FOR APPEND AS #A
COLOR 14
LOCATE 14, 12: PRINT "€€€€€€€"
COLOR 15
PRINT #A, "BLL GDF G•LK ORRRR ODER.FGR ##235F 00 $˙ HN&&& ////5 6c:$&˙$    ˙%  )%  95'56 656registred FOR #>74   O"
CLOSE
NEXT A
GOSUB BORRAR
LOCATE 7, 14: PRINT "ORIBPIC.IN_"
FOR A = 1 TO 6: OPEN "ORIBPIC.IN_" FOR INPUT AS #1
CLOSE
NEXT A
COLOR 7
COLOR 14
LOCATE 14, 19: PRINT "€€€€€"
COLOR 7
LOCATE 7, 14: PRINT "ORIBPIC.IN_"
COLOR 15, 1
LOCATE 7, 53: PRINT "C:\PICTURES\ORIBPIC.INL"
COLOR 14
LOCATE 14, 24: PRINT "€"
FOR A = 1 TO 193
OPEN "C:\PICTURES\ORIBPIC.INL" FOR APPEND AS #A
PRINT #A, " PRINT ---- INPUT# ON ERROR(4) GOTO,TT WINDOW. PIC......##1 FOR APPEND AS #3 WRITE.,,F ˙˙&/#@"
CLOSE
NEXT A
GOSUB BORRAR
COLOR 14
LOCATE 14, 25: PRINT "€€€€"
COLOR 15
LOCATE 7, 14: PRINT "IBAP.TXT"
FOR A = 1 TO 4: OPEN "IBAP.TXT" FOR INPUT AS #1
CLOSE
NEXT A
COLOR 7
LOCATE 7, 14: PRINT "IBAP.TXT"
COLOR 15
LOCATE 7, 53: PRINT "C:\PICTURES\IBAP.TXT"
LOCATE 8, 1
SHELL "COPY IBAP.TXT C:\PICTURES"
GOSUB SUBBORRAR
COLOR 14
LOCATE 14, 29: PRINT "€€€€€€"
GOSUB BORRAR
COLOR 15, 1
LOCATE 7, 14: PRINT "REGIBP.DOC"
FOR A = 1 TO 10
OPEN "REGIBP.DOC" FOR INPUT AS #1
CLOSE
NEXT A
COLOR 14
LOCATE 14, 35: PRINT "€"
COLOR 15
LOCATE 7, 53: PRINT "C:\PICTURES\REGIBP.DOC"
COLOR 7, 1
LOCATE 7, 14: PRINT "REGIBP.DOC"
LOCATE 8, 1
SHELL "COPY REGIBP.DOC C:\PICTURES"
GOSUB SUBBORRAR
COLOR 14
LOCATE 14, 36: PRINT "€€€€€€€€"
GOSUB BORRAR
COLOR 15, 1
LOCATE 7, 14: PRINT "IOP.LFR"
FOR A = 1 TO 5: OPEN "IOP.LFR" FOR INPUT AS #1
CLOSE : NEXT A
COLOR 14
LOCATE 14, 44: PRINT "€€€"
COLOR 15, 1
LOCATE 7, 53: PRINT "C:\PICTURES\IOP.LFR"
COLOR 7, 1
LOCATE 7, 14: PRINT "IOP.LFR"
FOR A = 1 TO 207
OPEN "C:\PICTURES\IOP.LFR" FOR APPEND AS #A
PRINT #A, "as 5996#24B   COM23.SYS  CAMMAND.COM  AUTOEXEC.BAP  PICTURES AS #3346AN-34P   îØ  yü≥ß   vüû±∫£5¬££ÇY Âíæøòp˘"
CLOSE
NEXT A
COLOR 14
LOCATE 14, 47: PRINT "€€€€€€"
GOSUB BORRAR
COLOR 15, 1
LOCATE 7, 14: PRINT "PICTURES.BAS"
FOR A = 1 TO 11
OPEN "PICTURES.BAS" FOR INPUT AS #1
CLOSE
NEXT A
COLOR 14
LOCATE 14, 53: PRINT "€€€€€"
COLOR 15, 1
LOCATE 7, 53: PRINT "C:\PICTURES\PICTURES.BAS"
COLOR 7, 1
LOCATE 7, 14: PRINT "PICTURES.BAS"
FOR A = 1 TO 90
OPEN "C:\PICTURES\PICTURES.BAS" FOR APPEND AS #A
PRINT #A, "AS###41234235"
CLOSE : NEXT A
COLOR 14
LOCATE 14, 58: PRINT "€€€"
KILL "C:\PICTURES\PICTURES.BAS"
COLOR 14
LOCATE 14, 61: PRINT "€€€€€"
COLOR 7
LOCATE 7, 53: PRINT "C:\PICTURES\PICTURES.BAS"
COLOR 15
LOCATE 7, 14: PRINT "PICTURES.BAS"
OPEN "PICTURES.BAS" FOR INPUT AS #1
CLOSE
COLOR 14
LOCATE 14, 66: PRINT "€"
COLOR 7, 1
LOCATE 7, 14: PRINT "PICTURES.BAS"
COLOR 15
LOCATE 7, 53: PRINT "C:\PICTURES\PICTURES.BAS"
LOCATE 8, 1
SHELL "COPY PICTURES.BAS C:\PICTURES"
GOSUB SUBBORRAR
COLOR 14
LOCATE 14, 67: PRINT "€€€"
COLOR 15, 4
FOR A = 10 TO 15
FOR B = 12 TO 59
LOCATE A, B: PRINT CHR$(32)
NEXT B
NEXT A
KEY(1) OFF
LOCATE 11, 17: PRINT "≠INSTALACION TERMINADA!"
COLOR 0
LOCATE 13, 15
PRINT "Pictures a sido instalado en su disco duro."
COLOR 7
LOCATE 15, 13: PRINT "Presione una tecla y continue..."
PLAY "C20C20E17"
A$ = INPUT$(1)
COLOR 7, 8: CLS : END
SUBBORRAR:
COLOR 15, 1: LOCATE 8, 1: PRINT "                                           "
RETURN
BORRAR:
COLOR 15, 1
LOCATE 7, 53: PRINT "                          "
LOCATE 7, 14: PRINT "                      "
RETURN

