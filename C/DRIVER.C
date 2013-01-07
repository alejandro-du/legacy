/* DRIVER (Nombre tramador)
programa para usuarios inexpertos y con pocos conocimientos de computadores */

#include <sys/exceptn.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int x;

  __djgpp_set_ctrl_c(1); // desactivar CONTROL+PAUSA

  printf("\n\n");
  for(x = 4; x < 55; x++) {
    delay(100);
    printf(".");
  }

  printf("\nDMA Driver - Release 7.4    Standar Version\n"); // tramador...
  printf("DPAXMS Version 3.99 already started\n"); // in inglish

  return(0);
}
