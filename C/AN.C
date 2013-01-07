#include <stdio.h>
#include <dos.h>
#include <graphics.h>

void mostrar_error (int codigo_error);

int huge DetectarVGA256() /* Iniciar modo Super VGA a 256 colores */
{
	int Vid = 0;

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
	char *sprite, *fondo, paleta[768];
	long int bytes = 0, cont = 0, xs = 0, ys = 0;
	register int color, numar, x =0;

	if (argc < 3) {
		puts ("Debe teclear el nombre del archivo SPR y la paleta PAL.");
		return 1;
	}

	if ((archivo = fopen (argv[2], "rb")) == NULL) {
		printf ("No se puede abrir la paleta: ", argv[2]);
		return 1;
	}
	fread (paleta, 768, 1, archivo);
	cont = 0;
	inicializar_modo ();
	for (color = 0; color < 256; color++) {
		outp (0x3c8, color);
		outp (0x3c9, paleta[cont]);
		outp (0x3c9, paleta[cont + 1]);
		outp (0x3c9, paleta[cont + 2]);
		cont += 3;
	}
	fclose (archivo);
	if ((archivo = fopen (argv[1], "rb")) == NULL) {
		printf ("No se puede abrir el sprite: %s", argv[numar]);
		return 1;
	}
	fseek (archivo, 0, SEEK_END);
	bytes = ftell (archivo);
	rewind (archivo);

	fread (&xs, 2, 1, archivo);
	fread (&ys, 2, 1, archivo);

	if ((sprite = (char *) malloc (bytes)) == NULL)
	{
		puts ("No hay memoria sufiente para abrir el sprite.");
		return 1;
	}
	if ((fondo = (char *) malloc (bytes)) == NULL)
	{
		puts ("No hay memoria sufiente para abrir el sprite.");
		return 1;
	}
	rewind (archivo);
	for (cont = 0; !feof (archivo); cont++) sprite[cont] = getc (archivo);
	fclose (archivo);

	getimage (x, 10,x+xs,10+ys, fondo);
	putimage (x, 10, sprite, COPY_PUT);

	while (!kbhit()) {

	putimage (x, 10, fondo, COPY_PUT);
	x++;
	getimage (x, 10,x+xs,10+ys, fondo);
	putimage (x, 10, sprite, COPY_PUT);

	delay (100);
	}
	return 0;
}