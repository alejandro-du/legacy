' ***************************************************************************
' *  Programa creador de archivos originales de disco de CONFESIONARIO      *
' *                                                                         *
' *  NOTA: Cambiar unidad destino antes de usar.                            *
' ***************************************************************************
CLS
LOCATE 13, 20: PRINT "Copiando el programa en el disco..."
SHELL "COPY e:\dpasoft\qbasic\CONFES.BAS A:\CONFES.PRB /V"
PLAY "MBMNC9C9D9"
CLS
LOCATE 13, 20: PRINT "Copiando el archivo REGP.TXT en el disco..."
SHELL "COPY e:\dpasoft\qbasic\REGP.TXT A:\REGP.TXT /V"
PLAY "MBMNC9C9D9"

CLS
LOCATE 13, 20: PRINT "Copiando el archivo INSTALAR.BAT en el disco..."
SHELL "COPY e:\dpasoft\qbasic\INSTPC.BAT A:\INSTALAR.BAT /V"
PLAY "MBMNC9C9D9"

CLS
LOCATE 1, 20: PRINT "Copiando archivo PROGOR.CFS"
LOCATE 13, 29: PRINT "de 210"
FOR A = 1 TO 210
OPEN "A:\PROGOR.CFS" FOR APPEND AS #A
LOCATE 13, 10: PRINT "Escribiendo #:"; A
WRITE #A, "j9�y PRINT INPUT$K�  9j�yj���iva� OPEN #�if621� FORjI APPEND jiAS #j"
CLOSE : NEXT A
PLAY "MBMNC9C9D9"

CLS
LOCATE 1, 20: PRINT "Copiando archivo EAQHQ.PSO"
LOCATE 13, 29: PRINT "de 159"
FOR A = 1 TO 159
OPEN "A:\EAQHQ.PSO" FOR APPEND AS #A
LOCATE 13, 10: PRINT "Escribiendo #:"; A
WRITE #A, "��XY���u���s��t�|�>3UVRQS�Y�![YZ^]�>�2����s� #�if621�  jiAS #j"
CLOSE : NEXT A
PLAY "MBMNC9C9D9"

CLS
LOCATE 1, 20: PRINT "Copiando archivo INST.CFS"
LOCATE 13, 29: PRINT "de 209"
FOR A = 1 TO 209
OPEN "A:\INST.CFS" FOR APPEND AS #A
LOCATE 13, 10: PRINT "Escribiendo #:"; A
WRITE #A, "�t��!C��Y[�P��/DD�=.t�VQWQP�݋D&�&����"
CLOSE : NEXT A
PLAY "MBMNC9C9D9"

CLS
LOCATE 1, 20: PRINT "Copiando archivo CON.CFS"
LOCATE 13, 29: PRINT "de 145"
FOR A = 1 TO 145
OPEN "A:\INST.CFS" FOR APPEND AS #A
LOCATE 13, 10: PRINT "Escribiendo #:"; A
WRITE #A, "�tVϺ���� F�5 �u����>�!����&Y���u���s��t�|Ϻ����   ���"
CLOSE : NEXT A
PLAY "MBMNC9C9D9"

CLS
LOCATE 13, 20: PRINT "Ocultando el archivo EAQHQ.PSO..."
SHELL "ATTRIB +H A:\EAQHQ.PSO"
PLAY "MBMNC9C9D9D9E9E9"

CLS
LOCATE 13, 30: PRINT "Copia terminada."
END

