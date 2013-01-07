// bfcull.c


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

} PUNTO3D, VECTOR;


typedef struct {
  PUNTO3D ver[4];
} POLIGONO3D;


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
  float trans_z = 12.1;
  POLIGONO3D cara[6]; // un cubo
  PUNTO3D ver_t[4]; // v‚rtices transformados para un pol¡gono
  V3D_f ver_p[4]; // v‚rtices proyectados (2d) para un pol¡gono
  MATRIX_f matriz;

  printf("\nEjemplo de: backface culling (eliminaci¢n de caras posteriores)");
  printf("\n\nControles:");
  printf("\n  Q, W, flechas = rotar cubo.");
  printf("\n  A, Z = z++, z--.");
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

  // inicializar las coordenadas 3d del cubo

  cara[0].ver[0].x = -2;
  cara[0].ver[0].y = -2;
  cara[0].ver[0].z = -2;
  cara[0].ver[1].x = 2;
  cara[0].ver[1].y = -2;
  cara[0].ver[1].z = -2;
  cara[0].ver[2].x = 2;
  cara[0].ver[2].y = 2;
  cara[0].ver[2].z = -2;
  cara[0].ver[3].x = -2;
  cara[0].ver[3].y = 2;
  cara[0].ver[3].z = -2;

  cara[1].ver[0].x = 2;
  cara[1].ver[0].y = -2;
  cara[1].ver[0].z = 2;
  cara[1].ver[1].x = -2;
  cara[1].ver[1].y = -2;
  cara[1].ver[1].z = 2;
  cara[1].ver[2].x = -2;
  cara[1].ver[2].y = 2;
  cara[1].ver[2].z = 2;
  cara[1].ver[3].x = 2;
  cara[1].ver[3].y = 2;
  cara[1].ver[3].z = 2;

  cara[2].ver[0].x = -2;
  cara[2].ver[0].y = -2;
  cara[2].ver[0].z = 2;
  cara[2].ver[1].x = -2;
  cara[2].ver[1].y = -2;
  cara[2].ver[1].z = -2;
  cara[2].ver[2].x = -2;
  cara[2].ver[2].y = 2;
  cara[2].ver[2].z = -2;
  cara[2].ver[3].x = -2;
  cara[2].ver[3].y = 2;
  cara[2].ver[3].z = 2;

  cara[3].ver[0].x = 2;
  cara[3].ver[0].y = -2;
  cara[3].ver[0].z = -2;
  cara[3].ver[1].x = 2;
  cara[3].ver[1].y = -2;
  cara[3].ver[1].z = 2;
  cara[3].ver[2].x = 2;
  cara[3].ver[2].y = 2;
  cara[3].ver[2].z = 2;
  cara[3].ver[3].x = 2;
  cara[3].ver[3].y = 2;
  cara[3].ver[3].z = -2;

  cara[4].ver[0].x = -2;
  cara[4].ver[0].y = -2;
  cara[4].ver[0].z = 2;
  cara[4].ver[1].x = 2;
  cara[4].ver[1].y = -2;
  cara[4].ver[1].z = 2;
  cara[4].ver[2].x = 2;
  cara[4].ver[2].y = -2;
  cara[4].ver[2].z = -2;
  cara[4].ver[3].x = -2;
  cara[4].ver[3].y = -2;
  cara[4].ver[3].z = -2;

  cara[5].ver[0].x = -2;
  cara[5].ver[0].y = 2;
  cara[5].ver[0].z = -2;
  cara[5].ver[1].x = 2;
  cara[5].ver[1].y = 2;
  cara[5].ver[1].z = -2;
  cara[5].ver[2].x = 2;
  cara[5].ver[2].y = 2;
  cara[5].ver[2].z = 2;
  cara[5].ver[3].x = -2;
  cara[5].ver[3].y = 2;
  cara[5].ver[3].z = 2;

  // inicializar las coordenadas de la textura
  ver_p[0].u = 0;
  ver_p[0].v = 0;
  ver_p[1].u = TEX_W;
  ver_p[1].v = 0;
  ver_p[2].u = TEX_W;
  ver_p[2].v = TEX_H;
  ver_p[3].u = 0;
  ver_p[3].v = TEX_H;

  set_projection_viewport(0, 0, SCREEN_W, SCREEN_H);

  do {

    // teclado
    if(key[KEY_UP]) {
       angulo_x++;
    }
    if(key[KEY_DOWN]) {
       angulo_x--;
    }
    if(key[KEY_RIGHT]) {
       angulo_y--;
    }
    if(key[KEY_LEFT]) {
       angulo_y++;
    }
    if(key[KEY_Q]) {
       angulo_z++;
    }
    if(key[KEY_W]) {
       angulo_z--;
    }
    if(key[KEY_A]) {
       trans_z+=0.2;
    }
    if(key[KEY_Z]) {
       trans_z-=0.2;
    }

    get_transformation_matrix_f(&matriz,
                                1, // escala
                                angulo_x, // angulo rotaci¢n x
                                angulo_y, // angulo rotaci¢n y
                                angulo_z, // angulo rotaci¢n z
                                0, // translaci¢n x
                                0, // translaci¢n y
                                trans_z); // translaci¢n z

    for(nPol = 0; nPol < 6; nPol++) { // cada pol¡gono

      for(i = 0; i < 4; i++) { // cada v‚rtice del pol¡gono

        // transformaci¢n
        apply_matrix_f(&matriz,
                       cara[nPol].ver[i].x,
                       cara[nPol].ver[i].y,
                       cara[nPol].ver[i].z,
                       &ver_t[i].x,
                       &ver_t[i].y,
                       &ver_t[i].z);

        // proyecci¢n
        persp_project_f(ver_t[i].x,
                        ver_t[i].y,
                        ver_t[i].z,
                        &ver_p[i].x,
                        &ver_p[i].y);

        ver_p[i].z = ver_t[i].z; // requerido para renderizar la textura
      }

      // si la normal al pol¡gono es positiva -> pintar
      if(polygon_z_normal_f(&ver_p[0], &ver_p[1], &ver_p[2]) > 0) {
        quad3d_f(back_buffer,
                 POLYTYPE_PTEX,
                 textura,
                 &ver_p[0],
                 &ver_p[1],
                 &ver_p[2],
                 &ver_p[3]);
      }
    }

    textprintf(back_buffer, font, 0, 190, 2, "%d FPS", nFramesPorSegundo);
    blit(back_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    nFrames++;
    clear(back_buffer);

  } while(!key[KEY_ESC]);

  allegro_exit();

  return 0;
}