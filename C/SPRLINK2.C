/* ASISTENTE PARA ENLAZAR FICHEROS SPR VERSION 1.0
	 1998 DPA Software. Todos los derechos reservados */

#include <stdio.h>
#include <string.h>

main (int argc, char *argv[])
{
	int totalsprites, cont = 0, x, y, num;
	char archivo[401][114]; /* Array de cadenas para los nombres de los archivos */
	long int bytes;
	FILE *archivoSPR, *archivoSPE;

	puts ("SPRITE LINK versi¢n 1.0 DPA Software 1998. Todos los derechos reservados.");
	puts ("Asistente para enlazar archivos SPR.");
	if (argc > 1) { /* Si fueron introducidos argumentos en la linea de ordenes */
		if (!strcmp (argv[1],"/?")) { /* Mostrar ayuda */
			puts ("\nSPRITE LINK versi¢n 1.0");
			puts ("Es un asistente que permine unir o enlazar los archivos SPR que forman parte");
			puts ("de un sprite o animaci¢n, para formar un fichero con formato SPE");
			puts ("El programa pide que se introduscan los nombres de los archivos SPR que se");
			puts ("quieren enlazar. Introdusca los nombres uno por uno.");
			puts ("Luego teclee el nombre del archivo de salida SPE.");
			puts ("El formato SPE tiene una cabecera de 9 Bytes:");
			puts ("    Bytes 4 - 5  N£mero total de imagenes del sprite.");
			puts ("    Bytes 6 - 7  Ancho (X) del sprite.");
			puts ("    Bytes 8 - 9  Alto (Y) de cada imagen.");
			puts ("Los siguientes bytes componen el sprite. Las imagenes estan colocadas de forma");
			puts ("lineal y se podria simular un array de sprites.");
		}
		return 0;
	}
	printf ("\nN£mero total de sprites SPR a enlazar: ");
	scanf ("%d", &totalsprites); /* Guardar n£mero total de sprites en totalsprites */

	printf ("Introdusca los nombres de los %d archivos a enlazar:\n", totalsprites);
	while (cont < totalsprites) { /* Bucle para la introducci¢n de los nombres de ficheros SPR */
		printf ("Fichero #%d: ", cont + 1);
		scanf ("%s", archivo[cont]);

		if (!strcmp (archivo[cont], "-1")) { /* Verificar si se ha introducido -1 para salir del programa */
			puts ("Programa abortado.");
			return 0; /* Salida normal del programa */
		}

		if (!strchr (archivo[cont], '.')) strcat (archivo[cont], ".SPR"); /* Si no hay extenci¢n se le coloca .SPR */

		if ((archivoSPR = fopen (archivo[cont], "rb")) == NULL) {
			printf ("\aError al intentar abrir el archivo: %s\n", archivo[cont]);
			cont--;
		}
		fclose (archivoSPR);
		cont++;
	}

	printf ("Introdusca el nombre del fichero de salida SPE: ");
	scanf ("%s", archivo[totalsprites]); /* Nombre del archivo SPE */
	if (!strchr (archivo[totalsprites], '.')) strcat (archivo[totalsprites], ".SPE"); /* Si no hay extenci¢n se le coloca .SPE */

	puts ("Creando fichero...");
	if ((archivoSPE = fopen (archivo[totalsprites], "wb")) == NULL) { /* archivo[totalsprites] contiene el nombre del archivo SPE */
		printf ("Error al intentar crear el archivo: %s\n", archivo[totalsprites]);
		return 1;
	}
	/* Introducir la cabecera SPE (9 bytes) */
	puts ("\nCreando cabecera SPE");
	fprintf (archivoSPE, "DPA"); /* Introducir los primeros 3 bytes de la cabecera SPE ("DPA") */

	fwrite (&totalsprites, 2, 1, archivoSPE); /* Escribir los bytes 4 - 5 de la cabecera SPE (n£mero total de sprites) */
	bytes = 5; /* Actualizar */

	puts ("Copiando los sprites...");
	printf ("Fichero SPE: %s", archivo[totalsprites]);

	/* Copiar todos los dem s sprites descartando la cabecera SPR */
	for (cont = 0; cont < totalsprites; cont++) { /* archivo[totalsprites - 1] contiene el nombre del £ltimo archivo de la lista de archivos SPR */
		if ((archivoSPR = fopen (archivo[cont], "rb")) == NULL) { /* Abrir el siguiente archivo SPR de la lista */
			printf ("Error al intentar abrir el archivo: %s\n", archivo[cont]);
			return 1;
		}
		fread(&x, 2, 1, archivoSPR);
		fread(&y, 2, 1, archivoSPR);
		x++; y++;
		fwrite (&x, 2, 1, archivoSPE);
		fwrite (&y, 2, 1, archivoSPE);
		for(num = 0; num < x * y; num++) {
			putc (getc (archivoSPR), archivoSPE);
			bytes++;
		}

		fclose (archivoSPR); /* Cerrar el archivo SPR */
	}
	fclose (archivoSPE); /* Cerrar el archivo SPE */
	printf ("\n%ld Bytes fueron enlazados.", bytes);
	puts ("\nLos archivos han sido enlazados correctamente.");
	return 0;
}