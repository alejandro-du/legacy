/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ                   Archivo de cabecera MOUSE.H                        บ
	บ                       1998 DPA Software.                             บ
	ฬออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
	บ                                                                      บ
	บ  Archivo fuente: MOUSE.H                                             บ
	บ  Versiขn: 1.0                                                        บ
	บ  Programador: Jairo Alejandro Duarte Avendaคo.                       บ
	บ  Tipo: Archivo de cabecera con prototipos de funciones, para         บ
	บ    trabajar con el mouse.                                            บ
	บ  Compilador: Borland C++ 3.1.                                        บ
	บ  Dependencias: Requiere el archivo cabecera DPALIB.H.                บ
	บ  Caracteristicas: Proporciona el control de las principales          บ
	บ    funciones del mouse, incluyendo inicializaciขn, visualizaciขn,    บ
	บ    posiciขn y nฃmero de botones del mouse.                           บ
	บ                                                                      บ
	ฬออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
	บ  DPA Software 1997.                                                  บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/


#ifndef __DPA_MOUSE__ /* protecciขn contra recompilaciขn */
#define __DPA_MOUSE__

#ifndef __DPA_GRAFICOS__
#include "graficos.h"
#endif

#include "dpalib.h" /* requerido */


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ                    DECLARACION DE DATOS GLOBALES                     บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

int Mouse_DivX = 8;
int Mouse_DivY = 4;
BYTE Mascara_Mouse = 0;
BOOL Mouse_Capturado = FALSO;
BOOL mouse_visible = VERDADERO;
union REGS registros; /* usada para interactuar con la BIOS */
s_SPRITE puntero_grafico, fondo_puntero_grafico;

/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ                      DECLARACION DE FUNCIONES                        บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

WORDSHORT Inicializar_Mouse(void); /* Prepara el mouse y borra los indicadores */
void Visualizar_Mouse(void); /* Muestrar el puntero del mouse en la pantalla */
void Ocultar_Mouse(void); /* Ocultar el puntero del mouse */
void Fijar_Limites_Horiz(WORDSHORT minimo, WORDSHORT maximo); /* Fija la posiciขn m xima y mกnima horizantal */
void Fijar_Limites_Vert(WORDSHORT minimo, WORDSHORT maximo); /* Fija la posiciขn m xima y mกnima vertical */
void Fijar_Razon(WORDSHORT horiz, WORDSHORT vert); /* Fijar la razขn */
WORDSHORT Datos_Mouse(s_MOUSECOOR *coordenadas); /* Obtener el botขn presionado y debolver las coordenadas */
WORDSHORT Boton_Liberado(s_MOUSECOOR *coordenadas); /* Obtener el botขn liberado y debolver las coordenadas */
void Liberar_Mouse(void);
void Capturar_Mouse(void);
BOOL Cargar_Puntero_Mouse(char *nombre_archivo);
void Descargar_Puntero_Mouse(void);
void Ocultar_Puntero_Mouse(s_MOUSECOOR *mouse1);
void Visualizar_Puntero_Mouse(void);


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ                      DEFINICION DE FUNCIONES                         บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Inicializar_Mouse();                                                 บ
	บ                                                                      บ
	บ Inicializa el controlador del mouse. Retorna el nฃmero de botones    บ
	บ del mouse.                                                           บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

WORDSHORT Inicializar_Mouse(void)
{
	registros.x.ax = 0x0;
	int86(MOUSE_INT, &registros, &registros);
	return registros.x.ax; /* retornar el nฃmero de botones del mouse */
}


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Visualizar_Mouse();                                                  บ
	บ                                                                      บ
	บ Visualiza el mouse hardware. Solo admite dos colores para el puntero บ
	บ gr fico.                                                             บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void Visualizar_Mouse(void)
{
	registros.x.ax = 0x1;
	int86(MOUSE_INT, &registros, &registros);
}


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Ocultar_Mouse();                                                     บ
	บ                                                                      บ
	บ Oculta el mouse hardware.                                            บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void Ocultar_Mouse(void)
{
	registros.x.ax = 0x2;
	int86(MOUSE_INT, &registros, &registros);
}


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Fijar_Limites_Horiz(0, 320);                                         บ
	บ                                                                      บ
	บ Fija los limites horizontales del puntero.                           บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void Fijar_Limites_Horiz(WORDSHORT minimo, WORDSHORT maximo)
{
	registros.x.cx = minimo;
	registros.x.dx = maximo;
	registros.x.ax = 0x7;
	int86(MOUSE_INT, &registros, &registros);
}


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Fijar_Limites_Vert(0, 200);                                          บ
	บ                                                                      บ
	บ Fija los limites Verticales del puntero.                             บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void Fijar_Limites_Vert(WORDSHORT minimo, WORDSHORT maximo)
{
	registros.x.cx = minimo;
	registros.x.dx = maximo;
	registros.x.ax = 0x8;
	int86(MOUSE_INT, &registros, &registros);
}


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Fijar_Razon(50, 50);                                                 บ
	บ                                                                      บ
	บ Ajusta la sensibilidad del mouse horizontal y verticalmente.         บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void Fijar_Razon(WORDSHORT horiz, WORDSHORT vert)
{
	registros.x.cx = horiz;
	registros.x.dx = vert;
	registros.x.ax = 0x0f;
	int86 (MOUSE_INT, &registros, &registros);
}


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Fijar_Limites_Horiz(0, 320);                                         บ
	บ                                                                      บ
	บ Obtiene las cordenadas actuales del mouse y devuelve el estado de    บ
	บ los botones (nฃmero del boton presionado).                           บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Fijar_Limites_Horiz(0, 320);                                         บ
	บ                                                                      บ
	บ Obtiene las cordenadas del mouse en el ฃltimo momento en que se      บ
	บ liberข algฃn boton. Devuelve en nฃmero del boton.                    บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Capturar_Mouse();   																		             บ
	บ                                                                      บ
	บ Captura el mouse para que las operaciones con los botones se         บ
	บ desactiven.                                                          บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void Capturar_Mouse(void)
{
	Mouse_Capturado = VERDADERO;
}


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Liberar_Mouse();   																		               บ
	บ                                                                      บ
	บ Libera el mouse para que las operaciones con los botones se activen. บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void Liberar_Mouse(void)
{
	Mouse_Capturado = FALSO;
}


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Cargar_Puntero_Mouse("mouse.spr");                                   บ
	บ                                                                      บ
	บ Carga un sprite para el puntero gr fico.                             บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Mover_Puntero_Mouse(&mouse1, &mouse2);                               บ
	บ                                                                      บ
	บ Mueve el puntero gr fico del mouse, segฃn las nuevas posiciones      บ
	บ del puerto.                                                          บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ Descargar_Puntero_Mouse();                                           บ
	บ                                                                      บ
	บ Libera la memoria asignada previamente para el sprite.               บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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