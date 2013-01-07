/* CONVERTIDOR DE PALETA PCX A PAL VERSION 1.0
	 1997 DPA Software. Todos los derechos reservados */

#include <stdio.h>

main (int argc, char *argv[])
{
	FILE *archivoPCX, *archivoPAL;
	long int pos, cont;
	char paleta[768];

	puts ("PCX-PAL versi¢n 1.0 DPA Software 1997. Todos los derechos reservados.");
	puts ("Extractor de paletas PCX a PAL.");

	if (argc < 3) { /* Verificar que se introdujo los nombres de los 2 archivos en la linea de ordenes */
		puts ("Sintaxis: PCXPAL Archivo.PXC Archivo.PAL");
		return 1;
	}

	if ((archivoPCX = fopen (argv[1], "rb")) == NULL) {
		printf ("Error al intentar abrir el archivo PCX: %s", argv[1]);
		return 1;
	}

	if ((archivoPAL = fopen (argv[2], "wb")) == NULL) {
		printf ("Error al intentar abrir el archivo PAL: %s", argv[1]);
		return 1;
	}

	printf ("Leyendo el fichero: %s", argv[1]);
	fseek (archivoPCX, 0, SEEK_END); /* Ir al final del archivo PCX */
	pos = ftell (archivoPCX); /* Averiguar la posici¢n o el tama¤o del archivo PCX */
	rewind (archivoPCX); /* Volver a la posici¢n inicial del archivo */
	for (cont = 1; cont < (pos - 767); cont++) getc (archivoPCX); /* Descartar toda la imagen sin la paleta (restar los 768 Bytes de la paleta) */
	printf ("\nEscribiendo la paleta en: %s", argv[2]);
	for (cont = 0; cont < 768; cont++) {
		putc (getc (archivoPCX) >> 2, archivoPAL);
	}
	puts ("\nPaleta copiada.");
	return 0;
}