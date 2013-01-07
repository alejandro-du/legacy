' Author unknown
DEFINT A-Z
DIM Prefix(4095), Suffix(4095), OutStack(4095), shiftout%(8)
DIM Ybase AS LONG, powersof2(11) AS LONG, WorkCode AS LONG
 
FOR a% = 0 TO 7: shiftout%(8 - a%) = 2 ^ a%: NEXT a%
FOR a% = 0 TO 11: powersof2(a%) = 2 ^ a%: NEXT a%
INPUT "Archivo GIF: "; a$
INPUT "Archivo destino SPR: "; archivo$
IF a$ = "" THEN INPUT "GIF file"; a$: IF a$ = "" THEN END
IF INSTR(a$, ".") = 0 THEN a$ = a$ + ".gif"
OPEN a$ FOR BINARY AS #1
a$ = "      ": GET #1, , a$
IF a$ <> "GIF87a" THEN PRINT "Not a GIF87a file.": END
GET #1, , TotalX: GET #1, , TotalY: GOSUB GetByte
NumColors = 2 ^ ((a% AND 7) + 1): NoPalette = (a% AND 128) = 0
GOSUB GetByte: Background = a%
GOSUB GetByte: IF a% <> 0 THEN PRINT "Bad screen descriptor.": END
IF NoPalette = 0 THEN P$ = SPACE$(NumColors * 3): GET #1, , P$
DO
    GOSUB GetByte
    IF a% = 44 THEN
        EXIT DO
    ELSEIF a% <> 33 THEN
        PRINT "Unknown extension type.": END
    END IF
    GOSUB GetByte
    DO: GOSUB GetByte: a$ = SPACE$(a%): GET #1, , a$: LOOP UNTIL a% = 0
LOOP
GET #1, , XStart: GET #1, , YStart: GET #1, , XLength: GET #1, , YLength
XEnd = XStart + XLength: YEnd = YStart + YLength: GOSUB GetByte
IF a% AND 128 THEN PRINT "Can't handle local colormaps.": END
Interlaced = a% AND 64: PassNumber = 0: PassStep = 8
GOSUB GetByte
ClearCode = 2 ^ a%
EOSCode = ClearCode + 1
FirstCode = ClearCode + 2: NextCode = FirstCode
StartCodeSize = a% + 1: CodeSize = StartCodeSize
StartMaxCode = 2 ^ (a% + 1) - 1: MaxCode = StartMaxCode
 
BitsIn = 0: BlockSize = 0: BlockPointer = 1
X% = XStart: Y% = YStart: Ybase = Y% * 320&
 
SCREEN 13: DEF SEG = &HA000
IF NoPalette = 0 THEN
    OUT &H3C7, 0: OUT &H3C8, 0
    FOR a% = 1 TO NumColors * 3: OUT &H3C9, ASC(MID$(P$, a%, 1)) \ 4: NEXT a%
END IF
LINE (0, 0)-(319, 199), Background, BF
DO
    GOSUB GetCode
    IF Code <> EOSCode THEN
        IF Code = ClearCode THEN
            NextCode = FirstCode
            CodeSize = StartCodeSize
            MaxCode = StartMaxCode
            GOSUB GetCode
            CurCode = Code: LastCode = Code: LastPixel = Code
            IF X% < 320 THEN POKE X% + Ybase, LastPixel
            X% = X% + 1: IF X% = XEnd THEN GOSUB NextScanLine
        ELSE
            CurCode = Code: StackPointer = 0
            IF Code > NextCode THEN EXIT DO
            IF Code = NextCode THEN
                CurCode = LastCode
                OutStack(StackPointer) = LastPixel
                StackPointer = StackPointer + 1
            END IF
 
            DO WHILE CurCode >= FirstCode
                OutStack(StackPointer) = Suffix(CurCode)
                StackPointer = StackPointer + 1
                CurCode = Prefix(CurCode)
            LOOP
 
            LastPixel = CurCode
            IF X% < 320 THEN POKE X% + Ybase, LastPixel
            X% = X% + 1: IF X% = XEnd THEN GOSUB NextScanLine
 
            FOR a% = StackPointer - 1 TO 0 STEP -1
                IF X% < 320 THEN POKE X% + Ybase, OutStack(a%)
                X% = X% + 1: IF X% = XEnd THEN GOSUB NextScanLine
            NEXT a%
 
            IF NextCode < 4096 THEN
                Prefix(NextCode) = LastCode
                Suffix(NextCode) = LastPixel
                NextCode = NextCode + 1
                IF NextCode > MaxCode AND CodeSize < 12 THEN
                    CodeSize = CodeSize + 1
                    MaxCode = MaxCode * 2 + 1
                END IF
            END IF
            LastCode = Code
        END IF
    END IF
LOOP UNTIL DoneFlag OR Code = EOSCode
CLOSE




OPEN archivo$ FOR BINARY AS #1
DIM xs AS INTEGER
DIM ys AS INTEGER

DIM xp AS INTEGER
DIM yp AS INTEGER
DIM posicion AS LONG
posicion = 6

xs = 319
ys = 199

PUT #1, 1, xs
PUT #1, 3, ys

FOR yp = 0 TO 199
        FOR xp = 0 TO 319
                byte = POINT(xp, yp)
                PSET (xp, yp), 0
                PUT #1, posicion, byte
                posicion = posicion + 1
        NEXT xp
NEXT yp
PRINT "Archivo Convertido."

CLOSE






END
 
GetByte: a$ = " ": GET #1, , a$: a% = ASC(a$): RETURN
 
NextScanLine:
    IF Interlaced THEN
        Y% = Y% + PassStep
        IF Y% >= YEnd THEN
            PassNumber = PassNumber + 1
            SELECT CASE PassNumber
            CASE 1: Y% = 4: PassStep = 8
            CASE 2: Y% = 2: PassStep = 4
            CASE 3: Y% = 1: PassStep = 2
            END SELECT
        END IF
    ELSE
        Y% = Y% + 1
    END IF
    X% = XStart: Ybase = Y% * 320&: DoneFlag = Y% > 199
RETURN
GetCode:
    IF BitsIn = 0 THEN GOSUB ReadBufferedByte: LastChar = a%: BitsIn = 8
    WorkCode = LastChar \ shiftout%(BitsIn)
    DO WHILE CodeSize > BitsIn
        GOSUB ReadBufferedByte: LastChar = a%
        WorkCode = WorkCode OR LastChar * powersof2(BitsIn)
        BitsIn = BitsIn + 8
    LOOP
    BitsIn = BitsIn - CodeSize
    Code = WorkCode AND MaxCode
RETURN
ReadBufferedByte:
    IF BlockPointer > BlockSize THEN
        GOSUB GetByte: BlockSize = a%
        a$ = SPACE$(BlockSize): GET #1, , a$
        BlockPointer = 1
    END IF
    a% = ASC(MID$(a$, BlockPointer, 1)): BlockPointer = BlockPointer + 1
RETURN

