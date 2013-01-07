#include <cuadros.h>
#include <conio.h>

void main (void)
{
	int x = 80, y = 23, px = 1, py = 1;
	char tecla;

	clrscr ();
	cuadro (70, 18, 5, 4, 205, 186, 201, 187, 200, 188);
	gotoxy (33, 5); printf ("INSTRUCCIONES");
	gotoxy (33, 6); printf ("-------------");
	gotoxy (10, 9); printf ("Para cambiar el tama¤o:");
	gotoxy (10, 10); printf ("Presione ENTRAR para aumentar el tama¤o de la ventana.");
	gotoxy (10, 11); printf ("Presione ESPACIO para disminuir el tama¤o de la ventana.");
	gotoxy (10, 13); printf ("Para avandonar el programa presione X o S.");
	gotoxy (24, 18); printf ("Presione cualquier tecla para continuar...");
	tecla = getch ();
	clrscr ();
	cuadro (80, 23, 1, 1, 205, 186, 201, 187, 200, 188);

	do {
			 tecla = getch ();
			 if (tecla == 32) {
				 clrscr (); x -= 2; y -= 2; px++; py++;
			 }
			 if (tecla == 13) {
				 clrscr (); x += 2; y += 2; px--; py--;
			 }
			 if (x < 60){
				 x = 60; y = 3; px = 11; py =  11;
			 }
			 if (x > 80){
				 x = 80; y = 23; px = 1; py =  1;
			 }
			 cuadro (x, y, px, py, 205, 186, 201, 187, 200, 188);
		 } while (tecla != 's' && tecla != 'S' && tecla != 'x' && tecla != 'X');
}