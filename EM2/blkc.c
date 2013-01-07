// Convertidor de archivos BLK de MAP MAKER

// DPA SOFTWARE.  Noviembre 20 de 1999.
// Autor: Jairo Alejandro Duarte.

/*
 ------------------------------------------------------------------------------------------

  FORMATO BLK

   6  bytes -> "DPABLK"
   1  byte  -> Versi¢n
   16 bytes -> Identificador definido por el programador (PRY1: "APOCALIPSIS     ")
   2  bytes -> N£mero de bloques
   2  bytes -> Ancho de bloque
   2  bytes -> Alto de bloque
   X  bytes -> bitmaps: array de bloques

   Despues de la lectura de cada bloque, leer un byte de atributo.

 ------------------------------------------------------------------------------------------
*/

#include <stdio.h>

main(char argc, char *argv[])
{
  FILE *fuente, *destino;
  unsigned char *blk, ids[17];
  long int cont;
  int nb, ancho, alto;

  printf("\n  BLKC versi¢n 1.0.  DPA SOFTWARE. 1999.\n");

  if(argc < 3) {
    printf("\nUso: BLKC archivo.BLK.MAPMAKER3.0 archivo.DPABLK\n\n");
    exit(0);
  }
/*  if(strcmp(argv[1], argv[2]) == 0) {
    printf("El archivo destino debe tener otro nombre.\n");
    exit(1);
  }
*/

  if((fuente = fopen(argv[1], "rb")) == NULL) {
    printf("  ERROR archivo fuente.\n");
    exit(2);
  }

  blk = (unsigned char*) malloc(240*32*32);
  if(blk == NULL) {
    printf("Memoria insuficiente.\n");
    exit(3);
  }

  for(cont = 0; cont < 240*32*32; cont++) {
    blk[cont] = getc(fuente);
    if(ferror(fuente)) {
      printf("  ERROR archivo fuente.\n");
      exit(2);
    }
  }

  fclose(fuente);

  if((destino = fopen(argv[2], "wb")) == NULL) {
    printf("  ERROR archivo destino.\n");
    exit(2);
  }

  nb = 240;
  ancho = alto = 32;

  // escribir cabecera
  fprintf(destino, "DPABLK"); // ID
  fprintf(destino, "%c", 1); // Versi¢n
  printf("\nIDS (max 16 caracteres): ");
  for(cont = 0; cont < 17; cont++) ids[cont] = ' ';
  scanf("%s", ids);
  ids[strlen(ids)] = ' ';
  fwrite(ids, 16, 1, destino);
  fwrite(&nb, 2, 1, destino);
  fwrite(&ancho, 2, 1, destino);
  fwrite(&alto, 2, 1, destino);
  if(ferror(destino)) {
    printf("  ERROR archivo destino.\n");
    exit(2);
  }

  for(cont = 0; cont < 240*32*32; cont++) {
    putc(blk[cont], destino);
    if(ferror(destino)) {
      printf("  ERROR archivo destino.\n");
      exit(2);
    }
  }

  printf("\n OK.");

  return(0);
}
