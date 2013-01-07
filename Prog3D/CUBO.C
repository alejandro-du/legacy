// cubo.c


#include <stdio.h>
#include "allegro.h"


#define TEX_W 64 // ancho de la textura
#define TEX_H 64 // alto de la textura


volatile int nFrames = 0;
volatile int nFramesPorSegundo = 0;


// un punto en el espacio 3d
typedef struct {

  float x, y, z; // n£meros continuos

} PUNTO3D;


// un punto en la pantalla
typedef struct {
  int x, y; // n£meros discretos
} PUNTO2D;


void cont_frames()
{
  nFramesPorSegundo = nFrames;
  nFrames = 0;
}
END_OF_FUNCTION(cont_frames);


int main(void)
{
  BITMAP *back_buffer;
  int i, tecla;
  char angulo_x = 0, angulo_y = 0, angulo_z = 0;
  float px = 0, py = 0, pz = 10;
  PUNTO3D ver[8]; // 8 v‚rtices para el cubo
  PUNTO3D ver_t[8]; // v‚rtices transformados
  V3D_f ver_p[8]; // v‚rtices proyectados (2d)
  MATRIX_f matriz;

  printf("\nPrograma para renderizar un cubo 3d.");
  printf("\n\nControles:");
  printf("\n  x = angulo_x++");
  printf("\n  y = angulo_y++");
  printf("\n  z = angulo_z++");
  printf("\n  flecha arriba = y--");
  printf("\n  flecha abajo = y++");
  printf("\n  flecha izquierda = x--");
  printf("\n  flecha derecha = x++");
  printf("\n  q = z++");
  printf("\n  a = z--");
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

  // inicializar las coordenadas 3d del cubo
  ver[0].x = -2;
  ver[0].y = 2;
  ver[0].z = -2;

  ver[1].x = 2;
  ver[1].y = 2;
  ver[1].z = -2;

  ver[2].x = 2;
  ver[2].y = -2;
  ver[2].z = -2;

  ver[3].x = -2;
  ver[3].y = -2;
  ver[3].z = -2;

  ver[4].x = -2;
  ver[4].y = 2;
  ver[4].z = 2;

  ver[5].x = 2;
  ver[5].y = 2;
  ver[5].z = 2;

  ver[6].x = 2;
  ver[6].y = -2;
  ver[6].z = 2;

  ver[7].x = -2;
  ver[7].y = -2;
  ver[7].z = 2;

  set_projection_viewport(0, 0, SCREEN_W, SCREEN_H);

  do {

    // teclado
    if(key[KEY_UP]) {
       py-=0.1;
    }
    if(key[KEY_DOWN]) {
       py+=0.1;
    }
    if(key[KEY_RIGHT]) {
       px+=0.1;
    }
    if(key[KEY_LEFT]) {
       px-=0.1;
    }
    if(key[KEY_Q]) {
       pz+=0.1;
    }
    if(key[KEY_A]) {
       pz-=0.1;
    }
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
                                px, // translaci¢n x
                                py, // translaci¢n y
                                pz); // translaci¢n z

    for(i = 0; i < 8; i++) { // cada v‚rtice del pol¡gono

      // transformaci¢n
      apply_matrix_f(&matriz, ver[i].x, ver[i].y, ver[i].z, &ver_t[i].x, &ver_t[i].y, &ver_t[i].z);

      // proyecci¢n
      persp_project_f(ver_t[i].x, ver_t[i].y, ver_t[i].z, &ver_p[i].x, &ver_p[i].y);
      ver_p[i].z = ver_t[i].z; // requerido para renderizar la textura
    }

    // renderizar
    line(back_buffer, ver_p[0].x, ver_p[0].y, ver_p[1].x, ver_p[1].y, 3);
    line(back_buffer, ver_p[1].x, ver_p[1].y, ver_p[2].x, ver_p[2].y, 3);
    line(back_buffer, ver_p[2].x, ver_p[2].y, ver_p[3].x, ver_p[3].y, 3);
    line(back_buffer, ver_p[3].x, ver_p[3].y, ver_p[0].x, ver_p[0].y, 3);

    line(back_buffer, ver_p[4].x, ver_p[4].y, ver_p[5].x, ver_p[5].y, 3);
    line(back_buffer, ver_p[5].x, ver_p[5].y, ver_p[6].x, ver_p[6].y, 3);
    line(back_buffer, ver_p[6].x, ver_p[6].y, ver_p[7].x, ver_p[7].y, 3);
    line(back_buffer, ver_p[7].x, ver_p[7].y, ver_p[4].x, ver_p[4].y, 3);

    line(back_buffer, ver_p[4].x, ver_p[4].y, ver_p[0].x, ver_p[0].y, 3);
    line(back_buffer, ver_p[0].x, ver_p[0].y, ver_p[3].x, ver_p[3].y, 3);
    line(back_buffer, ver_p[3].x, ver_p[3].y, ver_p[7].x, ver_p[7].y, 3);
    line(back_buffer, ver_p[7].x, ver_p[7].y, ver_p[4].x, ver_p[4].y, 3);

    line(back_buffer, ver_p[1].x, ver_p[1].y, ver_p[5].x, ver_p[5].y, 3);
    line(back_buffer, ver_p[5].x, ver_p[5].y, ver_p[6].x, ver_p[6].y, 3);
    line(back_buffer, ver_p[6].x, ver_p[6].y, ver_p[2].x, ver_p[2].y, 3);
    line(back_buffer, ver_p[2].x, ver_p[2].y, ver_p[1].x, ver_p[1].y, 3);

    textprintf(back_buffer, font, 0, 190, 2, "%d FPS", nFramesPorSegundo);
    blit(back_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    nFrames++;
    clear(back_buffer);

  } while(!key[KEY_ESC]);

  allegro_exit();
  return 0;
}