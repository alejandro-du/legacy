#include <stdio.h>
#include <conio.h>
#include <dir.h>
#include <string.h>
#include <alloc.h>
#include <stdlib.h>

int total_espacio (void);
void verificar_espacio (void);
void inicio (void);
void centrar (char texto[], int fila);
void directorios (void);
void crear_estructura_directorio (void);
void copiar_archivos (void);
void cuadro (int x_inicial, int y_inicial, int x_final, int y_final);
void restaurar_video (void);
void mostrar_error_creacion (void);
void mostrar_error_busqueda (void);
void mostrar_error_escritura (void);
void mostrar_error_lectura (void);
void mostrar_error_espacio (void);

int *buffer;
int unidad_busqueda;

void main (void)
{
	inicio ();
	directorios ();
	verificar_espacio ();
	crear_estructura_directorio ();
	copiar_archivos ();
	restaurar_video ();
}

void inicio (void)
{
	textmode (C80);
	window (1, 1, 80, 1);
	textbackground (WHITE);
	textcolor (BLUE);
	clrscr ();
	centrar ("Instalaci¢n del paquete de juegos  Versi¢n 1.00", 1);
	window (1, 2, 80, 25);
	textbackground (LIGHTBLUE);
	textcolor (WHITE);
	clrscr ();
}

void restaurar_video (void)
{
	textcolor (LIGHTGRAY);
	textbackground (BLACK);
	clrscr ();
	normvideo ();
	textmode (LASTMODE);
}

void centrar (char texto[], int fila)
{
	int numero_caracteres = strlen (texto);

	gotoxy (40 - (numero_caracteres / 2), fila ); cprintf ("%s", texto);
}

void verificar_espacio (void)
{
	long int tamano;
	FILE *temporal;

	cuadro (15, 7, 65, 12);
	textcolor (BLACK);
	centrar ("El Programa de instalaci¢n est  verificando que", 9);
	centrar("haya espacio suficiente en el disco...", 10);

	if ((temporal = fopen ("hj376yuh.!5_", "wb")) == NULL) {
		cprintf ("\nError al intentar crear el archivo temporal."); restaurar_video (); exit (1);
	}

	for (tamano = 0; tamano < 5568951; tamano++){
		putc (4, temporal);
		if (ferror (temporal)) mostrar_error_espacio ();
	}
	fclose (temporal);
	system ("del hj376yuh.!5_");
	puttext (15, 7, 65, 13, buffer);
}

void directorios ()
{
	FILE *archivo_control, *temporal;

	unidad_busqueda = getdisk ();

	textcolor (WHITE);
	gotoxy (4, 4); cprintf ("Verificando disco origen...");

	if ((archivo_control = fopen ("control.dat", "r")) == NULL) {
		cuadro (10,7,70,9);
		textcolor (RED);
		centrar ("No se puede iniciar la instalaci¢n", 8);
		getch ();
		restaurar_video ();
		exit (1);
	}
	fclose (archivo_control);

	gotoxy (4, 4); cprintf ("                            ");

	setdisk (2);

	if ((temporal = fopen ("hj376yuh.!5_", "wb")) == NULL) {
	cprintf ("\nError al intentar crear el archivo temporal."); restaurar_video (); exit (1);

	fclose (temporal);
	system ("del hj376yuh.!5_");
	}
}

void cuadro (int x_inicial, int y_inicial, int x_final, int y_final)
{
	int a, b;
	long int bytes = ((80 - x_final + x_inicial) * (25 - y_final + y_inicial)) * 2;
	free (buffer);
	if ((buffer = malloc (bytes)) == NULL) {
		cprintf ("Memoria insuficiente."); restaurar_video (); exit (1);
	}
	gettext (x_inicial, y_inicial, x_final, y_final + 1, buffer);

	textcolor (WHITE);
	textbackground (LIGHTGRAY);
	
	for (a = x_inicial; a < x_final; a++) {
		for (b = y_inicial; b < y_final; b++) {
			gotoxy (a, b); cprintf (" ");
		}
	}
	for (a = x_inicial + 1; a < x_final; a++) {
		gotoxy (a, y_inicial); cprintf ("Ä");
		gotoxy (a, y_final); cprintf ("Ä");
	}
	for (a = y_inicial + 1; a < y_final; a++) {
		gotoxy (x_inicial, a); cprintf ("³");
		gotoxy (x_final, a); cprintf ("³");
		gotoxy (x_inicial, y_inicial); cprintf ("Ú");
		gotoxy (x_inicial, y_final); cprintf ("À");
		gotoxy (x_final, y_inicial); cprintf ("¿");
		gotoxy (x_final, y_final); cprintf ("Ù");
	}
}
void mostrar_error_lectura (void)
{
	cuadro (15, 7, 65, 9);
	textcolor (RED);
	centrar ("Error de lectura del archivo origen.", 8); 
	getch ();
	restaurar_video ();
	exit (1);
}

void mostrar_error_escritura (void)
{
	cuadro (15, 7, 65, 9);
	textcolor (RED);
	centrar ("Error de lectura del archivo origen.", 8); 
	getch ();
	restaurar_video ();
	exit (1);
}

void mostrar_error_busqueda (void)
{
	cuadro (15, 7, 65, 9);
	textcolor (RED);
	centrar ("Error en la busqueda del directorio.", 8); 
	getch ();
	restaurar_video ();
	exit (1);
}

void mostrar_error_creacion (void)
{
	cuadro (15, 7, 65, 9);
	textcolor (RED);
	centrar ("Error en la creaci¢n del directorio.", 8); 
	getch ();
	restaurar_video ();
	exit (1);
}

void mostrar_error_espacio (void)
{
	cuadro (10, 7, 70, 9);
	textcolor (RED);
	centrar ("No hay espacio suficiente en el disco para instalar los juegos.", 8); 
	system ("del hj376yuh.!5_");
	getch ();
	restaurar_video ();
	exit (1);
}

void crear_estructura_directorio (void)
{
	cuadro (15, 7, 65, 9);
	textcolor (BLACK);
	centrar ("Creando la estructura del directorio JUEGOS1...", 8); 

	if (chdir ("c:/")) mostrar_error_busqueda ();
	if (mkdir ("juegos1")) mostrar_error_creacion ();
	if (chdir ("juegos1")) mostrar_error_busqueda ();
	if (mkdir ("go")) mostrar_error_creacion ();
	if (mkdir ("mc")) mostrar_error_creacion ();
	if (mkdir ("td3")) mostrar_error_creacion ();
	if (mkdir ("fredy")) mostrar_error_creacion ();
	if (mkdir ("ajedrez")) mostrar_error_creacion ();
	if (mkdir ("basket")) mostrar_error_creacion ();
	puttext (15, 7, 65, 10, buffer);
}

void copiar_archivos (void)
{
	FILE *origen, *destino, *archivo_control;
	struct ffblk archivo_origen;
	char dato, tecla;
	int porcentaje2, total_bytes, total_bytes_directorio = 0, fin, contador, porcentaje, posicion = 0, posicion_cursor = 22;

	textcolor (WHITE);
	textbackground (BLUE);
	gotoxy (4, 4); cprintf ("Buscando directorios...");		

	setdisk (unidad_busqueda);

	if (chdir ("go")) mostrar_error_busqueda ();

	total_bytes_directorio = total_espacio ();

	textcolor (WHITE); gotoxy (1, 3); cprintf ("total_bytes_directorio = %d", total_bytes_directorio);
	textcolor (WHITE); gotoxy (1, 4); cprintf ("total_bytes_directorio (l) = %ld", total_bytes_directorio);

	fin = findfirst ("*.*", &archivo_origen, 0);
	if (fin) mostrar_error_lectura ();

	total_bytes = archivo_origen.ff_fsize;
	textcolor (BLACK);

	gotoxy (1, 19); cprintf ("total_bytes (l) = %ld", total_bytes);
	getch ();

	porcentaje2 = (total_bytes * 100) / total_bytes_directorio;
	textcolor (CYAN); gotoxy (1, 20); cprintf ("porcentaje2 = ", porcentaje2);
	getch ();
	setdisk (2);
	if (chdir ("go")) mostrar_error_busqueda ();

	cuadro (18, 7, 62, 18);
	centrar (" Instalando ", 7);

	while (!fin) {
		setdisk (unidad_busqueda);

		if ((origen = fopen (archivo_origen.ff_name, "rb")) == NULL) {
			mostrar_error_busqueda ();
		}
		setdisk (2);

		if ((destino = fopen (archivo_origen.ff_name, "wb")) == NULL) {
			mostrar_error_escritura ();
		}
		textbackground (BLUE);
		textcolor (WHITE);
		gotoxy (4, 4); cprintf ("Copiando los archivos al disco...");		
		textcolor (BLACK);
		textbackground (LIGHTGRAY);
		gotoxy (22, 9); cprintf ("Archivo: %s                ", archivo_origen.ff_name);
		gotoxy (22, 10); cprintf ("Bytes: %ld                ", archivo_origen.ff_fsize);
		gotoxy (22, 12); cprintf ("Destino: C:\\JUEGOS1\\GO\\             ", archivo_origen.ff_name);
		gotoxy (22, 12); cprintf ("Destino: C:\\JUEGOS1\\GO\\%s", archivo_origen.ff_name);
		cuadro (21, 14, 59, 16);
		centrar (" Progreso ", 14);
		gotoxy (22, 15); cprintf ("                                     ");
		gotoxy (23, 17); cprintf ("Porcentaje: ");
		textcolor (BLACK);
		gotoxy (52, 17); cprintf ("Disco: 1");

		while (!feof (origen)) {
			dato = getc (origen);
			if (ferror (origen)) mostrar_error_lectura ();
			putc (dato, destino);
			if (ferror (destino)) mostrar_error_escritura ();
			contador = archivo_origen.ff_fsize / 37;
			if (archivo_origen.ff_fsize <= 37) contador = 1;
			posicion++;
			if (posicion >= contador) {
				textcolor (WHITE);
				gotoxy (posicion_cursor, 15); cprintf ("²");
				porcentaje = ((posicion_cursor - 21) * 100) / 37;
				textcolor (BLACK);
				gotoxy (35, 17); cprintf ("%d\%  ", porcentaje);
				posicion_cursor++;
				if (posicion_cursor > 58) posicion_cursor = 58;
				posicion = 0;
			}
		}
		fclose (origen);
		if (ferror (origen)) mostrar_error_lectura ();
		fclose (destino);
		if (ferror (destino)) mostrar_error_lectura ();
		fin = findnext (&archivo_origen);

		total_bytes = total_bytes + archivo_origen.ff_fsize;
		porcentaje2 = (total_bytes * 100) / total_bytes_directorio;
		textcolor (DARKGRAY); gotoxy (1, 22); cprintf ("Porcentaje2 (2¦)= %d", porcentaje2);

		posicion_cursor = 22;
		posicion = 0;
	}
	pedir2:
	textbackground (BLUE);
	textcolor (WHITE);
	clrscr ();
	gotoxy (4, 4); cprintf ("Disco #1 copiado con exito.");
	cuadro (10, 7, 70, 13);
	gotoxy (12, 8); cprintf ("Introduzca el disco #2...");
	gotoxy (12, 10); cprintf ("Presione A para Abortar la instalaci¢n o cualquier otra");
	gotoxy (12, 11); cprintf ("tecla para continuar.");
	tecla = getch ();

	if (tecla == 'A' | tecla == 'a') {
		textbackground (BLUE);
		clrscr ();
		cuadro (10, 7, 70, 9);
		centrar ("No se termin¢ la instalaci¢n.", 8);
		getch ();
		restaurar_video ();
		exit (1);
	}
	textbackground (BLUE);
	clrscr ();
	textcolor (WHITE);
	gotoxy (4, 4); cprintf ("Verificando disco origen...");

	setdisk (unidad_busqueda);
	if ((archivo_control = fopen ("control2.dat", "r")) == NULL) goto pedir2;

	fclose (archivo_control);

	gotoxy (4, 4); cprintf ("                            ");

	textcolor (WHITE);
	textbackground (BLUE);
	gotoxy (4, 4); cprintf ("Buscando directorios...    ");		
	
	if (chdir ("td3")) mostrar_error_busqueda ();

	fin = findfirst ("*.*", &archivo_origen, 0);
	if (fin) mostrar_error_lectura ();

	setdisk (2);

	if (chdir ("c:\\juegos1\\td3")) mostrar_error_busqueda ();

	cuadro (18, 7, 62, 18);
	centrar (" Instalando ", 7);

	while (!fin) {
		setdisk (unidad_busqueda);

		if ((origen = fopen (archivo_origen.ff_name, "rb")) == NULL) {
			mostrar_error_busqueda ();
		}
		setdisk (2);

		if ((destino = fopen (archivo_origen.ff_name, "wb")) == NULL) {
			mostrar_error_escritura ();
		}
		textbackground (BLUE);
		textcolor (WHITE);
		gotoxy (4, 4); cprintf ("Copiando los archivos al disco...");		
		textcolor (BLACK);
		textbackground (LIGHTGRAY);
		gotoxy (22, 9); cprintf ("Archivo: %s                ", archivo_origen.ff_name);
		gotoxy (22, 10); cprintf ("Bytes: %ld                ", archivo_origen.ff_fsize);
		gotoxy (22, 12); cprintf ("Destino: C:\\JUEGOS1\\TD3\\            ", archivo_origen.ff_name);
		gotoxy (22, 12); cprintf ("Destino: C:\\JUEGOS1\\TD3\\%s  ", archivo_origen.ff_name);
		cuadro (21, 14, 59, 16);
		centrar (" Progreso ", 14);
		gotoxy (22, 15); cprintf ("                                     ");
		gotoxy (23, 17); cprintf ("Porcentaje: ");
		textcolor (BLACK);
		gotoxy (52, 17); cprintf ("Disco: 2");

		while (!feof (origen)) {
			dato = getc (origen);
			if (ferror (origen)) mostrar_error_lectura ();
			putc (dato, destino);
			if (ferror (destino)) mostrar_error_escritura ();
			contador = archivo_origen.ff_fsize / 37;
			if (archivo_origen.ff_fsize <= 37) contador = 1;
			posicion++;
			if (posicion >= contador) {
				textcolor (WHITE);
				gotoxy (posicion_cursor, 15); cprintf ("²");
				porcentaje = ((posicion_cursor - 21) * 100) / 37;
				textcolor (BLACK);
				gotoxy (35, 17); cprintf ("%d\%  ", porcentaje);
				posicion_cursor++;
				if (posicion_cursor > 58) posicion_cursor = 58;
				posicion = 0;
			}
		}
		fclose (origen);
		if (ferror (origen)) mostrar_error_lectura ();
		fclose (destino);
		if (ferror (destino)) mostrar_error_lectura ();
		fin = findnext (&archivo_origen);
		posicion_cursor = 22;
	}
	pedir3:
	textbackground (BLUE);
	textcolor (WHITE);
	clrscr ();
	gotoxy (4, 4); cprintf ("Disco #2 copiado con exito.");
	cuadro (10, 7, 70, 13);
	gotoxy (12, 8); cprintf ("Introduzca el disco #3...");
	gotoxy (12, 10); cprintf ("Presione A para Abortar la instalaci¢n o cualquier otra");
	gotoxy (12, 11); cprintf ("tecla para continuar.");
	tecla = getch ();

	if (tecla == 'A' | tecla == 'a') {
		textbackground (BLUE);
		clrscr ();
		cuadro (10, 7, 70, 9);
		centrar ("No se termin¢ la instalaci¢n.", 8);
		getch ();
		restaurar_video ();
		exit (1);
	}
	textbackground (BLUE);
	clrscr ();
	textcolor (WHITE);
	gotoxy (4, 4); cprintf ("Verificando disco origen...");

	setdisk (unidad_busqueda);
	if ((archivo_control = fopen ("control3.dat", "r")) == NULL) goto pedir3;

	fclose (archivo_control);

	gotoxy (4, 4); cprintf ("                            ");

	textcolor (WHITE);
	textbackground (BLUE);
	gotoxy (4, 4); cprintf ("Buscando directorios...    ");		
	
	if (chdir ("fredy")) mostrar_error_busqueda ();

	fin = findfirst ("*.*", &archivo_origen, 0);

	if (fin) mostrar_error_lectura ();

	setdisk (2);

	if (chdir ("c:\\juegos1\\fredy")) mostrar_error_busqueda ();

	cuadro (18, 7, 62, 18);
	centrar (" Instalando ", 7);

	while (!fin) {
		setdisk (unidad_busqueda);

		if ((origen = fopen (archivo_origen.ff_name, "rb")) == NULL) {
			mostrar_error_busqueda ();
		}
		setdisk (2);

		if ((destino = fopen (archivo_origen.ff_name, "wb")) == NULL) {
			mostrar_error_escritura ();
		}
		textbackground (BLUE);
		textcolor (WHITE);
		gotoxy (4, 4); cprintf ("Copiando los archivos al disco...");		
		textcolor (BLACK);
		textbackground (LIGHTGRAY);
		gotoxy (22, 9); cprintf ("Archivo: %s                ", archivo_origen.ff_name);
		gotoxy (22, 10); cprintf ("Bytes: %ld                ", archivo_origen.ff_fsize);
		gotoxy (22, 12); cprintf ("Destino: C:\\JUEGOS1\\FREDY\\            ", archivo_origen.ff_name);
		gotoxy (22, 12); cprintf ("Destino: C:\\JUEGOS1\\FREDY\\%s  ", archivo_origen.ff_name);
		cuadro (21, 14, 59, 16);
		centrar (" Progreso ", 14);
		gotoxy (22, 15); cprintf ("                                     ");
		gotoxy (23, 17); cprintf ("Porcentaje: ");
		textcolor (BLACK);
		gotoxy (52, 17); cprintf ("Disco: 3");

		while (!feof (origen)) {
			dato = getc (origen);
			if (ferror (origen)) mostrar_error_lectura ();
			putc (dato, destino);
			if (ferror (destino)) mostrar_error_escritura ();
			contador = archivo_origen.ff_fsize / 37;
			if (archivo_origen.ff_fsize <= 37) contador = 1;
			posicion++;
			if (posicion >= contador) {
				textcolor (WHITE);
				gotoxy (posicion_cursor, 15); cprintf ("²");
				porcentaje = ((posicion_cursor - 21) * 100) / 37;
				textcolor (BLACK);
				gotoxy (35, 17); cprintf ("%d\%  ", porcentaje);
				posicion_cursor++;
				if (posicion_cursor > 58) posicion_cursor = 58;
				posicion = 0;
			}
		}
		fclose (origen);
		if (ferror (origen)) mostrar_error_lectura ();
		fclose (destino);
		if (ferror (destino)) mostrar_error_lectura ();
		fin = findnext (&archivo_origen);
		posicion_cursor = 22;
	}

	pedir4:
	textbackground (BLUE);
	textcolor (WHITE);
	clrscr ();
	gotoxy (4, 4); cprintf ("Disco #3 copiado con exito.");
	cuadro (10, 7, 70, 13);
	gotoxy (12, 8); cprintf ("Introduzca el disco #4...");
	gotoxy (12, 10); cprintf ("Presione A para Abortar la instalaci¢n o cualquier otra");
	gotoxy (12, 11); cprintf ("tecla para continuar.");
	tecla = getch ();

	if (tecla == 'A' | tecla == 'a') {
		textbackground (BLUE);
		clrscr ();
		cuadro (10, 7, 70, 9);
		centrar ("No se termin¢ la instalaci¢n.", 8);
		getch ();
		restaurar_video ();
		exit (1);
	}
	textbackground (BLUE);
	clrscr ();
	textcolor (WHITE);
	gotoxy (4, 4); cprintf ("Verificando disco origen...");

	setdisk (unidad_busqueda);
	if ((archivo_control = fopen ("control4.dat", "r")) == NULL) goto pedir4;

	fclose (archivo_control);

	gotoxy (4, 4); cprintf ("                            ");

	textcolor (WHITE);
	textbackground (BLUE);
	gotoxy (4, 4); cprintf ("Buscando directorios...    ");		
	
	if (chdir ("mc")) mostrar_error_busqueda ();

	fin = findfirst ("*.*", &archivo_origen, 0);

	if (fin) mostrar_error_lectura ();

	setdisk (2);

	if (chdir ("c:\\juegos1\\mc")) mostrar_error_busqueda ();

	cuadro (18, 7, 62, 18);
	centrar (" Instalando ", 7);

	while (!fin) {
		setdisk (unidad_busqueda);

		if ((origen = fopen (archivo_origen.ff_name, "rb")) == NULL) {
			mostrar_error_busqueda ();
		}
		setdisk (2);

		if ((destino = fopen (archivo_origen.ff_name, "wb")) == NULL) {
			mostrar_error_escritura ();
		}
		textbackground (BLUE);
		textcolor (WHITE);
		gotoxy (4, 4); cprintf ("Copiando los archivos al disco...");		
		textcolor (BLACK);
		textbackground (LIGHTGRAY);
		gotoxy (22, 9); cprintf ("Archivo: %s                ", archivo_origen.ff_name);
		gotoxy (22, 10); cprintf ("Bytes: %ld                ", archivo_origen.ff_fsize);
		gotoxy (22, 12); cprintf ("Destino: C:\\JUEGOS1\\MC\\            ", archivo_origen.ff_name);
		gotoxy (22, 12); cprintf ("Destino: C:\\JUEGOS1\\MC\\%s  ", archivo_origen.ff_name);
		cuadro (21, 14, 59, 16);
		centrar (" Progreso ", 14);
		gotoxy (22, 15); cprintf ("                                     ");
		gotoxy (23, 17); cprintf ("Porcentaje: ");
		textcolor (BLACK);
		gotoxy (52, 17); cprintf ("Disco: 4");

		while (!feof (origen)) {
			dato = getc (origen);
			if (ferror (origen)) mostrar_error_lectura ();
			putc (dato, destino);
			if (ferror (destino)) mostrar_error_escritura ();
			contador = archivo_origen.ff_fsize / 37;
			if (archivo_origen.ff_fsize <= 37) contador = 1;
			posicion++;
			if (posicion >= contador) {
				textcolor (WHITE);
				gotoxy (posicion_cursor, 15); cprintf ("²");
				porcentaje = ((posicion_cursor - 21) * 100) / 37;
				textcolor (BLACK);
				gotoxy (35, 17); cprintf ("%d\%  ", porcentaje);
				posicion_cursor++;
				if (posicion_cursor > 58) posicion_cursor = 58;
				posicion = 0;
			}
		}
		fclose (origen);
		if (ferror (origen)) mostrar_error_lectura ();
		fclose (destino);
		if (ferror (destino)) mostrar_error_lectura ();
		fin = findnext (&archivo_origen);
		posicion_cursor = 22;
	}
	pedir5:
	textbackground (BLUE);
	textcolor (WHITE);
	clrscr ();
	gotoxy (4, 4); cprintf ("Disco #4 copiado con exito.");
	cuadro (10, 7, 70, 13);
	gotoxy (12, 8); cprintf ("Introduzca el disco #5...");
	gotoxy (12, 10); cprintf ("Presione A para Abortar la instalaci¢n o cualquier otra");
	gotoxy (12, 11); cprintf ("tecla para continuar.");
	tecla = getch ();

	if (tecla == 'A' | tecla == 'a') {
		textbackground (BLUE);
		clrscr ();
		cuadro (10, 7, 70, 9);
		centrar ("No se termin¢ la instalaci¢n.", 8);
		getch ();
		restaurar_video ();
		exit (1);
	}
	textbackground (BLUE);
	clrscr ();
	textcolor (WHITE);
	gotoxy (4, 4); cprintf ("Verificando disco origen...");

	setdisk (unidad_busqueda);
	if ((archivo_control = fopen ("control5.dat", "r")) == NULL) goto pedir5;

	fclose (archivo_control);

	gotoxy (4, 4); cprintf ("                            ");

	textcolor (WHITE);
	textbackground (BLUE);
	gotoxy (4, 4); cprintf ("Buscando directorios...    ");		
	
	if (chdir ("basket")) mostrar_error_busqueda ();

	fin = findfirst ("*.*", &archivo_origen, 0);

	if (fin) mostrar_error_lectura ();

	setdisk (2);

	if (chdir ("c:\\juegos1\\basket")) mostrar_error_busqueda ();

	cuadro (18, 7, 62, 18);
	centrar (" Instalando ", 7);

	while (!fin) {
		setdisk (unidad_busqueda);

		if ((origen = fopen (archivo_origen.ff_name, "rb")) == NULL) {
			mostrar_error_busqueda ();
		}
		setdisk (2);

		if ((destino = fopen (archivo_origen.ff_name, "wb")) == NULL) {
			mostrar_error_escritura ();
		}
		textbackground (BLUE);
		textcolor (WHITE);
		gotoxy (4, 4); cprintf ("Copiando los archivos al disco...");		
		textcolor (BLACK);
		textbackground (LIGHTGRAY);
		gotoxy (22, 9); cprintf ("Archivo: %s                ", archivo_origen.ff_name);
		gotoxy (22, 10); cprintf ("Bytes: %ld                ", archivo_origen.ff_fsize);
		gotoxy (22, 12); cprintf ("Destino: C:\\JUEGOS1\\BASKET\\            ", archivo_origen.ff_name);
		gotoxy (22, 12); cprintf ("Destino: C:\\JUEGOS1\\BASKET\\%s  ", archivo_origen.ff_name);
		cuadro (21, 14, 59, 16);
		centrar (" Progreso ", 14);
		gotoxy (22, 15); cprintf ("                                     ");
		gotoxy (23, 17); cprintf ("Porcentaje: ");
		textcolor (BLACK);
		gotoxy (52, 17); cprintf ("Disco: 5");

		while (!feof (origen)) {
			dato = getc (origen);
			if (ferror (origen)) mostrar_error_lectura ();
			putc (dato, destino);
			if (ferror (destino)) mostrar_error_escritura ();
			contador = archivo_origen.ff_fsize / 37;
			if (archivo_origen.ff_fsize <= 37) contador = 1;
			posicion++;
			if (posicion >= contador) {
				textcolor (WHITE);
				gotoxy (posicion_cursor, 15); cprintf ("²");
				porcentaje = ((posicion_cursor - 21) * 100) / 37;
				textcolor (BLACK);
				gotoxy (35, 17); cprintf ("%d\%  ", porcentaje);
				posicion_cursor++;
				if (posicion_cursor > 58) posicion_cursor = 58;
				posicion = 0;
			}
		}
		fclose (origen);
		if (ferror (origen)) mostrar_error_lectura ();
		fclose (destino);
		if (ferror (destino)) mostrar_error_lectura ();
		fin = findnext (&archivo_origen);
		posicion_cursor = 22;
	}
	setdisk (unidad_busqueda);

	if (chdir ("..")) mostrar_error_busqueda ();

 	textcolor (WHITE);
	textbackground (BLUE);
	gotoxy (4, 4); cprintf ("Buscando directorios...          ");		
	
	if (chdir ("ajedrez")) mostrar_error_busqueda ();

	fin = findfirst ("*.*", &archivo_origen, 0);

	if (fin) mostrar_error_lectura ();

	setdisk (2);

	if (chdir ("c:\\juegos1\\ajedrez")) mostrar_error_busqueda ();

	cuadro (18, 7, 62, 18);
	centrar (" Instalando ", 7);

	while (!fin) {
		setdisk (unidad_busqueda);

		if ((origen = fopen (archivo_origen.ff_name, "rb")) == NULL) {
			mostrar_error_busqueda ();
		}
		setdisk (2);

		if ((destino = fopen (archivo_origen.ff_name, "wb")) == NULL) {
			mostrar_error_escritura ();
		}
		textbackground (BLUE);
		textcolor (WHITE);
		gotoxy (4, 4); cprintf ("Copiando los archivos al disco...");		
		textcolor (BLACK);
		textbackground (LIGHTGRAY);
		gotoxy (22, 9); cprintf ("Archivo: %s                ", archivo_origen.ff_name);
		gotoxy (22, 10); cprintf ("Bytes: %ld                ", archivo_origen.ff_fsize);
		gotoxy (22, 12); cprintf ("Destino: C:\\JUEGOS1\\AJEDREZ\\            ", archivo_origen.ff_name);
		gotoxy (22, 12); cprintf ("Destino: C:\\JUEGOS1\\AJEDREZ\\%s", archivo_origen.ff_name);
		cuadro (21, 14, 59, 16);
		centrar (" Progreso ", 14);
		gotoxy (22, 15); cprintf ("                                     ");
		gotoxy (23, 17); cprintf ("Porcentaje: ");
		textcolor (BLACK);
		gotoxy (52, 17); cprintf ("Disco: 5");

		while (!feof (origen)) {
			dato = getc (origen);
			if (ferror (origen)) mostrar_error_lectura ();
			putc (dato, destino);
			if (ferror (destino)) mostrar_error_escritura ();
			contador = archivo_origen.ff_fsize / 37;
			if (archivo_origen.ff_fsize <= 37) contador = 1;
			posicion++;
			if (posicion >= contador) {
				textcolor (WHITE);
				gotoxy (posicion_cursor, 15); cprintf ("²");
				porcentaje = ((posicion_cursor - 21) * 100) / 37;
				textcolor (BLACK);
				gotoxy (35, 17); cprintf ("%d\%  ", porcentaje);
				posicion_cursor++;
				if (posicion_cursor > 58) posicion_cursor = 58;
				posicion = 0;
			}
		}
		fclose (origen);
		if (ferror (origen)) mostrar_error_lectura ();
		fclose (destino);
		if (ferror (destino)) mostrar_error_lectura ();
		fin = findnext (&archivo_origen);
		posicion_cursor = 22;
	}
	textbackground (BLUE);
	clrscr ();
	cuadro (20, 8, 60, 12);
	textcolor (BLACK);
	centrar ("Instalaci¢n finalizada...", 10);
	textcolor (WHITE);
	gotoxy (4, 4); cprintf ("Presione una tecla para continuar...");
	textbackground (BLUE);
	clrscr ();
	cuadro (12, 2, 70, 14);
	textcolor (BLACK);
	gotoxy (14, 3); cprintf ("Los juegos se han instalado con ‚xito en su disco duro.");
	gotoxy (14, 4); cprintf ("Esta es la estructura del directorio de los juegos:");
	gotoxy (18, 6); cprintf ("C:");
	gotoxy (18, 7); cprintf ("ÀÄÄJUEGOS1");
	gotoxy (18, 8); cprintf ("   ÃÄÄGO");
	gotoxy (18, 9); cprintf ("   ÃÄÄMC");
	gotoxy (18, 10); cprintf ("   ÃÄÄTD3 ");
	gotoxy (18, 11); cprintf ("   ÃÄÄFREDY");
	gotoxy (18, 12); cprintf ("   ÃÄÄAJEDREZ");
	gotoxy (18, 13); cprintf ("   ÀÄÄBASKET");
	textcolor (WHITE);
	textbackground (BLUE);
	centrar ("Programa de instalaci¢n", 16);
	centrar ("Versi¢n 1.00", 18);
	centrar ("Copyright (c) 1996 por", 20);
	centrar ("Jairo Alejandro Duarte", 21);
	centrar ("Juan Carlos Duarte", 22);
	centrar ("DPA Software.", 23);
	getch ();
}

int total_espacio ()
{
	struct ffblk archivo;
	int fin, total_bytes_directorio = 0;

	fin = findfirst ("*.*", &archivo, 0);
	total_bytes_directorio = archivo.ff_fsize;

	while (!fin)
	{
		fin = findnext(&archivo);
		total_bytes_directorio = total_bytes_directorio + archivo.ff_fsize;
		textcolor (BLACK);
		gotoxy (1, 2); cprintf ("tolal_bytes_actual = %ld", total_bytes_directorio);
		getch ();
	}
	textcolor (RED); gotoxy (1, 2); cprintf ("total_bytes_directorio (l): %ld", total_bytes_directorio);
	getch ();
	return (total_bytes_directorio);

}