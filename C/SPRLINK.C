/* ASISTENTE PARA ENLAZAR FICHEROS SPR VERSION 1.0
	 1997 DPA Software. Todos los derechos reservados */

#include <stdio.h>
#include <string.h>

main (int argc, char *argv[])
{
	int totalsprites, cont = 0;
	char archivo[401][114]; /* Array de cadenas para los nombres de los archivos */
	long int bytes, x = 0, y = 0, x2 = 0, y2 = 0;
	FILE *archivoSPR, *archivoSPE;

	puts ("BLK LINKER versi¢n 1.0 DPA Software 1999.");
	puts ("Asistente para enlazar archivos.");
	if (argc > 1) { /* Si fueron introducidos argumentos en la linea de ordenes */
		if (!strcmp (argv[1],"/?")) { /* Mostrar ayuda */
			puts ("\nBLK LINKER versi¢n 1.0");
			puts ("Es un asistente que permine unir o enlazar los archivos BLK con bloques");
			puts ("para formar un fichero con mayor n£mero de de estos.");
			puts ("El programa pide que se introduscan los nombres de los archivos BLK que se");
			puts ("quieren enlazar. Introdusca los nombres uno por uno.");
			puts ("Luego teclee el nombre del archivo de salida.");
		}
		return 0;
	}
	printf ("\nN£mero total de archivos a enlazar: ");
	scanf ("%d", &totalsprites); /* Guardar n£mero total de sprites en totalsprites */

	printf ("Introdusca los nombres de los %d archivos a enlazar:\n", totalsprites);
	while (cont < totalsprites) { /* Bucle para la introducci¢n de los nombres de ficheros SPR */
		printf ("Fichero #%d: ", cont + 1);
		scanf ("%s", archivo[cont]);

		if (!strcmp (archivo[cont], "-1")) { /* Verificar si se ha introducido -1 para salir del programa */
			puts ("Programa abortado.");
			return 0; /* Salida normal del programa */
		}

		if (!strchr (archivo[cont], '.')) strcat (archivo[cont], ".BLK"); /* Si no hay extenci¢n se le coloca .BLK */

		if ((archivoSPR = fopen (archivo[cont], "rb")) == NULL) {
			printf ("\aError al intentar abrir el archivo: %s\n", archivo[cont]);
			cont--;
		}
		fclose (archivoSPR);
		cont++;
	}

	printf ("Introdusca el nombre del fichero de salida: ");
	scanf ("%s", archivo[totalsprites]); /* Nombre del archivo de escritura */
	if (!strchr (archivo[totalsprites], '.')) strcat (archivo[totalsprites], ".BLK"); /* Si no hay extenci¢n se le coloca .BLK */

	puts ("Creando fichero...");
	if ((archivoSPE = fopen (archivo[totalsprites], "wb")) == NULL) { /* archivo[totalsprites] contiene el nombre del archivo SPE */
		printf ("Error al intentar crear el archivo: %s\n", archivo[totalsprites]);
		return 1;
	}
	if ((archivoSPR = fopen (archivo[0], "rb")) == NULL) {
		printf ("Error al intentar abrir el archivo: %s\n", archivo[0]);
		return 1;
	}

	printf ("Fichero de salida: %s", archivo[totalsprites]);
	puts ("Copiando los sprites...");

	/* Copiar todos los dem s sprites descartando la cabecera SPR */
	for (cont = 0; cont < (totalsprites - 1); cont++) { /* archivo[totalsprites - 1] contiene el nombre del £ltimo archivo de la lista de archivos SPR */
    	  printf ("Fichero: %s", archivo[cont]);
		while (!feof (archivoSPR)) {
			putc (getc (archivoSPR), archivoSPE);
			bytes++;
		}
		fclose (archivoSPR); /* Cerrar el archivo SPR */
		if ((archivoSPR = fopen (archivo[cont], "rb")) == NULL) { /* Abrir el siguiente archivo SPR de la lista */
			printf ("Error al intentar abrir el archivo: %s\n", archivo[cont]);
			return 1;
		}
	}
	fclose (archivoSPE); /* Cerrar el archivo SPE */
	printf ("\n%ld Bytes fueron enlazados.", bytes);
	puts ("Los archivos han sido enlazados correctamente.");
	return 0;
}