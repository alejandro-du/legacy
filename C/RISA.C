#include<stdlib.h>
#include<conio.h>


#define MAX_NOMBRES      30
#define MAX_LONG_NOMBRE  19
#define MAX_ACCIONES     44
#define MAX_LONG_ACCION  10
#define MAX_PARTES       41
#define MAX_LONG_PARTE   22

void imprimir(char *cadena);


main(void)
{
	char nombre[MAX_NOMBRES][MAX_LONG_NOMBRE] = {"Juan Carlos",
																				 "Edgar Arturo",
																				 "Mar¡a Ang‚lica",
																				 "La mama",
																				 "Jairo",
																				 "El abuelito Eliseo",
																				 "La abuelita Adela",
																				 "Ruth",
																				 "Jonathan",
																				 "Ricardo",
																				 "Cristina",
																				 "Catalina",
																				 "Marcelo",
																				 "Johana",
																				 "La mam  mona",
																				 "El pap  Moises",
																				 "Marina",
																				 "Carlos",
																				 "Lina",
																				 "Paola",
																				 "Sandra",
																				 "Javier",
																				 "Arturo",
																				 "Jilma",
																				 "Camilo",
																				 "Pipe",
																				 "Federico",
																				 "Ana Rosa",
																				 "Isis",
																				 "Diana"};

	char accion[MAX_ACCIONES][MAX_LONG_ACCION] = {"lame",
																								"chupa",
																								"come",
																								"prueva",
																								"rompe",
																								"patea",
																								"liquida",
																								"espicha",
																								"bloquea",
																								"escupe",
																								"vomita",
																								"despedaza",
																								"mira",
																								"canta",
																								"pinta",
																								"baila",
																								"gira",
																								"jala",
																								"pellisca",
																								"brilla",
																								"esnsera",
																								"barre",
																								"trapea",
																								"laba",
																								"moja",
																								"lee",
																								"resa",
																								"estira",
																								"alarga",
																								"encoje",
																								"roba",
																								"presta",
																								"compra",
																								"vende",
																								"alsa",
																								"bota",
																								"peina",
																								"escucha",
																								"toca",
																								"abre",
																								"cierra",
																								"saca",
																								"cuelga",
																								"encierra"};

	char parte[MAX_PARTES][MAX_LONG_PARTE] = {"el cabello",
																						"la frente",
																						"las cejas",
																						"las pesta¤as",
																						"la nuca",
																						"la nariz",
																						"los mocos",
																						"las laga¤as",
																						"las lagrimas",
																						"la boca",
																						"las babas",
																						"la lengua",
																						"el paladar",
																						"el cuello",
																						"el bigote",
																						"los hombros",
																						"el pecho",
																						"la espalda",
																						"la columna",
																						"la barriga",
																						"los muslos",
																						"las piernas",
																						"las rodillas",
																						"los pies",
																						" los brazos",
																						"la caja de dientes",
																						"las manos",
																						"las u¤as",
																						"el mugre de las u¤as",
																						"las garras",
																						"la sangre",
																						"el pancreas",
																						"los intestinos",
																						"los pulmones",
																						"las pesu¤as",
																						"la lombriz intestinal",
																						"las arrugas",
																						"las axilas",
																						"el sudor",
																						"la piel",
																						"los dedos"};

	int num, codigo, fila;

	clrscr();
	randomize();

	for(num = 0, fila = 3; num < 20; num++, fila++) {
		codigo = random(MAX_NOMBRES);
		gotoxy(3, fila);
		printf("%s ", nombre[codigo]);

		codigo = random(MAX_ACCIONES);
		printf("%s ", accion[codigo]);

		codigo = random(MAX_PARTES);
		printf("%s de ", parte[codigo]);

		codigo = random(MAX_NOMBRES);
		printf("%s.", nombre[codigo]);
	}
	getch();
	return 0;
}

void imprimir(char *cadena)
{
	int num;
	for(num = 0; cadena[num]; num++) {
		if(cadena[num] == " ") printf(" ");
		putch(cadena[num]);
	}
}