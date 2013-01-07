#include <stdio.h>
#include <stdlib.h>

void RutErr (int cod);
typedef struct Mapa_s
{
	int LonX;
	int LonY;
	char TipoByte;
} MAPA;

int main (int argc, char *argv[])
{
	FILE *archivo;
	MAPA mapa;
	int x, y;

	if (argc < 2) RutErr (0);
	if ((archivo = fopen (argv[1], "rb")) == NULL) RutErr (1);

	if (fread (&mapa.LonX, 1, 2, archivo) != 2) RutErr (2);
	if (fread (&mapa.LonY, 1, 2, archivo) != 2) RutErr (2);
	mapa.LonY = 23;

	clrscr ();
	for (y = 1; y < mapa.LonY; y++) {
		for (x = 1; x <= mapa.LonX; x++) {

			if ((mapa.TipoByte = getc (archivo)) == EOF) RutErr (2);

			gotoxy (x, y); printf ("%c", mapa.TipoByte + 90);
		}
	}
	getch ();
	return 0;
} /* main */

void RutErr (int cod)
{
	switch (cod) {
		case 0:
			puts ("Map Reader versi¢n 1.0");
			puts ("Lector de mapas de Map Maker versi¢n 2.0");
			puts ("Sintaxis: MAP fichero.map");
		break;
		case 1:
			puts ("Error al intentar abrir el archivo MAP.");
		break;
		case 2:
			puts ("Error leyendo el archivo MAP.");
		break;
		default:
			printf ("Error de ejecuci¢n n£mero: %d.", cod);
		break;
	} /* switch (cod) */
	exit (cod);
} /* RutErr */