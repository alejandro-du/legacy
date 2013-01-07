#include <conio.h>
#include <stdlib.h>

void input (char *entrada);
void responder (int cod);

main (void)
{
	int num;
	char *frase[] = {"adios", "chao", "hastaluego", "hastapronto", "comoestas", "hola"};
	char entrada[120];

	clrscr ();

	textcolor (LIGHTBLUE);

	cprintf ("\r\nHola.\n");

	for (;;) {
		textcolor (YELLOW);
		input (entrada);
//		printf ("%d",strcmp (entrada, frase[num]));
		/* comprobar */
		for (num = 0; num < 5; num++) {
			if (!strcmp (entrada, frase[num])) {
				responder (num);
				break;
			}
		}
	} /* bucle infinito */
}

void input (char *entrada)
{
	int cont;

	for (cont = 0; cont < 120; cont++) {
		entrada[cont] = getch ();
		if (entrada[cont] == 13) break;
		cprintf ("%c", entrada[cont]);
		entrada[cont] = tolower (entrada[cont]);
		if (entrada[cont] == 32) cont--;
	}
	entrada[cont] = '\0';
	printf ("\n");
}

void responder (int cod)
{
	textcolor (YELLOW);
	switch (cod) {
		case 0:
		case 1:
		case 2:
		case 3:
			cprintf ("Chao...");
			exit (0);
		break;
	}
}