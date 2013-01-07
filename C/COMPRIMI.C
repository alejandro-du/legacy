#include <conio.h>
#include <stdio.h>

main (int argc, char *argv[])
{
	FILE *archivo, *comprimido;
	int num;
	int car;

	clrscr ();

	if (argc < 3) {
		puts ("Debe teclear el nombre de los archivos.");
		return 1;
	}

	if ((archivo = fopen (argv[1], "rb")) == NULL) {
		printf ("No se puede abrir el archivo: %s", argv[1]);
		return 1;
	}

/*	while (!feof (archivo)) {
		if ((car = getc (archivo)) > mayor) mayor = car;
		printf ("%X", car);
	}
	printf ("\nMayor = %d", mayor);*/
	remove ("e:\borlandc\temp\teclado");

	if ((comprimido = fopen (argv[2], "wb")) == NULL) {
		printf ("No se puede abrir el archivo: %s", argv[2]);
		return 1;
	}

	car = getc (archivo);

	car = car << 1;


	return 0;
}