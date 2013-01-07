#include <dos.h>
#include <stdio.h>
#include <conio.h>
int inkey ();

main (void)
{
	int tecla;
	int x = 10, y = 10;

	clrscr ();
	while (tecla != 1) {
		tecla = inkey ();
		printf ("%d", tecla);
		switch (tecla) {
			case 72:
				y -=1;
			break;
			case 80:
				y +=1;
			break;
		}
	}
	return 0;
}

int inkey () /* presionar una tecla */
{
	int tecla, temp;

	tecla = inp (0x60);

	if (kbhit ()) {
		if (tecla == 1) exit (0);
		outportb (0x61,(temp = inportb(0x61)) | 0x80);
		outportb (0x61,temp);
		return (tecla);
	}
	else return (0);
} /* inkey */
