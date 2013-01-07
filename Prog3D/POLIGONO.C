// poligono.c


#include <stdio.h>
#include "allegro.h"


#define TEX_W 64 // ancho de la textura
#define TEX_H 64 // alto de la textura
#define NUMERO_DE_POLIGONOS 1 // # de pol¡gonos a renderizar por c¡clo


volatile int nFrames = 0;
volatile int nFramesPorSegundo = 0;


// un punto en el espacio 3d
typedef struct {

  float x, y, z; // n£meros continuos

} PUNTO3D;


void cont_frames()
{
  nFramesPorSegundo = nFrames;
  nFrames = 0;
}
END_OF_FUNCTION(cont_frames);


int main(void)
{
  BITMAP *textura, *back_buffer;
  int x, y, c; // para rellenar la textura
  int tecla;
  int nPol;
  int i;
  char angulo_x = 0, angulo_y = 0, angulo_z = 0;
  PUNTO3D ver[3]; // v‚rtices del pol¡gono
  PUNTO3D ver_t[3]; // v‚rtices transformados
  V3D_f ver_p[3]; // v‚rtices proyectados (2d)
  MATRIX_f matriz;

  printf("\nPrograma para renderizar un pol¡gono 3d.");
  printf("\n\nControles:");
  printf("\n  x = angulo_x++");
  printf("\n  y = angulo_y++");
  printf("\n  z = angulo_z++");
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

  back_buffer = create_bitmap(SCREEN_W, SCREEN_H);
  clear(back_buffer);

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

  textprintf(textura, font, 1, 1, 13, "Textura");

  // inicializar las coordenadas 3d del pol¡gono
  ver[0].x = -2;
  ver[0].y = -2;
  ver[0].z = 0;

  ver[1].x = 2;
  ver[1].y = -2;
  ver[1].z = 0;

  ver[2].x = 0;
  ver[2].y = 2;
  ver[2].z = 0;

  // inicializar las coordenadas de la textura
  ver_p[0].u = 0;
  ver_p[0].v = 0;

  ver_p[1].u = TEX_W;
  ver_p[1].v = 0;

  ver_p[2].u = TEX_W / 2;
  ver_p[2].v = TEX_H;

  set_projection_viewport(0, 0, SCREEN_W, SCREEN_H);

  do {

    // teclado
    if(key[KEY_X]) {
       angulo_x++;
    }
    if(key[KEY_Y]) {
       angulo_y++;
    }
    if(key[KEY_Z]) {
       angulo_z++;
    }

    get_transformation_matrix_f(&matriz,
                                1, // escala
                                angulo_x, // angulo rotaci¢n x
                                angulo_y, // angulo rotaci¢n y
                                angulo_z, // angulo rotaci¢n z
                                0, // translaci¢n x
                                0, // translaci¢n y
                                8); // translaci¢n z

    for(i = 0; i < 3; i++) { // cada v‚rtice del pol¡gono

      // transformaci¢n
      apply_matrix_f(&matriz, ver[i].x, ver[i].y, ver[i].z, &ver_t[i].x, &ver_t[i].y, &ver_t[i].z);

      // proyecci¢n
      persp_project_f(ver_t[i].x, ver_t[i].y, ver_t[i].z, &ver_p[i].x, &ver_p[i].y);
      ver_p[i].z = ver_t[i].z; // requerido para renderizar la textura
    }

    // renderizar
    for(nPol = 0; nPol < NUMERO_DE_POLIGONOS; nPol++) { // cada pol¡gono
      triangle3d_f(back_buffer, POLYTYPE_ATEX, textura, &ver_p[0], &ver_p[1], &ver_p[2]);
    }

    textprintf(back_buffer, font, 0, 190, 2, "%d FPS", nFramesPorSegundo);
    blit(back_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    nFrames++;
    clear(back_buffer);

  } while(!key[KEY_ESC]);

  allegro_exit();
  return 0;
}