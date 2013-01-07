#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <dos.h>
#include <ctype.h>
#include <stdlib.h>

#define NUMARCHIVOS 35

void dibujar_pantalla(void); /* Dibujar la pantalla del programa */
void centrar(char *texto, int fila); /* Centrado de texto en la pantalla */
void error(char *texto); /* Muestra un mensaje de error y termina el programa */
void verificar_espacio(void); /* Verifica el espacio disponible en el disco */
void ventana(int x_inicial, int y_inicial, int x_final, int y_final); /* dibujar una ventana */
void verificar_disco(void); /* verifica el disco origen */
void pedir_unidad(void); /* Unidad destino */
void disque_instalar(void); /* copia los archivos al disco destino */

int unidad_destino;
int unidad_actual;

main(void)
{
	unidad_actual = getdisk();
	_setcursortype(_NOCURSOR);
	dibujar_pantalla();
//	verificar_disco();
//	pedir_unidad();
//	verificar_espacio();
	disque_instalar();
	return 0;
}


/* Centrado de texto en la pantalla */
void centrar(char *texto, int fila)
{
	gotoxy(40 - (strlen(texto) / 2), fila );
	cprintf("%s", texto);
}


/* dibujar una ventana */
void ventana(int x_inicial, int y_inicial, int x_final, int y_final)
{
	int a, b;

	textcolor (WHITE);
	textbackground (LIGHTGRAY);
	
	for (a = x_inicial; a < x_final; a++) { /* dibujar ventana */
		for (b = y_inicial; b < y_final; b++) {
			gotoxy (a, b); cprintf (" ");
		}
	}

	for (a = x_inicial + 1; a < x_final; a++) { /* dibujar bordes horizontales */
		gotoxy (a, y_inicial); cprintf ("Ä");
		gotoxy (a, y_final); cprintf ("Ä");
	}

	for (a = y_inicial + 1; a < y_final; a++) { /* bordes verticales */
		gotoxy (x_inicial, a); cprintf ("³");
		gotoxy (x_final, a); cprintf ("³");
	}

	gotoxy (x_inicial, y_inicial); cprintf ("Ú"); /* esquinas */
	gotoxy (x_inicial, y_final); cprintf ("À");
	gotoxy (x_final, y_inicial); cprintf ("¿");
	gotoxy (x_final, y_final); cprintf ("Ù");
}


/* Dibujar la pantalla del programa */
void dibujar_pantalla(void)
{
	textbackground(BLUE); /* fondo azul */
	clrscr();
	textbackground(LIGHTGRAY); /* fondo del titulo */
	textcolor(BLACK);
	centrar("           PROGRAMA DE INSTALACION DEL PAQUETE DE JUEGOS versi¢n 2.0            ", 1);
}


/* Muestra un mensaje de error y termina el programa */
void error(char *texto)
{
	dibujar_pantalla(); /* borrar pantalla */
	ventana(8,11,72,15);
	textcolor(RED);
	centrar(texto, 13);
	getch();
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
	clrscr();
	puts ("DPA Software.");
	_setcursortype(_NORMALCURSOR);
	exit(1);
}


/* verifica el disco origen */
void verificar_disco(void)
{
	FILE *archivo;
	int cont;

	ventana(8,11,72,15);
	centrar("Verificando integridad del disco...", 13);

	for(cont = 0; cont < 16666; cont++) {
		if((archivo = fopen("inst.dat", "rb")) == NULL) {
			error("Error al verificar el disco.");
		}
		getc(archivo);
		fclose(archivo);
	}
	dibujar_pantalla();
}


/* Unidad destino */
void pedir_unidad(void)
{
	int a;
	FILE *archivo;

	ventana(10,10,70,15);
	centrar("Unidad destino:", 12);
	textbackground(BLACK);
	textcolor(LIGHTGRAY);
	centrar("    ", 13);
	gotoxy(39, 13);
	_setcursortype(_NORMALCURSOR);
	unidad_destino = getch();
	_setcursortype(_NOCURSOR);
	gotoxy(39, 13); cprintf("%c:", toupper(unidad_destino));
	delay(200);
	unidad_destino = toupper(unidad_destino) - 'A';
	textcolor(WHITE);
	textbackground(LIGHTGRAY);
	centrar("Verificando unidad_destino destino...", 12);
	setdisk(unidad_destino);
	gotoxy(38, 13); cprintf(" %c: ", toupper(unidad_destino + 'A'));
	for(a = 0; a < 40; a++) {
		if((archivo = fopen("6DPAS666.666", "wt")) == NULL) {
			error("Error al intentar leer la unidad_destino.");
		}
		putc(1, archivo);
		fclose(archivo);
		remove("6DPAS666.666");
	}
	setdisk(unidad_actual);
}


/* Verifica el espacio disponible en el disco */
void verificar_espacio(void)
{
	int cont;
	FILE *archivo;
	long int tamano;

	dibujar_pantalla();
	for(cont = 0; cont < 500; cont++) {
		if((archivo = fopen("inst.dat", "rb")) == NULL) {
			error("Error al leer el disco origen.");
		}
		getc(archivo);
		fclose(archivo);
	}
	ventana(8,10,72,15);
	textcolor(BLACK);
	centrar("El programa de instalaci¢n esta verificando que", 12);
	centrar("haya espacio suficiente en el disco...", 13);

	setdisk(unidad_destino);
	if((archivo = fopen("6DPASoft.666", "wb")) == NULL) {
		error("Error al escribir en el disco destino.");
	}

	for(tamano = 0; tamano < 50000000; tamano++){
		putc(4, archivo);
		if (ferror(archivo)) {
			error("Espacio insuficiente en el disco.");
			fclose(archivo);
			remove("6DPASoft.666");
		}
	}
	fclose(archivo);
	remove("6DPASoft.666");
}


/* copia los archivos al disco destino */
void disque_instalar(void)
{
	int num;
	register long int bytes_copiados = 0, total_bytes = 0, porcentaje = 0, contador, contador2;
	char pos;
	long int bytes[NUMARCHIVOS] = {3000666,
																 352452,
																 7567672,
																 2456069,
																 56722,
																 622,
																 567,
																 5678,
																 1235626,
																 355625,
																 45672,
																 367721,
																 1245620,
																 678678,
																 2456822,
																 344564,
																 457822,
																 4356675,
																 3456627,
																 35622,
																 3456502,
																 1456368,
																 1674427,
																 5678663,
																 1666545,
																 8762,
																 45674,
																 6720,
																 12768,
																 1220,
																 6756345,
																 545,
																 4567,
																 15620,
																 143560};

	char archivo[NUMARCHIVOS][13] = {"DPA.DAT",
												"3DTL.DAT",
												"3DLIBX.DAT",
												"MUSIC1.SND",
												"MUSIC2.SND",
												"MUSIC3.SND",
												"SNDBLSTR.DRV",
												"SND.DRV",
												"ADB.DRV",
												"README.TXT",
												"UTIL.TXT",
												"RBTT3D.C",
												"SOUNDFX.DRV",
												"SOUND.DRV",
												"SOUND.DLD",
												"BKS.DAT",
												"BKM.DAT",
												"CONST.DAT",
												"LIBENM.SPR",
												"OPENL.DAT",
												"ENT3D.DAT",
												"MM3D.COM",
												"INIT.INI",
												"SHED.INI",
												"OMN3D.LNK",
												"DPA.1",
												"WIND.EXE",
												"WIND.INI",
												"RUNING.EXE",
												"DEATH.INI",
												"TRGAME2.EXE",
												"TRGAME2.INI",
												"DEATH.EXE",
												"DPA.2",
												"DPA.3"};

	dibujar_pantalla();
	ventana(10, 7, 70, 20);
	centrar(" Instalando... ", 7);
	textcolor(BLACK);
	gotoxy(13, 9); cprintf("El programa de instalaci¢n esta copiando los archivos.");
	gotoxy(13, 12); cprintf("Archivo:");
	gotoxy(13, 16); cprintf("Porcentaje total: 0%");
	textcolor(WHITE);
	centrar("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 17);

	for (num = 0;num < NUMARCHIVOS; num++) {
		total_bytes += bytes[num];
	}
	for(num = 0; num < NUMARCHIVOS; num++) {
		centrar("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 13); /* 53 caracteres */
		pos = 13;
		textcolor(BLACK);
		gotoxy(22, 12); cprintf("%s        ", archivo[num]);
		contador = bytes[num] / 53;
		contador2 = 0;
		for(bytes_copiados = 0; bytes_copiados <= bytes[num]; bytes_copiados++) {
			contador2++;
			if(contador2 >= contador) {
				contador2 = 0;
				pos++;
			}
			if(pos > 12) {
				gotoxy(pos, 13); cprintf("Û");
			}

		}/* for (byt... */



	} /* for(num... */









}