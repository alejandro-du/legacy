/* CONVERTIDOR DE PALETA PCX A PAL VERSION 1.0
	 1997 DPA Software. Todos los derechos reservados */

#include <stdio.h>

main (int argc, char *argv[])
{
	FILE *archivoMAP, *archivo;
	int x, y, xmap, ymap, byte, num;

	puts ("CONVERTIDOR DE MAPAS 1.0 DPA Software 1997. Todos los derechos reservados.");
	puts ("Programa para transformar el mapas de Map Maker 2.0.");

	if (argc < 3) { /* Verificar que se introdujo los nombres de los 2 archivos en la linea de ordenes */
		puts ("Sintaxis: MAPCONV Archivo.MAP Destino");
		return 1;
	}

	puts ("Abriendo y creando archivos...");
	if ((archivoMAP = fopen (argv[1], "rb")) == NULL) {
		printf ("Error al intentar abrir el archivo MAP: %s", argv[1]);
		return 1;
	}

	if ((archivo = fopen (argv[2], "wb")) == NULL) {
		printf ("Error al intentar crear el archivo destino: %s", argv[2]);
		return 1;
	}

	if (fread (&xmap, 1, 2, archivoMAP) != 2) {
		puts ("Error al intentar leer el archivo MAP.");
		return 1;
	}
		if (fread (&ymap, 1, 2, archivoMAP) != 2) {
		puts ("Error al intentar leer el archivo MAP.");
		return 1;
	}

	puts ("Escribiendo cabecera...");
	printf ("X = %d  Y = %d\n", xmap, ymap);
	fwrite (&xmap, 1, 2, archivo);
	fwrite (&ymap, 1, 2, archivo);

	puts ("Conviertiendo...");
	for (x = 0; x < ymap; x++) {
		for (num = 0; num < (x * xmap); num++) { /* lugar de inicio */
			if (getc (archivoMAP) == EOF) {
				puts ("\nError de lectura 1.");
				return 1;
			}
		}
		for (num = 0; num < (xmap - 1); num++) {
			if ((byte = getc (archivoMAP)) == EOF) {
				puts ("\nError de lectura 2.");
				return 1;
			}
			if (putc (byte, archivo) == EOF) {
				puts ("\nError de escritura.");
				return 1;
			}
			printf ("Byte No.: %ld %d\r", ftell(archivo), byte);
			for (y = 0; y < (ymap - 1); y++) {
				if (getc (archivoMAP) == EOF) {
					puts ("\nError de lectura 3.");
					return 1;
				}
			}
		}
		rewind (archivoMAP);
	}
	fclose (archivoMAP);
	fclose (archivo);
	puts ("\nMapa convertido.");
	return 0;
}