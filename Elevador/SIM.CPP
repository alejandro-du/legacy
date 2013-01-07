#include "elevador.h"
#include <pc.h>
#include <conio.h>
#include <stdlib.h>

main(void)
{
    C_Edificio edificio; // distancia entre cada piso
    int total_personas;

    srandom(time(0));
    clrscr();
    _setcursortype(_NOCURSOR);

    cprintf(" SIMULADOR DE UN ELEVADOR - DPA SOFTWARE.");

    do {
        total_personas = 0;
        edificio.GenerarPersonas();
//        edificio.AnimarPersonas();
//        edificio.MoverElevador();

        // imprimir datos
        for(int linea = 3, piso = 18; piso >= 0; piso--, linea++) {
            gotoxy(5, linea); cprintf("Piso %d: ", piso+1);
            cprintf("%d personas ", edificio.piso[piso].num_personas);
            gotoxy(5, 23); cprintf("Intervalo: %d   ", edificio.tasa.reloj.intervalo);
        }

        for(int piso = 0; piso < EDIFICIO_PISOS; piso++) {
            total_personas += edificio.piso[piso].num_personas;
        }

        gotoxy(50, 3); cprintf("Tasa de llegada:");
        gotoxy(50, 4); cprintf("  [%d, %d]s %d personas", TASA_MINIMO, TASA_MAXIMO, TASA_UNA_PERSONA);
        gotoxy(50, 6); cprintf("Edificio: %d pisos", edificio.pisos);
        gotoxy(50, 8); cprintf("%d personas esperando", total_personas);


//        delay(5000);

    } while (!kbhit());






    return 0;
}
