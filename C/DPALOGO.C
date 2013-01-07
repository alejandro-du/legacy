#include <stdio.h>
#include <dos.h>
#include <graphics.h>

void mostrar_error (int codigo_error);
void abrir (char *nombre);

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

main (void)
{
	inicializar_modo ();
	setactivepage (1);
	clearviewport ();
	setvisualpage (1);
	setactivepage (0);
	abrir ("dpalogo.pcx");
	setvisualpage (0);
	setactivepage (1);
	abrir ("dpalogo2.pcx");
	setvisualpage (1);
	getch ();
	for (;;) {
		setvisualpage (0);
		delay (1000);
		setvisualpage (1);
		delay (1000);
	}

	return 0;
}

void abrir (char *nombre)
{
	FILE *archivo;
	register int x = 0, y = 0, color, buffer, cont, arch = 0;
	register long int tam, cb = 128, k = 0;
	char paleta[768];

	if ((archivo = fopen (nombre, "rb")) == NULL) {
		printf ("No se puede abrir el archivo: dpalogo.pcx");
		return 1;
	}

	fseek (archivo, 0, SEEK_END);
	tam = ftell (archivo);
	rewind (archivo);

	fread (paleta, 128, 1, archivo);

	while (cb < (tam - 768)) {
		buffer = getc (archivo);
		cb++;
		if (buffer > 191) {
			color = getc (archivo);
			cb++;
			buffer -= 192;
			for (cont = 1; cont <= buffer; cont++) {
				putpixel (x, y, color);
				x++;
				if (x > 639) {
					y++;
					x = 0;
				}
			}
		}
		else {
			putpixel (x, y, buffer);
			x++;
			if (x > 639) {
				y++;
				x = 0;
			}
		}
	}
	fread (paleta, 768, 1, archivo);
	for (color = 0; color < 256; color++) {
		outp (0x3c8, color);
		outp (0x3c9, paleta[k] >> 2);
		outp (0x3c9, paleta[k + 1] >> 2);
		outp (0x3c9, paleta[k + 2] >> 2);
		k += 3;
	}
}