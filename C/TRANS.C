/*
C O D I F I C A D O R D E   F R A S E S   S E C R E T A S
Un programa para intercambiar frases codificadas.
Versi¢n 1.0
DPA Software.
Copyright (c) 1996 Jairo Alejandro Duarte Avenda¤o.
Santaf‚ de Bogot , D.C. Colombia. Diciembre de 1996.
*/

#include <conio.h>
#include <string.h>

void presentacion (void); /* Pantalla inicial del programa */
void centrar (char *cad, int fila); /* Declaraci¢n del la funci¢n de centrado del texto */
void mostrar_menu (void);
void menu_principal (void); /* Men£ principal del programa */
void codificar_frase (void); /* Transformar la frase normal a secreta */

void main (void)
{
	presentacion ();
	menu_principal ();
}

void presentacion (void) /* Presentaci¢n del programa */
{
	textbackground (0);
	clrscr ();
	textcolor (15);
	centrar ("C O D I F I C A D O R   D E   F R A C E S   S E C R E T A S", 4);
	textcolor (7);
	centrar ("Un programa para intercambiar fraces codificadas.", 7);
	centrar ("Escrito en Turbo C. 1.0", 8);
	centrar ("DPA SOFTWARE", 12);
	centrar ("Copyright (c) 1996 Jairo Alejandro Duarte.", 13);
	centrar ("Todos los derechos reservados.", 14);
	centrar ("Santaf‚ de Bogot , D.C. Colombia.", 15);
	centrar ("Versi¢n 1.0", 16);
	centrar ("(Presione una tecla para continuar)", 22);
	getch ();
}

void centrar (char *cad, int fila) /* Centrado del texto */
{
	gotoxy (((80 - strlen (cad)) / 2), fila);
	cprintf ("%s", cad);
}

void menu_principal (void)
{
	char eleccion;

	clrscr ();
	mostrar_menu ();

	for (;;) {
		scanf ("%s", eleccion);
		switch (atoi (eleccion)) {
			case 1: codificar_frase ();
			break;
//			case 2: codificar_frase ();
//			break;
//			case 3: abrir ();
//			break;
//			case 4: guardar ();
//			break;
				case 5: 
					clrscr ();
					exit (0);
				break;
			default:
				gotoxy (1, 19); delline ();
				gotoxy (30, 18); clreol ();
			break;
		}
	}
}

void mostrar_menu (void)
{
	textcolor (15);
	centrar ("C O D I F I C A D O R   D E   F R A C E S   S E C R E T A S", 1);
	textcolor (7);
	centrar ("MENU PRINCIPAL", 4);
	gotoxy (8, 7); puts ("1 - Codificar frase");
	gotoxy (8, 9); puts ("2 - Decodificar frase");
	gotoxy (8, 11); puts ("3 - Abrir");
	gotoxy (8, 13); puts ("4 - Guardar");
	gotoxy (8, 15); puts ("5 - Salir del programa");
	gotoxy (12, 18); printf ("Haga su elecci¢n: ");
}

void codificar_frase (void)
{
	char *cadena;
	register int num; /* N£mero de caracteres leidos */

	clrscr ();

	if (!(cadena = malloc (1921))) { /* Asignaci¢n de memoria para la cadena */
		printf ("No hay memoria suficiente para continuar el programa.");
		exit (1);
	}

	printf ("Introdusca el texto: ");

	for (num = 0; num <= 1920; num++) {
		if ((cadena[num] = getch ()) == 13) break;
		printf ("%c", cadena[num]);
	}

}