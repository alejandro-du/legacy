/****************************************************************************
*	    		 A D M I N I S T R A D O R   D E   B I B L I O T E C A            *
*		  			  Un £til programa para administrar su biblioteca.              *
*			  											 Versi¢n 1.0                                  *
*				  										DPA Software.                                 *
*				   	Copyright (c) 1997 Jairo Alejandro Duarte Avenda¤o.             *
*				      Santaf‚ de Bogot , D.C. Colombia. Mayo de 1997.               *
*								  		 Redactado en Borland C++ 3.1                         *
*****************************************************************************/

#include <stdio.h>
#include <conio.h>

void presentacion (void); /* Presentaci¢n del programa */
void centrar (char *cad, int fila); /* Centrado del texto */
void menu (void);

extern int _wscroll = 0;

main (void)
{
	presentacion ();
	menu ();
	return 0;
}

void presentacion (void) /* Presentaci¢n del programa */
{
	_setcursortype(_NOCURSOR);
	textbackground (0);
	clrscr ();
	textcolor (15);
	centrar ("A D M I N I S T R A D O R   D E   B I B L I O T E C A", 4);
	textcolor (7);
	centrar ("Un £til programa para administrar su biblioteca.", 7);
	centrar ("Escrito en lenguaje C", 8);
	centrar ("DPA SOFTWARE", 12);
	centrar ("Copyright (c) 1997 Jairo Alejandro Duarte Avenda¤o.", 13);
	centrar ("Todos los derechos reservados.", 14);
	centrar ("Santaf‚ de Bogot , D.C. Colombia.", 15);
	centrar ("Versi¢n 1.0", 16);
	centrar ("(Presione una tecla para continuar)", 22);
	if (getch () == 27) {
		clrscr ();
		printf ("Autor: Jairo Alejandro Duarte Avenda¤o. Colombia, 1997.");
		exit (0);
	}
}

void menu (void)
{
	textbackground (1);
	clrscr ();
	textbackground (3);
	textcolor (1);
	centrar ("            A D M I N I S T R A D O R   D E   B I B L I O T E C A               ", 1);
	textbackground (7);
	textcolor (0);
	centrar (" F1 Ayuda                                                                       ", 25);
	
}



void centrar (char *cad, int fila) /* Centrado del texto */
{
	gotoxy ((82 - strlen (cad)) / 2, fila);
	cprintf ("%s", cad);
}