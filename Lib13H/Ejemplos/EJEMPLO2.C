#include "dpalib.h"
#include "graficos.h"
#include "mouse.h"

#define ANIM1 24 /* ids. para las animaciones dentro del mapa */
#define ANIM2 47
#define ANIM3 48


main(void)
{
	s_MAPA mapa;
	s_BLK blk;
        s_SPRITE_SPE anim1, anim2, anim3;
        int frame_anim1 = 0;
        int frame_anim2 = 0;

        if(!Cargar_Mapa("ejemplo2.map", &mapa)) {
		printf("Error Map\a");
		return 1;
	}
        if(!Cargar_Bloques("ejemplo2.blk", &blk, 32, 32, 240)) {
		printf("Error BLK\a");
		return 1;
	}

        if(!Cargar_Sprite_Enlazado("ac.spe", &anim1)) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
        if(!Cargar_Sprite_Enlazado("aa.spe", &anim2)) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}
        if(!Cargar_Sprite_Enlazado("ab.spe", &anim3)) {
		printf("\nError al cargar el archivo sprite\n\a");
		return 1;
	}

	Inicializar_Mouse();
	Inicializar_320x200X();

        if(!Cargar_Paleta("ejemplo2.pal")) {
		printf("Error pal\a");
		return 1;
	}

	mapa.bloques_horizontales = 8 + 2;
	mapa.bloques_verticales = 4 + 2;
/*	mapa.x_pant = 32;
	mapa.y_pant = 32;*/
        mapa.x = 0;
        mapa.y = mapa.long_y - mapa.bloques_verticales;

	Inicializar_Pantalla_Virtual();
	Pantalla_Virtual = 1;
        for(;;) {
		if(kbhit()) break;

                if(mapa.y > 0) {
                        Borrar_Mem_Video(0);
                        Scroll_Vertical_D(&mapa, &blk, 1);
                }

                // manejar las animaciones en el mapa
                Mostrar_Sprite_Mapa(&mapa, &blk, &anim1, 3, ANIM1, frame_anim1, FALSO, SC_V);
                Mostrar_Sprite_Mapa(&mapa, &blk, &anim2, 3, ANIM2, frame_anim2, FALSO, SC_V);
                Mostrar_Sprite_Mapa(&mapa, &blk, &anim3, 3, ANIM3, frame_anim2, FALSO, SC_V);

                frame_anim1++;
		if(frame_anim1 >= anim1.total_sprites) frame_anim1 = 0;
		frame_anim2++;
		if(frame_anim2 >= anim2.total_sprites) frame_anim2 = 0;

		Volcar_Pantalla_Virtual();
                gotoxy(1,25); printf("%d ", mapa.despy);
	}

        Desvanecer_Pantalla(0, 1000, 0);
	Liberar_Sprite(blk.bloque);
	Restaurar_Modo();

	return 0;
}
