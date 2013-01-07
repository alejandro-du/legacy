// Convertidor BMP, PCX, LBM, TGA -> BLK

// DPA SOFTWARE.  Noviembre 20 de 1999.
// Autor: Jairo Alejandro Duarte.

/*
 ------------------------------------------------------------------------------------------

  FORMATO BLK

   6  bytes -> "DPABLK"
   1  byte  -> Versi¢n
   16 bytes -> Identificador definido por el programador
   2  bytes -> N£mero de bloques
   2  bytes -> Ancho de bloque
   2  bytes -> Alto de bloque
   X  bytes -> bloques con sus atributos

   Despues de la lectura de cada bloque, leer un byte de atributo.

 ------------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "allegro.h"

main(char argc, char *argv[])
{
  PALLETE pal;
  BITMAP *img;
  FILE *blk;
  unsigned char ids[17];
  int x, y, ancho, alto, bx, by, xp, yp, nb;

  long int cont;

  printf("\n  BB versi¢n 1.0.  DPA SOFTWARE. 1999.\n");

  if(argc < 2 || argc > 3) {
    printf("\n\n  Uso:\n\n BB archivo.BMP .PCX .LBM .TGA archivo.BLK\n");
    exit(0);
  }

  printf("  Cargando bitmap...");

  if((img = load_bitmap(argv[1], pal)) == NULL) {
    printf("  Error.\n");
    exit(1);
  }
  printf("  OK.\n");

  printf("  Creando %s...", argv[2]);

  if((blk = fopen(argv[2], "wb")) == NULL) {
    printf("  ERROR.\n");
    exit(1);
  }
  printf("  OK.\n");
  printf("  X - %d\n  Y - %d\n", img->w, img->h);

  printf("Ancho de bloque (x) : ");
  scanf("%d", &ancho);
  printf("Alto de bloque (y) : ");
  scanf("%d", &alto);
  printf("N£mero de bloques horizontales : ");
  scanf("%d", &bx);
  printf("N£mero de bloques verticales : ");
  scanf("%d", &by);

  printf("\n    Convirtiendo imagen...");

  nb = bx*by;

  // cabecera
  fprintf(blk, "DPABLK"); // ID
  fprintf(blk, "%c", 1); // Versi¢n
  printf("\nIDS (max 16 caracteres): ");
  for(cont = 0; cont < 17; cont++) ids[cont] = ' ';
  scanf("%s", ids);
  ids[strlen(ids)] = ' ';
  fwrite(ids, 16, 1, blk);
  fwrite(&nb, 2, 1, blk);
  fwrite(&ancho, 2, 1, blk);
  fwrite(&alto, 2, 1, blk);

  for(x = 0; x < bx; x++) {
    for(yp = 0; yp < alto*by; yp++) {
      for(xp = 0; xp < ancho; xp++) {
        fputc(img->line[yp][xp + (ancho*x)], blk);
        if(ferror(blk)) {
          printf("  ERROR.\n");
          exit(1);
        }
      }
    }
  }

  for(cont = 0; cont < bx*by; cont++) {
    putc(0, blk); // atributo del bloque
    if(ferror(blk)) {
      printf("  ERROR.\n");
      exit(1);
    }
  }
  fclose(blk);

  printf("  OK.\n");

  return 0;
}
