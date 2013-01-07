#include <conio.h>

void main (void)
{
	char c;

	printf ("\n");
		printf ("C:\\>");

	do {
		c = getch ();
		if (isspace (c)) {
			printf ("%c", c);
			c = '\0';
		}
		if (isprint (c)) printf ("%c", c + 1);
	} while (c != 3);
	return 0;
}