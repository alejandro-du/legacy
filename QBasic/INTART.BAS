DECLARE SUB ataque ()
DECLARE SUB PONERPAL (colorn AS INTEGER, r AS INTEGER, G AS INTEGER, b AS INTEGER)
DECLARE SUB leepcx (NOMBRE AS STRING)
DIM SHARED HEROE%(444)
DIM SHARED ENEMIGO%(444)
DEFINT A-Z
SCREEN 13
CALL leepcx("d:\imagenes\rose.PCX")
GET (0, 0)-(19, 19), ENEMIGO%
GET (20, 0)-(39, 19), HEROE%
CLS
CALL ataque

SUB ataque
        POSX = 160
        POSY = 100
        ENX = 0
        ENY = 0
        FIN = 0
        WHILE FIN = 0
                kbds$ = INKEY$ 'Movimiento humano
                SELECT CASE kbds$
                CASE CHR$(0) + "H"
                        POSY = POSY - 2
                CASE CHR$(0) + "P"
                        POSY = POSY + 2
               
                CASE CHR$(0) + "K"
                        POSX = POSX - 2
               
                CASE CHR$(0) + "M"
                        POSX = POSX + 2
               
                CASE CHR$(0) + "G"
                        POSX = POSX - 2
                        POSY = POSY - 2
               
                CASE CHR$(0) + "I"
                        POSX = POSX + 2
                        POSY = POSY - 2
               
                CASE CHR$(0) + "O"
                        POSX = POSX - 2
                        POSY = POSY + 2
               
                CASE CHR$(0) + "Q"
                        POSX = POSX + 2
                        POSY = POSY + 2
                CASE ELSE
                END SELECT
                'Movimiento atacante del enemigo
                IF N = 100 THEN
                        IF POSX > ENX THEN ENX = ENX + 1
                        IF POSX < ENX THEN ENX = ENX - 1
                        IF POSY > ENY THEN ENY = ENY + 1
                        IF POSY < ENY THEN ENY = ENY - 1
                        N = 0
                END IF
                        IF POSX < 0 THEN POSX = 0
                        IF POSX > 300 THEN POSX = 300
                        IF POSY < 0 THEN POSY = 0
                        IF POSY > 180 THEN POSY = 180
                PUT (POSX, POSY), HEROE%, PSET
                PUT (ENX, ENY), ENEMIGO%, PSET
                IF POSX = ENX AND POSY = ENY THEN FIN = 1
                N = N + 1
        WEND
END SUB

SUB leepcx (NOMBRE AS STRING)
  OPEN NOMBRE FOR BINARY AS #1
  DIM DATO AS STRING * 1
  DIM BASURA AS STRING * 128
  DIM BUFFER AS STRING * 128
  DIM CABECERA AS STRING * 10
  GET #1, , BASURA 'LEEMOS Y DESPRECIAMOS LA CABECERA
  FOR N = 1 TO (LOF(1) / 128) - 7 'LEEMOS LA ZONA COMPRIMIDA RLE
    GET #1, , BUFFER
    FOR J = 1 TO 128
      DATO = MID$(BUFFER, J, 1)
      IF TIPOBYTE = 1 THEN
        FOR K = 1 TO NUMDATOS
          PSET (X, Y), ASC(DATO)
          X = X + 1
          IF X > 319 THEN
            Y = Y + 1
            X = 0
          END IF
        NEXT K
        TIPOBYTE = 0
      ELSE
        IF ASC(DATO) > 191 THEN
          TIPOBYTE = 1
          NUMDATOS = (ASC(DATO) - 192)
        ELSE
          PSET (X, Y), ASC(DATO)
          X = X + 1
          IF X > 319 THEN
            Y = Y + 1
            X = 0
          END IF
        END IF
      END IF
   NEXT J
  NEXT N
  DIM PALETA AS STRING * 768 'LEEMOS PALETA
  GET #1, LOF(1) - 767, PALETA
  K = 1
  FOR N = 0 TO 255
    CALL PONERPAL(N, ASC(MID$(PALETA, K, 1)) / 4, ASC(MID$(PALETA, K + 1, 1)) / 4, ASC(MID$(PALETA, K + 2, 1)) / 4)
    K = K + 3
  NEXT N
  CLOSE
END SUB

DEFSNG A-Z
SUB PONERPAL (colorn AS INTEGER, r AS INTEGER, G AS INTEGER, b AS INTEGER)
  OUT (&H3C8), colorn
  OUT (&H3C9), r
  OUT (&H3C9), G
  OUT (&H3C9), b
  'a$ = INPUT$(1)
  'PRINT colorn; "="; r; ","; g; ","; b; "  "

END SUB

