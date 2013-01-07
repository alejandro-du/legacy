/*
Copyright(c) 1996 Jairo Alejandro Duarte Avenda¤o.
*/

#include <graphics.h>
#include <stdio.h>

void arriba (void);
void abajo (void);
void acercar (void);
void pedir (void);
void mostrar (void);
void alejar (void);
void giro_derecha (void);
void giro_izquierda (void);
int x1 = 0, y1 = 0, x2 = 639, y2 = 0, x3 = 639, y3 = 349, x4 = 0, y4 = 349, pagina = 0;


void main (void)
{
	int controlador = VGA, modo = VGAMED;
	
	initgraph (&controlador, &modo, "");

	setcolor (9);
	setfillstyle (1, 1);
	mostrar ();
	for (;;) pedir ();
}

void pedir (void)
{
	char c;

	c = getch ();
	
	switch (c) {
		case 'Q':
		case 'q':
			acercar ();
			break;
		case 'A':
		case 'a':
			alejar ();
			break;
		case 'P':
		case 'p':
			giro_derecha ();
			break;
		case 'O':
		case 'o':
			giro_izquierda ();
			break;
		case 'W':
		case 'w':
			arriba ();
			break;
		case 'S':
		case 's':
			abajo ();
			break;

		case 'X':
		case 'x':
			closegraph ();
			exit (0);
			break;
	}
}

void mostrar (void)
{
	pagina = !pagina;
	setactivepage (pagina);
	clearviewport ();
	line (x1, y1, x2, y2);
	line (x2, y2, x3, y3);
	line (x3, y3, x4, y4);
	line (x4, y4, x1, y1);
	line (x1, y1, 0, 0);
	line (x2, y2, 639, 0);
	line (x3, y3, 639, 349);
	line (x4, y4, 0, 349);

	if (y1 < y2) floodfill (x2 - 1, y2 + 1, 9);
	else floodfill (x1 + 1, y1 + 1, 9);
	setvisualpage (pagina);
}

void alejar (void)
{
	x1+=8;
	y1+=4;
	x2-=8;
	y2+=4;
	x3-=8;
	y3-=4;
	x4+=8;
	y4-=4;
	mostrar ();
}

void acercar (void)
{
	x1-=8;
	y1-=4;
	x2+=8;
	y2-=4;
	x3+=8;
	y3+=4;
	x4-=8;
	y4+=4;
	mostrar ();
}

void giro_derecha (void)
{
	x1-=11;
	x2-=11;
	x3-=11;
	x4-=11;
	if (y1 == y2 | y1 < y2) {
		y1-=0.5;
		y4+=1;
	}
	else {
		y2+=1;
		y3-=1;
	}
	mostrar ();
}

void giro_izquierda (void)
{
	x1+=11;
	x2+=11;
	x3+=11;
	x4+=11;
	if (y1 == y2 | y1 > y2) {
		y2-=0.5;
		y3+=1;
	}
	else {
		y1+=1;
		y4-=1;
	}
	mostrar ();
}

void arriba (void)
{
	y1+=10;
	y2+=10;
	y3+=10;
	y4+=10;
	mostrar ();
}

void abajo (void)
{
	y1-=10;
	y2-=10;
	y3-=10;
	y4-=10;
	mostrar ();
}