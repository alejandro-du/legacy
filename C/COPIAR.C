/* Este codigo copia dos archivos. */

#include <stdio.h>

main (int argc, char *argv[])
{
	FILE *origen, *destino;
	char car;

	if (argc != 3) {
		puts ("Debe teclear el nombre del archivo origen y el destino.");
		return 1;
	}
	if ((origen = fopen (argv[1], "rb")) == NULL) {
		puts ("No se puede abrir el archivo origen.");
		return 1;
	}
	if ((destino = fopen (argv[2], "wb")) == NULL) {
		puts ("No se puede abrir el archivo destino.");
		return 1;
	}
	while (!feof(origen)) {
		car = getc (origen);
		putc (car, destino);
	}
	fclose (origen); fclose (destino);
	puts ("Archivo copiado.");
	return 1;
}