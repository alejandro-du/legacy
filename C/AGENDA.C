/*
			Agenda telefonica.
			Autor: Jairo Alejandro Duarte Avenda¤o.
			D.P.A. Software.
*/

#include <conio.h>
#include <cuadros.h>

void presentacion (void);
void menu_principal (void);
void anadir_fichas (void);
void borrar (void);
void guardar_datos (void);

void main (void)
{
	presentacion ();
	menu_principal ();
}

void presentacion (void)
{
	clrscr ();
	gotoxy (25, 12); printf ("****** AGENDA TELEFONICA ******");
	gotoxy (27, 13); printf ("POR: JAIRO ALEJANDRO DUARTE");
	gotoxy (33, 14); printf ("D.P.A. Software");
	delay (480);
}

void menu_principal (void)
{
	int a;
	char opcion;

	clrscr ();
	cuadro (80, 23, 1, 1, 205, 186, 201, 187, 200, 188);
	for (a = 2; a < 80; a++) {
		gotoxy (a, 3); printf ("%c", 205);
	}
	gotoxy (4, 2); printf ("A G E N D A    T E L E F O N I C A     / MENU PRINCIPAL");
	gotoxy (13, 7); printf ("1   A¥ADIR FICHAS");
	gotoxy (13, 9); printf ("2   BORRAR FICHAS");
	gotoxy (13, 11); printf ("3   MODIFICAR FICHAS");
	gotoxy (13, 13); printf ("4   CONSULTAR FICHAS");
	gotoxy (13, 15); printf ("5   VER TODAS LAS FICHAS");
	gotoxy (13, 17); printf ("6   SALIR DEL PROGRAMA");
	gotoxy (4, 20); printf ("SIRVASE INTRODUCIR SU SELECCION: ");
	opcion = getche ();
	if (opcion == '1') anadir_fichas ();
/*	if (a == 2) borrar_fichas ();
	if (a == 3) modificar_fichas ();
	if (a == 4) consultar_fichas ();
	if (a == 5) ver_todas_fichas ();
	if (a == 6) salir ();*/
}

void borrar (void)
{
	int x, y;

	for (x = 2; x < 80; x++) {
		for (y = 4; y < 23; y++) {
			gotoxy (x, y); printf (" ");
		}
	}
}




void anadir_fichas (void)
{
	const short int maximo_caracteres = 52;
	char primer_apellido[80], *pa, segundo_apellido[80], *sa, nombres[80], *n, direccion[80], *d, telefono[80], *t, datos[80], *dt;
	primer_apellido[0] = maximo_caracteres;
	segundo_apellido[0] = maximo_caracteres;
	nombres[0] = maximo_caracteres;
	direccion[0] = maximo_caracteres;
	telefono[0] = maximo_caracteres;
	datos[0] = maximo_caracteres;

	borrar ();
	gotoxy (45, 2); printf ("A¥ADIR FICHAS  ");
	gotoxy (10, 7); printf ("PRIMER APELLIDO.:");
	gotoxy (10, 9); printf ("SEGUNDO APELLIDO:");
	gotoxy (10, 11); printf ("NOMBRES.........:");
	gotoxy (10, 13); printf ("DIRECCION.......:");
	gotoxy (10, 15); printf ("TELEFONO........:");
	gotoxy (10, 17); printf ("DATOS...........:");
	gotoxy (28, 7); pa = cgets (primer_apellido);
	gotoxy (28, 9); sa = cgets ( segundo_apellido);
	gotoxy (28, 11); n = cgets ( nombres);
	gotoxy (28, 13); d = cgets ( direccion);
	gotoxy (28, 15); t = cgets ( telefono);
	gotoxy (28, 17); dt = cgets ( datos);
	guardar_datos ();
}

void guardar_datos (void)
{
	FILE *archivo;

	if ((archivo = fopen ("c:\progra~2\agenda.dat", "b")) == NULL) {
		gotoxy (2, 2); printf ("No se pudo abrir el archivo");
	}
	fputs (pa, archivo);
}