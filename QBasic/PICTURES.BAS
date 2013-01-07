'  -*-*-*-*-*-*-*-*-* I M P R O B A S   P I C T U E S *-*-*-*-*-*-*-*-*-   +
' -----------------------------------------------------------------------  +
'                                                                    1995  +
'                                                                          +
'               Creado en Colombia por Improbas Software, inc.             +
'                                                                          +
'               Este programa es exclusivo de Improbas Software,           +
'               y los derechos de autor estan reservados para              +
'               su autor.                                                  +
'                                                                          +
'                                                                          +
'      Si desea arrancar este programa solo presione SHIFT+F5.             +
'      El programa contiene una peque¤a ayuda, para invocarla              +
'      presione F1, en cualquier momento de ejecuci¢n del programa.        +
'      - - -                                               - - -           +
'    ESTE ES UN PRODUCTO SHEREWARE Y TODA LA INFORMACIàN ACERCA DE SU      +
'    REGISTRO SE ENCUENTRA EN EL ARCHIVO REGIBP.DOC, QUE PUEDE SER LEÖDO   +
'    POR EL EDITOR DEL MS-DOS(EDIT). ASÖ MISMO CUALQUIER AYUDA ADICIONAL   +
'    SE PUEDE ENCONTRAR EN EL ARCHIVO IBAP.TXT.                            +
'                                                                          +
' *************************************************************************+
' Comienza el programa.
CLEAR
'*+*+*+*+ ESTA ES LA VARIABLE QUE INDICA EL NUMERO DE PANTALLAZOS *+*+*+*+*+*
                             NUMPANT = 15
'*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*
COLOR 4, 0: KEY OFF: CLS
LOCATE 3, 1
PRINT "            **********  I B  -  P I C T U R E S  **********"
COLOR 15
PRINT "                              QuickBasic"
COLOR 14
LOCATE 6, 1
PRINT "            ÛßßßßßÜ            Û"
PRINT "            Û     Û           ÜÛÜ"
PRINT "            ÛÜÜÜÜÜß  ß  Üßßßß  Û  Û    Û  ÛÜ ÜßßßÜ  ÜßßßÜ   "
PRINT "            Û        Û  Û      Û  Û    Û  Û  Ûßßß    ßßÜ"
PRINT "            Û        Û  ßÜÜÜÜ  Û  ßÜÜÜÜß  Û  ßÜÜÜÜ  ßÜÜÜß"
PRINT "            Û"
PRINT "             ßÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ"
COLOR 2
PRINT
PRINT "            ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»    "
PRINT "            º                                                º   "
PRINT "            ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¹   "
PRINT "            º                                                º    "
PRINT "            º                                                º"
PRINT "            º                                                º    "
PRINT "            º                                                º    "
PRINT "            º                                                º   "
PRINT "            ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼      "
COLOR 3
LOCATE 15, 18
PRINT "**********  P I C T U R E S  **********"
COLOR 15
LOCATE 17, 15
PRINT " IB-Pictures de Improbas Software, 1995."
GOSUB ADP
LOCATE 18, 15
PRINT AUTOR$
LOCATE 19, 15
PRINT " Versi¢n: 1.21"
LOCATE 20, 15
PRINT " Creado en Colombia."
LOCATE 21, 15
PRINT " Todos los derechos reservados."
COLOR 7
LOCATE 23, 5
PRINT "                          Presione una tecla y contin£e..."
GOSUB PAUSA
DIM A$(NUMPANT + 1)
DIM A(NUMPANT + 1)
100
CLOSE
FOR A = 1 TO NUMPANT
LET A$(A) = ""
NEXT A
PRINCIPAL$ = "Sin_Nombre"
110 COLOR 15, 3: CLS
LOCATE 25, 4: PRINT " PICTURES  -  IMPROBAS Sofware. Productos Inform ticos para Basic. "
COLORP = 7: PANTALLA = 1
COLOR 0, 3
LOCATE 1, 33
PRINT " PICTURES "
COLOR 14, 1
FOR A = 3 TO 78
LOCATE 2, A
PRINT " "
NEXT A
LOCATE 2, 4
PRINT "   Archivo       Edici¢n       Color       Ejecutar     ³            Ayuda"
COLOR 0, 3
FOR A = 4 TO 79
LOCATE 3, A
PRINT "ß"
NEXT A
LOCATE 2, 79
PRINT "Ü"
COLOR 15, 1
LOCATE 2, 4
PRINT "F2ú"
LOCATE 2, 18
PRINT "F3ú"
LOCATE 2, 32
PRINT "F4ú"
LOCATE 2, 44
PRINT "F5ú"
LOCATE 2, 70
PRINT "F1ú"
COLOR 15, 1
FOR A = 6 TO 9
LOCATE A, 3
PRINT "                                                                          "
NEXT A
COLOR 0, 3
FOR A = 4 TO 77
LOCATE 10, A
PRINT "ß"
NEXT A
FOR A = 7 TO 9
LOCATE A, 77
PRINT "Û"
NEXT A
LOCATE 6, 77
PRINT "Ü"
COLOR 0
FOR A = 1 TO 80
LOCATE 11, A
PRINT "Ä"
NEXT A
GOSUB IMPDATOS
ON KEY(1) GOSUB AYUDA
ON KEY(2) GOSUB ARCHIVO
ON KEY(3) GOSUB EDICION
ON KEY(4) GOSUB COLORPP
ON KEY(5) GOSUB EJECUTAR
FOR A = 1 TO 5
KEY(A) ON
NEXT A
COLOR 7, 1
FOR B = 1 TO NUMPANT
LOCATE 8, 4
COLOR 15, 1
PRINT "                                                                        "
LOCATE 8, 4
COLOR COLORP, 1
INPUT "", A$(B)
LET A = LEN(A$(B))
IF A > 72 THEN GOTO 100
PANTALLA = PANTALLA + 1
GOSUB IMPDATOS
NEXT B
FOR A = 1 TO 1D+36
B$ = INPUT$(1)
IF B$ = CHR$(27) THEN COLOR 7, 8: CLS : END
NEXT A
IMPDATOS:
COLOR 1, 3
LOCATE 12, 3
PRINT "Principal: ", : COLOR 15, 3
LOCATE 12, 14: PRINT PRINCIPAL$
COLOR 1, 3
LOCATE 12, 35
PRINT "Pantalla: ", : COLOR 15, 3
LOCATE 12, 45: PRINT PANTALLA
COLOR 1, 3
LOCATE 12, 59
PRINT "Color: ", : COLOR 15, 3
LOCATE 12, 66: PRINT COLORP
COLOR 0, 3
FOR A = 1 TO 80
LOCATE 13, A
PRINT "Ä"
NEXT A
RETURN
ARCHIVO:
COLOR 1, 3
LOCATE 15, 5
PRINT " 1= Nuevo            2= Abrir..."
LOCATE 17, 5
PRINT " 3= Salvar           4= Salvar como... "
LOCATE 19, 5
PRINT " 5= Borrar           6= Salir"
290 C$ = "": C$ = INKEY$: IF C$ = "" THEN 290
IF C$ = "1" THEN GOTO 100
IF C$ = "2" THEN GOTO ABRIR
IF C$ = "3" THEN GOTO SALVAR
IF C$ = "4" THEN GOTO SALVARCOMO
IF C$ = "5" THEN GOTO BORRAR
IF C$ = "6" THEN GOTO SALIR ELSE GOTO 110
SALIR:
COLOR 15, 3
LOCATE 22, 3
INPUT "Desea guardar los cambios"; CAM$
A$ = LEFT$(CAM$, 1)
IF A$ = "S" OR A$ = "s" THEN GOTO SALVAR
IF A$ = "n" OR A$ = "N" THEN COLOR 7, 8: CLS : CLS : CLS : END
IF A$ = "" THEN GOTO 110 ELSE GOTO SALVAR
SALVAR:
IF PRINCIPAL$ = "Sin_Nombre" THEN GOTO SALVARCOMO
FOR A = 1 TO 20
OPEN PRINCIPAL$ FOR APPEND AS #A
PRINT #A, A$(A)
CLOSE
NEXT A
GOTO 110
ABRIR:
COLOR 7, 8: CLS : FILES
COLOR 15
LOCATE 23, 4
INPUT "Nombre de la pel¡cula: "; PELICULA$
IF PELICULA$ = "" THEN GOTO 110
OPEN PELICULA$ FOR INPUT AS #1
FOR A = 1 TO NUMPANT
LINE INPUT #1, A$(A)
NEXT A
CLOSE
PRINCIPAL$ = PELICULA$
CLOSE
GOTO 110
SALVARCOMO:
COLOR 7, 8: CLS
FILES
LOCATE 23, 3
INPUT "Nombre de la pel¡cula: "; PELICULA$
IF PELICULA$ = "" THEN GOTO 110
COLOR 15, 1
LOCATE 14, 10
PRINT "   GUARDANDO.....   "
FOR A = 1 TO NUMPANT
OPEN PELICULA$ FOR APPEND AS #A
PRINT #A, A$(A)
CLOSE
NEXT A
GOTO 100
BORRAR:
COLOR 7, 8: CLS
FILES
COLOR 4
LOCATE 23, 2
INPUT "Pel¡cula a BORRAR: "; BO$
IF BO$ = "" THEN GOTO 110
BEEP
COLOR 24, 9
LOCATE 12, 16: PRINT "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
LOCATE 13, 16: PRINT "DESEA BORRAR ESTE ARCHIVO ???"
COLOR 15, 1
LOCATE 21, 16: INPUT "SI o NO"; SIONO$
IF SIONO$ = "SI" OR SIONO$ = "si" THEN GOTO BORRARSI
GOTO 110
BORRARSI:
COLOR 7, 8: CLS
FILES
COLOR 15, 1
LOCATE 12, 10: PRINT "  BORRANDO.....  "; BO$
KILL BO$
GOTO 110
EDICION:
PRE:
COLOR 0, 3
LOCATE 17, 4: PRINT "                                                        "
LOCATE 17, 4
COLOR 0, 3
PRINT "N£mero de l¡nea a editar (max."; NUMPANT; "):"
LOCATE 17, 42: INPUT "", LINEAE
COLOR 15, 3
IF LINEAE = 0 THEN GOTO 110
IF LINEAE < 1 OR LINEAE > NUMPANT THEN BEEP: GOTO PRE
LOCATE 19, 3: PRINT A$(LINEAE)
COLOR 15, 3
LOCATE 21, 4
PRINT "Edite la l¡nea....."
LOCATE 22, 4
INPUT "", A$(LINEAE)
LET B = LEN(A$(LINEAE))
IF B > 72 THEN GOTO 100
COLOR 1, 3
FOR A = 19 TO 23
LOCATE A, 1: PRINT "                                                                    "
NEXT A
GOTO 110
END
COLORPP:
COLOR 1, 3
300 LOCATE 20, 3
INPUT "N£mero de color: ", COLORP
IF COLORP = 0 THEN GOSUB SUBBORRAR: RETURN
IF COLORP > 31 THEN LOCATE 19, 20: PRINT "                                                                  ": BEEP: GOTO 300
LOCATE 20, 2: PRINT "                                                          "
GOSUB IMPDATOS
GOSUB SUBBORRAR
RETURN
EJECUTAR:
310 COLOR 0, 3
LOCATE 20, 3
INPUT "Ejecutar desde: "; ED
IF ED = 0 THEN GOSUB SUBBORRAR: RETURN
IF ED < 1 THEN BEEP: GOTO 310
IF ED > NUMPANT THEN BEEP: GOTO 310
INPUT "  Ejecutar hasta: "; EH
IF EH > NUMPANT THEN BEEP: GOTO 310
IF EH < 1 THEN BEEP: GOTO 310
320 LOCATE 23, 3: INPUT "Velocidad de rodaje: "; VR
IF VR < 1 THEN BEEP: GOTO 320
FOR B = ED TO EH
COLOR COLORP, 1
LOCATE 8, 4
PRINT A$(B)
PANTALLA = B
GOSUB IMPDATOS
FOR A = 1 TO VR: NEXT A
COLOR COLORP, 1
LOCATE 8, 4: PRINT "                                                                         "
NEXT B
COLOR 1, 3
LOCATE 20, 2: PRINT "                                               "
PRINT "                                                               "
LOCATE 23, 2: PRINT "                                                                        "
RETURN
AYUDA:
CLOSE
COLOR 14, 1
LOCATE 14, 14
PRINT "          ********* A Y U D A **********           "
COLOR 4, 3
PRINT "     MENU PRINCIPAL DE LA AYUDA DE IB-PICTURES  "
COLOR 1, 3
PRINT
PRINT "     1 = Como usar la ayuda  "
PRINT "     2 = ¨Qu‚ es? "
PRINT "     3 = Como usar la barra de men£"
PRINT "     4 = Men£ Archivo"
PRINT "     5 = Men£ Edici¢n"
PRINT "     6 = Men£ Color"
PRINT "     7 = Men£ Ejecutar"
244 A$ = "": A$ = INKEY$: IF A$ = "" THEN 244
IF A$ = "1" THEN GOTO COMOUSAR
IF A$ = "2" THEN GOTO QUEES
IF A$ = "3" THEN GOTO COMOBARMEN
IF A$ = "4" THEN GOTO AYARCHIVO
IF A$ = "5" THEN GOTO AYEDICION
IF A$ = "6" THEN GOTO AYCOLOR
IF A$ = "7" THEN GOTO AYEJECUTAR
IF A$ = CHR$(27) THEN GOSUB SUBBORRAR: GOTO 110
COMOUSAR:
GOSUB SUBBORRAR
COLOR 0, 3
LOCATE 14, 1
PRINT "   Para usar la ayuda de IB-Pictures..."
COLOR 1, 3
PRINT
PRINT "   En cualquier momento de ejecuci¢n del programa presione"
PRINT "   la tecla de funci¢n F1, esto invocar  el men£ principal"
PRINT "   de ayuda."
PRINT
PRINT "   Para seleccionar un tema de ayuda presione el n£mero que"
PRINT "   se antepone a la opci¢n."
PRINT
COLOR 15, 3
PRINT "   Presione ESPACIO para continuar......"
483 A$ = "": A$ = INKEY$: IF A$ = "" THEN 483
IF A$ = CHR$(32) THEN GOTO 484 ELSE GOTO 483
484 GOSUB SUBBORRAR
GOTO 110

QUEES:
GOSUB SUBBORRAR
COLOR 4, 3
LOCATE 14, 11
PRINT "  ----------------- ¨ Q U E   E S ? --------------------"
COLOR 14, 1
LOCATE 15, 5
PRINT " IB-Pictures es un producto sofware desarrollado y producido por      "
LOCATE 16, 5
PRINT " IMPROBAS Software, inc localizado en Bogot -Colombia.                "
LOCATE 17, 5
PRINT "                                                                      "
LOCATE 18, 5
PRINT " Todos los derechos de copia estan reservados para su autor.          "
LOCATE 19, 5
PRINT " Queda terminantemente prohibido desensamblar, modificar o reproducir "
LOCATE 20, 5
PRINT " total o parcialmente el programa sin autorizaci¢n expresa del autor. "
LOCATE 21, 5
PRINT " Usted puede crear solamente copias de seguridad del software para su "
LOCATE 22, 5
PRINT " uso personal.                                                        "
COLOR 15, 3
LOCATE 23, 12
PRINT "Presione ESPACIO para continuar....."
510 GOSUB PAUSA
IF A$ = CHR$(32) THEN GOTO 438 ELSE GOTO 510
IF A$ = CHR$(27) THEN GOTO 110
438 GOSUB SUBBORRAR
COLOR 0, 3
LOCATE 15, 1
PRINT "  Con IB-Pictures el usuario tendr  la oportunidad de crear pel¡culas"
PRINT "  editadas en c¢digos ASCII."
PRINT "  Por medio de un peque¤o editor de texto de tan solo una l¡nea se "
PRINT "  introducir n pantallazos uno tras otro, al momento de rodar la"
PRINT "  pel¡cula los pantallazos editados anteriormente se visualizar n"
PRINT "  en forma consecutiva, dando una sensaci¢n de movimiento.    "
PRINT "  "
COLOR 15, 3
PRINT "          Presione ESPACIO para continuar....."
522 GOSUB PAUSA
IF A$ = CHR$(32) THEN GOTO 110 ELSE GOTO 522
IF A$ = CHR$(27) THEN GOTO 110
COMOBARMEN:
GOSUB SUBBORRAR
COLOR 4, 3
LOCATE 14, 1
PRINT "                ********* COMO USAR LA BARRA DE MENU **********      "
COLOR 0
PRINT
PRINT "   La barra de men£ se encuentra en la parte superior de la pantalla, "
PRINT "   Cada opci¢n esta representada por una tecla de funci¢n (F1 a F5) "
PRINT "   si se desea tener acceso a un men£, presione la tecla de funci¢n "
PRINT "   que representa la subrutina deseada."
PRINT "   Por defecto, algunas veces hay que oprimir ENTER despu‚s de pulsar"
PRINT "   una tecla de funci¢n."
PRINT
COLOR 15
PRINT "              Presione ESPACIO para continuar....."
222 GOSUB PAUSA
IF A$ = CHR$(32) THEN GOSUB SUBBORRAR: GOTO 110 ELSE GOTO 222
IF A$ = CHR$(27) THEN GOTO 110
AYARCHIVO:
GOSUB SUBBORRAR
COLOR 4, 3
LOCATE 14, 5
PRINT "            ********* MENU ARCHIVO **********   "
COLOR 0, 3
PRINT
PRINT "   Para llamar al men£ Archivo oprima la tecla de funci¢n F2, al  "
PRINT "   hacerlo aparecer  un cuadro de dialogo en la parte inferior,"
PRINT "   indicando las opciones suministradas."
PRINT "   Para ejecutar una opci¢n presione un n£mero de 1 a 6."
PRINT
COLOR 15, 3
PRINT "         Presione una tecla para continuar....."
GOSUB PAUSA
IF A$ = CHR$(27) THEN GOTO 110
GOSUB SUBBORRAR
COLOR 1
LOCATE 14, 1
PRINT "   La opci¢n NUEVO le permitir  realizar un trabajo nuevo."
PRINT "   Si desea rodar una pel¡cula anteriormente grabada seleccione"
PRINT "   ABRIR del men£ Archivo, el programa pide el nombre del archivo"
PRINT "   en el cual fue guardada la pel¡cula."
PRINT "   Si ha terminado un trabajo se guardar  con la opci¢n GUARDAR,"
PRINT "   si la pel¡cula ya tiene un nombre se grabar  con ese mismo nombre"
PRINT "   por el contrario, si la pel¡cula no ten¡a un nombre el programa"
PRINT "   lo pedir ."
PRINT
COLOR 15, 3
PRINT "          Presione una tecla para continuar...."
GOSUB PAUSA
IF A$ = CHR$(27) THEN GOTO 110
GOSUB SUBBORRAR
COLOR 0
LOCATE 14, 1
PRINT "   La opci¢n 4 (SALVAR COMO) le permitir  guardar con otro nombre "
PRINT "   el trabajo realizado."
PRINT "   Si desea borrar alg£n archivo en el cual haya almacenado una "
PRINT "   pel¡cula seleccione BORRAR del men£ Archivo, en seguida teclee "
PRINT "   el nombre del archivo y presione ENTER."
PRINT "   Cuando desee terminar una sesi¢n de trabajo seleccione la opci¢n"
PRINT "   SALIR, el programa preguntar  si se desea grabar el trabajo."
PRINT
COLOR 15
PRINT "            Presione una tecla para continuar....."
GOSUB PAUSA
GOTO 110
AYEDICION:
GOSUB SUBBORRAR
COLOR 4, 3
LOCATE 14, 1
PRINT "               ********* MENU EDICION *********** "
COLOR 0
PRINT
PRINT "   Para invocar el men£ Edici¢n pulse F3, en la parte inferior"
PRINT "   de la pantalla se pide el n£mero del pantallazo que se desea"
PRINT "   cambiar, digite un n£mero de 1 a 20, seg£n se desee.  "
PRINT "   A continuaci¢n edite la l¡nea nueva."
PRINT
COLOR 15
PRINT "             Presione una tecla para continuar....."
GOSUB PAUSA
GOTO 110
AYCOLOR:
GOSUB SUBBORRAR
COLOR 4
LOCATE 14, 1
PRINT "                    ********* MENU COLOR *********"
COLOR 0
PRINT "   Este men£ le permite cambiar el color de la pel¡cula en cualquier"
PRINT "   momento de ejecuci¢n del programa, presione F4 para llamar al men£"
PRINT "   digite un n£mero de 1 a 31."
PRINT
COLOR 15
PRINT "                     Presione una tecla para continuar....."
GOSUB PAUSA
IF A$ = CHR$(27) THEN GOTO 110
GOSUB SUBBORRAR
COLOR 4
LOCATE 14, 1
PRINT "               CODIGOS PARA EL COLOR"
COLOR 0
PRINT "   Color 1 =        Color 9 =        Color 17=        Color 25="
PRINT "   Color 2 =        Color 10=        Color 18=        Color 26="
PRINT "   Color 3 =        Color 11=        Color 19=        Color 27="
PRINT "   Color 4 =        Color 12=        Color 20=        Color 28="
PRINT "   Color 5 =        Color 13=        Color 21=        Color 29="
PRINT "   Color 6 =        Color 14=        Color 22=        Color 30="
PRINT "   Color 7 =        Color 15=        Color 23=        Color 31="
PRINT "   Color 8 =        Color 16=        Color 24=        "
A$ = "ÛÛÛÛÛ"
B = 1: C = 14
FOR A = 15 TO 22
COLOR B
LOCATE A, C
PRINT A$
B = B + 1
NEXT A
B = 9
C = 31
FOR A = 15 TO 22
LOCATE A, C
COLOR B
PRINT A$
B = B + 1
NEXT A
B = 17
C = 48
FOR A = 15 TO 22
LOCATE A, C
COLOR B
PRINT A$
B = B + 1
NEXT A
B = 25
C = 65
FOR A = 15 TO 21
LOCATE A, C
COLOR B
PRINT A$
B = B + 1
NEXT A
COLOR 15
PRINT
PRINT "            Presione una tecla para continuar....."
GOSUB PAUSA
GOTO 110
AYEJECUTAR:
GOSUB SUBBORRAR
COLOR 4
LOCATE 14, 1
PRINT "                ******** MENU EJECUTAR ******** "
COLOR 0
PRINT "   Cuando haya terminado de editar una pel¡cula tendr  la opci¢n "
PRINT "   de rodarla, es decir, ver cada pantallazo en forma consecutiva."
PRINT "   Si desea rodar una pel¡cula pulse F5, a continuaci¢n, en la parte"
PRINT "   inferior de la pantalla, aparece un cuadro de dialogo, digite el "
PRINT "   n£mero del pantallazo desde el cual desea empezar a rodar la "
PRINT "   pel¡cula, luego, digite el n£mero del pantallazo en el cual desea"
PRINT "   terminar de rodar la pel¡cula. Por £ltimo teclee un n£mero que "
PRINT "   corresponde a la velocidad de rodamiento de la pel¡cula."
COLOR 15
PRINT "            Presione una tecla para continuar....."
GOSUB PAUSA
GOTO 110
SUBBORRAR:
COLOR 15, 3
FOR A = 14 TO 23
LOCATE A, 1: PRINT "                                                                            "
NEXT A
RETURN
PAUSA:
547 A$ = "": A$ = INKEY$: IF A$ = "" THEN 547
RETURN
ADP:
AUTOR$ = " Por Jairo Alejandro Duarte Avenda¤o."
RETURN

