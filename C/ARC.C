#include <conio.h>
#include <dir.h>

main ()
{
	struct ffblk archivo;
	int fin, total_bytes_directorio = 0;

	clrscr ();

	fin = findfirst ("*.*", &archivo, 0);

	total_bytes_directorio = total_bytes_directorio + archivo.ff_fsize;

	total_bytes_directorio = archivo.ff_fsize;

	gotoxy (3, 3); cprintf ("\nNombre: %s", archivo.ff_name);
	gotoxy (3, 5); cprintf ("\nbytes: %ld", archivo.ff_fsize);
	gotoxy (3, 7); cprintf ("\ntotal bytes: %d", total_bytes_directorio);

	getch ();



	while (!fin) {
		fin = findnext (&archivo);

		total_bytes_directorio = total_bytes_directorio + archivo.ff_fsize;

		gotoxy (3, 3); cprintf ("\nNombre: %s", archivo.ff_name);
		gotoxy (3, 5); cprintf ("\nbytes: %ld", archivo.ff_fsize);
		gotoxy (3, 7); cprintf ("\ntotal bytes: %d", total_bytes_directorio);
		gotoxy (3, 9); cprintf ("\ntotal bytes l: %ld", total_bytes_directorio);
		getch ();


	}
}