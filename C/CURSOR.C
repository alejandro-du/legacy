/* PACKMAN 1.0 DPA SOFTWARE */
/* Codigo fuente: Jairo Alejandro Duarte Avenda¤o */
/* 1997 - 1998 */

#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<dos.h>
#include<time.h>

#define IZ 1 /* direcciones */
#define DR 2
#define AR 3
#define AB 4
#define XPANT 40
#define YPANT 23

#define FALSO 0
#define VERDADERO 1

#define PUNTOS_FANTASMA 188 /* puntajes */
#define PUNTOS_GALLETA 6
#define PUNTOS_SUPER 19
#define PUNTOS_ROJA 203
#define PUNTOS_AZUL 231

#define DURACION_SUPER 80 /* tiempo a esperar por los especiales */
#define DURACION_FRUTA 55

#define XFRUTA 21 /* posici¢n inicial del packman */
#define YFRUTA 17
#define TOTAL_TABLEROS 3
#define	TOTALCLAVES 1
#define LONGITUD (22 * 10) + (10 * 10) + (1 * 10) + 1
#define ULTIMO_RCD 22 + 10 + 1

int inkey(void); /* presionar una tecla */
void salir(void); /* sale del juego */
void record(long int puntos, char tablero); /* guarda de record */
void mostrar_records(void); /* muestra la lista de records */
int presentacion(void);
void celebrar(void);

main(void)
{
	register long int num, puntos;
	char mapa[4000], tecla, fondo, fondo_enm[5], vidas, muerte, super, color_enm, inc_enm, opcion = 0;
	FILE *archivo;
	register unsigned char x, y, direccion = 0, direccion_enm[5], tempx, tempy, tempd, direccion_enmt[5];
	unsigned char xenm[5], yenm[5], xenmt[5], yenmt[5], tiempo_super, tiempo_fruta, sonido;
	int galletas, total_galletas, num2;
	char tablero[TOTAL_TABLEROS][12] = {"T1.MAP", "T2.MAP", "T3.MAP"}, indice = 0, fin, demo = VERDADERO;

	textmode(C40); /* 40 columnas * 25 filas */
	_wscroll = 0; /* desactivar el scroll */
	_setcursortype(_NOCURSOR); /* ocultar el cursor parpadeante */


	/* empezar un nuevo tablero */
	do {

	if(demo) demo = presentacion();

	if((archivo = fopen(tablero[indice], "rb")) == NULL) { /* abrir el archivo */
		textmode(C80);
		puts ("No se puede abrir el archivo mapa.");
		return 1;
	}

	/* preparar la pantalla */
	clrscr();
	/* verificar los 4 primeros bytes de ancho y alto */
	if(fread(&num2, 1, 2, archivo) != 2) {
		textmode(C80);
		puts ("Error leyendo el archivo mapa.");
		return 1;
	}
	if(num2 != XPANT) {
		textmode(C80);
		puts ("Error verificando el archivo mapa.");
		return 1;
	}
	if(fread(&num2, 1, 2, archivo) != 2) {
		textmode(C80);
		puts ("Error leyendo el archivo mapa.");
		return 1;
	}
	if(num2 != YPANT) {
		textmode(C80);
		puts ("Error verificando el archivo mapa.");
		return 1;
	}

	for(num = 0; num < 4000; num++) mapa[num] = getc(archivo); /* cargar el mapa en memoria */
	fclose(archivo);

	/* inicializar */
	total_galletas = 0;
	fin = FALSO;
	num = 0;
	vidas = 5;
	puntos = 0;

	/* mostrar el mapa en la pantalla */
	for(x = 1; x <= XPANT; x++) {
		for(y = 1; y <= YPANT; y++) {
			gotoxy(x, y);
			textcolor(LIGHTGRAY);
			if(*(mapa + num) == 1) {
				cprintf("Û");
			}
			else if(*(mapa + num) == 0) {
				cprintf("ú");
				total_galletas++;
			}
			else if(*(mapa + num) == 2) {
				textcolor(LIGHTGRAY);
				cprintf("+");
				total_galletas++;
			}
			else if(*(mapa + num) == 3) {
				textcolor(BLUE);
				cprintf("Û");
			}
			else if(*(mapa + num) == 4) {
				textcolor(RED);
				cprintf("Û");
			}
			else if(*(mapa + num) == 5) {
				textcolor(YELLOW);
				cprintf("Û");
			}
			else if(*(mapa + num) == 6) {
				textcolor(GREEN);
				cprintf("Û");
			}
			else if(*(mapa + num) == 7) {
				cprintf("°");
			}
			num++;
		} /* for... */
	}
	/* preparar el texto de la pantalla */
	textcolor(CYAN | BLINK);
	gotoxy(5, YPANT + 2);
	cprintf("Listo!");
	delay(700); /* esperar un momento */
	textcolor(LIGHTGRAY);
	gotoxy(1, YPANT + 2);
	cprintf("Puntos:0       Galletas:0    Vidas: %c%c%c%c", 2, 2, 2, 2);
	randomize();

	galletas = 1;
	do { /* empezar una nueva vida del packman */
	color_enm = MAGENTA;
	muerte = FALSO;
	vidas--; /* restar una vida */
	sonido = 0;
	super = FALSO; /* desabilitar posible especial (super) */
	tiempo_fruta = FALSO; /* desabilitar posible especial (fruta) */
	gotoxy(XFRUTA, YFRUTA); cprintf(" "); /* borrar posibles frutas */
	inc_enm = 1; /* velocidad o incremento del enemigo */
	gotoxy(36 + vidas, YPANT + 2); cprintf(" "); /* borrar una cara */
	x = XFRUTA; y = YFRUTA; /* inicializar el packman */
	xenm[0] = XPANT / 2 - 4; yenm[0] = YPANT / 2; /* inicializar las posiciones de 5 enemigos */
	xenm[1] = XPANT / 2 - 2; yenm[1] = YPANT / 2;
	xenm[2] = XPANT / 2; yenm[2] = YPANT / 2;
	xenm[3] = XPANT / 2 - 2; yenm[3] = YPANT / 2 + 1;
	xenm[4] = XPANT / 2 + 1; yenm[4] = YPANT / 2 + 1;

	if(demo) direccion = IZ;
	direccion_enm[0] = random(4) + 1; /* inicializar 5 direcciones */
	direccion_enm[1] = random(4) + 1;
	direccion_enm[2] = random(4) + 1;
	direccion_enm[3] = random(4) + 1;
	direccion_enm[4] = random(4) + 1;

	fondo_enm[0] = ' '; /* fondo vacio para cada enemigo */
	fondo_enm[1] = ' ';
	fondo_enm[2] = ' ';
	fondo_enm[3] = ' ';
	fondo_enm[4] = ' ';
	for(num2 = 100; num2 < 500; num2++) { /* sonido de inicio */
		sound(num2);
		delay(3);
	}
	nosound();
	if(!demo) tecla = getch(); /* esperar pulsaci¢n para iniciar */
	do { /* un ciclo por movimiento */
		if(demo) {
			if(kbhit()) {
					vidas = 0;
				muerte = VERDADERO;
				puntos = -1;
				break;
			}
		}
		if(!demo) tecla = inkey();
		gotoxy(x, y); cprintf(" "); /* borrar packman */
		textcolor(LIGHTGRAY);
		for (num = 0; num < 5; num++) { /* borrar 5 fantasmas */
			gotoxy(xenm[num], yenm[num]);
			cprintf("%c", fondo_enm[num]);
			/* obtener fondo para evitar restar una galleta */
			gettext(XPANT / 2, YPANT /2, XPANT /2, YPANT/2, &num2);
			if(num2 == 'ú' || num2 == '+') galletas++;
		}
		tempd = direccion; /* temporal de la direcci¢n del packman por si no hay vacio */

		if (!demo) switch(tecla) {
			case 75: /* izqierda */
				direccion = IZ;
			break;

			case 77: /* derecha */
				direccion = DR;
			break;

			case 72: /* arriba */
				direccion = AR;
			break;

			case 80: /* abajo */
				direccion = AB;
			break;
		} /* switch(tecla...*/

		tempx = x; /* temporales de posici¢n */
		tempy = y;
		switch(direccion) { /* mover el packman */
			case IZ:
				x--;
			break;

			case DR:
				x++;
			break;

			case AR:
				y--;
			break;

			case AB:
				y++;
			break;
		} /* switch(direcc... */
		for (num = 0; num < 5; num++) { /* revisar si se han estrellado */
			if(x == xenm[num]) {
				if(y == yenm[num]) { /* si se encuentra con un enemigo */
					if(super) { /* revisar si la super est  activa */
						puntos += PUNTOS_FANTASMA;
						textcolor(GREEN);
						gotoxy(8, YPANT + 2);
						cprintf("%ld", puntos);
						xenm[num] = XPANT / 2;
						yenm[num] = YPANT / 2;
						for(num2 = 466; num2 < 500; num2++) { /* sonido de comer enemigos */
							sound(num2);
							delay(1);
						}
					}
					else muerte = VERDADERO;
				}
			} /* if(x... */

		} /* for... */
		for (num = 0; num < 5; num++) { /* temporales de los enemigos */
			xenmt[num] = xenm[num];	yenmt[num] = yenm[num];
		}
		for (num = 0; num < 5; num++) { /* mover 5 enemigos */
			switch(direccion_enm[num]) {
				case IZ:
					xenm[num]-=inc_enm;
				break;

				case DR:
					xenm[num]+=inc_enm;
				break;

				case AR:
					yenm[num]-=inc_enm;
				break;

				case AB:
					yenm[num]+=inc_enm;
				break;
			} /* switch(direccion_enm... */
		} /* for(... */
		if(x < 1) x = XPANT; /* comprobar limites del packman */
		if(y < 1) y = YPANT;
		if(x > XPANT) x = 1;
		if(y > YPANT) y = 1;

		for(num = 0; num < 5; num++) { /* comprobar limites de los enemigos */
			if(xenm[num] < 1) xenm[num] = XPANT;
			if(yenm[num] < 1) yenm[num] = YPANT;
			if(xenm[num] > XPANT) xenm[num] = 1;
			if(yenm[num] > YPANT) yenm[num] = 1;
		}
		gettext(x, y, x, y, &fondo);
		if(fondo != 'ú' && fondo != ' ' && fondo != '+') { /* no pasar por las barreras (packman)*/
			x = tempx; /* reestablecer */
			y = tempy;
			direccion = tempd;
			sonido = 0;
			if(demo) direccion = random(4) + 1;
		} else sonido = 80;
		if(fondo == 'ú') { /* verificar si hay una galleta (packman) */
			puntos += PUNTOS_GALLETA;
			galletas++;
			textcolor(GREEN);
			gotoxy(8, YPANT + 2);
			cprintf("%ld", puntos);
			gotoxy(25, YPANT + 2);
			cprintf("%d", galletas);
			if(sonido == 80) sonido = 140;
			else sonido = 80;
		}
		else if(fondo == '+') { /* verificar si hay un super */
			puntos += PUNTOS_SUPER;
			galletas++;
			textcolor(GREEN);
			gotoxy(8, YPANT + 2);
			cprintf("%ld", puntos);
			gotoxy(25, YPANT + 2);
			cprintf("%d", galletas);
			for(num2 = 766; num2 > 666; num2--) { /* sonido del super */
				sound(num2);
				delay(1);
			}
			for(num = 0; num < 5; num++) { /* cambiar la direcci¢n de los enemigos (super) */
				if(direccion_enm[num] == IZ) direccion_enm[num] = DR;
				else if(direccion_enm[num] == DR) direccion_enm[num] = IZ;
				else if(direccion_enm[num] == AR) direccion_enm[num] = AB;
				else if(direccion_enm[num] == AB) direccion_enm[num] = AR;
			}
			super = VERDADERO; /* activar la super */
			tiempo_super = 0;
			color_enm = BROWN;
		}
		else if(fondo == 6) { /* si hay una especial roja */
			puntos += PUNTOS_ROJA;
			textcolor(GREEN);
			gotoxy(8, YPANT + 2);
			cprintf("%ld", puntos);
			gotoxy(25, YPANT + 2);
			cprintf("%d", galletas);
			for(num2 = 866; num2 > 766; num2--) { /* sonido de especial roja */
				sound(num2);
				delay(1);
			}
			gotoxy(XFRUTA, YFRUTA); cprintf(" "); /* borrarla */
			tiempo_fruta = FALSO;
		}
		else if(fondo == 15) { /* si hay una especial zul */
			puntos += PUNTOS_AZUL;
			textcolor(GREEN);
			gotoxy(8, YPANT + 2);
			cprintf("%ld", puntos);
			gotoxy(25, YPANT + 2);
			cprintf("%d", galletas);
			for(num2 = 966; num2 > 890; num2--) { /* sonido de especial azul */
				sound(num2);
				delay(1);
			}
			gotoxy(XFRUTA, YFRUTA); cprintf(" "); /* borrarla */
			tiempo_fruta = FALSO;
			super = VERDADERO; /* activar super */
			tiempo_super = 0;
			color_enm = LIGHTBLUE;
			inc_enm = 0;
		}
		for(num = 0; num < 5; num++) { /* temporales direccion enemigos */
			direccion_enmt[num] = direccion_enm[num];
		}
		for(num = 0; num < 5; num++) {
			if(super) {
				if(x > xenm[num]) direccion_enm[num] = IZ;
				else if(x < xenm[num]) direccion_enm[num] = DR;
				else if(y > yenm[num]) direccion_enm[num] = AR;
				else if(y < yenm[num]) direccion_enm[num] = AB;
			} else {
				if(x > xenm[num]) direccion_enm[num] = DR;
				else if(x < xenm[num]) direccion_enm[num] = IZ;
				else if(y > yenm[num]) direccion_enm[num] = AB;
				else if(y < yenm[num]) direccion_enm[num] = AR;
			}
			/* los enemigos no deben devolverse */
			if(direccion_enm[num] == IZ && direccion_enmt[num] == DR) direccion_enm[num] = direccion_enmt[num];
			else if(direccion_enm[num] == AB && direccion_enmt[num] == AR) direccion_enm[num] = direccion_enmt[num];
			else if(direccion_enm[num] == DR && direccion_enmt[num] == IZ) direccion_enm[num] = direccion_enmt[num];
			else if(direccion_enm[num] == AR && direccion_enmt[num] == AB) direccion_enm[num] = direccion_enmt[num];

			switch(direccion_enm[num]) { /* verificar que haya vacio */
				case IZ:
					gettext(xenm[num] - 1, yenm[num], xenm[num] - 1, yenm[num], &fondo);
				break;

				case DR:
					gettext(xenm[num] + 1, yenm[num], xenm[num] + 1, yenm[num], &fondo);
				break;

				case AR:
					gettext(xenm[num], yenm[num] - 1, xenm[num], yenm[num] - 1, &fondo);
				break;

				case AB:
					gettext(xenm[num], yenm[num] + 1, xenm[num], yenm[num] + 1, &fondo);
				break;
			}
			if(fondo != 'ú' && fondo != ' ' && fondo != '+' && fondo != '°' && fondo != 6 && fondo != 15) { /* solo pasar por los espacios (enemigo) */
				direccion_enm[num] = direccion_enmt[num];
			}
		}

		for(num = 0; num < 5; num++) {
			gettext(xenm[num], yenm[num], xenm[num], yenm[num], &fondo); /* solo pasar por los espacios (enemigo) */
			if(fondo != 'ú' && fondo != ' ' && fondo != '+'  && fondo != '°' && fondo != 6 && fondo != 15) {
				direccion_enm[num] = random(4) + 1; /* nueva direccion del enemigo */
				xenm[num] = xenmt[num];	yenm[num] = yenmt[num];
			}
		}
		for(num = 0; num < 5; num++) { /* guardar el fondo del enemigo */
			gettext(xenm[num], yenm[num], xenm[num], yenm[num], &fondo_enm[num]);
		}
		if(galletas == total_galletas) fin = VERDADERO; /* verificar fin del juego */
		if(fin) break; /* terminar tablero */

		for(num = 0; num < 5; num++) { /* revisar si se han estrellado */
			if(x == xenm[num]) {
				if(y == yenm[num]) { /* si se encuentra con un enemigo */
					if(super) { /* revisar si la super est  activa */
						puntos += PUNTOS_FANTASMA;
						textcolor(GREEN);
						gotoxy(8, YPANT + 2);
						cprintf("%ld", puntos);
						xenm[num] = XPANT / 2;
						yenm[num] = YPANT / 2;
						for(num2 = 466; num2 < 500; num2++) { /* sonido al atrapar un enemigo */
							sound(num2);
							delay(1);
						}
					}
					else muerte = VERDADERO; /* muerte */
				}
			} /* if(x... */
		} /* for... */
		if(puntos > 2600 && tiempo_fruta == FALSO) { /* mostrar especial roja */
			if(random(200) == 66) {
				gotoxy(XFRUTA, YFRUTA);
				textcolor(RED);
				cprintf("%c", 6);
				tiempo_fruta = VERDADERO;
			}
		}
		if(puntos > 2666 && tiempo_fruta == FALSO) { /* mostrar especial azul */
			if(random(395) == 66) {
				gotoxy(XFRUTA, YFRUTA);
				textcolor(LIGHTBLUE);
				cprintf("%c", 15);
				tiempo_fruta = VERDADERO;
			}
		}
		if(tiempo_fruta) tiempo_fruta++; /* contabilizar especial */
		if(tiempo_fruta >= DURACION_FRUTA) { /* si se agota el tiempo */
			tiempo_fruta = FALSO;
			gotoxy(XFRUTA, YFRUTA); cprintf(" "); /* borrar */
		}

		textcolor(LIGHTCYAN);
		gotoxy(x, y); /* mostrar packman */
		cprintf("%c", 2);
		textcolor(color_enm);
		for (num = 0; num < 5; num++) { /* mostrar los enemigos */
			gotoxy(xenm[num], yenm[num]); /* mostrar un enemigo */
			cprintf("%c", 1);
		}
		if(super) { /* contabilizar super */
			tiempo_super++;
			if(tiempo_super > DURACION_SUPER) {
				super = FALSO; /* desactivar */
				color_enm = MAGENTA;
				tiempo_super = 0;
				inc_enm = 1;
			}
		}
		sound(sonido);
		delay(40);
		nosound();
		delay(75);

	} while(!muerte); /* do {... */
	gotoxy(x, y); /* borrar packman */
	cprintf(" ");
	textcolor(LIGHTGRAY);
	for (num = 0; num < 5; num++) { /* borrar 5 enemigos */
		gotoxy(xenm[num], yenm[num]);
		cprintf("%c", fondo_enm[num]);
	}
	if(fin) break; /* terminar si se alcanza el total de galletas */

	} while(vidas > 1); /* GAME OVER! */

	if(fin) { /* si termino por total de galletas */
		for(num2 = 0; num2 < 600; num2++) { /* sonido al pasar el tablero */
			sound(num2);
			delay(2);
		}
		for(num2 = 0; num2 < 100; num2++) {
			sound(600);
			delay(1);
		}
		nosound();
		opcion = 's';
		if(!demo && (indice + 1) == TOTAL_TABLEROS) { /* fin del juego */
			puntos += 1666;
			record(puntos, indice); /* Verificar si el puntaje es alto para guardarlo */
			celebrar();
			indice = 0;
		}
		else indice++;
	} /* if(fin... */
	else if(!demo) {
		gotoxy(XPANT / 2 - 1, YPANT / 2);
		cprintf("GAME");
		gotoxy(XPANT / 2 - 1, YPANT / 2 + 1);
		cprintf("OVER!");

		for(num2 = 500; num2 > 0; num2--) { /* sonido de "Game Over" */
			sound(num2);
			delay(2);
		}
		for(num2 = 0; num2 < 450; num2++) {
			sound(1);
			delay(1);
		}
		nosound();

		record(puntos, indice); /* Verificar si el puntaje es alto para guardarlo */
		mostrar_records();

		textcolor(CYAN | BLINK);
		gotoxy(1, YPANT + 2); cprintf("¨Quieres volver a jugar?               ");
		do {
			opcion = getch();
			indice = 0;
		} while(tolower(opcion) != 's' && tolower(opcion) != 'n');
	} /* else if(!demo... */
	else if(demo) {
		if(kbhit()) demo = FALSO;
		opcion = 's';
		inkey();
		mostrar_records();
		for(num2 = 0; num2 < 10000 && !kbhit(); num2++) delay(1);
	}
	} while(tolower(opcion) == 's');

	salir();
	return 0;
} /* main */


int inkey (void) /* presionar una tecla */
{
	register int tecla;

	tecla = inp (0x60);

	if (kbhit ()) {
		getch ();
		switch (tecla) {
			case 30:
				tecla = 'A';
			break;
			case 48:
				tecla = 'B';
			break;
			case 46:
				tecla = 'C';
			break;
			case 32:
				tecla = 'D';
			break;
			case 18:
				tecla = 'E';
			break;
			case 33:
				tecla = 'F';
			break;
			case 34:
				tecla = 'G';
			break;
			case 35:
				tecla = 'H';
			break;
			case 23:
				tecla = 'I';
			break;
			case 36:
				tecla = 'J';
			break;
			case 37:
				tecla = 'K';
			break;
			case 38:
				tecla = 'L';
			break;
			case 50:
				tecla = 'M';
			break;
			case 49:
				tecla = 'N';
			break;
			case 39:
				tecla = '¥';
			break;
			case 24:
				tecla = 'O';
			break;
			case 25:
				tecla = 'P';
			break;
			case 16:
				tecla = 'Q';
			break;
			case 19:
				tecla = 'R';
			break;
			case 31:
				tecla = 'S';
			break;
			case 20:
				tecla = 'T';
			break;
			case 22:
				tecla = 'U';
			break;
			case 47:
				tecla = 'V';
			break;
			case 17:
				tecla = 'W';
			break;
			case 45:
				tecla = 'X';
			break;
			case 21:
				tecla = 'Y';
			break;
			case 44:
				tecla = 'Z';
			break;
			case 51:
				tecla = ',';
			break;
			case 52:
				tecla = '.';
			break;
			case 53:
				tecla = '-';
			break;
			case 1: /* ESC */
				salir();
			break;
		} /* switch */
		return(tecla);
	} /* if */
	else return(0);
} /* inkey */

void salir(void) {
	textmode(C80);
	textbackground(BLACK);
	textcolor(LIGHTGRAY);
	clrscr();
	puts("DPA Software. 1997");
	puts("Jairo Alejandro Duarte Avenda¤o.");
	_setcursortype(_NORMALCURSOR); /* mostrar de nuevo el cursor */
	nosound();
	exit(0);
}

void record(long int puntos, char tablero) /* guarda de record */
{
	FILE *archivo;
	int cont, cont2, rest;
	char nombre[23], *nom, tablero_arch, cab, puntos_arch[11], buffer[LONGITUD + 1];

	if((archivo = fopen("packman.rcd", "r+")) == NULL) { /* abrir el archivo de records */
		puts ("No se puede abrir el archivo packman.rcd.");
		exit(0);
	}
	if((cab = getc(archivo)) == EOF) { /* byte de reconociemiento */
		puts ("Error al leer el archivo packman.rcd.");
		exit(0);
	}
	if(cab != 'D') { /* verificar archivo */
		puts ("Error al verificar el archivo packman.rcd.");
		exit(0);
	}
	for(cont = 0; cont < 10; cont++) {
		if(fread(nombre, 1, 22, archivo) != 22) { /* leer y descartar el nombre */
			puts ("Error leyendo el archivo packman.rcd.");
			exit(0);
		}
		if(fread(puntos_arch, 1, 10, archivo) != 10) { /* leer puntos */
			puts ("Error leyendo el archivo packman.rcd.");
			exit(0);
		}
		puntos_arch[10] = '\0';
		if(atol(puntos_arch) <= puntos) { /* comparar */
			/* guardar los dem s records en memoria para desplazarlos */
			fseek(archivo, (cont * 22) + (cont * 10) + (cont * 1) + 1, SEEK_SET);

			if(fread(buffer, (LONGITUD - ftell(archivo)) - ULTIMO_RCD, 1, archivo) != 1) {
				puts ("Error al intentar leer el archivo packman.rcd.");
				exit(0);
			}
			/* escribir el nuevo record en el lugar correcto */
			clrscr();
			textcolor(CYAN);
			gotoxy(1, 1);
			cprintf("Nombre:");
			textbackground(BLUE);
			textcolor(YELLOW);
			gotoxy(8, 1);
			cprintf("                      "); /* fondo */
			nombre[0] = 23; /* maximo 22 caracteres */
			gotoxy(8, 1);
			nom = cgets(nombre);
			fseek(archivo, (cont * 22) + (cont * 10) + cont + 1, SEEK_SET); /* llegar al lugar correcto */
			*(nom + 22) = '\0';
			rest = fprintf(archivo, "%s", nom);
			for(cont2 = 0; cont2 < 22 - rest; cont2++) putc(' ', archivo); /* espacios */
			rest = fprintf(archivo, "%ld", puntos);
			for(cont2 = 0; cont2 < 10 - rest; cont2++) putc(' ', archivo); /* espacios */
			fprintf(archivo, "%c", tablero + 1);
			/* escribir el resto de records */
			fseek(archivo, ((cont + 1) * 22) + ((cont + 1) * 10) + (cont + 1) + 1, SEEK_SET);
			buffer[LONGITUD + 1] = '\0';
			fwrite(buffer, 1, (LONGITUD - ftell(archivo)) - ULTIMO_RCD, archivo);
			break;
		} /* if(... */
		if(fread(&tablero_arch, 1, 1, archivo) != 1) { /* leer y descartar el tablero */
			puts ("Error leyendo el archivo packman.rcd.");
			exit(0);
		}
	} /* for(... */
	fclose(archivo);
	textbackground(BLACK);
}

void mostrar_records(void)
{
	FILE *archivo;
	char cab, num, buffer_nom[23], buffer_pun[11], buffer_tab, fila = 6;

	clrscr();
	textcolor(LIGHTBLUE);
	gotoxy(8, 1); cprintf("* * * R E C O R D S * * *");

	if((archivo = fopen("packman.rcd", "r+")) == NULL) { /* abrir el archivo de records */
		puts ("No se puede abrir el archivo packman.rcd.");
		exit(0);
	}
	if((cab = getc(archivo)) == EOF) { /* byte de reconociemiento */
		puts ("Error al leer el archivo packman.rcd.");
		exit(0);
	}
	if(cab != 'D') { /* verificar archivo */
		puts ("Error al verificar el archivo packman.rcd.");
		exit(0);
	}
	gotoxy(1, 3);
	textcolor(CYAN);
	cprintf("Nombre                  Puntaje     Mapa");
	gotoxy(1, 4);
	cprintf("----------------------  ----------  ----");

	for(num = 0; num < 10; num++) {
		if(fread(buffer_nom, 22, 1, archivo) != 1) {
			puts ("Error al leer el archivo packman.rcd.");
			exit(0);
		}
		buffer_nom[22] = '\0';
		gotoxy(1, fila);
		if(num == 0) textcolor(RED); /* primer record en rojo */
		cprintf("%s", buffer_nom); /* nombre */

		if(fread(buffer_pun, 10, 1, archivo) != 1) {
			puts ("Error al leer el archivo packman.rcd.");
			exit(0);
		}
		buffer_pun[10] = '\0';
		gotoxy(25, fila);
		cprintf("%s", buffer_pun); /* puntos */

		if(fread(&buffer_tab, 1, 1, archivo) != 1) {
			puts ("Error al leer el archivo packman.rcd.");
			exit(0);
		}
		gotoxy(37, fila);
		cprintf("%d", buffer_tab); /* tablero */
		textcolor(LIGHTGRAY);
		fila += 2;
	}
	fclose(archivo);
}


int presentacion(void)
{
	char x = 2;
	int sonido;

	clrscr();
	textcolor(LIGHTBLUE);
	gotoxy(9, 24); cprintf("D P A  S o f t w a r e");
	textcolor(LIGHTGRAY);
	gotoxy(2, 12); cprintf("............P a c k m a n............");

	inkey();
	textcolor(LIGHTCYAN);
	while(!kbhit() && x < 40) {
		gotoxy(x, 12); cprintf("%c", 2);
		gotoxy(x - 1, 12); cprintf(" ");
		sound(100 + random(300));
		delay(30);
		nosound();
		delay(80);
		x++;
	}
	gotoxy(x - 1, 12); cprintf(" ");

	x = 23;
	sonido = 166;
	textcolor(LIGHTBLUE);
	while(!kbhit() && x >= 1) {
		gotoxy(9, x); cprintf("D P A  S o f t w a r e");
		sound(sonido);
		sonido += 12;
		gotoxy(9, x + 1); cprintf("                      ");
		delay(46);
		x--;
	}
	gotoxy(9, 1); cprintf("                      ");

	sonido = 100;
	x = 2;
	textcolor(CYAN);
	while(!kbhit() && x < 13) {
		gotoxy(13, x); cprintf("P A C K M A N");
		sound(sonido);
		sonido += 53;
		gotoxy(13, x - 1); cprintf("             ");
		delay(100);
		x++;
	}
	nosound();
	sonido = BLUE;

	while(!kbhit() && sonido < 4666) {
		textcolor(x);
		gotoxy(13, 12); cprintf("P A C K M A N");
		if(x > WHITE) x = BLUE;
		sonido++;
		x++;
		delay(3);
	}
	if(kbhit()) return FALSO;
	else return VERDADERO;
}

void celebrar(void)
{
	int num;

	clrscr();

	for(num = 0; num < 500; num++) {
		sound(num + 50);
		delay(3);
	}
	nosound();
}