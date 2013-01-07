// FECHA DE INICIO:                                                            21 - 11 - 98

/* Archivos requeridos: BITMAP.DAT
                        IMG1.DAT
                        SONIDO.DAT
                        PR1.DAT
                        NIVEL1.MAP
                        IMG.BLK
*/

//-----------------------------------------------------------------------------------------
//	                              LIBRERIAS
//-----------------------------------------------------------------------------------------
// Librerias C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "allegro.h" // libreria allegro 3.0

// Archivos de cabecera para las definiciones de los elementos DAT (Grabber)

#include "bitmap.h"	// archivo BITMAP.DAT
#include "sonido.h"	// archivo SONIDO.DAT
#include "pr.h"			// archivo PR1.DAT

//-----------------------------------------------------------------------------------------
//	                            DEFINICIONES
//-----------------------------------------------------------------------------------------
// Codigos de error
#define	ERR_ARCHIVO	2	// error al intentar abrir un archivo
#define	ERR_VIDEO		3	// error al inicializar un modo gr fico
#define	ERR_MEMORIA	4	// memoria insuficiente
#define	ERR_MOUSE		5	// no hay controlador del mouse

// Nombres de los archivos externos requeridos
#define	STR_ARCHIVO_BITMAP	 "BITMAP.DAT"	// archivo DAT para los gr ficos
#define	STR_ARCHIVO_SONIDO	 "SONIDO.DAT"	// archivo DAT para la m£sica y efectos
#define	STR_ARCHIVO_CARGANDO "IMG.DAT"		// archivo PCX cargando...
#define	STR_ARCHIVO_BLK			 "img.BLK"		// archivo de gr ficos de bloques (Map Maker)

// Posiciones iniciales y tama¤o de sprites
#define	SP_IND_MENU_X			 169 // posicion inicial del se¤alador del menu (eje X)
#define	SP_ANCHO_BLOQUE		 32	// ancho de un bloque
#define	SP_ALTO_BLOQUE		 32	// alto de un bloque
#define	SP_MAPA_X					 0 // posicion del mapa
#define	SP_MAPA_Y					 0
#define	SP_PERSONAJE_ANCHO b_personaje ->	w	// longitud del personaje
#define	SP_PERSONAJE_ALTO	 b_personaje ->	h

// Identificadores
#define	ID_NUEVO		0	// menu
#define	ID_CARGAR		1
#define	ID_SALVAR		2
#define	ID_CREDITOS	3
#define	ID_SALIR		4

#define	ID_INICIAR	 1 // estado de juego
#define	ID_CONTINUAR 2

#define	ID_QUIETO				0	// estado del personaje
#define	ID_CAMINANDO		2
#define	ID_CORRIENDO		4

#define	ID_NORTE				1	// direcciones de desplazamiento
#define	ID_SUR					2
#define	ID_ESTE					3
#define	ID_OESTE				4
#define	ID_NORESTE			5
#define	ID_NOROESTE			6
#define	ID_SURESTE			7
#define	ID_SUROESTE			8

// Constantes de control y datos de incremento
#define	CNT_TOTAL_MAPAS					 1	 // n£mero de archivos de tableros
#define	CNT_TOTAL_BLOQUES				 240 // n£mero de bloques a cargar del archivo BLK
#define	CNT_BLOQUES_HORIZONTALES 20	 // tama¤o del mapeado
#define	CNT_BLOQUES_VERTICALES	 13
//#define	CNT_BLOQUES_HORIZONTALES 64 // tama¤o del mapeado
//#define	CNT_BLOQUES_VERTICALES	 48
#define	CNT_BYTES_BLOQUE SP_ANCHO_BLOQUE * SP_ALTO_BLOQUE
#define	CNT_LIMITE_HORIZONTAL	CNT_BLOQUES_HORIZONTALES * SP_ALTO_BLOQUE
#define	CNT_LIMITE_VERTICAL	CNT_BLOQUES_VERTICALES * SP_ANCHO_BLOQUE
#define	CNT_TIMER_PR 1

// posici¢n actual en el mapa de un bitmap
#define	POS_BLK_X(px)	((px - mapa.sc_h)	/ SP_ANCHO_BLOQUE) + mapa.x
#define	POS_BLK_Y(py)	((py - mapa.sc_v)	/ SP_ALTO_BLOQUE)	+	mapa.y

#define	POS_BLK_PX ((personaje.x + (SP_PERSONAJE_ANCHO >>	1) - mapa.sc_h)	/ SP_ANCHO_BLOQUE) + mapa.x
#define	POS_BLK_PY ((personaje.y + (SP_PERSONAJE_ALTO	-	(SP_PERSONAJE_ALTO >>	2))	-	mapa.sc_v) / SP_ALTO_BLOQUE) + mapa.y

#define	SP_POS_ORIGEN_Y	(CNT_LIMITE_VERTICAL >>	1) - (SP_PERSONAJE_ALTO	>> 1)
#define	SP_POS_ORIGEN_X	(CNT_LIMITE_HORIZONTAL >>	1) - (SP_PERSONAJE_ANCHO >>	1)

#define	BLK_P	*(mapa.mapa	+	(POS_BLK_PX-1) * mapa.alto + POS_BLK_PY)
//#define	AT_P *(mapa.at + BLK_P)
#define	AT_P 0 // ­­­ la linea de arriba es la correcta !!!

#define	PENTIUM_100_TIMER	32			// 32

//-----------------------------------------------------------------------------------------
//	               ESTRUCTURAS Y TIPOS DE DATOS GLOBALES
//-----------------------------------------------------------------------------------------
typedef	unsigned char	BOOL;	// FALSE - TRUE
typedef	unsigned char	BYTE;	// 0 - 256

// estructura para el manejo del mapeado
typedef	struct {
	BYTE ancho;											// longitud horizontal del mapa
	BYTE alto;											// longitud vertical del mapa
	int	x;													// posicion horizontal dentro del mapa
	int	y;													// posicion vertical dentro del mapa
	BITMAP *blk[CNT_TOTAL_BLOQUES];	// memoria para guardar los bloques
	BYTE at[CNT_TOTAL_BLOQUES];			// atributo de los bloques
	int	*mapa;											// apuntador a la memoria que contiene el mapa
	char dir_h;											// direcci¢n horizontal de movimiento del mapa
	char dir_v;											// direcci¢n vertical de movimiento del mapa
	signed char	sc_v;
	signed char	sc_h;
}	s_MAPA;



//typedef struct {
//} s_ITEMS;


// datos del personaje
typedef	struct {
	// variables de movimiento
	int	x;
	int	y;
	char direccion;
	char estado;
	unsigned int frame;
	int	timer;
	char destino;
	int	destino_x;
	int	destino_y;
	int	armadura;	// nivel de armadura

//  s_ITEMS item;

}	s_PERSONAJE;


//-----------------------------------------------------------------------------------------
 //	                       DECLARACION DE FUNCIONES
//-----------------------------------------------------------------------------------------
void inicializar_programa(void);					// inicializa dispositivos (graficos, teclado)
void descargar_programa(void);						// libera la memoria utilizada por dispositivos
void descargar_datos(void);								// libera la memoria usada por variables
void cargar_datos(void);									// carga archivos de datos
void menu(void);													// menu principal del programa
void jugar(BOOL	juego);										// comienza el juego
void cargar_juego(char tablero,						// carga un tablero
									char nombre_mapa[13]);
void cargar_blk(void);										// carga el archivo de bloques BLK en un array
void pintar_mapa(BITMAP	*buffer);					// pinta el mapa en pantalla
void rut_err(char	cod, char	mensaje[80]);	// controla errores
void animar_personaje(void);


//-----------------------------------------------------------------------------------------
//	                     DECLARACION DE DATOS GLOBALESS
//-----------------------------------------------------------------------------------------
// Archivos de datos (Grabber)
DATAFILE *dat_bitmap;		 // controlador para el archivo de datos BITMAP.DAT
DATAFILE *dat_sonido;		 // controlador para el archivo de datos SONIDO.DAT
DATAFILE *dat_personaje; // controlador para el archivo de datos PRx.DAT

BITMAP *buffer;
BITMAP *b_personaje;


char archivo_mapa[CNT_TOTAL_MAPAS][12] = {"NIVEL1.MAP"}; // archivos de los tableros
char archivo_pr[1][12] = {"PR1.DAT"};

s_MAPA mapa;					 // mapa del juego
s_PERSONAJE	personaje; // variable para datos del personaje principal

// controladores o incrementadores
volatile int cnt_timer;	// variable usada para el control del timer
char velocidad;

int	PR_ESTE_CM_ULTIMO;
int	PR_OESTE_CM_ULTIMO;
int	PR_NORTE_CM_ULTIMO;
int	PR_SUR_CM_ULTIMO;
int	PR_NE_CM_ULTIMO;
int	PR_NO_CM_ULTIMO;
int	PR_SE_CM_ULTIMO;
int	PR_SO_CM_ULTIMO;
int	PR_ESTE_CM_00;
int	PR_OESTE_CM_00;
int	PR_NORTE_CM_00;
int	PR_SUR_CM_00;
int	PR_NE_CM_00;
int	PR_NO_CM_00;
int	PR_SE_CM_00;
int	PR_SO_CM_00;


// Switches
BOOL sw_sonido;	 // activaci¢n o desactivaci¢n del sonido
BOOL sw_jugando; // contiene el estado de si se est  jugando o no
BOOL sw_limite_este;
BOOL sw_limite_oeste;
BOOL sw_limite_norte;
BOOL sw_limite_sur;
BOOL sw_limite_noreste;
BOOL sw_limite_noroccidente;
BOOL sw_limite_sureste;
BOOL sw_limite_suroccidente;

//-----------------------------------------------------------------------------------------
//	                        CONTROLADOR DEL TIMER
//-----------------------------------------------------------------------------------------
void timer_proc()
{
	cnt_timer++;
}
END_OF_FUNCTION(timer_proc);


//-----------------------------------------------------------------------------------------
//	                       FUNCION PRINCIPAL (MAIN)
//-----------------------------------------------------------------------------------------
main(void)
{
	inicializar_programa();
	cargar_datos();
	menu();
	descargar_datos();
	descargar_programa();
	return 0;
}


//-----------------------------------------------------------------------------------------
//	                       DEFINICION DE FUNCIONES
//-----------------------------------------------------------------------------------------

//----------------------------------------------------------------| inicializar_programa();
// Inicializa los dispositivos requeridos: teclado, modo de video, timer, sonido, mouse.
// Llamada en: main()
void inicializar_programa(void)
{
	BITMAP *cargando;	// mensje "cargando..."
	PALETTE	paleta;	// paleta de la imagen PCX ("cargando...")


	allegro_init();
	if(set_gfx_mode(GFX_VESA1, 640,	480, 0,	0) !=	0) { // inicializar modo gr fico VGA
		rut_err(ERR_VIDEO, "640 * 480 * 256");
	}
/*	cargando = load_pcx(STR_ARCHIVO_CARGANDO,	paleta); // cargar el archivo PCX
	if(!cargando)	rut_err(ERR_ARCHIVO, STR_ARCHIVO_CARGANDO);	// verificar

	set_palette(black_palette);	// empezar con paleta negra para que no aparesca nada en pantalla
	draw_sprite(screen,	cargando,	(SCREEN_W	/ 2) - ((cargando	-> w)	/ 2),	(SCREEN_H	/ 2) - ((cargando	-> h)	/ 2));
   fade_in(paleta, 1); // aclarar pantalla para que aparesca el mensaje
*/
	install_keyboard();
	if(install_mouse() ==	-1)	rut_err(ERR_MOUSE,"");
	install_timer();
	// verificar si se logra inicializar el driver sonido y activar la variable sonidos
/*  if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) sw_sonido = FALSE;
  else sw_sonido = TRUE;    ************************/
	sw_jugando = FALSE;
//	destroy_bitmap(cargando);

}


//------------------------------------------------------------------------| cargar_datos();
// Carga los archivos necesarios en memoria.
// Llamada en: main();
void cargar_datos(void)
{
	dat_bitmap = load_datafile(STR_ARCHIVO_BITMAP);
	if(!dat_bitmap)	rut_err(ERR_ARCHIVO, STR_ARCHIVO_BITMAP);	// verificar
	dat_sonido = load_datafile(STR_ARCHIVO_SONIDO);
	if(!dat_sonido)	rut_err(ERR_ARCHIVO, STR_ARCHIVO_SONIDO);	// verificar
	cargar_blk();
//  fade_out(1); // oscurecer pantalla*/
	clear(screen);
}


//---------------------------------------------------------------------| descargar_datos();
// Libera la memoria usada por los archivos.
// Llamada en: main();
void descargar_datos(void)
{
	int	contador;

	// liberar memoria de archivos de datos (Grabber)
	unload_datafile(dat_bitmap);
	unload_datafile(dat_sonido);

	// liberar la memoria de los bloques BLK
	for(contador = 0;	contador < CNT_TOTAL_BLOQUES;	contador++)	{
		destroy_bitmap(mapa.blk[contador]);
	}

	if(sw_jugando) free(mapa.mapa);	// descargar mapa
}


//------------------------------------------------------------------| descargar_programa();
// Libera la memoria utilizada por dispositivos o restaura estos.
// Llamada en: main(), rut_err()
void descargar_programa(void)
{
	fade_out(15);	// oscurecer pantalla
	clear(screen); // borrar posibles rastros
	remove_keyboard();
	remove_mouse();
	set_gfx_mode(GFX_TEXT, 0,	0, 0,	0);	// volver al modo de texto
	allegro_exit();
}


//--------------------------------------------------------------------------------| menu();
// Controla la opcion del usuario en el menu principal.
// Llamada en: main();
void menu(void)
{
	int	cont,	seleccion	=	0;
	int	pos_ind[5] = {155, 219,	280, 340,	399};
	BITMAP *fondo_ind;

	fondo_ind	=	create_bitmap(68,	47);
	clear(fondo_ind);

	install_int_ex(timer_proc, MSEC_TO_TIMER(75));
	LOCK_VARIABLE(cnt_timer);
	LOCK_FUNCTION(timer_proc);

	if(sw_sonido)	play_midi(dat_sonido[DAT_MUSICA_MENU].dat, TRUE);
	set_palette(black_palette);	// empezar con paleta negra para que no aparesca nada en pantalla
	draw_sprite(screen,	dat_bitmap[DAT_MENU].dat,	0, 0); // Dibujar pantalla del men£
	fade_in(dat_bitmap[DAT_MENU_PALETA].dat, 15);
	cnt_timer	=	0;
	// obtener el fondo
	masked_blit(screen,	fondo_ind, SP_IND_MENU_X,	pos_ind[seleccion],	0, 0,	68,	47);
	clear_keybuf();

	for(cont = DAT_IND_MENU_01;	;) { // bucle principal del menu
		if(cnt_timer > 0)	{
			vsync();
			// dibujar fondo
			draw_sprite(screen,	fondo_ind, SP_IND_MENU_X,	pos_ind[seleccion]);
			// dibujar indicador
			draw_sprite(screen,	dat_bitmap[cont].dat,	SP_IND_MENU_X, pos_ind[seleccion]);
			cont++;	// pasar al siguiente frame del indicador
			cnt_timer	=	0;
		}
		if(cont	>= DAT_IND_MENU_ULTIMO)	cont = DAT_IND_MENU_01;
		if(key[KEY_DOWN])	{	// bajar el indicador
			draw_sprite(screen,	fondo_ind, SP_IND_MENU_X,	pos_ind[seleccion]);
			seleccion++; // bajar
			if(seleccion > 4)	seleccion	=	0; // verificar limites
			blit(screen, fondo_ind,	SP_IND_MENU_X, pos_ind[seleccion], 0,	0, 68, 47);
			cnt_timer++; // permitir el dibujado
			clear_keybuf();
		}
		if(key[KEY_UP])	{	// subir el indicador
			draw_sprite(screen,	fondo_ind, SP_IND_MENU_X,	pos_ind[seleccion]);
			seleccion--; // subir
			if(seleccion < 0)	seleccion	=	4; // verificar limites
			blit(screen, fondo_ind,	SP_IND_MENU_X, pos_ind[seleccion], 0,	0, 68, 47);
			cnt_timer++; // permitir redibujado
			clear_keybuf();
		}

		if(key[KEY_SPACE]	|| key[KEY_ENTER]	|| (key[KEY_ESC] &&	sw_jugando)) { // se ha seleccionado una opci¢n
			if(key[KEY_ESC]	&& sw_jugando) jugar(ID_CONTINUAR);
			else switch(seleccion) {
				case ID_NUEVO:
					jugar(ID_INICIAR); // empezar
				break;
				case ID_CARGAR:
				break;
				case ID_SALVAR:
				break;
				case ID_CREDITOS:
				break;
				case ID_SALIR:
					descargar_datos();
					descargar_programa();
					exit(0);
				break;
			}
			clear(screen);
			set_pallete(dat_bitmap[DAT_MENU_PALETA].dat);
			draw_sprite(screen,	dat_bitmap[DAT_MENU].dat,	0, 0); // Dibujar pantalla del men£
			blit(screen, fondo_ind,	SP_IND_MENU_X, pos_ind[seleccion], 0,	0, 65, 48);
			if(sw_sonido)	play_midi(dat_sonido[DAT_MUSICA_MENU].dat, TRUE);
			install_int_ex(timer_proc, MSEC_TO_TIMER(65));
			cnt_timer++; // permitir el dibujado
			clear_keybuf();
		}
	}	// for(cont...
}


//-------------------------------------------------------------------------------| jugar();
// Empezar a jugar.
// Llamada en: menu()
void jugar(BOOL	juego)
{
	int	i, num;
/*	// LUZ
	RGB_MAP	rgb_tabla;
	COLOR_MAP	color_tabla;
	BITMAP *spr_luz;
*/
	clear(screen);
	if(juego ==	ID_INICIAR)	cargar_juego(0,	""); // comenzar desde el principio

	stop_midi();
	sw_jugando = TRUE; // activar juego
	buffer = create_bitmap(CNT_LIMITE_HORIZONTAL,	CNT_LIMITE_VERTICAL);
	clear(buffer);

	clear_keybuf();
	set_pallete(dat_bitmap[DAT_PALETA].dat);

	b_personaje	=	(BITMAP*)	dat_personaje[DAT_PR_NORTE_QT_01].dat;

	personaje.x	=	SP_POS_ORIGEN_X;
	personaje.y	=	SP_POS_ORIGEN_Y;
	personaje.direccion	=	ID_NORTE;
	personaje.estado = ID_QUIETO;
	personaje.frame	=	DAT_PR_NORTE_QT_01;

	mapa.dir_h = ID_QUIETO;
	mapa.dir_v = ID_QUIETO;
	mapa.sc_h	=	0;
	mapa.sc_v	=	0;

	personaje.destino	=	ID_QUIETO;
	personaje.destino_x	=	personaje.x;
	personaje.destino_y	=	personaje.y;

	mapa.x = 10;
	mapa.y = 15;



/*	create_rgb_table(&rgb_tabla, dat_bitmap[DAT_PALETA].dat, NULL);
	rgb_map	=	&rgb_tabla;
	create_light_table(&color_tabla, dat_bitmap[DAT_PALETA].dat, 0,	0, 0,	NULL);
	color_map	=	&color_tabla;

	spr_luz	=	create_bitmap(640, 480);
	clear(spr_luz);
	num	=	370;
	for(i=0; i < 256;	i++) {
		circlefill(spr_luz,	320, 240,	num, i);
		num-=1;
	}
  */

	install_int_ex(timer_proc, MSEC_TO_TIMER(PENTIUM_100_TIMER));	// reprogramar timer
	cnt_timer	=	-2;	// reiniciar contador del timer



//  spr_luz = create_bitmap(640, 480);
//  for(i=0; i<256; i++) circlefill(spr_luz, 320, 240, 320-i/2, i);


  set_pallete(dat_bitmap[DAT_PALETA].dat);

	for(;;)	{	// ****************  bucle principal del juego  ****************

		// volcar buffer a la pantalla real
    vsync();
		blit(buffer, screen, 0,	0, SP_MAPA_X,	SP_MAPA_Y, CNT_LIMITE_HORIZONTAL,	CNT_LIMITE_VERTICAL);
		// DEBUG: Fluctuaci¢n en la pantalla al hacer el volcado.

		if(cnt_timer >=	1) { // dibujar
			pintar_mapa(buffer); // pintar el mapa

			// dibujar personaje
			b_personaje	=	(BITMAP*)dat_personaje[personaje.frame].dat;
			masked_blit(b_personaje, buffer, 0,	0, personaje.x,	personaje.y, SP_PERSONAJE_ANCHO, SP_PERSONAJE_ALTO);

			//textprintf(buffer, font, 5,	5, 25, "%d  %d        SY%d  Dir %d",	mapa.sc_h, mapa.sc_v,	POS_BLK_PY,	personaje.direccion);

			// Verificar la direcci¢n que tomar  el personaje y mover scroll
			animar_personaje();
			//draw_trans_sprite(buffer, spr_luz, 0, 0); // luz

			draw_sprite(buffer,	dat_bitmap[DAT_MOUSE_1].dat, mouse_x,	mouse_y);	// dibujar mouse

			cnt_timer	=	0; // reiniciar
		}	// timer
    else if(cnt_timer > 1) rut_err(66, "timer");
		if(key[KEY_ESC]) break;	// volver al menu principal
	}	// for(;;...
}


//-------------------------------------------------------------------| animar_perosonaje();
// Anima el personaje y desplaza el scroll
// Llamada en: jugar()
void animar_personaje(void)
{
	if((mouse_b	&	2) &&	(mouse_b & 1)) { // clic izquierdo y derecho al mismo tiempo
		// guardar la posicion dentro del mapa
		personaje.destino_x	=	POS_BLK_X(mouse_x);
		personaje.destino_y	=	POS_BLK_Y(mouse_y);
		// determinar direccion del personaje
		if(personaje.destino_x > POS_BLK_PX
		&& personaje.destino_y < POS_BLK_PY) personaje.destino = ID_NORESTE;
		else if(personaje.destino_x	<	POS_BLK_PX
		&& personaje.destino_y < POS_BLK_PY) personaje.destino = ID_NOROESTE;
		else if(personaje.destino_x	>	POS_BLK_PX
		&& personaje.destino_y > POS_BLK_PY) personaje.destino = ID_SURESTE;
		else if(personaje.destino_x	<	POS_BLK_PX
		&& personaje.destino_y > POS_BLK_PY) personaje.destino = ID_SUROESTE;
		else if(personaje.destino_x	>	POS_BLK_PX)	personaje.destino	=	ID_ESTE;
		else if(personaje.destino_x	<	POS_BLK_PX)	personaje.destino	=	ID_OESTE;
		else if(personaje.destino_y	<	POS_BLK_PY)	personaje.destino	=	ID_NORTE;
		else if(personaje.destino_y	>	POS_BLK_PY)	personaje.destino	=	ID_SUR;
		velocidad	=	ID_CORRIENDO;

		PR_ESTE_CM_ULTIMO	=	DAT_PR_ESTE_CRR_ULTIMO;
		PR_OESTE_CM_ULTIMO = DAT_PR_OESTE_CRR_ULTIMO;
		PR_NORTE_CM_ULTIMO = DAT_PR_NORTE_CRR_ULTIMO;
		PR_SUR_CM_ULTIMO = DAT_PR_SUR_CRR_ULTIMO;
		PR_NE_CM_ULTIMO	=	DAT_PR_NE_CRR_ULTIMO;
		PR_NO_CM_ULTIMO	=	DAT_PR_NO_CRR_ULTIMO;
		PR_SE_CM_ULTIMO	=	DAT_PR_SE_CRR_ULTIMO;
		PR_SO_CM_ULTIMO	=	DAT_PR_SO_CRR_ULTIMO;
		PR_ESTE_CM_00	=	DAT_PR_ESTE_CRR_00;
		PR_OESTE_CM_00 = DAT_PR_OESTE_CRR_00;
		PR_NORTE_CM_00 = DAT_PR_NORTE_CRR_00;
		PR_SUR_CM_00 = DAT_PR_SUR_CRR_00;
		PR_NE_CM_00	=	DAT_PR_NE_CRR_00;
		PR_NO_CM_00	=	DAT_PR_NO_CRR_00;
		PR_SE_CM_00	=	DAT_PR_SE_CRR_00;
		PR_SO_CM_00	=	DAT_PR_SO_CRR_00;
	}
	else if(mouse_b	&	2) { // clic derecho
		// guardar la posicion dentro del mapa
		personaje.destino_x	=	POS_BLK_X(mouse_x);
		personaje.destino_y	=	POS_BLK_Y(mouse_y);
		// determinar direccion del personaje
		if(personaje.destino_x > POS_BLK_PX
		&& personaje.destino_y < POS_BLK_PY) personaje.destino = ID_NORESTE;
		else if(personaje.destino_x	<	POS_BLK_PX
		&& personaje.destino_y < POS_BLK_PY) personaje.destino = ID_NOROESTE;
		else if(personaje.destino_x	>	POS_BLK_PX
		&& personaje.destino_y > POS_BLK_PY) personaje.destino = ID_SURESTE;
		else if(personaje.destino_x	<	POS_BLK_PX
		&& personaje.destino_y > POS_BLK_PY) personaje.destino = ID_SUROESTE;
		else if(personaje.destino_x	>	POS_BLK_PX)	personaje.destino	=	ID_ESTE;
		else if(personaje.destino_x	<	POS_BLK_PX)	personaje.destino	=	ID_OESTE;
		else if(personaje.destino_y	<	POS_BLK_PY)	personaje.destino	=	ID_NORTE;
		else if(personaje.destino_y	>	POS_BLK_PY)	personaje.destino	=	ID_SUR;
		velocidad	=	ID_CAMINANDO;

		PR_ESTE_CM_ULTIMO	=	DAT_PR_ESTE_CM_ULTIMO;
		PR_OESTE_CM_ULTIMO = DAT_PR_OESTE_CM_ULTIMO;
		PR_NORTE_CM_ULTIMO = DAT_PR_NORTE_CM_ULTIMO;
		PR_SUR_CM_ULTIMO = DAT_PR_SUR_CM_ULTIMO;
		PR_NE_CM_ULTIMO	=	DAT_PR_NE_CM_ULTIMO;
		PR_NO_CM_ULTIMO	=	DAT_PR_NO_CM_ULTIMO;
		PR_SE_CM_ULTIMO	=	DAT_PR_SE_CM_ULTIMO;
		PR_SO_CM_ULTIMO	=	DAT_PR_SO_CM_ULTIMO;
		PR_ESTE_CM_00	=	DAT_PR_ESTE_CM_00;
		PR_OESTE_CM_00 = DAT_PR_OESTE_CM_00;
		PR_NORTE_CM_00 = DAT_PR_NORTE_CM_00;
		PR_SUR_CM_00 = DAT_PR_SUR_CM_00;
		PR_NE_CM_00	=	DAT_PR_NE_CM_00;
		PR_NO_CM_00	=	DAT_PR_NO_CM_00;
		PR_SE_CM_00	=	DAT_PR_SE_CM_00;
		PR_SO_CM_00	=	DAT_PR_SO_CM_00;
	}

			if(personaje.destino ==	ID_ESTE) {
				personaje.direccion	=	ID_ESTE;
				if(personaje.destino_x ==	POS_BLK_PX)	{
					personaje.destino	=	ID_QUIETO;
				}
				else { // si no ha llegado al destino
					if(AT_P	== 0)	{
						if(!sw_limite_este &&	personaje.x	== SP_POS_ORIGEN_X)	mapa.sc_h	-= velocidad;
						else personaje.x +=	velocidad;
					}
					else personaje.destino = ID_QUIETO;
					mapa.dir_h = ID_ESTE;

					if(personaje.frame >=	PR_ESTE_CM_00	&& personaje.frame <=	PR_ESTE_CM_ULTIMO) {
						if(personaje.timer >=	CNT_TIMER_PR)	{
							personaje.frame++;
							personaje.timer	=	0; // reiniciar timer
						}
						else personaje.timer++;
						if(personaje.frame > PR_ESTE_CM_ULTIMO)	personaje.frame	=	PR_ESTE_CM_00;
					}
					else {
						personaje.frame	=	PR_ESTE_CM_00;
						personaje.timer	=	0;
					}
				}
			}
			else if(personaje.destino	== ID_OESTE) {
				personaje.direccion	=	ID_OESTE;
				if(personaje.destino_x ==	POS_BLK_PX)	{
					personaje.destino	=	ID_QUIETO;
				}
				else {
					if(AT_P	== 0)	{
						if(!sw_limite_oeste	&& personaje.x ==	SP_POS_ORIGEN_X) mapa.sc_h +=	velocidad;
						else personaje.x -=	velocidad;
					}
					else personaje.destino = ID_QUIETO;
					mapa.dir_h = ID_OESTE;
					if(personaje.frame >=	PR_OESTE_CM_00 &&	personaje.frame	<= PR_OESTE_CM_ULTIMO) {
						if(personaje.timer >=	CNT_TIMER_PR)	{
							personaje.frame++;
							personaje.timer	=	0; // reiniciar timer
						}
						else personaje.timer++;
						if(personaje.frame > PR_OESTE_CM_ULTIMO) personaje.frame = PR_OESTE_CM_00;
					}
					else {
						personaje.frame	=	PR_OESTE_CM_00;
						personaje.timer	=	0;
					}
				}
			}
			else if(personaje.destino	== ID_NORTE) {
				personaje.direccion	=	ID_NORTE;
				if(personaje.destino_y ==	POS_BLK_PY)	{
					personaje.destino	=	ID_QUIETO;
				}
				else {
					if(AT_P	== 0)	{
						if(!sw_limite_norte	&& personaje.y ==	SP_POS_ORIGEN_Y) mapa.sc_v +=	velocidad;
						else personaje.y -=	velocidad;
					}
					else personaje.destino = ID_QUIETO;
					mapa.dir_v = ID_NORTE;

					if(personaje.frame >=	PR_NORTE_CM_00 &&	personaje.frame	<= PR_NORTE_CM_ULTIMO) {
						if(personaje.timer >=	CNT_TIMER_PR)	{
							personaje.frame++;
							personaje.timer	=	0; // reiniciar timer
						}
						else personaje.timer++;
						if(personaje.frame > PR_NORTE_CM_ULTIMO) personaje.frame = PR_NORTE_CM_00;
					}
					else {
						personaje.frame	=	PR_NORTE_CM_00;
						personaje.timer	=	0;
					}
				}
			}
			else if(personaje.destino	== ID_SUR) {
				personaje.direccion	=	ID_SUR;
				if(personaje.destino_y ==	POS_BLK_PY)	{
					personaje.destino	=	ID_QUIETO;
				}
				else {
					if(AT_P	== 0)	{
						if(!sw_limite_sur	&& personaje.y ==	SP_POS_ORIGEN_Y) mapa.sc_v -=	velocidad;
						else personaje.y +=	velocidad;
					}
					else personaje.destino = ID_QUIETO;
					mapa.dir_v = ID_SUR;
					if(personaje.frame >=	PR_SUR_CM_00 &&	personaje.frame	<= PR_SUR_CM_ULTIMO) {
						if(personaje.timer >=	CNT_TIMER_PR)	{
							personaje.frame++;
							personaje.timer	=	0; // reiniciar timer
						}
						else personaje.timer++;
						if(personaje.frame > PR_SUR_CM_ULTIMO) personaje.frame = PR_SUR_CM_00;
					}
					else {
						personaje.frame	=	PR_SUR_CM_00;
						personaje.timer	=	0;
					}
				}
			}
			else if(personaje.destino	== ID_NORESTE) {
				personaje.direccion	=	ID_NORESTE;
				if(personaje.frame >=	PR_NE_CM_00	&& personaje.frame <=	PR_NE_CM_ULTIMO) {
					if(personaje.timer >=	CNT_TIMER_PR)	{
						personaje.frame++;
						personaje.timer	=	0; // reiniciar timer
					}
					else personaje.timer++;
					if(personaje.frame > PR_NE_CM_ULTIMO)	personaje.frame	=	PR_NE_CM_00;
				}
				else {
					personaje.frame	=	PR_NE_CM_00;
					personaje.timer	=	0;
				}
				if(personaje.destino_y !=	POS_BLK_PY)	{
					if(!sw_limite_norte	&& personaje.y ==	SP_POS_ORIGEN_Y) mapa.sc_v +=	velocidad;
					else personaje.y -=	velocidad;
					mapa.dir_v = ID_NORTE;
				}
				else personaje.destino = ID_ESTE;

				if(personaje.destino_x !=	POS_BLK_PX)	{
					mapa.dir_h = ID_ESTE;
					if(!sw_limite_este &&	personaje.x	== SP_POS_ORIGEN_X)	mapa.sc_h	-= velocidad;
					else personaje.x +=	velocidad;
				}
				else personaje.destino = ID_NORTE;
			}
			else if(personaje.destino	== ID_NOROESTE)	{
				personaje.direccion	=	ID_NOROESTE;
				if(personaje.frame >=	PR_NO_CM_00	&& personaje.frame <=	PR_NO_CM_ULTIMO) {
					if(personaje.timer >=	CNT_TIMER_PR)	{
						personaje.frame++;
						personaje.timer	=	0; // reiniciar timer
					}
					else personaje.timer++;
					if(personaje.frame > PR_NO_CM_ULTIMO)	personaje.frame	=	PR_NO_CM_00;
				}
				else {
					personaje.frame	=	PR_NO_CM_00;
					personaje.timer	=	0;
				}
				if(personaje.destino_y !=	POS_BLK_PY)	{
					if(!sw_limite_norte	&& personaje.y ==	SP_POS_ORIGEN_Y) mapa.sc_v +=	velocidad;
					else personaje.y -=	velocidad;
					mapa.dir_v = ID_NORTE;
				}
				else personaje.destino = ID_OESTE;

				if(personaje.destino_x !=	POS_BLK_PX)	{
					if(!sw_limite_oeste	&& personaje.x ==	SP_POS_ORIGEN_X) mapa.sc_h +=	velocidad;
					else personaje.x -=	velocidad;
					mapa.dir_h = ID_OESTE;
				}
				else personaje.destino = ID_NORTE;
			}
			else if(personaje.destino	== ID_SURESTE) {
				personaje.direccion	=	ID_SURESTE;
				if(personaje.frame >=	PR_SE_CM_00	&& personaje.frame <=	PR_SE_CM_ULTIMO) {
					if(personaje.timer >=	CNT_TIMER_PR)	{
						personaje.frame++;
						personaje.timer	=	0; // reiniciar timer
					}
					else personaje.timer++;
					if(personaje.frame > PR_SE_CM_ULTIMO)	personaje.frame	=	PR_SE_CM_00;
				}
				else {
					personaje.frame	=	PR_SE_CM_00;
					personaje.timer	=	0;
				}
				if(personaje.destino_y !=	POS_BLK_PY)	{
					if(!sw_limite_sur	&& personaje.y ==	SP_POS_ORIGEN_Y) mapa.sc_v -=	velocidad;
					else personaje.y +=	velocidad;
					mapa.dir_v = ID_SUR;
				}
				else personaje.destino = ID_ESTE;

				if(personaje.destino_x !=	POS_BLK_PX)	{
					if(!sw_limite_este &&	personaje.x	== SP_POS_ORIGEN_X)	mapa.sc_h	-= velocidad;
					else personaje.x +=	velocidad;
					mapa.dir_h = ID_ESTE;
				}
				else personaje.destino = ID_SUR;
			}
			else if(personaje.destino	== ID_SUROESTE)	{
				personaje.direccion	=	ID_SUROESTE;
				if(personaje.frame >=	PR_SO_CM_00	&& personaje.frame <=	PR_SO_CM_ULTIMO) {
					if(personaje.timer >=	CNT_TIMER_PR)	{
						personaje.frame++;
						personaje.timer	=	0; // reiniciar timer
					}
					else personaje.timer++;
					if(personaje.frame > PR_SO_CM_ULTIMO)	personaje.frame	=	PR_SO_CM_00;
				}
				else {
					personaje.frame	=	PR_SO_CM_00;
					personaje.timer	=	0;
				}
				if(personaje.destino_y !=	POS_BLK_PY)	{
					if(!sw_limite_sur	&& personaje.y ==	SP_POS_ORIGEN_Y) mapa.sc_v -=	velocidad;
					else personaje.y +=	velocidad;
					mapa.dir_v = ID_SUR;
				}
				else personaje.destino = ID_OESTE;

				if(personaje.destino_x !=	POS_BLK_PX)	{
					if(!sw_limite_oeste	&& personaje.x ==	SP_POS_ORIGEN_X) mapa.sc_h +=	velocidad;
					else personaje.x -=	velocidad;
					mapa.dir_h = ID_OESTE;
				}
				else personaje.destino = ID_SUR;
			}

			// verificar si ha llegado al destino
			if(personaje.destino_x ==	POS_BLK_PX &&	personaje.destino_y	== POS_BLK_PY) {
				personaje.destino	=	ID_QUIETO;
			}
			// animar personaje quieto
			if(personaje.destino ==	ID_QUIETO) {
				if(personaje.direccion ==	ID_ESTE) {
					if(personaje.frame >=	DAT_PR_ESTE_QT_00	&& personaje.frame <=	DAT_PR_ESTE_QT_ULTIMO) {
						if(personaje.timer >=	CNT_TIMER_PR)	{
							personaje.frame++;
							personaje.timer	=	0; // reiniciar timer
						}
						else personaje.timer++;
						if(personaje.frame > DAT_PR_ESTE_QT_ULTIMO)	personaje.frame	=	DAT_PR_ESTE_QT_00;
					}
					else {
						personaje.frame	=	DAT_PR_ESTE_QT_00;
						personaje.timer	=	0;
					}
				}
				if(personaje.direccion ==	ID_OESTE)	{
					if(personaje.frame >=	DAT_PR_OESTE_QT_00 &&	personaje.frame	<= DAT_PR_OESTE_QT_ULTIMO) {
						if(personaje.timer >=	CNT_TIMER_PR)	{
							personaje.frame++;
							personaje.timer	=	0; // reiniciar timer
						}
						else personaje.timer++;
						if(personaje.frame > DAT_PR_OESTE_QT_ULTIMO) personaje.frame = DAT_PR_OESTE_QT_00;
					}
					else {
						personaje.frame	=	DAT_PR_OESTE_QT_00;
						personaje.timer	=	0;
					}
				}
				if(personaje.direccion ==	ID_NORTE)	{
					if(personaje.frame >=	DAT_PR_NORTE_QT_00 &&	personaje.frame	<= DAT_PR_NORTE_QT_ULTIMO) {
						if(personaje.timer >=	CNT_TIMER_PR)	{
							personaje.frame++;
							personaje.timer	=	0; // reiniciar timer
						}
						else personaje.timer++;
						if(personaje.frame > DAT_PR_NORTE_QT_ULTIMO) personaje.frame = DAT_PR_NORTE_QT_00;
					}
					else {
						personaje.frame	=	DAT_PR_NORTE_QT_00;
						personaje.timer	=	0;
					}
				}
				if(personaje.direccion ==	ID_SUR)	{
					if(personaje.frame >=	DAT_PR_SUR_QT_00 &&	personaje.frame	<= DAT_PR_SUR_QT_ULTIMO) {
						if(personaje.timer >=	CNT_TIMER_PR)	{
							personaje.frame++;
							personaje.timer	=	0; // reiniciar timer
						}
						else personaje.timer++;
						if(personaje.frame > DAT_PR_SUR_QT_ULTIMO) personaje.frame = DAT_PR_SUR_QT_00;
					}
					else {
						personaje.frame	=	DAT_PR_SUR_QT_00;
						personaje.timer	=	0;
					}
				}
				if(personaje.direccion ==	ID_NORESTE)	{
					if(personaje.frame >=	DAT_PR_NE_QT_00	&& personaje.frame <=	DAT_PR_NE_QT_ULTIMO) {
						if(personaje.timer >=	CNT_TIMER_PR)	{
							personaje.frame++;
							personaje.timer	=	0; // reiniciar timer
						}
						else personaje.timer++;
						if(personaje.frame > DAT_PR_NE_QT_ULTIMO)	personaje.frame	=	DAT_PR_NE_QT_00;
					}
					else {
						personaje.frame	=	DAT_PR_NE_QT_00;
						personaje.timer	=	0;
					}
				}
				if(personaje.direccion ==	ID_NOROESTE) {
					if(personaje.frame >=	DAT_PR_NO_QT_00	&& personaje.frame <=	DAT_PR_NO_QT_ULTIMO) {
						if(personaje.timer >=	CNT_TIMER_PR)	{
							personaje.frame++;
							personaje.timer	=	0; // reiniciar timer
						}
						else personaje.timer++;
						if(personaje.frame > DAT_PR_NO_QT_ULTIMO)	personaje.frame	=	DAT_PR_NO_QT_00;
					}
					else {
						personaje.frame	=	DAT_PR_NO_QT_00;
						personaje.timer	=	0;
					}
				}
				if(personaje.direccion ==	ID_SURESTE)	{
					if(personaje.frame >=	DAT_PR_SE_QT_00	&& personaje.frame <=	DAT_PR_SE_QT_ULTIMO) {
						if(personaje.timer >=	CNT_TIMER_PR)	{
							personaje.frame++;
							personaje.timer	=	0; // reiniciar timer
						}
						else personaje.timer++;
						if(personaje.frame > DAT_PR_SE_QT_ULTIMO)	personaje.frame	=	DAT_PR_SE_QT_00;
					}
					else {
						personaje.frame	=	DAT_PR_SE_QT_00;
						personaje.timer	=	0;
					}
				}
				if(personaje.direccion ==	ID_SUROESTE) {
					if(personaje.frame >=	DAT_PR_SO_QT_00	&& personaje.frame <=	DAT_PR_SO_QT_ULTIMO) {
						if(personaje.timer >=	CNT_TIMER_PR)	{
							personaje.frame++;
							personaje.timer	=	0; // reiniciar timer
						}
						else personaje.timer++;
						if(personaje.frame > DAT_PR_SO_QT_ULTIMO)	personaje.frame	=	DAT_PR_SO_QT_00;
					}
					else {
						personaje.frame	=	DAT_PR_SO_QT_00;
						personaje.timer	=	0;
					}
				}
			}

}


//-------------------------------------------------------------------------| pintar_mapa();
// Pinta el mapa en la posicion actual
// Llamada en: jugar()
void pintar_mapa(BITMAP	*buffer)
{
	int	x, y,	num	=	0;

	sw_limite_este = FALSE;
	sw_limite_oeste	=	FALSE;
	sw_limite_norte	=	FALSE;
	sw_limite_sur	=	FALSE;

	if(mapa.dir_h	== ID_ESTE &&	mapa.sc_h	<= -SP_ANCHO_BLOQUE) { // incrementar posicion
		mapa.x++;
		mapa.sc_h	=	0;
	}
	if((mapa.x + CNT_BLOQUES_HORIZONTALES) >=	(mapa.ancho	-	1))	{	// limite este
		mapa.x = mapa.ancho	-	CNT_BLOQUES_HORIZONTALES - 2;
		mapa.sc_h	=	-SP_ANCHO_BLOQUE;
		sw_limite_este = TRUE;
	}
	if(mapa.dir_h	== ID_OESTE	&& mapa.sc_h >=	0) { // incrementar posicion
		mapa.x--;
		mapa.sc_h	=	-SP_ANCHO_BLOQUE;
	}
	if(mapa.x	<= 0)	{	// limite oeste
		mapa.x = 1;
		mapa.sc_h	=	0;
		sw_limite_oeste	=	TRUE;
	}
	if(mapa.dir_v	== ID_NORTE	&& mapa.sc_v >=	0) { // incrementar posicion
		mapa.y--;
		mapa.sc_v	=	-SP_ALTO_BLOQUE;
	}
	if(mapa.y	<= 0)	{	// limite norte
		mapa.y = 1;
		mapa.sc_v	=	0;
		sw_limite_norte	=	TRUE;
	}
	if(mapa.dir_v	== ID_SUR	&& mapa.sc_v <=	-SP_ALTO_BLOQUE) { // incrementar posicion
		mapa.y++;
		mapa.sc_v	=	0;
	}
	if((mapa.y + CNT_BLOQUES_VERTICALES) >=	(mapa.alto - 1)) { // limite sur
		mapa.y = mapa.alto - CNT_BLOQUES_VERTICALES	-	2;
		mapa.sc_v	=	-SP_ALTO_BLOQUE;
		sw_limite_sur	=	TRUE;
	}





	num	+= mapa.alto * (mapa.x - 1)	+	(mapa.y	-	1);	// avanzar a la posicion actual
	// pintar el mapa
	for(x	=	0; x < CNT_BLOQUES_HORIZONTALES	+	2; x++)	{
		for(y	=	0; y < CNT_BLOQUES_VERTICALES	+	2; y++)	{
			blit(mapa.blk[mapa.mapa[num]], buffer, 0,	0, mapa.sc_h + (x	*	SP_ANCHO_BLOQUE) + SP_MAPA_X - SP_ANCHO_BLOQUE,	mapa.sc_v	+	(y * SP_ALTO_BLOQUE) + SP_MAPA_Y - SP_ALTO_BLOQUE, SP_ANCHO_BLOQUE,	SP_ALTO_BLOQUE);
			num++;
		}
		num	+= mapa.alto - (CNT_BLOQUES_VERTICALES + 2);
	}
}


//------------------------------------------------------------------------| cargar_juego();
// Carga el archivo MAP especificado por los parametros.
// Llamada en: jugar()
void cargar_juego(char tablero,	char nombre_mapa[13])
{
	FILE *archivo; // manejador del archivo
	char nombre_archivo[13]; // nombre del archivo a cargar
	long int contador;

	if(tablero >=	0) strcpy(nombre_archivo,	archivo_mapa[tablero]);	// cargar un nuevo tablero
	else strcpy(nombre_archivo,	nombre_mapa);

	// abrir el archivo
	if((archivo	=	fopen(nombre_archivo,	"rb")) ==	NULL)
		rut_err(ERR_ARCHIVO, nombre_archivo);

	// leer la cabecera: ancho y alto del mapa
	if(fread(&mapa.ancho,	2, 1,	archivo) !=	1)
		rut_err(ERR_ARCHIVO, nombre_archivo);
	if(fread(&mapa.alto, 2,	1, archivo)	!= 1)
		rut_err(ERR_ARCHIVO, nombre_archivo);


	mapa.alto	=	60;
	mapa.ancho = 60;

	// reservar la memoria necesaria

	// DEBUG:
	//        Error al cargar o asignar memoria cuando ya se ha echo antes

	if(mapa.mapa ==	NULL)
	if((mapa.mapa	=	(int*)malloc((long)mapa.ancho	*	mapa.alto))	== NULL)
		rut_err(ERR_MEMORIA, "para cargar el mapa");

	// cargar el mapa
	for(contador = 0;	contador < (mapa.ancho * mapa.alto); contador++) {
		*(mapa.mapa	+	contador)	=	getc(archivo);
		if(ferror(archivo))	rut_err(ERR_ARCHIVO, nombre_archivo);
	}
	// cargar los atributos de los bloques
	for(contador = 0;	contador < CNT_TOTAL_BLOQUES;	contador++)	{
		*(mapa.at	+	contador)	=	getc(archivo);
		if(ferror(archivo))	rut_err(ERR_ARCHIVO, nombre_archivo);
	}
	// DEBUG: Al cargar un mapa guardado por el usuario se debe guardar la posicion del
	//        jugador

	personaje.armadura = 0;
	dat_personaje	=	load_datafile(archivo_pr[personaje.armadura]);
	if(!dat_personaje) rut_err(ERR_ARCHIVO,	STR_ARCHIVO_BITMAP); // verificar

	fclose(archivo);
}


//--------------------------------------------------------------------------| cargar_blk();
// Carga el archivo de bloques y lo guarda en un array de bitmaps
// Llamada en: cargar_datos()
void cargar_blk(void)
{
	FILE *archivo;
	int	num; // bloque actual
	long int contador; // byte dentro de el bloque
	char *puntero;

	// preparar la memoria
	for(num	=	0; num < CNT_TOTAL_BLOQUES;	num++) {
		mapa.blk[num]	=	create_bitmap(SP_ANCHO_BLOQUE, SP_ALTO_BLOQUE);
		clear(mapa.blk[num]);
	}

	if((archivo	=	fopen(STR_ARCHIVO_BLK, "rb"))	== NULL) // abrir el archivo en modo binario
		rut_err(ERR_ARCHIVO, STR_ARCHIVO_BLK);

	// cargar los bloques
	contador = 0;
	for(num	=	0; num < CNT_TOTAL_BLOQUES;	contador++)	{
		puntero	=	mapa.blk[num]	-> dat;	// direccionar memoria
		*(puntero	+	contador)	=	getc(archivo); // obtener el byte del archivo
		if(ferror(archivo))	rut_err(ERR_ARCHIVO, STR_ARCHIVO_BLK); // verificar
		if(contador	>= (SP_ANCHO_BLOQUE	*	SP_ALTO_BLOQUE)) { // pasar al siguiente bloque
			contador = 0;	// retornar contador
			num++;
		}
	}
	fclose(archivo);
}


//-----------------------------------------------------------------------------| rut_err();
// Manejador de codigos de error.
// Llamada en: inicializar_programa(), cargar_datos()

void rut_err(char	cod, char	mensaje[80])
{
	descargar_programa();

	switch(cod)	{
		case ERR_ARCHIVO:	// posiblemente el archivo no existe o se a alterado su contenido
			 printf("Error al leer el archivo");
		break;

		case ERR_VIDEO:	// error al intentar colocar un modo gr fico
			 printf("No se puede inicializar el modo gr fico");
		break;

		case ERR_MEMORIA:	// No se logro obtener la memoria con malloc()
			 printf("Memoria insuficiente");
		break;

		case ERR_MOUSE:
			 printf("No se encontr¢ el controlador del mouse");
		break;

		default: // error personalizado
			printf("Error de ejecuci¢n #%d", cod);
		break;
	}

	printf(" %s.\n", mensaje); // imprimir mensaje adicional

	exit(cod);
}
