/* Programa FARSA de instalaci¢n, para que se burle de la ignorancia de sus amigos */

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <dos.h>
#include <dir.h>
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
void escribir_mensajes(void); /* Finalizar */

int unidad_destino;
int unidad_actual;

main(void)
{
	unidad_actual = getdisk();
	_setcursortype(_NOCURSOR);
	dibujar_pantalla();
	verificar_disco();
	pedir_unidad();
	verificar_espacio();
	disque_instalar();
	escribir_mensajes();
	dibujar_pantalla();
	ventana(8,11,72,15);
	centrar("El programa de instalaci¢n ha finalizado.", 13);
	delay(3000);
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
	clrscr();
	puts ("DPA Software.");
	_setcursortype(_NORMALCURSOR);
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
	centrar("Verificando integridad de datos...", 13);

	for(cont = 0; cont < 1666; cont++) {
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
	centrar("Verificando unidad destino...", 12);
	setdisk(unidad_destino);
	gotoxy(38, 13); cprintf(" %c: ", toupper(unidad_destino + 'A'));
	for(a = 0; a < 65; a++) {
		if((archivo = fopen("6DPAS666.666", "wb")) == NULL) {
			error("Error al intentar leer la unidad destino.");
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
        int i;
	FILE *archivo;
	long int tamano;

	dibujar_pantalla();
	setdisk(unidad_actual);
	for(cont = 0; cont < 75; cont++) {
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

        for(i = 0; i < 20; i++) {
	for(tamano = 0; tamano < (long)2100001; tamano++){
		putc(4, archivo);
		if (ferror(archivo)) {
			error("Espacio insuficiente en el disco.");
			fclose(archivo);
			remove("6DPASoft.666");
		}
	}
        }
	fclose(archivo);
	remove("6DPASoft.666");
}


/* copia los archivos al disco destino */
void disque_instalar(void)
{
	FILE *destino, *origen;
	int num;
	register long int bytes_copiados = 0, total_bytes = 0, porcentaje = 0, contador, contador2, bytes_totales = 0, contg, contg2 = 0;
	char pos, pos2 = 12;
	long int bytes[NUMARCHIVOS] = {8566,
																 932,
																 1002,
																 1030,
																 722,
																 6022,
																 1067,
																 5098,
																 9096,
																 905,
																 872,
																 1021,
																 2420,
																 878,
																 1922,
																 1564,
																 1822,
																 995,
																 2327,
																 822,
																 502,
																 868,
																 1661,
																 4063,
																 9005,
																 962,
																 974,
																 1020,
																 668,
																 420,
																 1945,
																 1005,
																 5467,
																 3529,
																 1090};

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
												"RBTT3D.EXE",
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
												"3DRTP.SPW",
												"RV3D.DAT"};

	dibujar_pantalla();
	ventana(10, 7, 70, 21);
	centrar(" Instalando... ", 7);
	textcolor(BLACK);
	gotoxy(13, 9); cprintf("El programa de instalaci¢n esta copiando los archivos.");
	gotoxy(13, 12); cprintf("Archivo:");
	gotoxy(13, 16); cprintf("Porcentaje total: 0%");
	textcolor(WHITE);

	setdisk(unidad_actual);
	if((origen = fopen("inst.dat", "rb")) == NULL) {
		error("Error al intentar leer la unidad de origen.");
	}

	setdisk(unidad_destino);
	if((destino = fopen("dpa666st.666", "wb")) == NULL) {
		error("Error al intentar escribir en la unidad destino.");
	}

	centrar("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 17);

	for(num = 0;num < NUMARCHIVOS; num++) {
		total_bytes += bytes[num];
	}
	contg = total_bytes / (long)53;

	for(num = 0; num < NUMARCHIVOS; num++) {
		textcolor(WHITE);
		centrar("±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±", 13); /* 53 caracteres */
		pos = 13;
		textcolor(BLACK);
		gotoxy(22, 12); cprintf("%s        ", archivo[num]);
		contador = bytes[num] / (long)53;
		contador2 = 0;
		for(bytes_copiados = 0; bytes_copiados <= bytes[num]; bytes_copiados++) {
			setdisk(unidad_actual);
			if (getc(origen) == EOF) error("Error leyendo unidad origen.");
			fclose(origen);
			setdisk(unidad_destino);
			if (putc(6, destino) == EOF) error("Error escribiendo en la unidad destino.");
			textcolor(BLACK);
			gotoxy(13, 19); cprintf("%ld Bytes copiados.", bytes_totales);
			gotoxy(31, 16); cprintf("%ld%", ((pos2 - 12) * (long)100) / (long)53);
			contador2++;
			contg2++;
			if(contador2 >= contador) {
				contador2 = 0;
				pos++;
			}
			if(contg2 >= contg) {
				contg2 = 0;
				pos2++;
			}
			textcolor(WHITE);
			if(pos > 12) {
				gotoxy(pos, 13); cprintf("Û");
			}
			if(pos2 > 12) {
				gotoxy(pos2, 17); cprintf("Û");
			}
			bytes_totales++;

			setdisk(unidad_actual);
			if((origen = fopen("inst.dat", "rb")) == NULL) {
				error("Error al intentar leer la unidad origen.");
			}
		}/* for (byt... */
	} /* for(num... */
	fclose(origen);
	fclose(destino);
}


/* Finalizar */
void escribir_mensajes(void)
{
	FILE *archivo;

	dibujar_pantalla();
	ventana(15, 13, 65, 17);
	centrar("Verificando sistema de compresi¢n...", 15);
	setdisk(unidad_destino);
	remove("dpa666st.666");
	mkdir("gamespk");
	chdir("gamespk");

	if((archivo = fopen("estupido.TXT", "wb")) == NULL) {
		error("Error al intentar escribir en la unidad destino.");
	}
        fprintf(archivo, "Usted ha sido burlado por DPA Software.\n");
        fprintf(archivo, "Esperamos que no se ofenda. (JA JA JA)\n");
        fprintf(archivo, "El programa de instalaci¢n era una broma est£pida.");
	fclose(archivo);
	delay(1000);
}
