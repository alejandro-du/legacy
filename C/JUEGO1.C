#include <graphics.h>
#include <stdio.h>
#include "svga256.h"

void inicializar_modo (void);
void mostrar_error (int codigo_error);

int huge DetectarVGA256() /* Iniciar modo Super VGA a 256 colores */
{
	int Vid = 0;
	return Vid;
}

void main (void)
{
	inicializar_modo ();
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