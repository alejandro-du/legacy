/*
	����������������������������������������������������������������������ͻ
	�                   Archivo de cabecera MOUSE.H                        �
	�                       1998 DPA Software.                             �
	����������������������������������������������������������������������͹
	�                                                                      �
	�  Archivo fuente: MOUSE.H                                             �
	�  Versi�n: 1.0                                                        �
	�  Programador: Jairo Alejandro Duarte Avenda�o.                       �
	�  Tipo: Archivo de cabecera con prototipos de funciones, para         �
	�    trabajar con el mouse.                                            �
	�  Compilador: Borland C++ 3.1.                                        �
	�  Dependencias: Requiere el archivo cabecera DPALIB.H.                �
	�  Caracteristicas: Proporciona el control de las principales          �
	�    funciones del mouse, incluyendo inicializaci�n, visualizaci�n,    �
	�    posici�n y n�mero de botones del mouse.                           �
	�                                                                      �
	����������������������������������������������������������������������͹
	�  DPA Software 1997.                                                  �
	����������������������������������������������������������������������ͼ
*/


#ifndef __DPA_MOUSE__ /* protecci�n contra recompilaci�n */
#define __DPA_MOUSE__

#ifndef __DPA_GRAFICOS__
#include "graficos.h"
#endif

#include "dpalib.h" /* requerido */


/*
	����������������������������������������������������������������������ͻ
	�                    DECLARACION DE DATOS GLOBALES                     �
	����������������������������������������������������������������������ͼ
*/

int Mouse_DivX = 8;
int Mouse_DivY = 4;
BYTE Mascara_Mouse = 0;
BOOL Mouse_Capturado = FALSO;
BOOL mouse_visible = VERDADERO;
union REGS registros; /* usada para interactuar con la BIOS */
s_SPRITE puntero_grafico, fondo_puntero_grafico;

/*
	����������������������������������������������������������������������ͻ
	�                      DECLARACION DE FUNCIONES                        �
	����������������������������������������������������������������������ͼ
*/

WORDSHORT Inicializar_Mouse(void); /* Prepara el mouse y borra los indicadores */
void Visualizar_Mouse(void); /* Muestrar el puntero del mouse en la pantalla */
void Ocultar_Mouse(void); /* Ocultar el puntero del mouse */
void Fijar_Limites_Horiz(WORDSHORT minimo, WORDSHORT maximo); /* Fija la posici�n m�xima y m�nima horizantal */
void Fijar_Limites_Vert(WORDSHORT minimo, WORDSHORT maximo); /* Fija la posici�n m�xima y m�nima vertical */
void Fijar_Razon(WORDSHORT horiz, WORDSHORT vert); /* Fijar la raz�n */
WORDSHORT Datos_Mouse(s_MOUSECOOR *coordenadas); /* Obtener el bot�n presionado y debolver las coordenadas */
WORDSHORT Boton_Liberado(s_MOUSECOOR *coordenadas); /* Obtener el bot�n liberado y debolver las coordenadas */
void Liberar_Mouse(void);
void Capturar_Mouse(void);
BOOL Cargar_Puntero_Mouse(char *nombre_archivo);
void Descargar_Puntero_Mouse(void);
void Ocultar_Puntero_Mouse(s_MOUSECOOR *mouse1);
void Visualizar_Puntero_Mouse(void);


/*
	����������������������������������������������������������������������ͻ
	�                      DEFINICION DE FUNCIONES                         �
	����������������������������������������������������������������������ͼ
*/

/*
	����������������������������������������������������������������������ͻ
	� Inicializar_Mouse();                                                 �
	�                                                                      �
	� Inicializa el controlador del mouse. Retorna el n�mero de botones    �
	� del mouse.                                                           �
	����������������������������������������������������������������������ͼ
*/

WORDSHORT Inicializar_Mouse(void)
{
	registros.x.ax = 0x0;
	int86(MOUSE_INT, &registros, &registros);
	return registros.x.ax; /* retornar el n�mero de botones del mouse */
}


/*
	����������������������������������������������������������������������ͻ
	� Visualizar_Mouse();                                                  �
	�                                                                      �
	� Visualiza el mouse hardware. Solo admite dos colores para el puntero �
	� gr�fico.                                                             �
	����������������������������������������������������������������������ͼ
*/

void Visualizar_Mouse(void)
{
	registros.x.ax = 0x1;
	int86(MOUSE_INT, &registros, &registros);
}


/*
	����������������������������������������������������������������������ͻ
	� Ocultar_Mouse();                                                     �
	�                                                                      �
	� Oculta el mouse hardware.                                            �
	����������������������������������������������������������������������ͼ
*/

void Ocultar_Mouse(void)
{
	registros.x.ax = 0x2;
	int86(MOUSE_INT, &registros, &registros);
}


/*
	����������������������������������������������������������������������ͻ
	� Fijar_Limites_Horiz(0, 320);                                         �
	�                                                                      �
	� Fija los limites horizontales del puntero.                           �
	����������������������������������������������������������������������ͼ
*/

void Fijar_Limites_Horiz(WORDSHORT minimo, WORDSHORT maximo)
{
	registros.x.cx = minimo;
	registros.x.dx = maximo;
	registros.x.ax = 0x7;
	int86(MOUSE_INT, &registros, &registros);
}


/*
	����������������������������������������������������������������������ͻ
	� Fijar_Limites_Vert(0, 200);                                          �
	�                                                                      �
	� Fija los limites Verticales del puntero.                             �
	����������������������������������������������������������������������ͼ
*/

void Fijar_Limites_Vert(WORDSHORT minimo, WORDSHORT maximo)
{
	registros.x.cx = minimo;
	registros.x.dx = maximo;
	registros.x.ax = 0x8;
	int86(MOUSE_INT, &registros, &registros);
}


/*
	����������������������������������������������������������������������ͻ
	� Fijar_Razon(50, 50);                                                 �
	�                                                                      �
	� Ajusta la sensibilidad del mouse horizontal y verticalmente.         �
	����������������������������������������������������������������������ͼ
*/

void Fijar_Razon(WORDSHORT horiz, WORDSHORT vert)
{
	registros.x.cx = horiz;
	registros.x.dx = vert;
	registros.x.ax = 0x0f;
	int86 (MOUSE_INT, &registros, &registros);
}


/*
	����������������������������������������������������������������������ͻ
	� Fijar_Limites_Horiz(0, 320);                                         �
	�                                                                      �
	� Obtiene las cordenadas actuales del mouse y devuelve el estado de    �
	� los botones (n�mero del boton presionado).                           �
	����������������������������������������������������������������������ͼ
*/

WORDSHORT Datos_Mouse(s_MOUSECOOR *coordenadas)
{
	registros.x.ax = 0x3;
	int86(MOUSE_INT, &registros, &registros);
	coordenadas -> x = (WORDSHORT) registros.x.cx / MOUSE_DIV;
	coordenadas -> y = (WORDSHORT) registros.x.dx;
	if(Mouse_Capturado) return 0;
	return (registros.x.bx);
}


/*
	����������������������������������������������������������������������ͻ
	� Fijar_Limites_Horiz(0, 320);                                         �
	�                                                                      �
	� Obtiene las cordenadas del mouse en el �ltimo momento en que se      �
	� liber� alg�n boton. Devuelve en n�mero del boton.                    �
	����������������������������������������������������������������������ͼ
*/

WORDSHORT Boton_Liberado(s_MOUSECOOR *coordenadas)
{
	registros.x.ax = 0xb;
	int86(MOUSE_INT, &registros, &registros);
	coordenadas -> x = (WORDSHORT) registros.x.cx;
	coordenadas -> y = (WORDSHORT) registros.x.dx;
	if(Mouse_Capturado) return 0;
	return (registros.x.bx);
}


/*
	����������������������������������������������������������������������ͻ
	� Capturar_Mouse();   																		             �
	�                                                                      �
	� Captura el mouse para que las operaciones con los botones se         �
	� desactiven.                                                          �
	����������������������������������������������������������������������ͼ
*/

void Capturar_Mouse(void)
{
	Mouse_Capturado = VERDADERO;
}


/*
	����������������������������������������������������������������������ͻ
	� Liberar_Mouse();   																		               �
	�                                                                      �
	� Libera el mouse para que las operaciones con los botones se activen. �
	����������������������������������������������������������������������ͼ
*/

void Liberar_Mouse(void)
{
	Mouse_Capturado = FALSO;
}


/*
	����������������������������������������������������������������������ͻ
	� Cargar_Puntero_Mouse("mouse.spr");                                   �
	�                                                                      �
	� Carga un sprite para el puntero gr�fico.                             �
	����������������������������������������������������������������������ͼ
*/

BOOL Cargar_Puntero_Mouse(char *nombre_archivo)
{
	BOOL estado;

	estado = Cargar_Sprite(nombre_archivo, &puntero_grafico);
	fondo_puntero_grafico.long_x = puntero_grafico.long_x;
	fondo_puntero_grafico.long_y = puntero_grafico.long_y;
	if ((fondo_puntero_grafico.sprite = malloc((puntero_grafico.long_x) * (puntero_grafico.long_y))) == NULL) estado = ERROR;
	return estado;
}


/*
	����������������������������������������������������������������������ͻ
	� Mover_Puntero_Mouse(&mouse1, &mouse2);                               �
	�                                                                      �
	� Mueve el puntero gr�fico del mouse, seg�n las nuevas posiciones      �
	� del puerto.                                                          �
	����������������������������������������������������������������������ͼ
*/

WORDSHORT Mover_Puntero_Mouse(s_MOUSECOOR *mouse1, s_MOUSECOOR *mouse2)
{
	if(mouse_visible) {
		if(mouse1 -> x != mouse2 -> x || mouse1 -> y != mouse2 -> y) {
			fondo_puntero_grafico.pos_x = mouse1 -> x;
			fondo_puntero_grafico.pos_y = mouse1 -> y;
			Mostrar_Sprite_Plano(&fondo_puntero_grafico);
			mouse1 -> x = mouse2 -> x;
			mouse1 -> y = mouse2 -> y;
			mouse1 -> estado = VERDADERO;
			mouse2 -> estado = VERDADERO;
		}
		else {
			mouse1 -> estado = FALSO;
			mouse2 -> estado = FALSO;
		}

		if(mouse1 -> estado) Obtener_Imagen(mouse1 -> x, mouse1 -> y, mouse1 -> x + puntero_grafico.long_x, mouse1 -> y + puntero_grafico.long_y, &fondo_puntero_grafico);
		puntero_grafico.pos_x = mouse1 -> x;
		puntero_grafico.pos_y = mouse1 -> y;
		Mostrar_Sprite_Mascara(&puntero_grafico, Mascara_Mouse);
	}
	return Datos_Mouse(mouse2);
}


/*
	����������������������������������������������������������������������ͻ
	� Descargar_Puntero_Mouse();                                           �
	�                                                                      �
	� Libera la memoria asignada previamente para el sprite.               �
	����������������������������������������������������������������������ͼ
*/

void Descargar_Puntero_Mouse(void)
{
	puntero_grafico.long_x = 0;
	puntero_grafico.long_y = 0;
	free(puntero_grafico.sprite);
	free(fondo_puntero_grafico.sprite);
}


void Ocultar_Puntero_Mouse(s_MOUSECOOR *mouse1)
{
	fondo_puntero_grafico.pos_x = mouse1 -> x;
	fondo_puntero_grafico.pos_y = mouse1 -> y;
	Mostrar_Sprite_Plano(&fondo_puntero_grafico);
	mouse_visible = FALSO;
}


void Visualizar_Puntero_Mouse(void)
{
	mouse_visible = VERDADERO;
	Mostrar_Sprite_Mascara(&puntero_grafico, Mascara_Mouse);
}


#endif /* __DPA_MOUSE__ */

/* Terminado el 27 de Enero de 1998. DPA Software. */