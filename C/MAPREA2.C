#include <stdio.h>
#include <dos.h>
#include <graphics.h>
#include <process.h>
#define XRES 640
#define YRES 400
#define XPANT XRES / 32
#define YPANT YRES / 32

typedef unsigned char BYTE;

void pintarBLK32x32 (int x, int y, BYTE *blk);
void mostrar_error (int codigo_error);
void leerBLK (FILE *archivo, BYTE num, BYTE *bloque);

int huge DetectarVGA256() /* Iniciar modo Super VGA a 256 colores */
{
	int Vid = 1;
	return Vid;
}

void inicializar_modo (void) /* Inicializar el modo gr fico */
{
	int controlador = DETECT, modo, codigo_error;

	installuserdriver ("Svga256", DetectarVGA256);

	initgraph (&controlador, &modo, ""); /* Inicializar modo grafico */
	mostrar_error (codigo_error = graphresult ()); /* Verificar que no ha sucedido ning£n error en la inicializaci¢n grafica */
}

/* Si ocurri¢ algun error lo detecta y muestra el mensaje correspondiente */
void mostrar_error (int codigo_error)
{
	if (codigo_error != grOk)  { /* Ha ocurrido un error de inicializaci¢n */
		clrscr ();
		switch (codigo_error) {
			case -1:
				puts ("Modo grafico no instalado.");
				break;
			case -2:
				puts ("Hardware de graficos no detectado.");
				break;
			case -3:
				puts ("No se encuentra el archivo del controlador de graficos.");
				break;
			case -4:
				puts ("Archivo controlador de dispositivo incorrecto.");
				break;
			case -5:
				puts ("Memoria insuficiente para cargar el controlador grafico.");
				break;
			case -6:
				puts ("-6");
				break;
			case -7:
				puts ("-7");
				break;
			case -8:
				puts ("Archivo de fuentes graficas no encontrado.");
				break;
			case -9:
				puts ("Memoria insuficiente para cargar la fuente grafica.");
				break;
			case -10:
				puts ("Modo grafico incorrecto al seleccionar el controlador.");
				break;
			case -11:
				puts ("Error de graficos.");
				break;
			case -12:
				puts ("Error de graficos de I/O (Entrada/Salida).");
				break;
			case -13:
				puts ("Archivo de fuente grafica incorrecto.");
				break;
			case -14:
				puts ("N£mero de fuente grafica incorrecto.");
				break;
			case -15:
				puts ("N£mero de dispositivo incorrecto.");
				break;
			case -18:
				puts ("N£mero de versi¢n incorrecto.");
				break;
			default:
				puts ("Ha ocurrido un error en la inicializaci¢n del modo grafico.");
		}
		exit (1); /* Salir del programa (error) */
	}
}

main (int argc, char *argv[])
{
	FILE *archivo;
	BYTE paleta[768], mapa[XPANT * YPANT];
	BYTE bloque[1024];
	int x, y, fila = 1, columna = 41, color, xmap, ymap,cod;
	unsigned long int cont = 0;
	BYTE num, op;

	if (argc < 4) {
		puts ("Debe teclear el nombre del archivo PAL, BLK y MAP.");
		return 1;
	}

	if ((archivo = fopen (argv[1], "rb")) == NULL) {
		printf ("No se puede abrir la paleta: ", argv[argc - 1]);
		return 1;
	}
	fread (paleta, 768, 1, archivo);
	fclose (archivo);
	inicializar_modo ();

	for (color = 0; color < 256; color++) {
		outp (0x3c8, color);
		outp (0x3c9, paleta[cont]);
		outp (0x3c9, paleta[cont + 1]);
		outp (0x3c9, paleta[cont + 2]);
		cont += 3;
	}

	for (;;) {

	if ((archivo = fopen (argv[3], "rb")) == NULL) {
		printf ("No se puede abrir el archivo MAP: ", argv[3]);
		return 1;
	}
	if (fread (&xmap, 1, 2, archivo) != 2) {printf ("ERROR MAP 1");exit (1);}
	if (fread (&ymap, 1, 2, archivo) != 2) {printf ("ERROR MAP 2");exit (1);}

	for (x = 0; x < (columna - 1) * ymap; x++) getc (archivo);
	for (y = 0; y < (fila - 1); y++) getc (archivo);
	num = 0;
	for (x = 0; x < XPANT; x++) {
		for (y = 0; y < YPANT; y++) {
			if ((mapa[num] = getc (archivo)) == EOF) {
				printf ("ERROR MAP 3");
				exit (1);
			}
		num++;
		}

		for (y = 0; y < (ymap - YPANT); y++) {
			if (getc (archivo) == EOF) {
				printf ("ERROR MAP 4");
				printf ("\n%ld  %d",ftell(archivo), y);
        break;
				exit (1);
			}
		}
	}

	fclose (archivo);

	if ((archivo = fopen (argv[2], "rb")) == NULL) {
		printf ("No se puede abrir el archivo BLK: ", argv[2]);
		return 1;
	}

	num = 0;
	for (x = 0; x < XPANT; x++) {
		for (y = 0; y < YPANT; y++) {
			leerBLK (archivo, mapa[num], bloque);
			pintarBLK32x32 (x * 32, y * 32, bloque);
			num++;
		}
	}
	fclose (archivo);
	op = getch ();
	switch (op) {
		case 'o':
			columna -= XPANT;
		break;
		case 'p':
			columna += XPANT;
		break;
		case 'a':
			fila += YPANT;
		break;
		case 'q':
			fila -= YPANT;
		break;
	}
	if (columna < 1 || fila < 1 || columna - 1 > (xmap - XPANT) || fila - 1 > (ymap - YPANT)) {
		printf ("%d, %d", fila, columna);
		return 0;
	}
	} /* for (;;)*/
}

void pintarBLK32x32 (int x, int y, BYTE *blk)
{
	register int num = 0, xp, yp;
	yp = y;
	for (; yp < y + 32; yp++) {
		xp = x;
		for (; xp < x + 32; xp++) {
			putpixel (xp, yp, *blk);
			blk++;
		}
	}
}

void leerBLK (FILE *archivo, BYTE num, BYTE *bloque)
{
	register unsigned long int cont;

	rewind (archivo);
	for (cont = 0; cont < (unsigned long) num * 1024; cont++) {
		if (getc (archivo) == EOF) {
			printf ("ERROR BLK 1");
			exit (1);
		}
	}
	for (cont = 0; cont < 1024; cont++) {
		if ((bloque[cont] = getc (archivo)) == EOF) {
			printf ("ERROR BLK 2");
			exit (1);
		}
	}
}