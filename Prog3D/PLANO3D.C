// plano3d.c


#include <stdio.h>
#include "allegro.h"



// un punto en la pantalla
typedef struct {
  int x, y; // n£meros discretos
} PUNTO2D;



// un punto en el espacio 3d
typedef struct {

  float x, y, z; // n£meros continuos

} PUNTO3D;



int main(void)
{
  PUNTO3D puntos3d[3];
  PUNTO2D puntos2d[3];
  int tecla;
  float incremento = 0.01;
  int distanciaFocal = 256;

  printf("\nEste es un programa para mostrar y mover un plano 3d.");
  printf("\n\nControles:");
  printf("\n  w = y--");
  printf("\n  s = y++");
  printf("\n  d = x++");
  printf("\n  a = x--");
  printf("\n  r = z++");
  printf("\n  f = z--");
  printf("\n  + = distanciaFocal++");
  printf("\n  - = distanciaFocal--");
  printf("\n\n\nPresione una tecla para comenzar...\n");
  getch();

  // inicializar allegro y el modo gr fico
  allegro_init();
  set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0);

  // inicializar las coordenadas 3d
  puntos3d[0].x = 0;
  puntos3d[0].y = 0;
  puntos3d[0].z = 4;

  puntos3d[1].x = 1;
  puntos3d[1].y = 0;
  puntos3d[1].z = 3.5;

  puntos3d[2].x = 1;
  puntos3d[2].y = 0.7;
  puntos3d[2].z = 3;

  do {

    // transformaci¢n
    puntos2d[0].x = (distanciaFocal * puntos3d[0].x / puntos3d[0].z);
    puntos2d[0].y = (distanciaFocal * puntos3d[0].y / puntos3d[0].z);

    puntos2d[1].x = (distanciaFocal * puntos3d[1].x / puntos3d[1].z);
    puntos2d[1].y = (distanciaFocal * puntos3d[1].y / puntos3d[1].z);

    puntos2d[2].x = (distanciaFocal * puntos3d[2].x / puntos3d[2].z);
    puntos2d[2].y = (distanciaFocal * puntos3d[2].y / puntos3d[2].z);

    // dibujar
    clear(screen);
    line(screen,
         puntos2d[0].x,
         puntos2d[0].y,
         puntos2d[1].x,
         puntos2d[1].y,
         2);

    line(screen,
         puntos2d[1].x,
         puntos2d[1].y,
         puntos2d[2].x,
         puntos2d[2].y,
         2);

    line(screen,
         puntos2d[2].x,
         puntos2d[2].y,
         puntos2d[0].x,
         puntos2d[0].y,
         2);

    tecla = getch();

    if(tecla == 'w') {
      puntos3d[0].y -= incremento;
      puntos3d[1].y -= incremento;
      puntos3d[2].y -= incremento;
    }
    else if(tecla == 's') {
      puntos3d[0].y += incremento;
      puntos3d[1].y += incremento;
      puntos3d[2].y += incremento;
    }
    else if(tecla == 'd') {
      puntos3d[0].x += incremento;
      puntos3d[1].x += incremento;
      puntos3d[2].x += incremento;
    }
    else if(tecla == 'a') {
      puntos3d[0].x -= incremento;
      puntos3d[1].x -= incremento;
      puntos3d[2].x -= incremento;
    }
    else if(tecla == 'r') {
      puntos3d[0].z += incremento;
      puntos3d[1].z += incremento;
      puntos3d[2].z += incremento;
    }
    else if(tecla == 'f') {
      puntos3d[0].z -= incremento;
      puntos3d[1].z -= incremento;
      puntos3d[2].z -= incremento;
    }

    else if(tecla == '+')
      distanciaFocal++;

    else if(tecla == '-')
      distanciaFocal--;

  } while(tecla != 27); // !ESC



  allegro_exit();
  return 0;
}