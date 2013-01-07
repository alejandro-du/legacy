#include <conio.h>
#include <stdlib.h>
#define NUMMENSAJES 4

main (void)
{
	int a, b, respuesta, intentos, nume, bien = 0;
	char mensaje[NUMMENSAJES][80] = {"Correcto.",
											"Sigue as¡.",
											"­ Muy Bien !",
											"­ Exelente !"};

	clrscr ();

	puts ("TABLAS DE MULTIPLICAR");
	printf ("\nNumero de ejercicios: ");
	scanf ("%d", &nume);

	randomize ();

	for (intentos = 0;;) {
		a = random (8) + 2;
		b = random (8) + 2;
		while (respuesta != a * b) {
			printf ("\n %d.     %d x %d = ", intentos + 1, a, b);
			scanf ("%d", &respuesta);
			intentos++;
			if (intentos >= nume) {
				bien--;
				break;
			}
		}
		bien++;
		if (intentos >= nume) {
			if (respuesta == a * b)	bien++;
			break;
		}
		printf ("    %s\n", mensaje[random (NUMMENSAJES)]);
	}

	printf ("\n\n      RESULTADOS:\n");
	printf ("      ------------\n");
	printf ("\n     Total de ejercicios : %d\n", nume);
	printf ("\n     Ejercicios resueltos BIEN: %d\n", bien);
	printf ("\n     Ejercicios resueltos MAL: %d\n", nume - bien);
	printf ("\n     Nota final: %d", bien * 100 / intentos);
	getch ();

	return 0;
}