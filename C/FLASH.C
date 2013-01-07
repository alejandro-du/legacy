main ()
{
	char a;

	clrscr ();

	printf ("***** ­ Este es un \"Flash\" informativo ! *****\n");

	printf ("\n");
	puts ("Para obtener la informaci¢n presisa presione una tecla...");
	a = getch ();
	clrscr ();
	puts ("***************************************************************************");
	puts ("Esta es informaci¢n de ultima hora...");
	a = getch();
	puts ("En este momento usted esta leyendo esto...");
	puts ("Hasta la proxima...");
}