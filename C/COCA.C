/* Draw Pixel 2.0  Copyright (c) Jairo Alejandro Duarte Avenda¤o Septiembre 1996*/

#include <graphics.h>
#include "svga256.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>

void inicializar_modo (void); /* Inicializar el modo gr fico */
void mostrar_error (int codigo_error); /* Mostrar errores de inicializaci¢n */
void draw_pixel_principal (void); /* Rutina principal */
void dibujar_cursor (void); /* Dibuja el cursor del color "cursor.color" */
void borrar_cursor (void); /* Borra el cursor de la pantalla */
void inicializar_variables (void); /* Inicializa todas las variables con su correspondiente valor */
void movimiento_cursor (int funcion, int funcion2, int escape); /* Mueve el cursor dibujando o no segun los argumentos */
void dibujar_derecha (int funcion); /* Dibujar la linea hacia la derecha */
void dibujar_izquierda (int funcion); /* Dibujar la linea hacia la izquierda */
void dibujar_arriba (int funcion); /* Dibujar hacia arriba */
void dibujar_abajo (int funcion); /* Dibujar hacia abajo */
void dibujar_arribaderecha (int funcion); /* Dibujar hacia la esquina superior derecha */
void dibujar_arribaizquierda (int funcion); /* Dibujar hacia la esquina superior izquierda */
void dibujar_abajoderecha (int funcion); /* Dibujar hacia la esquina inferior derecha */
void dibujar_abajoizquierda (int funcion); /* Dibujar hacia la esquina inferior izquierda */
void dibujar_pixel (void); /* Pinta un pixel */
void borrar_pixel (void); /* Borra un pixel */
void mostrar_menu_principal (void); /* Llama al menu principal */
void mostrar_cordenadas (void); /* Muestra las cordenadas del cursor */
void seleccionar_opcion_dibujo (char tecla); /* Selecciona una opcion del men£ dibujo */
void seleccionar_opcion_imagen (char tecla); /* Selecciona una opcion del menu Imagen */void dibujar_linea (void); /* Dibuja un linea dadas las cordenadas por el usuario */
void dibujar_rectangulo (void); /* Dibuja un rectangulo segun las cordenadas dadas por el usuario */
void dibujar_circulo (void); /* Dibuja un circulo dadas las cordenadas por el usuario */
void dibujar_colorear (void); /* Rellena una figura cerrada */
void dibujar_color (void); /* Selecciona el color de dibujo actual */
void borrar_pantalla (void); /* Borra el area de trabajo */
void dibujar_poligonoirr (void);
void dibujar_elipse (void);
void dibujar_texto (void);
void dibujar_paralelas (void);

int color_tmp; /* Esta variable guarda el color del pixel que esta atras del cursor */

int huge DetectarVGA256() /* Iniciar modo Super VGA a 256 colores */
{
	int Vid = 1;

	return Vid;
}

struct { /* Estructura que define los atributos del cursor y la pantalla */
	unsigned int x; /* Cordenada X del cursor */
	unsigned int y; /* Cordenada Y del cursor */
	unsigned int maximo_x; /* Limite de la pantalla */
	unsigned int maximo_y; /* Limite de la pantalla */
	unsigned int color; /* Color actual del cursor en la pantalla */
	unsigned int colorf; /* Color por defecto del cursor (fijo) */
	unsigned short int tamano; /* Tama¤o del cursor */
} cursor;

struct { /* Definir las variables del contexto del dispositivo */
	unsigned int color; /* Color actual */
	unsigned int tipo_linea; /* Tipo actual de linea */
	unsigned int tipo_relleno; /* Tipo actual de relleno */
	unsigned int color_fondo; /* Color del fondo "transparente" */
	struct {
		int nombre;
		int direccion;
		int tamano;
		int interlineado;
	} fuente;
} contexto;

void main (void)
{
	inicializar_modo (); /* Inicializar el modo de graficos */
	inicializar_variables (); /* Iniciar los valores por defecto de las variables */
	draw_pixel_principal (); /* Comenzar la aplicaci¢n */
	closegraph ();
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

/* Inicializa las variables del cursor */
void inicializar_variables (void)
{
	cursor.maximo_x = getmaxx();
	cursor.maximo_y = getmaxy();
	cursor.x = (cursor.maximo_x / 2) - 2; /* Poner el cursor en la mitad de la pantalla */
	cursor.y = (cursor.maximo_y / 2) - 2;
	cursor.colorf = 4;
	cursor.tamano = 0;
	contexto.color = 15;
	contexto.tipo_linea = 3;
	contexto.tipo_relleno = 1;
	contexto.color_fondo = 0;
	contexto.fuente.nombre = 1;
	contexto.fuente.direccion = 0;
	contexto.fuente.tamano = 4;
	contexto.fuente.interlineado = 11;

	setcolor (contexto.color);
}

/* Dibuja el cursor en la nueva posici¢n y guarda el color del pixel que esta detras del cursor en la variable global color_tmp */
void dibujar_cursor (void)
{
	cursor.color = cursor.colorf;
	color_tmp = getpixel (cursor.x, cursor.y);
	if (color_tmp == cursor.colorf) cursor.color = 0;
	setfillstyle (1, cursor.color);
	bar (cursor.x, cursor.y, cursor.x + cursor.tamano, cursor.y + cursor.tamano);
	setfillstyle (contexto.tipo_relleno, contexto.color); /* Valores del contexto (restaurar) */
}

/* Borra el cursor de la pantalla: pixel del color "color_tmp" */
void borrar_cursor (void)
{
	setfillstyle (1, color_tmp);
	bar (cursor.x, cursor.y,  cursor.x + cursor.tamano, cursor.y + cursor.tamano);
	setfillstyle (contexto.tipo_relleno, contexto.color); /* Valores del contexto (restaurar) */
}

/* Rutina principal del programa */
void draw_pixel_principal (void)
{
	cleardevice (); /* Borrar pantalla */
	dibujar_cursor (); /* Dibujar el cursor por primera vez */
	movimiento_cursor (1, 1, 24); /* Empezar con el movimiento del cursor */
}

void dibujar_derecha (int funcion) /* Mueve el cursor a la derecha */
{
	borrar_cursor ();
	cursor.x++;
	if (funcion) putpixel (cursor.x - 1, cursor.y, contexto.color);
	dibujar_cursor ();
}

void dibujar_izquierda (int funcion) /* Mueve el cursor a la izquierda */
{
	borrar_cursor ();
	cursor.x--;
	if (funcion) putpixel (cursor.x + 1, cursor.y, contexto.color);
	dibujar_cursor ();
}

void dibujar_arriba (int funcion) /* Mueve el cursor arriba */
{
	borrar_cursor ();
	cursor.y--;
	if (funcion) putpixel (cursor.x, cursor.y + 1, contexto.color);
	dibujar_cursor ();
}

void dibujar_abajo (int funcion) /* Mueve el cursor abajo */
{
	borrar_cursor ();
	cursor.y++;
	if (funcion) putpixel (cursor.x, cursor.y - 1, contexto.color);
	dibujar_cursor ();
}

void dibujar_arribaderecha (int funcion)
{
	borrar_cursor ();
	cursor.y--;
	cursor.x++;
	if (funcion) putpixel (cursor.x - 1, cursor.y + 1, contexto.color);
	dibujar_cursor ();
}

void dibujar_arribaizquierda (int funcion)
{
	borrar_cursor ();
	cursor.y--;
	cursor.x--;
	if (funcion) putpixel (cursor.x + 1, cursor.y + 1, contexto.color);
	dibujar_cursor ();
}

void dibujar_abajoderecha (int funcion)
{
	borrar_cursor ();
	cursor.y++;
	cursor.x++;
	if (funcion) putpixel (cursor.x - 1, cursor.y - 1, contexto.color);
	dibujar_cursor ();
}

void dibujar_abajoizquierda (int funcion)
{
	borrar_cursor ();
	cursor.y++;
	cursor.x--;
	if (funcion) putpixel (cursor.x + 1, cursor.y - 1, contexto.color);
	dibujar_cursor ();
}

void dibujar_pixel (void) /* Dibuja un pantalla */
{
	borrar_cursor ();
	putpixel (cursor.x, cursor.y, contexto.color);
	cursor.x++;
	dibujar_cursor ();
}

void borrar_pixel (void) /* Dibuja un pixel del color del fondo */
{
	borrar_cursor ();
	putpixel (cursor.x, cursor.y, contexto.color_fondo);
	cursor.x++;
	dibujar_cursor ();
}

void movimiento_cursor (int funcion, int funcion2, int escape) /* Rutina para mover el cursor por la pantalla */
{
	char teclamc; /* Tecla pulsada */

	do {
		teclamc = getch ();
		switch (teclamc) {
			case 77:
				dibujar_derecha (0);
			break;
			case 75:
				dibujar_izquierda (0);
			break;
			case 72:
				dibujar_arriba (0);
			break;
			case 80:
				dibujar_abajo (0);
			break;
			case 73:
				dibujar_arribaderecha (0);
			break;
			case 71:
				dibujar_arribaizquierda (0);
			break;
			case 81:
				dibujar_abajoderecha (0);
			break;
			case 79:
				dibujar_abajoizquierda (0);
			break;

			case 54:
				dibujar_derecha (funcion);
			break;
			case 52:
				dibujar_izquierda (funcion);
			break;
			case 56:
				dibujar_arriba (funcion);
			break;
			case 50:
				dibujar_abajo (funcion);
			break;
			case 57:
				dibujar_arribaderecha (funcion);
			break;
			case 55:
				dibujar_arribaizquierda (funcion);
			break;
			case 51:
				dibujar_abajoderecha (funcion);
			break;
			case 49:
				dibujar_abajoizquierda (funcion);
			break;
			case 32:
				if (funcion2) dibujar_pixel ();
			break;
			case 13:
				if (funcion2) borrar_pixel ();
			break;
			case 27:
			case 68:
				if (funcion2) mostrar_menu_principal ();
			break;
			case 'l':
			case 'L':
				if (funcion2) dibujar_linea ();
			break;
			case 'r':
			case 'R':
				if (funcion2) dibujar_rectangulo ();
			break;
			case 'C':
			case 'c':
				if (funcion2) dibujar_circulo ();
			break;
			case 15: /* control + O */
				if (funcion2) dibujar_colorear ();
			break;
			case 3:  /* control + C */
				if (funcion2) dibujar_color ();
			break;
			case 16: /* control + P */
				if (funcion2) dibujar_poligonoirr ();
			break;
			case 'T':
			case 't':
				if (funcion2) dibujar_texto ();
			break;
			case 12: /* control + L */
				if (funcion2) dibujar_paralelas ();
			break;
			case 5: /* control + E */
				if (funcion2) dibujar_elipse ();
			break;

			case -109: /* control + supr */
				if (funcion2) borrar_pantalla ();
			break;
		}
	} while (teclamc != escape);
}

void mostrar_menu_principal (void) /* Llama al menu prinicipal */
{
	char tecla = 27;
	void *buffer_menu;
	void *buffer;
	int temp = 1;

	if (!(buffer_menu = malloc (imagesize (0, 0, cursor.maximo_x, 9)))) return 0; /* Si no hay memoria no se ejecuta el menu */

	settextstyle (SMALL_FONT, HORIZ_DIR, 6);
	setfillstyle (1, 1);
	setcolor (15);
	getimage (0, 0, cursor.maximo_x, 9, buffer_menu);
	bar (0, 0, cursor.maximo_x, 9);

	do {
		setcolor (15);
		outtextxy (0, 0, "1 Archivo      2 Dibujo      3 Imagen      4 Opciones");
		setcolor (11);
		tecla = getch ();
		switch (tecla) {
			case '1':
			case 'A':
			case 'a':
				outtextxy (0, 0, "1 Archivo");

				if (!(buffer = malloc (imagesize (0, 20, 160, 130)))) return 0; /* Si no hay memoria no se ejecuta el menu */
				getimage (0, 20, 160, 130, buffer);

				rectangle (0, 20, 160, 130);
				bar (1, 21, 159, 129);
				setcolor (7);
				outtextxy (3, 23, "A Acerca de...");
				outtextxy (3, 37, "B Nuevo");
				outtextxy (3, 51, "C Abrir...");
				outtextxy (3, 65, "D Guardar...");
				outtextxy (3, 79, "E Guardar como...");
				outtextxy (3, 93, "F DOS shell");
				outtextxy (3, 107, "G Macro...");
				outtextxy (3, 121, "H Salir");

				if ((tecla = getch ()) != 27) {
					putimage (0, 20, buffer, COPY_PUT);
					free (buffer);
					putimage (0, 0, buffer_menu, COPY_PUT);
					free (buffer_menu);

					/* Aqui va la funcion "Selecionar_opcion_archivo" */

					tecla = 27;
					temp = 0;
					break;
				}
				putimage (0, 20, buffer, COPY_PUT);
				free (buffer);
				tecla = NULL;
			break;

			case '2':
			case 'D':
			case 'd':
				outtextxy (120, 0, "2 Dibujo");

				if (!(buffer = malloc (imagesize (118, 20, 311, 200)))) return 0; /* Si no hay memoria no se ejecuta el menu */
				getimage (118, 20, 311, 200, buffer);

				rectangle (118, 20, 311, 200);
				bar (119, 21, 310, 199);

				setcolor (7);
				outtextxy (121, 23, "A Linea");
				outtextxy (121, 37, "B Rectangulo");
				outtextxy (121, 51, "C Circulo");
				outtextxy (121, 65, "D Colorear");
				outtextxy (121, 79, "E Color");
				outtextxy (121, 93, "F Poligono irregular");
				outtextxy (121, 107, "G Elipse");
				outtextxy (121, 121, "H Texto");
				outtextxy (121, 135, "I Paralelas");
				outtextxy (121, 149, "J Borrador");
				outtextxy (121, 163, "K Cubo");

				if ((tecla = getch ()) != 27) {
					putimage (118, 20, buffer, COPY_PUT);
					free (buffer);
					putimage (0, 0, buffer_menu, COPY_PUT);
					free (buffer_menu);

					seleccionar_opcion_dibujo (tecla);

					tecla = 27;
					temp = 0;
					break;
				}
				putimage (118, 20, buffer, COPY_PUT);
				free (buffer);
				tecla = NULL;
			break;

			case '3':
			case 'I':
			case 'i':
				outtextxy (232, 0, "3 Imagen");

				if (!(buffer = malloc (imagesize (236, 20, 393, 200)))) return 0; /* Si no hay memoria no se ejecuta el menu */
				getimage (236, 20, 393, 200, buffer);

				rectangle (236, 20, 393, 200);
				bar (237, 21, 392, 199);
				setcolor (7);

				outtextxy (240, 23, "A Cortar");
				outtextxy (240, 37, "B Copiar");
				outtextxy (240, 51, "C Pegar");
				outtextxy (240, 65, "D Mover");
				outtextxy (240, 79, "E Borrar");
				outtextxy (240, 93, "F Borrar pantalla");
				outtextxy (240, 107, "G Insertar...");
				outtextxy (240, 121, "H Color de fondo...");
				outtextxy (240, 135, "I Textura...");

				if ((tecla = getch ()) != 27) {
					putimage (236, 20, buffer, COPY_PUT);
					free (buffer);
					putimage (0, 0, buffer_menu, COPY_PUT);
					free (buffer_menu);

					seleccionar_opcion_imagen (tecla);

					tecla = 27;
					temp = 0;
					break;
				}
				putimage (236, 20, buffer, COPY_PUT);
				free (buffer);
				tecla = NULL;
			break;

			case '4':
			case 'O':
			case 'o':
				outtextxy (344, 0, "4 Opciones");

				if (!(buffer = malloc (imagesize (354, 20, 550, 200)))) return 0; /* Si no hay memoria no se ejecuta el menu */
				getimage (354, 20, 550, 200, buffer);

				rectangle (354, 20, 550, 200);
				bar (355, 21, 549, 199);
				setcolor (7);

				outtextxy (358, 23, "A Autocoloreado");
				outtextxy (358, 37, "B Fuentes...");
				outtextxy (358, 51, "C Estilo de l¡nea...");
				outtextxy (358, 65, "D Grosor de linea...");
				outtextxy (358, 79, "E Tama¤o del borrador");
				outtextxy (358, 93, "F Estilo de coloreado...");
				outtextxy (358, 107, "G Color del cursor...");
				outtextxy (358, 121, "H Formato de archivo...");

				if ((tecla = getch ()) != 27) {
					putimage (354, 20, buffer, COPY_PUT);
					free (buffer);
					putimage (0, 0, buffer_menu, COPY_PUT);
					free (buffer_menu);

					/* Aqui va la funcion "Selecionar_opcion_opciones" */

					tecla = 27;
					temp = 0;
					break;
				}
				putimage (354, 20, buffer, COPY_PUT);
				free (buffer);
				tecla = NULL;

			break;
		}
	} while (tecla != 27);
	if (temp)	{
		putimage (0, 0, buffer_menu, COPY_PUT);
		free (buffer_menu);
		setcolor (contexto.color);
	}
	temp = 1;
}

void seleccionar_opcion_dibujo (char tecla) /* Selecciona una opcion del menu Dibujo */
{
	switch (tecla) {
		case 'A':
		case 'a':
		case '1': /* Se puede introducir un n£mero como opci¢n */
			dibujar_linea ();
		break;

		case 'B':
		case 'b':
		case '2':
			dibujar_rectangulo ();
		break;

		case 'C':
		case 'c':
		case '3':
			dibujar_circulo ();
		break;

		case 'D':
		case 'd':
		case '4':
			dibujar_colorear ();
		break;

		case 'E':
		case 'e':
		case '5':
			dibujar_color ();
		break;

		case 'F':
		case 'f':
		case '6':
			dibujar_poligonoirr ();
		break;

		case 'G':
		case 'g':
		case '7':
			dibujar_elipse ();
		break;

		case 'H':
		case 'h':
		case '8':
			dibujar_texto ();
		break;

		case 'I':
		case 'i':
		case '9':
			dibujar_paralelas ();
		break;
	}
}


void seleccionar_opcion_imagen (char tecla) /* Selecciona una opcion del menu Imagen */
{
	switch (tecla) {
		case 'F':
		case 'f':
		case '6':
			borrar_pantalla ();
		break;
	}
}

/*void mostrar_cordenadas (void)
{
	char *cordenadas[3];

	setcolor (0);
	settextstyle (SMALL_FONT, HORIZ_DIR, 5);
	setfillstyle (1, 7);
	bar (0, 0, cursor.maximo_x, 10);

	gcvt (cursor.x, 3, cordenadas);
	outtextxy (0, 3, cordenadas);
} */

void dibujar_linea (void) /* Dibuja una linea dados dos puntos */
{
	int x1, y1;

	movimiento_cursor (0, 0, 13);
	borrar_cursor ();
	x1 = cursor.x;
	y1 = cursor.y;
	putpixel (cursor.x, cursor.y, contexto.color);
	dibujar_cursor ();
	movimiento_cursor (0, 0, 13);
	setcolor (contexto.color);
	line (cursor.x, cursor.y, x1, y1);
	dibujar_cursor ();
}

void dibujar_rectangulo (void) /* Dibujar un rectangulo dados dos puntos */
{
	int x1, y1;

	movimiento_cursor (0, 0, 13);
	borrar_cursor ();
	x1 = cursor.x;
	y1 = cursor.y;
	putpixel (cursor.x, cursor.y, contexto.color);
	dibujar_cursor ();
	movimiento_cursor (0, 0, 13);
	setcolor (contexto.color);
	rectangle (x1, y1, cursor.x, cursor.y);
	dibujar_cursor ();
}

void dibujar_circulo (void) /* Dibuja un circulo dado el circuncentro y el radio */
{
	int x1, y1, radio, col;

	movimiento_cursor (0, 0, 13);
	borrar_cursor ();
	x1 = cursor.x;
	y1 = cursor.y;
	col = getpixel (x1, y1);
	putpixel (x1, y1, contexto.color);
	dibujar_cursor ();
	movimiento_cursor (0, 0, 13);
	borrar_cursor ();
	putpixel (x1, y1, col);

	if (x1 < cursor.x) for (radio = 0; x1 + radio < cursor.x; radio++);
	if (x1 > cursor.x) for (radio = 0; x1 - radio > cursor.x; radio++);

	setcolor (contexto.color);
	circle (x1, y1, radio);
	dibujar_cursor ();
}

void dibujar_colorear (void) /* Rellena un area de dibujo */
{
	int col;

	movimiento_cursor (0, 0, 13);
	borrar_cursor ();
	col = color_tmp;
	dibujar_cursor ();
	movimiento_cursor (0, 0, 13);
	setfillstyle (contexto.tipo_relleno, contexto.color);
	borrar_cursor ();
	floodfill (cursor.x, cursor.y, col);
	dibujar_cursor ();
}

void dibujar_color (void) /* Seleciona el color actual de dibujo */
{
	void *buffer;
	char cade[4];
	int num;

	if (!(buffer = malloc (imagesize (2, 2, 174, 11)))) return 0; /* Si no hay memoria no se ejecuta */
	getimage (2, 2, 174, 11, buffer);

	setfillstyle (1, 15);
	setcolor (8);
	settextstyle (SMALL_FONT, HORIZ_DIR, 5);
	bar (2, 2, 174, 11);
	outtextxy (3, 3, "N£mero del color?");
	setcolor (11);
	textcolor (1);
	gotoxy (19, 1);

	for (num = 0; num < 4; num++) { /* Introducci¢n de los tres numeros del color */
		cade[num] = getch ();

		if (cade[num] == 13) break; /* Si se presiona ENTER se sale del bucle for */
		if (cade[num] == 27) {
			putimage (2, 2, buffer, COPY_PUT);
			free (buffer);
			return 0;
		}
		printf ("%c", cade[num]);
	}
	cade[3] = NULL; /* El £ltimo caracter es anulado */

	putimage (2, 2, buffer, COPY_PUT);
	free (buffer);

	contexto.color = atoi (cade); /* El valor introducido es asignado al actual (contexto) */
}

void borrar_pantalla (void) /* Borra el area de tabajo en su totalidad */
{
	borrar_cursor ();
	cleardevice (); /* Borrar pantalla */
	dibujar_cursor ();
}

void dibujar_poligonoirr (void) /* Dibujar un poligono irregular */
{
	int x1, y1;

	movimiento_cursor (0, 0, 13);

	for (;;) {
		x1 = cursor.x; y1 = cursor.y;
		movimiento_cursor (0, 0, 13);
		borrar_cursor ();
		line (x1, y1, cursor.x, cursor.y);
		dibujar_cursor ();
		if (getch () == 27) break;
	}
}

void dibujar_elipse (void)
{
}

void dibujar_texto (void)
{
	char cad[80];
	moveto (cursor.x, cursor.y); /* Mover la posici¢n del cursor (CP) para empezar a escribir ah¡ */
	settextstyle (contexto.fuente.nombre, contexto.fuente.direccion, contexto.fuente.tamano);
	borrar_cursor ();

	for (;;) {
		*cad = getch ();
		if (*cad == 13) {
			cursor.y += contexto.fuente.interlineado;
			moveto (cursor.x, cursor.y);
			*cad = NULL;
		}
		if (*cad == 27) break;
		outtext (cad);
	}
	dibujar_cursor ();
}

void dibujar_paralelas (void)
{
	int x1=0, y1=0, x2=0, y2=0, x3=0, y3=0, x4=0, y4=0;

	movimiento_cursor (0, 0, 13);
	x1 = cursor.x;
	y1 = cursor.y;
	borrar_cursor ();
	putpixel (x1, y1, contexto.color);

	dibujar_cursor ();
	movimiento_cursor (0, 0, 13);

	borrar_cursor ();
	line (x1, y1, cursor.x, cursor.y);
	dibujar_cursor ();

	x2 = cursor.x;
	y2 = cursor.y;

	movimiento_cursor (0, 0, 13);
	x3 = cursor.x;
	y3 = cursor.y;
	borrar_cursor ();
	putpixel (x3, y3, contexto.color);

	x4 = x3 - x1;
	y4 = y1 - y3;

	line (x3, y3, x2 + x4, y2 - y4);
	dibujar_cursor ();

}