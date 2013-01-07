#include <conio.h>
#include <stdio.h>

main (void)
{
	FILE *origen[3], *fdestino;
	char *archivos[3], *destino, car;
	int num;

	clrscr ();

	for (num=0; num < 3; num++) {
		printf ("\nArchivo origen #%d: ", num + 1);
		scanf ("%s", archivos[num]);
		if ((origen[num] = fopen (archivos[num], "rb")) == NULL) {
			puts ("No se puede abrir el archivo.");
			return 1;
		}
	}

	printf ("\nArchivo destino: ");
	scanf ("%s", destino);
	if ((fdestino = fopen (destino, "wb")) == NULL) {
		puts ("No se puede crear el archivo.");
		return 1;
	}

	printf ("\nTrabajando...");
	for (num = 0; num < 3; num++) {
		while (!feof(origen[num])) {
			car = getc (origen[num]);
			putc (car, fdestino);
		}
		fputs ("DPA SOFTWARE  dpa software", fdestino);
	}
}