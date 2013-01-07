#include"dpalib.h"
#include"mouse.h"
#include"graficos.h"

main(void)
{
	s_MOUSECOOR mouse, mouse_temp;
	s_SPRITE sp;
	s_MAPA map;
	s_BLK blk;
	s_FUENTE f;

	Inicializar_320x200X();
	Inicializar_Mouse();

        // cargar los archivos
        if(!Cargar_Sprite("sprite.spr", &sp)) {
		printf("Error spr\a");
		return 1;
	}

        Mostrar_Sprite_Mascara(&sp, 0);
        free(sp.sprite); // se debe liberar la memoria

        if(!Cargar_Paleta("ejemplo1.pal")) {
		printf("Error pal\a");
		return 1;
	}

        if(!Cargar_Mapa("ejemplo1.map", &map)) {
		printf("Error Map\a");
		return 1;
	}

        if(Cargar_Fuente("fnt1.spe", &f, "0123456789") != OK) {
		printf("Error FUENTE\a");
		return 1;
	}

        if(!Cargar_Bloques("ejemplo1.blk", &blk, 32, 32, 240)) {
		printf("Error BLK\a");
		return 1;
	}

        Cargar_Puntero_Mouse("mouse.spr");

        Escribir_Texto("123456", &f, 120, 180);
	map.x_pant = 40;
	map.y_pant = 10;
	map.bloques_horizontales = 7;
	map.bloques_verticales = 5;

        for(;;) {
                if(mouse.x >= 319) {
			map.x++;
			if(map.x > (map.long_x) - map.bloques_horizontales) map.x = (map.long_x) - map.bloques_horizontales;
			Mostrar_Mapa(&map, &blk);
		}
                if(mouse.y >= 199) {
			map.y++;
			if(map.y > (map.long_y) - map.bloques_verticales) map.y = (map.long_y) - map.bloques_verticales;
			Mostrar_Mapa(&map, &blk);
		}
                if(mouse.x <= 0) {
			map.x--;
			if(map.x < 0) map.x = 0;
			Mostrar_Mapa(&map, &blk);
		}
                if(mouse.y <= 0) {
			map.y--;
			if(map.y < 0) map.y = 0;
			Mostrar_Mapa(&map, &blk);
		}

                Mover_Puntero_Mouse(&mouse, &mouse_temp);

		if(kbhit()) break;
	}

        Oscurecer_Paleta(5, MAX_GAMA);
	Restaurar_Modo();
        farfree(blk.bloque); // se debe liberar la memoria de los bloques
	free(sp.sprite);

        return 0;
}
