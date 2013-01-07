/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ                 Archivo de cabecera GRAFICOS.H                       บ
	บ                       1998 DPA Software.                             บ
	ฬออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
	บ                                                                      บ
	บ  Archivo fuente: GRAFICOS.H                                          บ
	บ  Versiขn: 1.0                                                        บ
	บ  Programador: Jairo Alejandro Duarte Avendaคo.                       บ
	บ  Tipo: Archivo de cabecera con prototipos de funciones, para         บ
	บ    trabajar con el modo gr fico, rutinas para tratar con mapas de    บ
	บ    bloques y otras utilidades m s.                                   บ
	บ  Compilador: Borland C++ 3.1.                                        บ
	บ  Dependencias: Requiere el archivo cabecera DPALIB.H.                บ
	บ  Caracteristicas: Proporciona el control de las principales          บ
	บ    funciones gr ficas como inicalizar el modo 13H y dibujar sprites  บ
	บ    mapas de bloques. Tambin contiene funciones para dibujar con     บ
	บ    doble buffer.                                                     บ
	บ                                                                      บ
	ฬออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
	บ  DPA Software 1997.                                                  บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/


#ifndef __DPA_GRAFICOS__ /* protecciขn contra recompilaciขn */
#define __DPA_GRAFICOS__

#include "dpalib.h"

#define Activar_PV 		  Pantalla_Virtual = CIERTO
#define Desactivar_PV   Pantalla_Virtual = FALSO
#define Liberar_Sprite(sprite)  farfree(sprite)

#pragma warn -eff


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ                    DECLARACION DE DATOS GLOBALES                     บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

int resolucion_horizontal = 0;
int resolucion_vertical = 0;
BYTE huge *pantalla_virtual = NULL;
BOOL Pantalla_Virtual = FALSO;


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ                      DECLARACION DE FUNCIONES                        บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void Inicializar_320x200X(void);
void Restaurar_Modo(void);
BOOL Cargar_Sprite(char *nombre_archivo, s_SPRITE *destino);
BOOL Cargar_Mostrar_Sprite_Comprimido(char *nombre_archivo, int coor_x, int coor_y);
void Mostrar_Sprite_Plano(s_SPRITE *sp);
BOOL Cargar_Paleta(char *nombre_archivo);
void Mostrar_Sprite_Mascara(s_SPRITE *sp, int mascara);
BOOL Oscurecer_Paleta(int demora, int fin_gama);
BOOL Oscurecer_Gama_Paleta(int demora, BOOL rojo_ok, BOOL verde_ok, BOOL azul_ok, int fin_gama);
BOOL Aclarar_Paleta(int demora, int fin_gama);
BOOL Aclarar_Gama_Paleta(int demora, BOOL rojo_ok, BOOL verde_ok, BOOL azul_ok, int fin_gama);
void Desvanecer_Pantalla(int color, unsigned int numero_pixels, int demora);
BOOL Cargar_Sprite_Enlazado(char *nombre_archivo, s_SPRITE_SPE *destino);
BOOL Mostrar_Sprite_Enlazado_Mascara(s_SPRITE_SPE *sp, int numero_sprite, int mascara);
BOOL Mostrar_Sprite_Enlazado(s_SPRITE_SPE *sp, int numero_sprite);
void Esperar_Retrazo_Vertical(void);
//void OutPortb(int port, BYTE dato);
BYTE Obtener_Pixel(int x, int y);
BOOL Pintar_Pixel(int x, int y, BYTE color);
void Borrar_Mem_Video(BYTE color);
BOOL Cargar_Mapa(char *nombre_archivo, s_MAPA *destino);
BOOL Cargar_Bloques(char *nombre_archivo, s_BLK *destino, int long_x, int long_y, int num_bloques);
BOOL Mostrar_Bloque(s_BLK *bloque, int num, int coor_x, int coor_y);
void Mostrar_Mapa(s_MAPA *mapa, s_BLK *bloque);
WORDSHORT Obtener_Bloque_Sprite(s_BLK *bloque, s_MAPA *mapa, int x_sprite, int y_sprite);
WORDSHORT Obtener_Posicion_Sprite(s_BLK *bloque, s_MAPA *mapa, int x_sprite, int y_sprite);
BOOL Cargar_Fuente(char *nombre_archivo, s_FUENTE *destino, char *alfabeto);
void Escribir_Texto_Color(char *texto, s_FUENTE *fuente, int coor_x, int coor_y, int color);
void Escribir_Texto(char *texto, s_FUENTE *fuente, int coor_x, int coor_y);
BOOL Obtener_Sprite_Mapa(s_MAPA *mapa, int num_blk, int *x_destino, int *y_destino, int total_sprites);
BOOL Inicializar_Sprite(s_SPRITE *sprite, int long_x, int long_y);
BOOL Inicializar_Pantalla_Virtual(void);
void Volcar_Pantalla_Virtual(void);
void Scroll_Horizontal_D(s_MAPA *mapa, s_BLK *bloque, int scroll);
void Scroll_Horizontal_I(s_MAPA *mapa, s_BLK *bloque, int scroll);
void Scroll_Vertical_D(s_MAPA *mapa, s_BLK *bloque, int scroll);
void Scroll_Vertical_A(s_MAPA *mapa, s_BLK *bloque, int scroll);
BOOL Mostrar_Bloque_Desp(s_BLK *bloque, s_MAPA * mapa, int num, int coor_x, int coor_y);
BOOL Colision(int sp1x, int  sp1y, int sp1ancho, int sp1alto, int sp2x, int sp2y, int sp2ancho, int sp2alto);
BOOL Colision_Punto(int x, int y, int spx, int spy, int spancho, int spalto);
BOOL Cargar_Sprite_Comprimido(char *nombre_archivo, s_SPRITE_SPC *destino);
BOOL Mostrar_Sprite_Comprimido(s_SPRITE_SPC *sprite, int coor_x, int coor_y, int mascara);
void Mostrar_Sprite_Mapa(s_MAPA *mapa, s_BLK *bloque, s_SPRITE_SPE *sprite, int max_anims, int id_anim, int frame, int dir_sc_x, int dir_sc_y);


/*
	ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
	บ                      DEFINICION DE FUNCIONES                         บ
	ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void Inicializar_320x200X(void)
{
	asm  mov ax , VGA_13h							  	/* inicializamos modo 13h est ndar */
	asm  int VGA_INT

	resolucion_horizontal = 320;
	resolucion_vertical = 200;
}




void Restaurar_Modo(void)
{
	asm	mov ax, MODO_3h
	asm int VGA_INT
}


BOOL Pintar_Pixel(int x, int y, BYTE color)
{
	BYTE huge *p_pantalla;

	if(x >= resolucion_horizontal) return ERROR;
	if(y >= resolucion_vertical) return ERROR;
	if(x < 0) return ERROR;
	if(y < 0) return ERROR;

	if(Pantalla_Virtual) p_pantalla = MK_FP(FP_SEG(pantalla_virtual), FP_OFF(pantalla_virtual) + (y << 8) + (y << 6) + x);
	else p_pantalla = MK_FP(SEG_PANTALLA, OFF_PANTALLA + (y << 8) + (y << 6) + x);

	*(p_pantalla) = color;

	return OK;
}


BYTE Obtener_Pixel(int x, int y)
{
	register unsigned int offs;
	BYTE huge *p_pantalla;

	if(Pantalla_Virtual) p_pantalla = MK_FP(FP_SEG(pantalla_virtual), FP_OFF(pantalla_virtual));
	else p_pantalla = MK_FP(SEG_PANTALLA, OFF_PANTALLA);

	offs = y * resolucion_horizontal + x;
	return *(p_pantalla + offs);
}


BOOL Cargar_Sprite(char *nombre_archivo, s_SPRITE *destino)
{
	FILE *f_archivo;
	int contador;

	if((f_archivo = fopen(nombre_archivo, "rb")) == NULL) return ERROR;

	if(fread(&destino -> long_x, 2, 1, f_archivo) != 1) return ERROR;
	if(fread(&destino -> long_y, 2, 1, f_archivo) != 1) return ERROR;

	destino -> long_x++;
	destino -> long_y++;

	destino -> sprite = (BYTE *) malloc(destino -> long_x * destino -> long_y);
	if(destino -> sprite == NULL) return ERROR;

	for(contador = 0; contador < destino -> long_x * destino -> long_x; contador++) {
		*(destino -> sprite + contador) = getc(f_archivo);
		if(ferror(f_archivo)) return ERROR - 1;
	}
	fclose(f_archivo);
	destino -> pos_x = 0;
	destino -> pos_y = 0;
	return OK;
}


BOOL Cargar_Sprite_Enlazado(char *nombre_archivo, s_SPRITE_SPE *destino)
{
	FILE *f_archivo;
	int contador;
	unsigned int total_bytes;
	BYTE *cabecera[5];

	if((f_archivo = fopen(nombre_archivo, "rb")) == NULL) return ERROR;

	if(fread(cabecera, 1, 3, f_archivo) != 3) return ERROR - 1; /* cabecera (DPA) */
	if(fread(&destino -> total_sprites, 2, 1, f_archivo) != 1) return ERROR - 1;

	for(total_bytes = 0; !feof(f_archivo); total_bytes++) {
		getc(f_archivo);
		if(ferror(f_archivo)) return ERROR;
	}

	if((destino -> sprite = (BYTE huge*)farmalloc(total_bytes)) == NULL) return ERROR;

	rewind(f_archivo);
	if(fread(cabecera, 1, 5, f_archivo) != 5) return ERROR - 1;

	for(contador = 0; !feof(f_archivo); contador++) {
		*(destino -> sprite + contador) = getc(f_archivo);
		if(ferror(f_archivo)) return ERROR - 2;
	}
	fclose(f_archivo);
	destino -> pos_x = 0;
	destino -> pos_y = 0;
	return OK;
}


void Obtener_Imagen(int x_inicial, int y_inicial, int x_final, int y_final, s_SPRITE *destino)
{
	register int x_pant, y_pant;
	BYTE *p_sp;

	p_sp = destino -> sprite;

	destino -> long_x = x_final - x_inicial;
	destino -> long_y = y_final - y_inicial;

	for(y_pant = y_inicial; y_pant < y_inicial + destino -> long_y; y_pant++) {
		for(x_pant = x_inicial; x_pant < x_inicial + destino -> long_x; x_pant++) {
			*(p_sp) = Obtener_Pixel(x_pant, y_pant);
			p_sp++;
		}
	}
	destino -> pos_x = 0;
	destino -> pos_y = 0;
}


BOOL Cargar_Paleta(char *nombre_archivo)
{
	FILE *f_archivo;
	BYTE paleta[768];
	union REGS Regs ;
	struct SREGS sRegs ;

	if((f_archivo = fopen(nombre_archivo, "rb")) == NULL) return ERROR;
	if(fread(paleta, 1, 768, f_archivo) != 768) return ERROR - 1;
	fclose(f_archivo);

	Regs.x.ax = 0x1012 ;
	Regs.x.bx = 0 ;
	Regs.x.cx = 256 ;
	sRegs.es = FP_SEG(paleta) ;
	Regs.x.dx = FP_OFF(paleta) ;
	int86x( 0x10, &Regs, &Regs, &sRegs);
	return OK;
}


BOOL Oscurecer_Paleta(int demora, int fin_gama)
{
	int rojo, verde, azul, gama, color;

	if(fin_gama > 64) return ERROR;

	for(gama = 1; gama <= fin_gama; gama++) {
		for(color = 0; color < 256; color++) {
			outp(OUT_PORT_C_R, color);
			rojo = inp(OUT_PORT_G);
			verde = inp(OUT_PORT_G);
			azul = inp(OUT_PORT_G);

			if(rojo > 0) rojo--;
			if(verde > 0) verde--;
			if(azul > 0) azul--;
			outp(OUT_PORT_C_W, color);
			outp(OUT_PORT_G, rojo);
			outp(OUT_PORT_G, verde);
			outp(OUT_PORT_G, azul);
		}
		delay(demora);
	}
	return OK;
}


BOOL Oscurecer_Gama_Paleta(int demora, BOOL rojo_ok, BOOL verde_ok, BOOL azul_ok, int fin_gama)
{
	int rojo, verde, azul, gama, color;

	if(fin_gama > 64) return ERROR;

	for(gama = 1; gama <= fin_gama; gama++) {
		for(color = 0; color < 256; color++) {
			outp(OUT_PORT_C_R, color);
			rojo = inp(OUT_PORT_G);
			verde = inp(OUT_PORT_G);
			azul = inp(OUT_PORT_G);

			if(rojo_ok) if(rojo > 0) rojo--;
			if(verde_ok) if(verde > 0) verde--;
			if(azul_ok) if(azul > 0) azul--;
			outp(OUT_PORT_C_W, color);
			outp(OUT_PORT_G, rojo);
			outp(OUT_PORT_G, verde);
			outp(OUT_PORT_G, azul);
		}
		delay(demora);
	}
	return OK;
}


BOOL Aclarar_Paleta(int demora, int fin_gama)
{
	int rojo, verde, azul, gama, color;

	if(fin_gama > 64) return ERROR;

	for(gama = 1; gama <= fin_gama; gama++) {
		for(color = 0; color < 256; color++) {
			outp(OUT_PORT_C_R, color);
			rojo = inp(OUT_PORT_G);
			verde = inp(OUT_PORT_G);
			azul = inp(OUT_PORT_G);

			if(rojo < 63) rojo++;
			if(verde < 63) verde++;
			if(azul < 63) azul++;
			outp(OUT_PORT_C_W, color);
			outp(OUT_PORT_G, rojo);
			outp(OUT_PORT_G, verde);
			outp(OUT_PORT_G, azul);
		}
		delay(demora);
	}
	return OK;
}


BOOL Aclarar_Gama_Paleta(int demora, BOOL rojo_ok, BOOL verde_ok, BOOL azul_ok, int fin_gama)
{
	int rojo, verde, azul, gama, color;

	if(fin_gama > 64) return ERROR;

	for(gama = 1; gama <= fin_gama; gama++) {
		for(color = 0; color < 256; color++) {
			outp(OUT_PORT_C_R, color);
			rojo = inp(OUT_PORT_G);
			verde = inp(OUT_PORT_G);
			azul = inp(OUT_PORT_G);

			if(rojo_ok) if(rojo < 63) rojo++;
			if(verde_ok) if(verde < 63) verde++;
			if(azul_ok) if(azul < 63) azul++;
			outp(OUT_PORT_C_W, color);
			outp(OUT_PORT_G, rojo);
			outp(OUT_PORT_G, verde);
			outp(OUT_PORT_G, azul);
		}
		delay(demora);
	}
	return OK;
}


void Desvanecer_Pantalla(int color, unsigned int numero_pixels, int demora)
{
	unsigned int cont;

	for(cont = 0; cont < numero_pixels; cont++) {
		Pintar_Pixel(random(resolucion_horizontal), random(resolucion_vertical), color);
		delay(demora);
	}
}


BOOL Inicializar_Sprite(s_SPRITE *sprite, int long_x, int long_y)
{
	sprite -> sprite = (BYTE *) malloc(long_x * long_y);
	if(sprite -> sprite == NULL) return ERROR;
	sprite -> long_x = long_x;
	sprite -> long_y = long_y;
	return OK;
}


BOOL Cargar_Mostrar_Sprite_Comprimido(char *nombre_archivo, int coor_x, int coor_y)
{
	FILE *f_archivo;
	int long_x, long_y, x_pant, y_pant;
	BYTE tipo_byte, byte, contador;

	if((f_archivo = fopen(nombre_archivo, "rb")) == NULL) return ERROR;

	if(fread(&long_x, 2, 1, f_archivo) != 1) return ERROR - 1;
	if(fread(&long_y, 2, 1, f_archivo) != 1) return ERROR - 1;

	if(long_x + coor_x >= resolucion_horizontal) return ERROR;

	x_pant = coor_x;
	y_pant = coor_y;

	do {
		tipo_byte = getc(f_archivo);
		if(ferror(f_archivo)) return ERROR - 2;

		if(tipo_byte > 192) {
			tipo_byte -= 192;
			byte = getc(f_archivo);
			if(ferror(f_archivo)) return ERROR - 2;
			for(contador = 0; contador < tipo_byte; contador++) {
				Pintar_Pixel(x_pant, y_pant, byte);
				x_pant++;
				if(x_pant - coor_x > long_x) {
					x_pant = coor_x;
					y_pant++;
				}
			}
		}
		else {
			Pintar_Pixel(x_pant, y_pant, tipo_byte);
			x_pant++;
			if(x_pant - coor_x > long_x) {
				x_pant = coor_x;
				y_pant++;
			}
		}
	} while(y_pant < coor_y + long_y);

	fclose(f_archivo);
	return OK;
}



BOOL Cargar_Sprite_Comprimido(char *nombre_archivo, s_SPRITE_SPC *destino)
{
	FILE *f_archivo;
	unsigned int total_bytes;
	int contador;
	BYTE *cabecera[5];

	if((f_archivo = fopen(nombre_archivo, "rb")) == NULL) return ERROR;

	if(fread(&destino -> long_x, 2, 1, f_archivo) != 1) return ERROR - 1;
	if(fread(&destino -> long_y, 2, 1, f_archivo) != 1) return ERROR - 1;

	for(total_bytes = 0; !feof(f_archivo); total_bytes++) {
		getc(f_archivo);
		if(ferror(f_archivo)) return ERROR;
	}

	if((destino -> sprite = (BYTE huge*)farmalloc(total_bytes)) == NULL) return ERROR;

	rewind(f_archivo);
	if(fread(cabecera, 1, 5, f_archivo) != 5) return ERROR - 1;

	for(contador = 0; !feof(f_archivo); contador++) {
		*(destino -> sprite + contador) = getc(f_archivo);
		if(ferror(f_archivo)) return ERROR - 2;
	}

	fclose(f_archivo);
	return OK;
}



BOOL Mostrar_Sprite_Comprimido(s_SPRITE_SPC *sprite, int coor_x, int coor_y, int mascara)
{
	register int x_pant, y_pant, cont = 0;
	BYTE tipo_byte, byte, contador;

	if(sprite -> long_x + coor_x >= resolucion_horizontal) return ERROR;

	x_pant = coor_x;
	y_pant = coor_y;

	do {
		tipo_byte = *(sprite -> sprite + cont);
		cont++;

		if(tipo_byte > 192) {
			tipo_byte -= 192;
			byte = *(sprite -> sprite + cont);
      cont++;
			for(contador = 0; contador < tipo_byte; contador++) {
				if(byte != mascara) Pintar_Pixel(x_pant, y_pant, byte);
				x_pant++;
				if(x_pant - coor_x > sprite -> long_x) {
					x_pant = coor_x;
					y_pant++;
				}
			}
		}
		else {
			if(tipo_byte != mascara) Pintar_Pixel(x_pant, y_pant, tipo_byte);
			x_pant++;
			if(x_pant - coor_x > sprite -> long_x) {
				x_pant = coor_x;
				y_pant++;
			}
		}
	} while(y_pant < coor_y + sprite -> long_y);
	return OK;

}



void Mostrar_Sprite_Plano(s_SPRITE *sp)
{
	int x_pant, y_pant;
	BYTE *p_sp;

	p_sp = sp -> sprite;

	for(y_pant = 0; y_pant < sp -> long_y; y_pant++) {
		for(x_pant = 0; x_pant < sp -> long_x; x_pant++) {
			if(x_pant + sp -> pos_x < resolucion_horizontal) Pintar_Pixel(x_pant + sp -> pos_x, y_pant + sp -> pos_y, *(p_sp));
			p_sp++;
		}
	}
}


void Mostrar_Sprite_Mascara(s_SPRITE *sp, int mascara)
{
	int x_pant, y_pant;
	BYTE *p_sp;

	p_sp = sp -> sprite;

	for(y_pant = 0; y_pant < sp -> long_y; y_pant++) {
		for(x_pant = 0; x_pant < sp -> long_x; x_pant++) {
			if(x_pant + sp -> pos_x < resolucion_horizontal) if(*(p_sp) != mascara) Pintar_Pixel(x_pant + sp -> pos_x, y_pant + sp -> pos_y, *(p_sp));
			p_sp++;
		}
	}
}



BOOL Mostrar_Sprite_Enlazado(s_SPRITE_SPE *sp, int numero_sprite)
{
	int x_pant, y_pant, x_sprite, y_sprite, contador;
	BYTE huge *p_sp;

	p_sp = sp -> sprite;

	if(numero_sprite > sp -> total_sprites) return ERROR;

	for(contador = 0; contador < numero_sprite; contador++) {
		x_sprite=*(p_sp);
		p_sp += 2;
		y_sprite=*(p_sp);
		p_sp += 2;
		p_sp += x_sprite * y_sprite;
	}

	x_sprite=*(p_sp);
	p_sp += 2;
	y_sprite=*(p_sp);
	p_sp += 2;

	for(y_pant = 0; y_pant < y_sprite; y_pant++) {
		for(x_pant = 0; x_pant < x_sprite; x_pant++) {
			if(x_pant + sp -> pos_x < resolucion_horizontal) Pintar_Pixel(x_pant + sp -> pos_x, y_pant + sp -> pos_y, *(p_sp));
			p_sp++;
		}
	}
	return OK;
}


BOOL Mostrar_Sprite_Enlazado_Mascara(s_SPRITE_SPE *sp, int numero_sprite, int mascara)
{
	int x_pant, y_pant, x_sprite, y_sprite, contador;
	BYTE huge *p_sp;

	p_sp = sp -> sprite;

	if(numero_sprite > sp -> total_sprites) return ERROR;

	for(contador = 0; contador < numero_sprite; contador++) {
		x_sprite = *(p_sp);
		p_sp += 2;
		y_sprite=*(p_sp);
		p_sp += 2;
		p_sp += x_sprite * y_sprite;
	}

	x_sprite=*(p_sp);
	p_sp += 2;
	y_sprite=*(p_sp);
	p_sp += 2;

	for(y_pant = 0; y_pant < y_sprite; y_pant++) {
		for(x_pant = 0; x_pant < x_sprite; x_pant++) {
			if(x_pant + sp -> pos_x < resolucion_horizontal) if(*(p_sp) != mascara) Pintar_Pixel(x_pant + sp -> pos_x, y_pant + sp -> pos_y, *(p_sp));
			p_sp++;
		}
	}
	return OK;
}


void Esperar_Retrazo_Vertical(void)
{
	asm mov dx, INPUT_STATUS_1;

	vert:;
	asm {
		in al, dx;
		test al, 8;
		jz vert;
	}
}



void Borrar_Mem_Video(BYTE color)
{
	if(Pantalla_Virtual) _fmemset((BYTE huge*)pantalla_virtual, color, resolucion_horizontal * resolucion_vertical);
	else _fmemset(MK_FP(SEG_PANTALLA, OFF_PANTALLA), color, resolucion_horizontal * resolucion_vertical);
}


BOOL Cargar_Mapa(char *nombre_archivo, s_MAPA *destino)
{
	FILE *f_archivo;
	long int contador;

	if((f_archivo = fopen(nombre_archivo, "rb")) == NULL) return ERROR;

	if(fread(&destino -> long_x, 2, 1, f_archivo) != 1) return ERROR - 1;
	if(fread(&destino -> long_y, 2, 1, f_archivo) != 1) return ERROR - 1;

	if((destino -> mapa = (BYTE far*)farmalloc((long)destino -> long_x * destino -> long_y)) == NULL) return ERROR - 2;

	for(contador = 0; contador < (destino -> long_x * destino -> long_y); contador++) {
		*(destino -> mapa + contador) = getc(f_archivo);
		if(ferror(f_archivo)) return ERROR;
	}
	fclose(f_archivo);
	destino -> x_pant = 0;
	destino -> y_pant = 0;
	destino -> bloques_horizontales = 0;
	destino -> bloques_verticales = 0;
	destino -> x = 0;
	destino -> y = 0;
	destino -> despx = 0;
	destino -> despy = 0;

	return OK;
}


BOOL Cargar_Bloques(char *nombre_archivo, s_BLK *destino, int long_x, int long_y, int num_bloques)
{
	FILE *f_archivo;
	long int contador;

	if((f_archivo = fopen(nombre_archivo, "rb")) == NULL) return ERROR;

	destino -> long_x = long_x;
	destino -> long_y = long_y;
	destino -> bytes_bloque = long_x * long_y;
	destino -> total_bloques = num_bloques;
	if((destino -> bloque = (BYTE huge*)farmalloc((long)(destino -> bytes_bloque) * num_bloques)) == NULL) return ERROR - 2;

	for(contador = 0; contador < (long)(destino -> bytes_bloque) * num_bloques; contador++) {
		*(destino -> bloque + contador) = getc(f_archivo);
		if(ferror(f_archivo)) return ERROR - 1;
	}
	fclose(f_archivo);
	return OK;
}



BOOL Mostrar_Bloque(s_BLK *bloque, int num, int coor_x, int coor_y)
{
	register int x_pant, y_pant;
	BYTE huge *p_sp;

	if(num > bloque -> total_bloques) return ERROR;

	p_sp = bloque -> bloque + ((long)num * (bloque -> bytes_bloque));

	for(y_pant = 0; y_pant < bloque -> long_y; y_pant++) {
		for(x_pant = 0; x_pant < bloque -> long_x; x_pant++) {
			Pintar_Pixel(x_pant + coor_x, y_pant + coor_y, *(p_sp));
			p_sp++;
		}
	}
	return OK;
}


void Mostrar_Mapa(s_MAPA *mapa, s_BLK *bloque)
{
	int x_map, y_map, num = 0;

	num += (mapa -> long_y) * (mapa -> x) + (mapa -> y);

	for(x_map = 0; x_map < (mapa -> bloques_horizontales); x_map++) {
		for(y_map = 0; y_map < (mapa -> bloques_verticales); y_map++) {
			Mostrar_Bloque(bloque, *(mapa -> mapa + num), x_map * bloque -> long_x + (mapa -> x_pant), y_map * bloque -> long_y + (mapa -> y_pant));
			num++;
		}
		num += (mapa -> long_y) - (mapa -> bloques_verticales);
	}
}


WORDSHORT Obtener_Bloque_Sprite(s_BLK *bloque, s_MAPA *mapa, int x_sprite, int y_sprite)
{
	int x, y, num = 0;

	x_sprite -= mapa -> x_pant;
	y_sprite -= mapa -> y_pant + mapa -> despy;

	x = (x_sprite / bloque -> long_x);
	y = (y_sprite / bloque -> long_y);

	if(y_sprite < 0) mapa -> y--;

	num += (mapa -> long_y) * (mapa -> x) + (mapa -> y); /* punto inicial en pantalla */
	num += (mapa -> long_y) * x + y; /* desplazamiento */

	if(y_sprite < 0) mapa -> y++;

	return *(mapa -> mapa + num);
}


WORDSHORT Obtener_Posicion_Sprite(s_BLK *bloque, s_MAPA *mapa, int x_sprite, int y_sprite)
{
	int x, y, num = 0;

	x_sprite -= mapa -> x_pant;
	y_sprite -= mapa -> y_pant;

	x = (x_sprite / bloque -> long_x);
	y = (y_sprite / bloque -> long_y);

	num += (mapa -> long_y) * (mapa -> x) + (mapa -> y);
	num += (mapa -> long_y) * x + y;

	return num;
}


BOOL Cargar_Fuente(char *nombre_archivo, s_FUENTE *destino, char *alfabeto)
{
	FILE *f_archivo;
	unsigned int total_bytes, contador;
	BYTE *cabecera[5];

	if((f_archivo = fopen(nombre_archivo, "rb")) == NULL) return ERROR;

	if(fread(cabecera, 1, 3, f_archivo) != 3) return ERROR - 1; /* cabecera (DPA) */
	if(fread(&destino -> total_caracteres, 2, 1, f_archivo) != 1) return ERROR - 1;

	if((destino -> alfabeto = (BYTE *)malloc(destino -> total_caracteres)) == NULL) return ERROR;
	memcpy(destino -> alfabeto, alfabeto, destino -> total_caracteres);


	for(total_bytes = 0; !feof(f_archivo); total_bytes++) {
		getc(f_archivo);
		if(ferror(f_archivo)) return ERROR;
	}

	if((destino -> fuente = (BYTE huge*)farmalloc(total_bytes)) == NULL) return ERROR;

	rewind(f_archivo);
	if(fread(cabecera, 1, 5, f_archivo) != 5) return ERROR - 1;

	for(contador = 0; !feof(f_archivo); contador++) {
		*(destino -> fuente + contador) = getc(f_archivo);
		if(ferror(f_archivo)) return ERROR - 2;
	}
	fclose(f_archivo);
	return OK;
}


void Escribir_Texto(char *texto, s_FUENTE *fuente, int coor_x, int coor_y)
{
	int contador, cont_texto, x_pant, y_pant, x_sprite, y_sprite, contador2;
	BYTE huge *p_sp;


	for(cont_texto = 0; cont_texto < strlen(texto); cont_texto++) {
		for(contador = 0; contador < fuente -> total_caracteres; contador++) {
			if(*(texto + cont_texto) == *((fuente -> alfabeto) + contador)) {

				p_sp = fuente -> fuente;
				for(contador2 = 0; contador2 < contador; contador2++) {
					x_sprite = *(p_sp);
					p_sp += 2;
					y_sprite = *(p_sp);
					p_sp += 2;
					p_sp += x_sprite * y_sprite;
				}

				x_sprite = *(p_sp);
				p_sp += 2;
				y_sprite = *(p_sp);
				p_sp += 2;

				for(y_pant = 0; y_pant < y_sprite; y_pant++) {
					for(x_pant = 0; x_pant < x_sprite; x_pant++) {
						if(x_pant + coor_x < resolucion_horizontal) if(*(p_sp) != 0) Pintar_Pixel(x_pant + coor_x, y_pant + coor_y, *(p_sp));
						p_sp++;
					}
				}
				coor_x += x_sprite + 1;
			} /* if... */
		} /* for(contador =... */
	}
}


void Escribir_Texto_Color(char *texto, s_FUENTE *fuente, int coor_x, int coor_y, int color)
{
	int contador, cont_texto, x_pant, y_pant, x_sprite, y_sprite, contador2;
	BYTE huge *p_sp;


	for(cont_texto = 0; cont_texto < strlen(texto); cont_texto++) {
		for(contador = 0; contador < fuente -> total_caracteres; contador++) {
			if(*(texto + cont_texto) == *((fuente -> alfabeto) + contador)) {

				p_sp = fuente -> fuente;
				for(contador2 = 0; contador2 < contador; contador2++) {
					x_sprite = *(p_sp);
					p_sp += 2;
					y_sprite=*(p_sp);
					p_sp += 2;
					p_sp += x_sprite * y_sprite;
				}

				x_sprite = *(p_sp);
				p_sp += 2;
				y_sprite=*(p_sp);
				p_sp += 2;

				for(y_pant = 0; y_pant < y_sprite; y_pant++) {
					for(x_pant = 0; x_pant < x_sprite; x_pant++) {
						if(x_pant + coor_x < resolucion_horizontal) if(*(p_sp) != 0) Pintar_Pixel(x_pant + coor_x, y_pant + coor_y, color);
						p_sp++;
					}
				}
				coor_x += x_sprite + 1;
			} /* if... */
		} /* for(contador =... */
	}
}


BOOL Obtener_Sprite_Mapa(s_MAPA *mapa, int num_blk, int *x_destino, int *y_destino, int total_sprites)
{
	int x_map, y_map, num = 0, incremento = 0, sc = 0;
	if(mapa -> despy) sc = 1;

	num += (mapa -> long_y) * (mapa -> x) + (mapa -> y - sc);

	for(x_map = 0; x_map < (mapa -> bloques_horizontales) + 1; x_map++) {
		for(y_map = 0; y_map < (mapa -> bloques_verticales + sc); y_map++) {
			if(*(mapa -> mapa + num) == num_blk) {
				incremento++;
				if(incremento == total_sprites) {
					*x_destino = x_map;
					*y_destino = y_map;
					if(*x_destino < mapa -> bloques_horizontales) return OK;
					else return ERROR;
				}
			}
			num++;
		}
		num += (mapa -> long_y) - (mapa -> bloques_verticales + sc);
	}
	return ERROR;
}



BOOL Inicializar_Pantalla_Virtual(void)
{
	if((pantalla_virtual = (BYTE huge*)farmalloc((long)resolucion_horizontal * resolucion_vertical)) == NULL) return ERROR;
	_fmemset((BYTE huge*)pantalla_virtual, 0, resolucion_horizontal * resolucion_vertical);

	return OK;
}



void Volcar_Pantalla_Virtual(void)
{
	movedata(FP_SEG(pantalla_virtual), FP_OFF(pantalla_virtual), SEG_PANTALLA, OFF_PANTALLA, (long)resolucion_horizontal * resolucion_vertical);
}



BOOL Mostrar_Bloque_Desp(s_BLK *bloque, s_MAPA * mapa, int num, int coor_x, int coor_y)
{
	register int x_pant, y_pant;
	BYTE huge *p_sp;

	if(num > bloque -> total_bloques) return ERROR;

	p_sp = bloque -> bloque + ((long)num * (bloque -> bytes_bloque));

	for(y_pant = 0; y_pant < bloque -> long_y; y_pant++) {
		for(x_pant = 0; x_pant < bloque -> long_x; x_pant++) {
			if(*(p_sp) != 0)
			if((x_pant + coor_x >= mapa -> x_pant) && (x_pant + coor_x <= (mapa -> bloques_horizontales * bloque -> long_x + mapa -> x_pant)))
			if((y_pant + coor_y >= mapa -> y_pant) && (y_pant + coor_y < (mapa -> bloques_verticales * bloque -> long_y + mapa -> y_pant)))
			Pintar_Pixel(x_pant + coor_x, y_pant + coor_y, *(p_sp));
			p_sp++;
		}
	}
	return OK;
}



void Scroll_Horizontal_D(s_MAPA *mapa, s_BLK *bloque, int scroll)
{
	int x_map, y_map, num = 0;

	mapa -> despx += scroll;

	if(mapa -> despx >= bloque -> long_x) {
		mapa -> despx = 0;
		mapa -> x--;
	}

	num += (mapa -> long_y) * (mapa -> x) + (mapa -> y);

	for(x_map = - 1; x_map < (mapa -> bloques_horizontales); x_map++) {
		for(y_map = 0; y_map < (mapa -> bloques_verticales); y_map++) {
			Mostrar_Bloque_Desp(bloque, mapa, *(mapa -> mapa + num), x_map * bloque -> long_x + (mapa -> x_pant) + mapa -> despx, y_map * bloque -> long_y + (mapa -> y_pant));
			num++;
		}
		num += (mapa -> long_y) - (mapa -> bloques_verticales);
	}
}



void Scroll_Horizontal_I(s_MAPA *mapa, s_BLK *bloque, int scroll)
{
	int x_map, y_map, num = 0;

	mapa -> despx -= scroll;
	-(mapa -> despx);

	if(-(mapa -> despx) >= bloque -> long_x) {
		mapa -> despx = 0;
		mapa -> x++;
	}
	num += (mapa -> long_y) * (mapa -> x) + (mapa -> y);

	for(x_map = 0; x_map < (mapa -> bloques_horizontales) + 1; x_map++) {
		for(y_map = 0; y_map < (mapa -> bloques_verticales); y_map++) {
			Mostrar_Bloque_Desp(bloque, mapa, *(mapa -> mapa + num), x_map * bloque -> long_x + (mapa -> x_pant) - (-(mapa -> despx)), y_map * bloque -> long_y + (mapa -> y_pant));
			num++;
		}
		num += (mapa -> long_y) - (mapa -> bloques_verticales);
	}
}



void Scroll_Vertical_D(s_MAPA *mapa, s_BLK *bloque, int scroll)
{
	int x_map, y_map, num = 0;

	mapa -> despy += scroll;

	if(mapa -> despy >= bloque -> long_y) {
		mapa -> despy = 0;
		mapa -> y--;
	}

	mapa -> y--;

	num += (mapa -> long_y) * (mapa -> x) + (mapa -> y);

	for(x_map = 0; x_map < (mapa -> bloques_horizontales); x_map++) {
		for(y_map = -1; y_map < (mapa -> bloques_verticales); y_map++) {
			Mostrar_Bloque_Desp(bloque, mapa, *(mapa -> mapa + num), x_map * bloque -> long_x + (mapa -> x_pant), y_map * bloque -> long_y + (mapa -> y_pant) + mapa -> despy);
			num++;
		}
		num += (mapa -> long_y) - (mapa -> bloques_verticales) - 1;
	}
	mapa -> y++;
}



void Scroll_Vertical_A(s_MAPA *mapa, s_BLK *bloque, int scroll)
{
	int x_map, y_map, num = 0;

	mapa -> despy -= scroll;
	-(mapa -> despy);

	if(-(mapa -> despy) >= bloque -> long_y) {
		mapa -> despy = 0;
		mapa -> y++;
	}

	mapa -> y--;

	num += (mapa -> long_y) * (mapa -> x) + (mapa -> y);

	for(x_map = 0; x_map < (mapa -> bloques_horizontales); x_map++) {
		for(y_map = 0; y_map < (mapa -> bloques_verticales + 1); y_map++) {
			Mostrar_Bloque_Desp(bloque, mapa, *(mapa -> mapa + num), x_map * bloque -> long_x + (mapa -> x_pant), y_map * bloque -> long_y + (mapa -> y_pant) + mapa -> despy);
			num++;
		}
		num += (mapa -> long_y) - (mapa -> bloques_verticales + 1);
	}
	mapa -> y++;
}




BOOL Colision(int sp1x, int  sp1y, int sp1ancho, int sp1alto, int sp2x, int sp2y, int sp2ancho, int sp2alto)
{
	int x, y;

	for(y = sp1y; y < sp1y + sp1alto; y++) {
		for(x = sp1x; x < sp1x + sp1ancho; x++) {
			if(x >= sp2x && y >= sp2y)
			if(x - sp2x <= sp2ancho && y - sp2y < sp2alto) return VERDADERO;
		}
	}
	return FALSO;
}



BOOL Colision_Punto(int x, int y, int spx, int spy, int spancho, int spalto)
{
	if(x >= spx && y >= spy)
	if(x - spx <= spancho && y - spy < spalto) return VERDADERO;
	return FALSO;
}



void Mostrar_Sprite_Mapa(s_MAPA *mapa, s_BLK *bloque, s_SPRITE_SPE *sprite, int max_anims, int id_anim, int frame, int dir_sc_x, int dir_sc_y)
{
	int inc, x, y, rv = resolucion_vertical;

	if(!dir_sc_x && !dir_sc_y);
	else if(mapa -> despy == 0 && !dir_sc_y) dir_sc_y = -1;
	else if(mapa -> despy == 0) dir_sc_y = 0;

	resolucion_vertical = (mapa -> bloques_verticales * (bloque -> long_y)) + mapa -> y_pant;
	for (inc = 1; inc <= max_anims; inc++) {
		if(Obtener_Sprite_Mapa(mapa, id_anim, &x, &y, inc)) {
			sprite -> pos_x = (x - dir_sc_x) * (bloque -> long_x) + mapa -> x_pant + mapa -> despx;
			sprite -> pos_y = (y - dir_sc_y) * (bloque -> long_x) + mapa -> y_pant + mapa -> despy;
			Mostrar_Sprite_Enlazado(sprite, frame);
		}
	}
	resolucion_vertical = rv;
}



#pragma warn +eff

#endif /* __DPA_GRAFICOS__ */

/* Terminado el 26 de Junio de 1998. DPA Software. */
