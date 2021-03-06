/*
	浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
	�                  Archivo de cabecera DPALIB.H                        �
	�                       1998 DPA Software.                             �
	麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様郵
	�                                                                      �
	�  Archivo fuente: DPALIB.H                                            �
	�  Versi�n: 1.0                                                        �
	�  Programador: Jairo Alejandro Duarte Avenda�o.                       �
	�  Tipo: Archivo de cabecera con definiciones, tipos de datos y        �
	�    estructuras globales, para trabajar con el mouse, y con el modo X �
	�    de la VGA.                                                        �
	�  Compilador: Borland C++ 3.1 para DOS.                               �
	�  Dependencias: Ninguna.                                              �
	�  Caracteristicas: Proporciona definiciones y estructuras para hacer  �
	�    el manejo de algunos dispositivos, m�s facil y legible.   	       �
	�                                                                      �
	麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様郵
	�  DPA Software 1998.                                                  �
	藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕
*/


#ifndef __DPA_LIB__ /* protecci�n contra incluci�n multiple */
#define __DPA_LIB__


#include <stdio.h> /* librerias Borland requeridas */
#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include <mem.h>
#include <alloc.h>
#include <string.h>
#include <conio.h>
#include <process.h>

/*
	浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
	�                           DEFINICIONES                               �
	藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕
*/

#define VERDADERO       1
#define FALSO           0
#define CIERTO          VERDADERO
#define ERROR           FALSO
#define OK              VERDADERO

#define MAX_GAMA        64
#define NUM_SCAN_QUE 256     // this MUST be 256, using BYTE roll-over for
														 // q code

#define SEG_PANTALLA    0xA000 /* direcci�n del segmento de la memoria de video */
#define OFF_PANTALLA    0x0000 /* direcci�n del desplazamiento de la memoria de video */

#define MOUSE_BOTONIZ   1 /* Identificadores de los botones del mouse */
#define MOUSE_BOTONDR   2
#define MOUSE_DIV       2

#define MOUSE_INT       0x33 /* N�mero de interrupci�n BIOS para controlar el mouse */
#define VGA_INT         10h /* interrupci�n BIOS para inicializar la VGA 13h standar */
#define VGA_13h         13h /* Funci�n BIOS para inicializar el modo X VGA */
#define MODO_3h         3h
#define SEQU_ADDR       0x3c4 /* SEQUENCER Adress */
#define CRTC_ADDR       0x3d4
#define GRAC_ADDR       0x3ce
#define	INPUT_STATUS_1  03dah /* Input Status Adress */

#define OUT_PORT_C_R    0x3c7 /* DAC */
#define OUT_PORT_C_W    0x3c8
#define OUT_PORT_G      0x3c9

#define SC_H 						CIERTO
#define SC_V 						CIERTO

/*
	浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
	�              ESTRUCTURAS Y TIPOS DE DATOS GLOBALES                   �
	藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕
*/

typedef unsigned char BYTE;
typedef char          BOOL;
typedef short int     WORDSHORT;

typedef struct { /* estructura para las cordenadas del mouse */
	WORDSHORT x;
	WORDSHORT y;
	BOOL estado;
} s_MOUSECOOR;

typedef struct { /* estructura para un sprite */
	WORDSHORT long_x;
	WORDSHORT long_y;
	WORDSHORT pos_x;
	WORDSHORT pos_y;
	BYTE *sprite;
} s_SPRITE;

typedef struct { /* estructura para un sprite comprimido */
	WORDSHORT long_x;
	WORDSHORT long_y;
	BYTE huge *sprite;
} s_SPRITE_SPC;

typedef struct { /* estructura para sprites enlazados (SPE) */
	WORDSHORT total_sprites;
	WORDSHORT pos_x;
	WORDSHORT pos_y;
	BYTE huge *sprite;
} s_SPRITE_SPE;

typedef struct { /* estructura para mapas */
	WORDSHORT long_x;
	WORDSHORT long_y;
	WORDSHORT bloques_verticales;
	WORDSHORT bloques_horizontales;
	WORDSHORT x_pant;
	WORDSHORT y_pant;
	WORDSHORT x;
	WORDSHORT y;
	int despx;
	int despy;
	BYTE huge *mapa;
} s_MAPA;

typedef struct { /* estructura para los bloques de un mapa */
	WORDSHORT long_x;
	WORDSHORT long_y;
	WORDSHORT bytes_bloque;
	WORDSHORT total_bloques;
	BYTE huge *bloque;
} s_BLK;

typedef struct { /* estructura para las fuentes gr�ficas */
	WORDSHORT total_caracteres;
	BYTE *alfabeto;
	BYTE huge *fuente;
} s_FUENTE;


#endif /* __DPA_LIB__ */

/* Terminado el 18 de Enero de 1998. DPA Software. */
