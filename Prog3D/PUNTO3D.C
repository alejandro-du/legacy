// punto3d.c


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
  PUNTO3D punto3d;
  PUNTO2D punto2d;
  int tecla;
  float incremento = 0.01;

  printf("\nEste es un programa para mostrar y mover un punto 3d.");
  printf("\n\nControles:");
  printf("\n  w = y--");
  printf("\n  s = y++");
  printf("\n  d = x++");
  printf("\n  a = x--");
  printf("\n  r = z++");
  printf("\n  f = z--");
  printf("\n\n\nPresione una tecla para comenzar...\n");
  getch();

  // inicializar allegro y el modo gr fico
  allegro_init();
  set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0);

  // inicializar las coordenadas 3d
  punto3d.x = 0;
  punto3d.y = 0;
  punto3d.z = 2;

  // transformaci¢n
  punto2d.x = (256 * punto3d.x / punto3d.z);
  punto2d.y = (256 * punto3d.y / punto3d.z);


  do {

    putpixel(screen, punto2d.x, punto2d.y, 5);

    // transformaci¢n
    punto2d.x = (256 * punto3d.x / punto3d.z);
    punto2d.y = (256 * punto3d.y / punto3d.z);

    textprintf(screen,
               font,
               0, 0,
               3,
               "(%f,%f,%f)(x%d,y%d)",
               punto3d.x, punto3d.y, punto3d.z, punto2d.x, punto2d.y);

    putpixel(screen, punto2d.x, punto2d.y, 2);

    tecla = getch();

    if(tecla == 'w')
      punto3d.y -= incremento;
    if(tecla == 's')
      punto3d.y += incremento;
    else if(tecla == 'd')
      punto3d.x += incremento;
    else if(tecla == 'a')
      punto3d.x -= incremento;
    else if(tecla == 'r')
      punto3d.z += incremento;
    else if(tecla == 'f')
      punto3d.z -= incremento;

  } while(tecla != 27); // !ESC



  allegro_exit();
  return 0;
}