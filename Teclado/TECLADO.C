#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

#define MAXINTENTOS 100
#define OBJETIVOPUNTOS 3500
#define MINPUNTOS (OBJETIVOPUNTOS / MAXINTENTOS)
#define TRUE 1
#define FALSE 0
int VELOCIDAD = 25;

//extern int _wscroll = FALSE; /* desactivar el scroll vertical */
void presentacion (void);
void iniciar (void); /* comienzo del juego */
void centrar (char *cad, int fila);
void fondo (char leccion, char *teclas);
int jugar (char *teclas);
void barraestado (char *comentario);
void subir (int pos, char car);
int inkey (); /* presionar una tecla */

int main (int argc, char *argv[])
{
	int leccion;

	if (argc == 2) { /* introducida la velocidad desde la l¡nea de ordenes */
		VELOCIDAD = atoi (argv[1]);
	}
	_setcursortype (_NOCURSOR); /* no mostrar cursor */
	presentacion ();
	iniciar (); /* iniciar el juego */

	textbackground (BLACK);
	textcolor (LIGHTGRAY);
	clrscr ();
        puts ("FELICITACIONES!!!");
        puts ("Ahora ya sabe mecanografiar con rapidez.\n");
        puts ("DPA Software. 1997");
	puts ("Autor: Jairo Alejandro Duarte Avenda¤o.");
	puts ("jaal81@yahoo.com");
	_setcursortype (_NORMALCURSOR); /* mostrar de nuevo el cursor */

	return 0;
} /* main */

void presentacion (void) /* presentaci¢n del programa */
{
	int color;

	textbackground (BLACK);
	clrscr ();
	textcolor (LIGHTGRAY);
	centrar ("Un £til programa para practicar con el teclado.", 7);
	centrar ("Escrito en lenguaje C", 8);
	textcolor (WHITE);
	centrar ("DPA SOFTWARE", 12);
	textcolor (LIGHTBLUE);
	centrar ("1997 Jairo Alejandro Duarte Avenda¤o.", 13);
	textcolor (LIGHTGRAY);
	centrar ("jaal81@yahoo.com", 14);
	centrar ("Santaf‚ de Bogot , D.C. Colombia.", 15);
	centrar ("Versi¢n 1.0", 16);
	textcolor (LIGHTGRAY | BLINK);
	centrar ("(Presione una tecla para continuar)", 22);
	for (color = BLUE; !inkey(); color++) { /* presionar un tecla para continuar */
		textcolor (color); /* degradaci¢n */
		centrar ("T E C L A D O", 4);
		delay (40);
		if (color > WHITE) color = BLUE;
	}
} /* presentacion */


void iniciar (void)
{
	int leccion = 0;
	char *teclas[] = {"ASDFG", "HJKL¥", "ASDFGHJKL¥", "QWERT", "YUIOP", "QWERTYUIOP", "ZXCVB", "NM,.-", "ZXCVBNM,.-", "ASDFGHJKL¥", "QWERTYUIOP", "ZXCVBNM,.-", "ASDFGHJKL¥QWERTYUIOP", "ASDFGHJKL¥ZXCVBNM,.-", "ASDFGHJKL¥QWERTYUIOPZXCVBNM,.-"};

	while (leccion < 15) {
		fondo (leccion + 1, teclas[leccion]); /* esperar a que se pulse una tecla para mostrar el fondo */
		if ((jugar (teclas[leccion])) == 1) leccion++; /* empezar a jugar, si pasa la lecci¢n contin£a con la siguiente*/
 } /* while */
} /* iniciar */


void fondo (char leccion, char *teclas) /* mostrar el fondo "tablero" */
{
	int color;

	textcolor (YELLOW);
	textbackground (BLACK);
	clrscr ();
	centrar ("L E C C I O N   #   ", 3); cprintf ("\b%d  ", leccion); /* imprimir el titulo */
	textcolor (LIGHTBLUE);
	cprintf ("\n\n\n\n\n\r   Este juego consiste en presionar la tecla que aparece desplazandose en");
	cprintf ("\n\r   la barra, lo m s pronto posible, para lograr obtener la mayor cantidad");
	cprintf ("\n\r   posible de puntos.");
	textcolor (RED);
	cprintf ("\n\n\n\r   Tienes que lograr hacer %d puntos en menos de %d intentos.", OBJETIVOPUNTOS, MAXINTENTOS);
	gotoxy (7, 17);
	textcolor (CYAN);
	cprintf ("Usa estas teclas: \"%s\"", teclas); /* teclas con las que hay que jugar */
	textcolor (LIGHTGRAY | BLINK);
	centrar ("­­­ Presiona una tecla para comenzar la lecci¢n !!!", 23);
	for (color = BLUE; !inkey(); color++) { /* presionar un tecla para continuar */
		textcolor (color); /* degradaci¢n */
		centrar ("L E C C I O N   #   ", 3); cprintf ("\b%d  ", leccion); /* imprimir el titulo */
		delay (40);
		if (color > WHITE) color = BLUE;
	}
	/* dibujar el "tablero" */
	clrscr ();
	textcolor (WHITE);
	textbackground (BLUE);
	centrar ("  L E C C I O N   #     ", 1); cprintf ("\b\b\b%d  ", leccion); /* imprimir el titulo */
	textcolor (BLUE);
	textbackground (BLACK);
	centrar (" ------------------------------------------------------------------------ ", 2);
	centrar (" ------------------------------------------------------------------------ ", 4);
	textcolor (LIGHTGRAY | BLINK);
	centrar (teclas, 3);

	textcolor (BLACK);
	textbackground (LIGHTGRAY);
	centrar ("                                                                          ", 6);
	centrar ("                                                                          ", 7);
	centrar ("                                                                          ", 8);
	centrar (" 04±±±10±±±15±±±20±±±25±±±30±±±35±±±40±±±45±±±50±±±55±±±60±±±65±±±70±±±75 ", 9);
	centrar ("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 10);
	centrar ("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 11);
	centrar ("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 12);
	centrar ("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 13);
	centrar ("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 14);
	centrar ("²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²", 15);
	centrar ("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 16);
	centrar ("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 17);
	centrar ("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 18);
	centrar ("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 19);
	centrar ("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 20);
	centrar (" 04±±±10±±±15±±±20±±±25±±±30±±±35±±±40±±±45±±±50±±±55±±±60±±±65±±±70±±±75 ", 21);
	centrar ("                                                                          ", 22);
	centrar ("                                                                          ", 23);
	centrar ("                                                                          ", 24);
	textbackground (BLUE);
	textcolor (LIGHTGRAY);
	centrar ("  Presiona las teclas adecuadas...                                          ", 25);
	textbackground (LIGHTGRAY);
	textcolor (RED);
	gotoxy (61, 7); cprintf ("Puntos:");
	gotoxy (24, 7); cprintf ("Letra No.:");
	gotoxy (41, 7); cprintf ("Porcentaje:");
	textbackground (BLUE);
	textcolor (LIGHTCYAN);
	gotoxy (7, 7); cprintf ("  Tecla:     ");
} /* fondo */

int jugar (char *teclas) /* funci¢n principal del juego */
{
	int puntos = 0; /* puntuaci¢n del jugador */
	int intentos = 1; /* n£mero de letras que han aparecido */
	int max = strlen (teclas);
	int tecla = 0; /* indice del array teclas */
        int tec;
	int pos = 77; /* final del tablero */
	char comentario[80];

//	randomize ();

	while (intentos <= MAXINTENTOS) { /* bucle principal */
		tecla = rand()%max; /* generar tecla aleatoria */
		textbackground (BLUE);
		textcolor (LIGHTCYAN);
		gotoxy (17, 7); cprintf ("%c", teclas [tecla]); /* mostrar en la posici¢n Tecla: */

		for (;;) { /* se ejecuta hasta que se presiona la tecla correcta */
			textbackground (LIGHTGRAY);
			textcolor (BLACK);
			gotoxy (pos, 15); cprintf ("%c", teclas [tecla]); /* mostrar en la barra */
			pos--;
			textcolor (RED);
			gotoxy (34, 7); cprintf ("%d", intentos);
			gotoxy (53, 7); cprintf ("%d", puntos / MINPUNTOS);
                        gotoxy (60, 7); cprintf ("Puntos: %d    ", puntos);
			textcolor (BLACK);
			if (pos < 4 || (tec = inkey ()) == teclas[tecla]) {
                          	gotoxy (pos + 1, 15); cprintf ("²"); /* borrar tecla */
				textcolor (RED);
				if (pos < 4) puntos -= pos;
				puntos += pos;
				if (pos > 70) strcpy (comentario,      "   ­­­ Fanfarr¢n !!!                                ");
				else if (pos > 60) strcpy (comentario, "   ­ Huy no, tan r pido el HP !                     ");
				else if (pos > 50) strcpy (comentario, "   No... que lento...                               ");
				else if (pos > 40) strcpy (comentario, "   Que imbecil...                                   ");
				else if (pos > 30) strcpy (comentario, "   ­ M s Rapido idiota !                            ");
				else if (pos > 20) strcpy (comentario, "   Es que no entiende maldito imbecil ???  ­R pido! ");
				else if (pos > 10) strcpy (comentario, "   ­ RAPIDO IDIOTA !                                ");
				else if (pos > 2) {
					strcpy (comentario,            "   ­­­ ESTUPIDO !!!                                 ");
					sound (70);
					delay (50);
					nosound ();
				} /* if */
				barraestado (comentario);
				if (pos > 3) subir (pos, teclas[tecla]);
				pos = 77;
				break;
			} /* if (pos < 4... */
                        else {
                             if(tec != 0 && puntos > 50) puntos -= 50;
                        }

			delay (VELOCIDAD);
			gotoxy (pos + 1, 15); cprintf ("²"); /* borrar tecla */
			gotoxy (pos, 15); cprintf ("%c", teclas[tecla]); /* mostrar en la barra */
                } /* for (;;) */
		if (puntos >= OBJETIVOPUNTOS) break; /* si se logra el n£mero de puntos */
		intentos++;
	} /* while */
	/* verificar si se ha lograda el objetivo o no */
	textbackground (BLACK);
	textcolor (LIGHTGRAY);
	clrscr ();
	centrar ("Presiona una tecla para continuar...", 24);
	if (intentos < MAXINTENTOS) { /* objetivo logrado */
		int color;
		for (color = BLUE; !inkey(); color++) { /* presionar un tecla para continuar */
			textcolor (color); /* degradaci¢n */
			centrar ("­ ­ ­  L O G R A S T E   E L   O B J E T I V O  ! ! !", 12);
			sound (color + 100);
			delay (40);
			if (color > WHITE) color = BLUE;
		}
		nosound ();
		return TRUE;
	} /* if (intentos... */
	else { /* si no se logr¢ el objetivo */
		centrar ("No has logrado el objetivo.", 10);
		centrar ("Tendr s que repetir la lecci¢n...", 11);
		getch ();
		return FALSE;
	}
} /* jugar */

int inkey () /* presionar una tecla */
{
	int tecla;

	tecla = inp (0x60);

	if (kbhit ()) {
		getch ();
		switch (tecla) {
			case 30:
				tecla = 'A';
			break;
			case 0:
				tecla = 0;
			break;
			case 48:
				tecla = 'B';
			break;
			case 46:
				tecla = 'C';
			break;
			case 32:
				tecla = 'D';
			break;
			case 18:
				tecla = 'E';
			break;
			case 33:
				tecla = 'F';
			break;
			case 34:
				tecla = 'G';
			break;
			case 35:
				tecla = 'H';
			break;
			case 23:
				tecla = 'I';
			break;
			case 36:
				tecla = 'J';
			break;
			case 37:
				tecla = 'K';
			break;
			case 38:
				tecla = 'L';
			break;
			case 50:
				tecla = 'M';
			break;
			case 49:
				tecla = 'N';
			break;
			case 39:
				tecla = '¥';
			break;
			case 24:
				tecla = 'O';
			break;
			case 25:
				tecla = 'P';
			break;
			case 16:
				tecla = 'Q';
			break;
			case 19:
				tecla = 'R';
			break;
			case 31:
				tecla = 'S';
			break;
			case 20:
				tecla = 'T';
			break;
			case 22:
				tecla = 'U';
			break;
			case 47:
				tecla = 'V';
			break;
			case 17:
				tecla = 'W';
			break;
			case 45:
				tecla = 'X';
			break;
			case 21:
				tecla = 'Y';
			break;
			case 44:
				tecla = 'Z';
			break;
			case 51:
				tecla = ',';
			break;
			case 52:
				tecla = '.';
			break;
			case 53:
				tecla = '-';
			break;
			case 1: /* ESC */
				textbackground (BLACK);
				textcolor (LIGHTGRAY);
				clrscr ();
				puts ("DPA Software. 1997");
				puts ("Autor: Jairo Alejandro Duarte Avenda¤o.");
				puts ("jaal81@yahoo.com");
				_setcursortype (_NORMALCURSOR); /* mostrar de nuevo el cursor */
				nosound ();
				exit (0);
			break;
                        default:
                           tecla = -1;
                        break;
		} /* switch */
		return (tecla);
	} /* if */
	else return (0);
} /* inkey */

void barraestado (char *comentario)
{
	textbackground (BLUE);
	textcolor (LIGHTGRAY);
	gotoxy (3, 25); cprintf ("%s", comentario);
} /* barraestado */

void subir (int pos, char car) /* animaci¢n del caracter car hacia arriba */
{
	int y;

	textbackground (LIGHTGRAY);
	textcolor (BLACK);
	sound (100);
	for (y = 14; y > 10; y--) { /* subir el caracter */
		gotoxy (pos, y); cprintf ("%c", car);
		delay (11);
	}
	nosound ();
	sound (400);
	for (y = 14; y > 10; y--) {
		gotoxy (pos, y); cprintf ("±");
		delay (6);
	}
	nosound ();
} /* subir */

void centrar (char *cad, int fila) /* Centrado de una cadena */
{
	gotoxy ((82 - strlen (cad)) / 2, fila);
	cprintf ("%s", cad);
} /* centrar */