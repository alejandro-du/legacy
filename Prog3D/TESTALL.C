// testall.c



#include <stdio.h>
#include "allegro.h"


#define TEX_W 64 // ancho de la textura
#define TEX_H 64 // alto de la textura
#define NUMERO_DE_POLIGONOS 100 // # de pol¡gonos a renderizar por ciclo


volatile int nFrames = 0;
volatile int nFramesPorSegundo = 0;



void cont_frames()
{
  nFramesPorSegundo = nFrames;
  nFrames = 0;
}
END_OF_FUNCTION(cont_frames);


int main(void)
{
  BITMAP *textura;
  int x, y, c; // para rellenar la textura
  int tecla;
  int nPol;
  V3D_f ver[3];


  printf("\nTest de rutinas 3d de Allgro.");
  printf("\nSe dibujar n %d pol¡gonos por ciclo.", NUMERO_DE_POLIGONOS);
  printf("\n\n\nPresione una tecla para comenzar...\n");
  getch();

  // inicializar allegro y otras cosas
  allegro_init();
  set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0);
  install_keyboard();
  install_timer();
  install_int(&cont_frames, 1000);
  LOCK_VARIABLE(nFrames);
  LOCK_VARIABLE(nFramesPorSegundo);
  LOCK_FUNCTION(cont_frames);

  // crear una textura
  textura = create_bitmap(TEX_W, TEX_H);
  clear(textura);

  c = 1; // color
  for(x = 0; x < TEX_W; x++) {
    for(y = 0; y < TEX_H; y++) {
      putpixel(textura, x, y, c);
      if(c++ > 64)
        c = 1;
    }
  }

  line(textura, 0, 0, TEX_W, TEX_H, 4);
  line(textura, TEX_W, 0, 0, TEX_H, 4);

  line(textura, 0, 0, 0, TEX_H, 4);
  line(textura, 0, 0, TEX_W, 0, 4);
  line(textura, 0, TEX_H - 1, TEX_W - 1, TEX_H - 1, 4);
  line(textura, TEX_W - 1, TEX_H - 1, TEX_W - 1, 0, 4);

  textprintf(textura, font, 1, 1, 3, "Textura");

  // inicializar las coordenadas 3d
  ver[0].x = 100;
  ver[0].y = 100;
  ver[0].z = 0;
  ver[0].u = 0;
  ver[0].v = 0;

  ver[1].x = 150;
  ver[1].y = 110;
  ver[1].z = 0;
  ver[1].u = TEX_W;
  ver[1].v = 0;

  ver[2].x = 120;
  ver[2].y = 140;
  ver[2].z = 0;
  ver[2].u = TEX_W;
  ver[2].v = TEX_H;

  blit(textura, screen, 0, 0, 0, 0, TEX_W, TEX_H);

  do {

    for(nPol = 0; nPol < NUMERO_DE_POLIGONOS; nPol++) {
      triangle3d_f(screen, POLYTYPE_ATEX, textura, &ver[0], &ver[1], &ver[2]);
    }

    nFrames++;
    textprintf(screen, font, 0, 190, 2, "%d FPS", nFramesPorSegundo);

  } while(!key[KEY_ESC]);

  allegro_exit();
  return 0;
}