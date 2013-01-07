#include "DPALIB.H"
#include "graficos.h"
#include "teclado.h"

#include "stdlib.h"

#define MASCARA 0 /* color que no se dibujar  en la memoria de video (fondo) */

#define ARRIBA    0 /* ids. para el array del teclado */
#define ABAJO     1
#define IZQUIERDA 2
#define DERECHA   3
#define FUEGO 		4

#define MAXB          10  /* n£mero m ximo de disparos activos de la nave */
#define MAXENP        100 /* N£mero m ximo de enemigos en el mapa */
#define MAX_P         152 /* n£mero m ximo de patrones de movimiento */
#define MAX_SPRITES   7   /* numero total de sprites para los enemigos */
#define MAX_ITEMS     4  	/* total de items posibles */
#define MAX_ARMAS     4
#define TB            13  /* velocidad del disparo */
#define DESTRUIR_BALA -1  /* valor para los disparos inactivos de la nave */
#define DESTRUIR_EN   -1  /* valor del estado inactivo para los enemigos */
#define DISPARO_LIBRE -1  /* permitir el disparo enemigo */
#define C_ESTRELLAS_I 223 /* color de las estrellas */

#define ANIM1 24 /* ids. para las animaciones dentro del mapa */
#define ANIM2 47
#define ANIM3 48

#define SC_INC   1         /* incremento del scroll (velocidad del juego) */
#define D_INC    200       /* duracion del turbo */
#define E_INC    1         /* aumento de energia */
#define A_INC    590       /* duracion de la armadura */
#define MAX_T    D_INC * 5 /* tope m ximo del turbo */
#define MAX_A    A_INC * 7 /* tope m ximo de la armadura */
#define DISP_A   570       /* da¤o de la armadura al recibir un disparo enemigo */
#define TURBO_V  5         /* velocidad turbo */
#define NORMAL_V 2         /* velocidad normal */

#define LASER_1 0
#define LASER_2 1
#define LASER_3 2
#define LASER_4 3

#define EN_GRIS    1 /* tipos de enemigos */
#define EN_MORADO  2
#define EN_CAFE    3
#define EN_ROJO    4
#define EN_PARED1I 5
#define EN_PARED1D 6
#define EN_BALA    7

#define I_TURBO    1 /* ids. para los items */
#define I_ENERGIA  2
#define I_VIDA     3
#define I_ARMADURA 4

int s_alto(s_SPRITE_SPE *sp, int numero_sprite);
int s_ancho(s_SPRITE_SPE *sp, int numero_sprite);


typedef struct { /* estructura de datos para cada enemigo */
	int x, y;            /* posicion en pantalla */
	int x_map, y_map;    /* posicion dentro del mapa */
	int tipo;            /* clase de enemigo */
	int x_1, y_1, x_d;   /* algoritmo de.............. */
	int x_2, y_2, y_d;
	int xinc1, xinc2,
			yinc1, yinc2;
			d, dinc1, dinc2;
	BYTE energia;        /* energia del enemigo */
	BYTE mov;            /* patron de movimiento */
	BOOL act;            /* estado */
	BOOL item;           /* item que guarda el enemigo */
} s_ENEMIGO;

main(void)
{
	s_MAPA mapa; s_BLK blk; /* mapa y graficos del esenario */

	s_SPRITE_SPE  nave,     /* sprites enlazados */
								disparo,
								expl,
								conb,
                armadura,
								enem[MAX_SPRITES],
								expen,
								anim1,
								nv,
								anim2,
								anim3,
								disp,
								elemento,
								item[MAX_ITEMS];

	s_FUENTE numeros,   /* fuente para mostrar el puntaje total */
					 numeros_p; /* fuente de n£meros peque¤a */

	BYTE tecla[5];    /* cada tecla que puede presionarse */
	BOOL muerte;      /* estado de la nave */

	s_ENEMIGO enemigo[MAXENP]; /* array para los datos de los enemigos */

	char frame_anim1 = 0, /* variables para controlar las vi¤etas de los sprites */
			 frame_anim2 = 0,
			 frame_enemigo = 0,
			 frame_nv = 0,
			 frame_nave = 0,
			 frame_arm = 0,
			 frame_disp = 0,
			 frame_item = 0;

	int	velocidad,              /* velocidad de la nave */
			energia,                /* energia restante de la nave */
			arma,
			municion_ad[MAX_ARMAS], /* municion adquirida */
			municion[MAX_ARMAS],    /* municion de cada arma */
			duracion_v,           	/* tiempo restante del turvo */
			duracion_a,           	/* tiempo restante de la armadura */
			armaduras,
			turbos,
			cont, cont2,          	/* contadores para los bucles */
			vidas = 3,            	/* total de las vidas */
			bloque,               	/* destino de los bloques de fondo (colisiones con el mapa) */
			deltax, deltay,
			en_ancho, en_alto,    	/* ancho y alto para cada sprite enemigo */
			total_enemigos_nivel, 	/* n£mero de enemigos en cada mapa (declarado en el archivo .DAT de los enemigos */
			TOPE_Y; 					    	/* tope vertical del scroll */

	long int puntos = 0; /* total de puntos */
	char buffer[10];

	BYTE  ult_b = 0; /* control de los disparos (salida lenta de cada disparo) */

	FILE *archivo;    /* flujo para los archivos */

	char patron[MAX_P] = /* patron de movimiento en circulo */
	{ -1,1,  -1,0,  -1,1,  -1,0, -1,1,  -1,0,  -1,1,  -1,1,  -1,1,  0,1,  -1,1,  0,1,  0,1,  0,1,  0,1,  0,1,  0,1,  0,1,  0,1,
		1,1,  0,1,  1,1,  1,1, 1,1,  1,0,  1,1,  1,0,  1,1,  1,0,  1,1,  1,0,  1,0,  1,0,  1,0,  1,0,  1,0,  1,0,  1,0,
		1,-1,  1,0,  1,-1,  1,0, 1,-1,  1,0,  1,-1,  1,-1,  1,-1,  0,-1,  1,-1,  0,-1,  0,-1,  0,-1,  0,-1,  0,-1,  0,-1,  0,-1,  0,-1,
		1,-1,  0,-1,  -1,-1,  -1,-1, -1,-1,  -1,0,  -1,-1,  -1,0,  -1,-1,  -1,0,  -1,-1,  -1,0,  -1,0,  -1,0,  -1,0,  -1,0,  -1,0,  -1,0,  -1,0
	};

	BYTE ancho_sprites[MAX_SPRITES] = {20, 21, 20, 20, 27, 27, 11}; /* ancho de cada sprite enemigo */
	BYTE alto_sprites[MAX_SPRITES] =  {11, 13, 11, 13, 17, 17, 13};  /* alto de cada sprite enemigo */
	BYTE ancho_items[MAX_ITEMS] = {21, 14, 9, 9};         /* ancho de cada item */
	BYTE alto_items[MAX_ITEMS] = {8, 9, 10, 10};          /* alto de cada item */
	BYTE v_disparos[MAX_SPRITES] = {3, 2, 0, 1, 1, 1, 1}; /* velocidad de los disparos enemigos */
	BYTE v_arma[MAX_ARMAS] = {3, 5, 9, 9};
	int puntos_en[MAX_SPRITES] = {800, 770, 610, 935, 910, 900};
	int puntos_it[MAX_ITEMS] = {15, 50, 110, 60};

	struct { /* estructura de datos para cada bala */
		int x,     /* posicion horizontal en la pantalla */
				y,     /* posicion vertical en la pantalla */
				act;   /* estado de la bala (activa o inactiva) */
		BYTE tipo;
	} bala[MAXB];

	/* Carga de archivos */

	if(Cargar_Fuente("fnt1.fnt", &numeros, "0123456789") != OK) {
		printf("Error FUENTE\a");
		return 1;
	}
	if(Cargar_Fuente("fnt2.fnt", &numeros_p, "0123456789") != OK) {
		printf("Error FUENTE\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("nv.spe", &nv) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("navesa1.spe", &anim1) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("disp1.spe", &disp) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("esc.spe", &armadura) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("aa.spe", &anim2) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("ab.spe", &anim3) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("turbo.spe", &item[0]) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("enrg.spe", &item[1]) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("vida.spe", &item[2]) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("arm.spe", &item[3]) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("element.spe", &elemento) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("enemigo1.spe", &enem[0]) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("enemigo2.spe", &enem[1]) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("enemigo3.spe", &enem[2]) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("enemigo4.spe", &enem[3]) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("enemigo5.spe", &enem[4]) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("enemigo6.spe", &enem[5]) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("enemigo7.spe", &enem[6]) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Mapa("nivel1.map", &mapa) != OK) {
		printf("\nError al cargar el mapa.\n\a");
		return 1;
	}
	if(Cargar_Bloques("naves.blk", &blk, 32, 32, 120) != OK) {
		printf("\nError al cargar archivo de bloques\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("nave.spe", &nave) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("expl.spe", &expl) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		Restaurar_Modo();
		exit(0);
	}
	if(Cargar_Sprite_Enlazado("expl.spe", &expen) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		Restaurar_Modo();
		exit(0);
	}
	if(Cargar_Sprite_Enlazado("cont.spe", &conb) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	if(Cargar_Sprite_Enlazado("disparo.spe", &disparo) != OK) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
	Inicializar_320x200X();

	if(!Cargar_Paleta("naves.pal")) {
		Restaurar_Modo();
		printf("\nError al cargar la paleta de colores\n\a");
		return 1;
	}

	Inicializar_Teclado();
	Inicializar_Pantalla_Virtual();
	Activar_PV; /* activar modo de pantalla virtual */


	do { /* bucle principal */
	for(cont = 0; cont < MAXB; cont++) bala[cont].act = DESTRUIR_BALA; /* desactivar todas las balas */
	for(cont = 0; cont < MAXENP; cont++) enemigo[cont].act = FALSO; /* desactivar todos los enemigos */

	mapa.bloques_horizontales = 10;
	mapa.bloques_verticales = 6;

	TOPE_Y = blk.long_y * mapa.bloques_verticales;
	nave.pos_y = 120;
	nave.pos_x = 130;
	mapa.y     = mapa.long_y - 6;
	mapa.despy = 0;
	muerte     = FALSO;
	nv.pos_y   = 3;
	puntos     = 0;
	energia    = 3;
	velocidad  = NORMAL_V;
	duracion_v = 0;
	duracion_a = 0;
	armaduras = 2;
	turbos = 3;
	vidas--;
	arma = LASER_1;
	municion_ad[LASER_1] = 100;
	municion[LASER_1] = municion_ad[LASER_1];
	municion_ad[LASER_2] = 100;
	municion[LASER_2] = municion_ad[LASER_2];
	municion_ad[LASER_3] = 100;
	municion[LASER_3] = municion_ad[LASER_3];
	municion_ad[LASER_4] = 100;
	municion[LASER_4] = municion_ad[LASER_4];

	tecla[ARRIBA]    = FALSO;
	tecla[ABAJO]     = FALSO;
	tecla[IZQUIERDA] = FALSO;
	tecla[DERECHA]   = FALSO;
	tecla[FUEGO]     = FALSO;


	/* cargar posiciones de los enemigos dentro del mapa */

	if((archivo = fopen("enmg.dat", "rb")) == NULL) {
		Restaurar_Modo();
		printf("Error al intentar abrir el archivo DAT.\a");
		return 1;
	}
	total_enemigos_nivel = getc(archivo); /* leer el n£mero de enemigos del nivel */
	if(total_enemigos_nivel > MAXENP) {
		Restaurar_Modo();
		printf("Error al leer el archivo .DAT.\a");
		return 1;
	}
	for(cont = 0; cont < total_enemigos_nivel; cont++) {
		enemigo[cont].tipo = getc(archivo);
		enemigo[cont].x_map = getc(archivo);
		enemigo[cont].y_map = getc(archivo);
		enemigo[cont].item = getc(archivo);

		if(ferror(archivo) || feof(archivo)) {
			Restaurar_Modo();
			printf("Error al leer el archivo .DAT.\a");
			return 1;
		}
		enemigo[cont].mov = 1;
		enemigo[cont].x_1 = DISPARO_LIBRE;
		if(enemigo[cont].tipo == EN_ROJO) {
			enemigo[cont].energia = 3;
			enemigo[cont].mov = 0;
		}
		else if(enemigo[cont].tipo == EN_BALA) enemigo[cont].energia = 6;
		else if(enemigo[cont].tipo == EN_MORADO) enemigo[cont].energia = 1;
		else if(enemigo[cont].tipo == EN_PARED1I || enemigo[cont].tipo == EN_PARED1D) enemigo[cont].energia = 4;
		else enemigo[cont].energia = 2;
	}
	fclose(archivo);

	do {
//		gotoxy(1, 25); printf("%d %d ", municion[1], municion[2]);

		if(gb_Codigo_Cabecera != gb_Codigo_Tail) {
			++gb_Codigo_Cabecera;
		}

		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 72 || gb_Codigo_q[gb_Codigo_Tail - 1] == 72) { /* arriba presionada */
			tecla[ARRIBA] = VERDADERO;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 200 || gb_Codigo_q[gb_Codigo_Tail - 1] == 200) { /* arriba liberada */
			tecla[ARRIBA] = FALSO;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 80 || gb_Codigo_q[gb_Codigo_Tail - 1] ==80) { /* abajo presionada */
			tecla[ABAJO] = VERDADERO;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 208 || gb_Codigo_q[gb_Codigo_Tail - 1] == 208) { /* abajo liberada */
			tecla[ABAJO] = FALSO;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 75 || gb_Codigo_q[gb_Codigo_Tail - 1] == 75) { /* izquierda presionada */
			tecla[IZQUIERDA] = VERDADERO;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 203 || gb_Codigo_q[gb_Codigo_Tail - 1] == 203) { /* izquierda liberada */
			tecla[IZQUIERDA] = FALSO;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 77 || gb_Codigo_q[gb_Codigo_Tail - 1] == 77) { /* derecha presionada */
			tecla[DERECHA] = VERDADERO;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 205 || gb_Codigo_q[gb_Codigo_Tail - 1] == 205) { /* derecha liberada */
			tecla[DERECHA] = FALSO;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 56 || gb_Codigo_q[gb_Codigo_Tail - 1] == 56) { /*  presionado */
			tecla[FUEGO] = VERDADERO;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 184 || gb_Codigo_q[gb_Codigo_Tail - 1] == 185) { /*  liberado */
			tecla[FUEGO] = FALSO;
			ult_b = TB;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 2 || gb_Codigo_q[gb_Codigo_Tail - 1] == 2) { /* 1 presionado */
			arma = LASER_1;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 3 || gb_Codigo_q[gb_Codigo_Tail - 1] == 3) { /* 2 presionado */
			arma = LASER_2;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 4 || gb_Codigo_q[gb_Codigo_Tail - 1] == 4) { /* 3 presionado */
			arma = LASER_3;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 5 || gb_Codigo_q[gb_Codigo_Tail - 1] == 5) { /* 4 presionado */
			arma = LASER_4;
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 20 || gb_Codigo_q[gb_Codigo_Tail - 1] == 20) { /* T liberada */
			gb_Codigo_q[gb_Codigo_Cabecera - 1] = 0;
			turbos--;
			if(turbos < 0) turbos = 0;
			else { /* activar */
				duracion_v += D_INC;
				if(duracion_v > MAX_T) duracion_v = MAX_T;
				velocidad = TURBO_V;
			}
		}
		if(gb_Codigo_q[gb_Codigo_Cabecera - 1] == 30 || gb_Codigo_q[gb_Codigo_Tail - 1] == 30) { /* A liberada */
			gb_Codigo_q[gb_Codigo_Cabecera - 1] = 0;
			armaduras--;
			if(armaduras < 0) armaduras = 0;
			else {
				duracion_a += A_INC;
				if(duracion_a > MAX_A) duracion_a = MAX_A;
			}
		}

		/* mover nave */
		if(tecla[ARRIBA]) nave.pos_y -= velocidad - 1;
		if(tecla[ABAJO]) nave.pos_y += velocidad;
		if(tecla[IZQUIERDA]) nave.pos_x -= velocidad;
		if(tecla[DERECHA]) nave.pos_x += velocidad;

		if(tecla[FUEGO]) {
			if(municion[arma] > 0) {
				for(cont = 0; cont < MAXB; cont++) {
					if(bala[cont].act == DESTRUIR_BALA) {
						if(ult_b >= TB) {
							bala[cont].x = nave.pos_x + 16;
							bala[cont].y = nave.pos_y - 5;
							bala[cont].act = 0;
							bala[cont].tipo = arma;
							disparo.pos_x = bala[cont].x;
							disparo.pos_y = bala[cont].y;
							municion[arma]--;
							ult_b = 0;
							break;
						}
					}
				}
			}
			else municion[arma] = -1;
		}
		ult_b++;
		/* limites en la pantalla de la nave */
		if(nave.pos_x < 0) {
			nave.pos_x = 0;
			tecla[IZQUIERDA] = FALSO;
		}
		if(nave.pos_y < 0) {
			nave.pos_y = 0;
			tecla[ARRIBA] = FALSO;
		}
		if(nave.pos_x + 37 > 320) {
			nave.pos_x = 320 - 37;
			tecla[DERECHA] = FALSO;
		}
		if(nave.pos_y + 28 > TOPE_Y) {
			nave.pos_y = TOPE_Y - 28;
			tecla[ABAJO] = FALSO;
		}


		/* *********** ESENARIO *********** */

		Borrar_Mem_Video(0);

		Desvanecer_Pantalla(C_ESTRELLAS_I, 10, 0); /* estrellas intermitentes */
		Desvanecer_Pantalla(C_ESTRELLAS_I + 1, 4, 0);

		if(mapa.y) Scroll_Vertical_D(&mapa, &blk, SC_INC);
		else Scroll_Vertical_D(&mapa, &blk, 0);
		Mostrar_Sprite_Mapa(&mapa, &blk, &anim1, 3, ANIM1, frame_anim1, FALSO, SC_V);
		Mostrar_Sprite_Mapa(&mapa, &blk, &anim2, 3, ANIM2, frame_anim2, FALSO, SC_V);
		Mostrar_Sprite_Mapa(&mapa, &blk, &anim3, 3, ANIM3, frame_anim2, FALSO, SC_V);

		for(cont = 0; cont < MAXB; cont++) { /* disparos */
			if(bala[cont].act == 0) {
				bala[cont].y -= v_arma[bala[cont].tipo];
				if (bala[cont].y < 0) bala[cont].act = DESTRUIR_BALA;
				disparo.pos_x = bala[cont].x;
				disparo.pos_y = bala[cont].y;

				bloque = Obtener_Bloque_Sprite(&blk, &mapa, bala[cont].x, bala[cont].y);
				if(bloque == 0 || bloque == 49 || bloque == 50 || bloque == 51)
				bloque = Obtener_Bloque_Sprite(&blk, &mapa, bala[cont].x + 4, bala[cont].y);
				if(bloque == 0 || bloque == 49 || bloque == 50 || bloque == 51) Mostrar_Sprite_Enlazado(&disparo, bala[cont].tipo);
				else {
					bala[cont].act = 1; /* contacto con un muro */
				}
			}
		}

		/* mostrar nave */
		resolucion_vertical = TOPE_Y;
		Mostrar_Sprite_Enlazado_Mascara(&nave, frame_nave, MASCARA);

		if(duracion_a) { /* mostrar armadura en la nave */
			armadura.pos_x = nave.pos_x; armadura.pos_y = nave.pos_y;
			Mostrar_Sprite_Enlazado_Mascara(&armadura, frame_arm, MASCARA);
		}

		/* ************  enemigos  ************ */

		for(cont = 0; cont < total_enemigos_nivel; cont++) {
			if(enemigo[cont].y_map == mapa.y -1 && enemigo[cont].act == FALSO) { /* surge enemigo */
				enemigo[cont].act = VERDADERO; /* activar enemigo */
				enemigo[cont].x = enemigo[cont].x_map * 32;
				enemigo[cont].y = -(blk.long_y - 1);
				if(enemigo[cont].tipo == EN_PARED1D) enemigo[cont].x += 4;
			}

			if(enemigo[cont].act == VERDADERO) { /* enemigo activo */
				enem[enemigo[cont].tipo - 1].pos_x = enemigo[cont].x;
				enem[enemigo[cont].tipo - 1].pos_y = enemigo[cont].y;
				Mostrar_Sprite_Enlazado_Mascara(&enem[enemigo[cont].tipo - 1], frame_enemigo, MASCARA); /* mostrar enemigo */

				/* movimientos enemigos */
				switch(enemigo[cont].tipo) {
					case EN_GRIS: /* movimiento hacia abajo y en zig zag */

						enemigo[cont].y += SC_INC * 2;
						if(enemigo[cont].x < (enemigo[cont].x_map * 32) - 5) enemigo[cont].mov = 1;
						else if(enemigo[cont].x > (enemigo[cont].x_map * 32) + 5) enemigo[cont].mov = 2;
						if(enemigo[cont].mov == 1) enemigo[cont].x += 1;
						else if(enemigo[cont].mov == 2) enemigo[cont].x -= 1;

					break;

					case EN_MORADO: /* avance rapido hacia abajo y en zig zag en el centro */

						enemigo[cont].y += SC_INC + 3;
						if(enemigo[cont].x < (resolucion_horizontal / 2) - 2) enemigo[cont].mov = 1;
						else if(enemigo[cont].x > (resolucion_horizontal / 2) + 2) enemigo[cont].mov = 2;
						if(enemigo[cont].mov == 1) enemigo[cont].x += 1;
						else if(enemigo[cont].mov == 2) enemigo[cont].x -= 1;
					break;

					case EN_CAFE: /* movimiento hacia la nave y avance lento */

						if(nave.pos_y + 26 > enemigo[cont].y) {
							if(nave.pos_x + 8 > enemigo[cont].x) enemigo[cont].x++;
							if(nave.pos_x + 8 < enemigo[cont].x) enemigo[cont].x--;
							enemigo[cont].y += SC_INC;
							enemigo[cont].mov++;
							if(enemigo[cont].mov >= 8) {
								enemigo[cont].y += SC_INC;
								enemigo[cont].mov = 0;
							}
						}
						else enemigo[cont].y += SC_INC << 1;
					break;

					case EN_ROJO: /* movimiento en circulos */

						enemigo[cont].x += patron[enemigo[cont].mov];
						enemigo[cont].mov++;
						enemigo[cont].y += patron[enemigo[cont].mov];
						enemigo[cont].mov++;
						if(enemigo[cont].mov >= MAX_P) enemigo[cont].mov = 0;
						enemigo[cont].y += SC_INC;

					break;

					case EN_PARED1I: /* movimiento hacia el enemigo en el eje Y izquierda (I) */

						if(nave.pos_y > enemigo[cont].y) {
							bloque = Obtener_Bloque_Sprite(&blk, &mapa, enemigo[cont].x - 2, enemigo[cont].y + 17);
							if(bloque != 0 && bloque != 49 && bloque != 50 && bloque != 51) enemigo[cont].y += SC_INC * 2;
							else enemigo[cont].y += SC_INC;
						}
						else if(nave.pos_y < enemigo[cont].y) {
							bloque = Obtener_Bloque_Sprite(&blk, &mapa, enemigo[cont].x - 2, enemigo[cont].y);
							if(bloque != 0 && bloque != 49 && bloque != 50 && bloque != 51) enemigo[cont].y -= SC_INC;
							else enemigo[cont].y += SC_INC;
						}
						else {
							bloque = Obtener_Bloque_Sprite(&blk, &mapa, enemigo[cont].x - 2, enemigo[cont].y);
							if(bloque == 0 || bloque == 49 || bloque == 50 || bloque == 51) enemigo[cont].y += SC_INC;
						}
					break;

					case EN_PARED1D: /* movimiento hacia el enemigo en el eje Y derecha (D) */

						if(nave.pos_y > enemigo[cont].y) {
							bloque = Obtener_Bloque_Sprite(&blk, &mapa, enemigo[cont].x + 29 + 28, enemigo[cont].y + 17);
							if(bloque != 0 && bloque != 49 && bloque != 50 && bloque != 51) enemigo[cont].y += SC_INC * 2;
							else enemigo[cont].y += SC_INC;
						}
						else if(nave.pos_y < enemigo[cont].y) {
							bloque = Obtener_Bloque_Sprite(&blk, &mapa, enemigo[cont].x + 29 + 28, enemigo[cont].y);
							if(bloque != 0 && bloque != 49 && bloque != 50 && bloque != 51) enemigo[cont].y -= SC_INC;
							else enemigo[cont].y += SC_INC;
						}
						else {
							bloque = Obtener_Bloque_Sprite(&blk, &mapa, enemigo[cont].x + 29 + 28, enemigo[cont].y);
							if(bloque == 0 || bloque == 49 || bloque == 50 || bloque == 51) enemigo[cont].y += SC_INC;
						}
					break;

					case EN_BALA:
						enemigo[cont].y += SC_INC << 1;
						enemigo[cont].mov++;
						if(enemigo[cont].mov >= 3) {
							if(nave.pos_x + 12 > enemigo[cont].x) enemigo[cont].x++;
							else if(nave.pos_x + 12 < enemigo[cont].x) enemigo[cont].x--;
							enemigo[cont].mov = 0;
						}
					break;

				}

				if(enemigo[cont].x_1 == DISPARO_LIBRE && random(10) == 6) { /* enemigo dispara */
					enemigo[cont].x_1 = enemigo[cont].x + (ancho_sprites[enemigo[cont].tipo - 1] >> 1);
					enemigo[cont].y_1 = enemigo[cont].y + (alto_sprites[enemigo[cont].tipo - 1] >> 1);
					enemigo[cont].x_2 = nave.pos_x + 17;
					enemigo[cont].y_2 = nave.pos_y;

					deltax = abs(enemigo[cont].x_2 - enemigo[cont].x_1);
					deltay = abs(enemigo[cont].y_2 - enemigo[cont].y_1);

					if(deltax >= deltay) {

						enemigo[cont].d = ( deltay << 1) - deltax;
						enemigo[cont].dinc1 = deltay << 1;
						enemigo[cont].dinc2 = (deltay - deltax) << 1;

						enemigo[cont].xinc1 = 1 + v_disparos[enemigo[cont].tipo - 1];
						enemigo[cont].xinc2 = 1 + v_disparos[enemigo[cont].tipo - 1];
						enemigo[cont].yinc1 = 0 + v_disparos[enemigo[cont].tipo - 1];
						enemigo[cont].yinc2 = 1 + v_disparos[enemigo[cont].tipo - 1];;
					}
					else {
						enemigo[cont].d = (deltax << 1) - deltay;
						enemigo[cont].dinc1 = deltax << 1;
						enemigo[cont].dinc2 = (deltax - deltay) << 1;

						enemigo[cont].xinc1 = 0 + v_disparos[enemigo[cont].tipo - 1];;
						enemigo[cont].xinc2 = 1 + v_disparos[enemigo[cont].tipo - 1];;
						enemigo[cont].yinc1 = 1 + v_disparos[enemigo[cont].tipo - 1];;
						enemigo[cont].yinc2 = 1 + v_disparos[enemigo[cont].tipo - 1];;
					}

					if(enemigo[cont].x_1 > enemigo[cont].x_2) {
						enemigo[cont].xinc1 = -(enemigo[cont].xinc1);
						enemigo[cont].xinc2 = -(enemigo[cont].xinc2);
					}

					if(enemigo[cont].y_1 > enemigo[cont].y_2) {
						enemigo[cont].yinc1 = -(enemigo[cont].yinc1);
						enemigo[cont].yinc2 = -(enemigo[cont].yinc2);
					}

					enemigo[cont].x_d = enemigo[cont].x_1;
					enemigo[cont].y_d = enemigo[cont].y_1;
				}

				if(enemigo[cont].y > 193) { /* sale enemigo */
					enemigo[cont].act = FALSO;
				}

			}

			if(enemigo[cont].x_1 > DISPARO_LIBRE) { /* manejar el disparo enemigo */
				disp.pos_x = enemigo[cont].x_d;
				disp.pos_y = enemigo[cont].y_d;
				enemigo[cont].y_d += SC_INC;
				Mostrar_Sprite_Enlazado_Mascara(&disp, frame_disp, MASCARA);
				if(enemigo[cont].d < 0) {
					enemigo[cont].d += enemigo[cont].dinc1;
					enemigo[cont].x_d += enemigo[cont].xinc1;
					enemigo[cont].y_d += enemigo[cont].yinc1;
				}
				else {
					enemigo[cont].d += enemigo[cont].dinc2;
					enemigo[cont].x_d += enemigo[cont].xinc2;
					enemigo[cont].y_d += enemigo[cont].yinc2;
				}
				 /* verificar si sale el disparo o si se estrella con un muro */
				if(enemigo[cont].y_d > 193 || enemigo[cont].y_d < 0 || enemigo[cont].x_d > 319 || enemigo[cont].x_d < 0) enemigo[cont].x_1 = DISPARO_LIBRE;
				bloque = Obtener_Bloque_Sprite(&blk, &mapa, enemigo[cont].x_d, enemigo[cont].y_d);
				if(bloque != 0 && bloque != 49 && bloque != 50 && bloque != 51) enemigo[cont].x_1 = DISPARO_LIBRE - conb.total_sprites;

				/* colisi¢n del disparo enemigo con la nave (cuadros de colisi¢n en NAVECL.SPR */
				if(Colision_Punto(enemigo[cont].x_d + 1, enemigo[cont].y_d + 1, nave.pos_x + 18, nave.pos_y + 4, 3, 4) ||
				Colision_Punto(enemigo[cont].x_d + 1, enemigo[cont].y_d + 1, nave.pos_x + 13, nave.pos_y + 13, 13, 6) ||
				Colision_Punto(enemigo[cont].x_d + 1, enemigo[cont].y_d + 1, nave.pos_x + 8, nave.pos_y + 15, 4, 5) ||
				Colision_Punto(enemigo[cont].x_d + 1, enemigo[cont].y_d + 1, nave.pos_x + 26, nave.pos_y + 15, 5, 4) ||
				Colision_Punto(enemigo[cont].x_d + 1, enemigo[cont].y_d + 1, nave.pos_x + 3, nave.pos_y + 19, 33, 4) ||
				Colision_Punto(enemigo[cont].x_d + 1, enemigo[cont].y_d + 1, nave.pos_x + 16, nave.pos_y + 23, 7, 5) ||
				Colision_Punto(enemigo[cont].x_d + 1, enemigo[cont].y_d + 1, nave.pos_x + 13, nave.pos_y + 26, 3, 2) ||
				Colision_Punto(enemigo[cont].x_d + 1, enemigo[cont].y_d + 1, nave.pos_x + 23, nave.pos_y + 26, 3, 2)) {
					if(duracion_a) {
						duracion_a -= DISP_A;
						if(duracion_a < 0) duracion_a = 0;
					}
					else energia--;
					enemigo[cont].x_1 = DISPARO_LIBRE - conb.total_sprites;
				}
			}
			if(enemigo[cont].x_1 < DISPARO_LIBRE) { /* exploci¢n disparo enemigo */
				conb.pos_x = enemigo[cont].x_d + 1;
				conb.pos_y = enemigo[cont].y_d + 1;
				Mostrar_Sprite_Enlazado_Mascara(&conb, -(enemigo[cont].x_1 + 2), MASCARA);
				enemigo[cont].x_1++;
				enemigo[cont].y_d += SC_INC;
			}
			if(enemigo[cont].act == VERDADERO) { /* destruir un enemigo */
				for(cont2 = 0; cont2 < MAXB; cont2++) {
					if(bala[cont2].act == 0) {
						en_ancho = ancho_sprites[enemigo[cont].tipo - 1];
						en_alto = alto_sprites[enemigo[cont].tipo - 1];
						if(Colision(bala[cont2].x, bala[cont2].y, s_ancho(&disparo, arma), s_alto(&disparo, arma), enemigo[cont].x, enemigo[cont].y, en_ancho, en_alto)) {
							enemigo[cont].energia--;
							if(enemigo[cont].energia == 0) {
								enemigo[cont].act = DESTRUIR_EN;
								bala[cont2].act = -(expen.total_sprites) - 1;
								bala[cont2].x = enemigo[cont].x - 6;
								bala[cont2].y = enemigo[cont].y - 6;
								puntos += puntos_en[enemigo[cont].tipo - 1];
								if(enemigo[cont].item) { /* verificar si guarda un item */
									enemigo[cont].item = -(enemigo[cont].item);
								}
							}
							else {
								bala[cont2].act = 1;
							}
						}
					}
				}

			}

			/* colision de la nave con un enemigo */
			if(enemigo[cont].act == VERDADERO)
			if(Colision_Punto(nave.pos_x + 17, nave.pos_y, enemigo[cont].x, enemigo[cont].y, ancho_sprites[enemigo[cont].tipo - 1], alto_sprites[enemigo[cont].tipo - 1]) ||
			Colision_Punto(nave.pos_x + 18, nave.pos_y, enemigo[cont].x, enemigo[cont].y, ancho_sprites[enemigo[cont].tipo - 1], alto_sprites[enemigo[cont].tipo - 1]) ||
			Colision_Punto(nave.pos_x, nave.pos_y + 18, enemigo[cont].x, enemigo[cont].y, ancho_sprites[enemigo[cont].tipo - 1], alto_sprites[enemigo[cont].tipo - 1]) ||
			Colision_Punto(nave.pos_x, nave.pos_y + 21, enemigo[cont].x, enemigo[cont].y, ancho_sprites[enemigo[cont].tipo - 1], alto_sprites[enemigo[cont].tipo - 1]) ||
			Colision_Punto(nave.pos_x + 36, nave.pos_y + 18, enemigo[cont].x, enemigo[cont].y, ancho_sprites[enemigo[cont].tipo - 1], alto_sprites[enemigo[cont].tipo - 1]) ||
			Colision_Punto(nave.pos_x + 36, nave.pos_y + 21, enemigo[cont].x, enemigo[cont].y, ancho_sprites[enemigo[cont].tipo - 1], alto_sprites[enemigo[cont].tipo - 1]) ||
			Colision_Punto(nave.pos_x + 11, nave.pos_y + 26, enemigo[cont].x, enemigo[cont].y, ancho_sprites[enemigo[cont].tipo - 1], alto_sprites[enemigo[cont].tipo - 1]) ||
			Colision_Punto(nave.pos_x + 9, nave.pos_y + 14, enemigo[cont].x, enemigo[cont].y, ancho_sprites[enemigo[cont].tipo - 1], alto_sprites[enemigo[cont].tipo - 1]) ||
			Colision_Punto(nave.pos_x + 30, nave.pos_y + 14, enemigo[cont].x, enemigo[cont].y, ancho_sprites[enemigo[cont].tipo - 1], alto_sprites[enemigo[cont].tipo - 1]) ||
			Colision_Punto(nave.pos_x + 25, nave.pos_y + 26, enemigo[cont].x, enemigo[cont].y, ancho_sprites[enemigo[cont].tipo - 1], alto_sprites[enemigo[cont].tipo - 1])) {

				expl.pos_x = nave.pos_x - 10;
				expl.pos_y = nave.pos_y - 4;
				Borrar_Mem_Video(0);
				Scroll_Vertical_D(&mapa, &blk, 0);

				for(cont2 = 0; cont2 < expl.total_sprites; cont2++) {
					Mostrar_Sprite_Enlazado_Mascara(&expl, cont2, MASCARA);
					Volcar_Pantalla_Virtual();
					Esperar_Retrazo_Vertical();
					delay(30);
				}
				muerte = VERDADERO;
			}
			/* manejo de los items */
			if(enemigo[cont].act == DESTRUIR_EN && enemigo[cont].item) { /* si existe el item */
				if(Colision_Punto(nave.pos_x + 17, nave.pos_y, enemigo[cont].x, enemigo[cont].y, ancho_items[-(enemigo[cont].item) - 1], alto_items[-(enemigo[cont].item) - 1]) ||
				Colision_Punto(nave.pos_x + 18, nave.pos_y, enemigo[cont].x, enemigo[cont].y, ancho_items[-(enemigo[cont].item) - 1], alto_items[-(enemigo[cont].item) - 1]) ||
				Colision_Punto(nave.pos_x, nave.pos_y + 18, enemigo[cont].x, enemigo[cont].y, ancho_items[-(enemigo[cont].item) - 1], alto_items[-(enemigo[cont].item) - 1]) ||
				Colision_Punto(nave.pos_x, nave.pos_y + 21, enemigo[cont].x, enemigo[cont].y, ancho_items[-(enemigo[cont].item) - 1], alto_items[-(enemigo[cont].item) - 1]) ||
				Colision_Punto(nave.pos_x + 36, nave.pos_y + 18, enemigo[cont].x, enemigo[cont].y, ancho_items[-(enemigo[cont].item) - 1], alto_items[-(enemigo[cont].item) - 1]) ||
				Colision_Punto(nave.pos_x + 36, nave.pos_y + 21, enemigo[cont].x, enemigo[cont].y, ancho_items[-(enemigo[cont].item) - 1], alto_items[-(enemigo[cont].item) - 1]) ||
				Colision_Punto(nave.pos_x + 11, nave.pos_y + 26, enemigo[cont].x, enemigo[cont].y, ancho_items[-(enemigo[cont].item) - 1], alto_items[-(enemigo[cont].item) - 1]) ||
				Colision_Punto(nave.pos_x + 9, nave.pos_y + 14, enemigo[cont].x, enemigo[cont].y, ancho_items[-(enemigo[cont].item) - 1], alto_items[-(enemigo[cont].item) - 1]) ||
				Colision_Punto(nave.pos_x + 30, nave.pos_y + 14, enemigo[cont].x, enemigo[cont].y, ancho_items[-(enemigo[cont].item) - 1], alto_items[-(enemigo[cont].item) - 1]) ||
				Colision_Punto(nave.pos_x + 25, nave.pos_y + 26, enemigo[cont].x, enemigo[cont].y, ancho_items[-(enemigo[cont].item) - 1], alto_items[-(enemigo[cont].item) - 1])) {
					if(enemigo[cont].item == -I_TURBO) {
						turbos++;
					}
					else if(enemigo[cont].item == -I_ENERGIA) {
						energia += E_INC;
					}
					else if(enemigo[cont].item == -I_VIDA) {
						vidas++;
					}
					else if(enemigo[cont].item == -I_ARMADURA) {
						armaduras++;
					}
					puntos += puntos_it[-enemigo[cont].item - 1];
					enemigo[cont].item = FALSO;
				}
				else {
					item[-(enemigo[cont].item) - 1].pos_x = enemigo[cont].x;
					item[-(enemigo[cont].item) - 1].pos_y = enemigo[cont].y;
					Mostrar_Sprite_Enlazado_Mascara(&item[-(enemigo[cont].item) - 1], frame_item, MASCARA);
					enemigo[cont].y += SC_INC;
				}
			}

		} /* for... */

		for(cont = 0; cont < MAXB; cont++) { /* explocion de la bala */
			if(bala[cont].act > 0) {
				conb.pos_x = bala[cont].x;
				conb.pos_y = bala[cont].y;
				Mostrar_Sprite_Enlazado_Mascara(&conb, bala[cont].act, MASCARA);
				bala[cont].act++;
				bala[cont].y++;
				if (bala[cont].act >= conb.total_sprites) bala[cont].act = DESTRUIR_BALA;
			}
			else if(bala[cont].act < DESTRUIR_BALA) { /* explocion enemigo */
				expen.pos_x = bala[cont].x;
				expen.pos_y = bala[cont].y;
				Mostrar_Sprite_Enlazado_Mascara(&expen, bala[cont].act + expen.total_sprites + 1, MASCARA);
				bala[cont].act++;
				bala[cont].y++;
				if (bala[cont].act >= -2 ) bala[cont].act = DESTRUIR_BALA;
			}
		}

		bloque = Obtener_Bloque_Sprite(&blk, &mapa, nave.pos_x + 17, nave.pos_y);
		if(bloque == 0 || bloque == 49 || bloque == 50 || bloque == 51)
		bloque = Obtener_Bloque_Sprite(&blk, &mapa, nave.pos_x + 18, nave.pos_y);
		if(bloque == 0 || bloque == 49 || bloque == 50 || bloque == 51)
		bloque = Obtener_Bloque_Sprite(&blk, &mapa, nave.pos_x, nave.pos_y + 18);
		if(bloque == 0 || bloque == 49 || bloque == 50 || bloque == 51)
		bloque = Obtener_Bloque_Sprite(&blk, &mapa, nave.pos_x, nave.pos_y + 21);
		if(bloque == 0 || bloque == 49 || bloque == 50 || bloque == 51)
		bloque = Obtener_Bloque_Sprite(&blk, &mapa, nave.pos_x + 35, nave.pos_y + 18);
		if(bloque == 0 || bloque == 49 || bloque == 50 || bloque == 51)
		bloque = Obtener_Bloque_Sprite(&blk, &mapa, nave.pos_x + 35, nave.pos_y + 21);
		if(bloque == 0 || bloque == 49 || bloque == 50 || bloque == 51)
		bloque = Obtener_Bloque_Sprite(&blk, &mapa, nave.pos_x + 11, nave.pos_y + 26);
		if(bloque == 0 || bloque == 49 || bloque == 50 || bloque == 51)
		bloque = Obtener_Bloque_Sprite(&blk, &mapa, nave.pos_x + 25, nave.pos_y + 26);
    else {
			expl.pos_x = nave.pos_x - 10;
			expl.pos_y = nave.pos_y - 4;
			Borrar_Mem_Video(0);
			Scroll_Vertical_D(&mapa, &blk, 0);

			for(cont = 0; cont < expl.total_sprites; cont++) {
				Mostrar_Sprite_Enlazado_Mascara(&expl, cont, MASCARA);
				Volcar_Pantalla_Virtual();
				delay(40);
			}
			muerte = VERDADERO;
		}

		/* actualizar displays */
		resolucion_vertical = 200;

		nv.pos_x = 5;
		for(cont = 0; cont < vidas; cont++) { /* numero de vidas de reserva */
			Mostrar_Sprite_Enlazado_Mascara(&nv, frame_nv, MASCARA);
			nv.pos_x += 17;
		}


		elemento.pos_y = 182; /* armadura */
		elemento.pos_x = 5;
		Mostrar_Sprite_Enlazado_Mascara(&elemento, 10, MASCARA);
		elemento.pos_y = 173; /* turbo */
		Mostrar_Sprite_Enlazado_Mascara(&elemento, 9, MASCARA);

		elemento.pos_y = 150; /* municion del arma activa */
		elemento.pos_x = 301;
		if(municion[arma] == -1) { /* si esta vacio */
			Mostrar_Sprite_Enlazado_Mascara(&elemento, 5, MASCARA); /* rojo */
			municion[arma] = 0;
		} else {
			Mostrar_Sprite_Enlazado_Mascara(&elemento, 3, MASCARA);
		}

		elemento.pos_x = 302;
		elemento.pos_y = 150 + 36;
		if(municion[arma] != 0) Mostrar_Sprite_Enlazado_Mascara(&elemento, 4, MASCARA);
		for(cont = 0; cont < (municion[arma] * 36 / (municion_ad[arma])); cont++) {
			Mostrar_Sprite_Enlazado_Mascara(&elemento, 4, MASCARA);
			elemento.pos_y--;
		}
		sprintf (buffer, "%d", municion[arma]);
		Escribir_Texto(buffer, &numeros_p, 270, 183);

		elemento.pos_x = 270; /* arma actual */
		elemento.pos_y = 175;
		Mostrar_Sprite_Enlazado_Mascara(&elemento, arma + 6, MASCARA);

		elemento.pos_y = 7;
		for(cont = 0; cont < energia; cont++) { /* energia de la nave */
			elemento.pos_x = (cont * 6) + vidas * 17 + 5;
			Mostrar_Sprite_Enlazado_Mascara(&elemento, I_ENERGIA - 1, MASCARA);
		}

		elemento.pos_x = 1;	elemento.pos_y = 194; /* Turbo */
		Mostrar_Sprite_Enlazado_Mascara(&elemento, I_TURBO - 1, MASCARA);

		sprintf (buffer, "%d", turbos);
		Escribir_Texto(buffer, &numeros_p, 14, 174);

		if(duracion_v == 1) {
			duracion_v = 0;
			velocidad = NORMAL_V;
		} else if (velocidad == TURBO_V) {
			for(cont = 0; cont <= duracion_v >> 3; cont++) {
				Pintar_Pixel(cont + 23, 195, 196); /* pixeles rojos */
				Pintar_Pixel(cont + 23, 196, 199);
				Pintar_Pixel(cont + 23, 197, 202);
			}
			duracion_v--; /* contabilizar */
		}

		elemento.pos_x = (MAX_T >> 3) + 25;	elemento.pos_y = 194; /* Armadura */
		Mostrar_Sprite_Enlazado_Mascara(&elemento, I_ARMADURA - 2, MASCARA);

		sprintf (buffer, "%d", armaduras);
		Escribir_Texto(buffer, &numeros_p, 14, 183);

		if(duracion_a) {
			for(cont = 0; cont <= duracion_a >> 5; cont++) {
				Pintar_Pixel(cont + (MAX_T >> 3) + 25 + 35, 195, 37); /* pixeles amarillos */
				Pintar_Pixel(cont + (MAX_T >> 3) + 25 + 35, 196, 39);
				Pintar_Pixel(cont + (MAX_T >> 3) + 25 + 35, 197, 41);
			}
			duracion_a--;
		}

		sprintf (buffer, "%ld", puntos);
		Escribir_Texto(buffer, &numeros, 240, 6);

		frame_nv++;
		if(frame_nv >= nv.total_sprites) frame_nv = 0;
		frame_nave++;
		if(frame_nave >= nave.total_sprites) frame_nave = 0;
		frame_enemigo++;
		if(frame_enemigo >= enem[0].total_sprites) frame_enemigo = 0;
		frame_anim1++;
		if(frame_anim1 >= anim1.total_sprites) frame_anim1 = 0;
		frame_anim2++;
		if(frame_anim2 >= anim2.total_sprites) frame_anim2 = 0;
		frame_item++;
		if(frame_item >= item[0].total_sprites) frame_item = 0;
		frame_disp++;
		if(frame_disp >= disp.total_sprites) frame_disp = 0;
		frame_arm++;
		if(frame_arm >= armadura.total_sprites) frame_arm = 0;

		Volcar_Pantalla_Virtual();
	} while(gb_Codigo != 1 && !muerte);
	} while(gb_Codigo != 1 && vidas > 0);
	Liberar_Sprite(mapa.mapa);
	Liberar_Sprite(blk.bloque);
	Liberar_Sprite(nave.sprite);
	Liberar_Sprite(expl.sprite);
	Liberar_Sprite(conb.sprite);
	Liberar_Sprite(enem[0].sprite);
	Liberar_Sprite(enem[1].sprite);
	Liberar_Sprite(enem[2].sprite);
	Liberar_Sprite(enem[3].sprite);
	Liberar_Sprite(enem[4].sprite);
	Liberar_Sprite(enem[5].sprite);
	Liberar_Sprite(enem[6].sprite);

	Restaurar_Teclado();
	Restaurar_Modo();

	return 0;
}


int s_ancho(s_SPRITE_SPE *sp, int numero_sprite)
{
	int contador, x_sprite, y_sprite;
	BYTE huge *p_sp;

	p_sp = sp -> sprite;

	if(numero_sprite >= sp -> total_sprites) return ERROR;

	for(contador = 0; contador < numero_sprite; contador++) {
		x_sprite=*(p_sp);
		p_sp += 2;
		y_sprite=*(p_sp);
		p_sp += 2;
		p_sp += x_sprite * y_sprite;
	}
	x_sprite=*(p_sp);

	return x_sprite;
}

int s_alto(s_SPRITE_SPE *sp, int numero_sprite)
{
	int contador, x_sprite, y_sprite;
	BYTE huge *p_sp;

	p_sp = sp -> sprite;

	if(numero_sprite >= sp -> total_sprites) return ERROR;

	for(contador = 0; contador < numero_sprite; contador++) {
		x_sprite=*(p_sp);
		p_sp += 2;
		y_sprite=*(p_sp);
		p_sp += 2;
		p_sp += x_sprite * y_sprite;
	}
	x_sprite=*(p_sp);
	p_sp += 2;
	y_sprite=*(p_sp);

	return y_sprite;
}