///////////////////////////////////////////////////////////////////////////////////////////
// Emulador Simpletron para el lenguaje SIM                                              //
// Autor: Jairo Alejandro Duarte Avenda¤o.                                               //
// Fecha: 1/mayo/2002                                                                    //
// Compilador: DJGPP C                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <ctype.h>
#include <conio.h>


#define MAX_MEMORIA  10 // n£mero m ximo de localidades de memoria
#define FIN_EDICION  -9999 // al introducir esto se termina la edici¢n

// C¢digos de operaci¢n SIM:

#define LEER          10
#define ESCRIBIR      11

#define CARGAR        20
#define ALMACENAR     21

#define SUMAR         30
#define RESTAR        31
#define DIVIDIR       32
#define MULTIPLICAR   33

#define BIFURCAR      40
#define BIFURCARNEG   41
#define BIFURCARCERO  42
#define TERMINAR      43


main (void)
{
   int memoria[MAX_MEMORIA]; // localidades de memoria
   int acumulador; // registro del acumulador
   int contador; // localidad en ejecuci¢n
   int codigo; // operaci¢n actual
   int operando; // localidad de memoria sobre la que opera la instrucci¢n actual
   int instruccion; // instrucci¢n a ejecutar


   // Mensaje de inicio
   puts ("\n\n*** Simpletron. DPA Software. ***\n\n");

   // Introducci¢n del programa
   contador = 0;
   do {
      printf ("%02d : ", contador);
      scanf ("%d", &memoria[contador]);
      if(memoria[contador] < FIN_EDICION || memoria[contador] > -FIN_EDICION) {
         printf("*** ERROR: El c¢digo debe estar en un rrango de %d a %d\n",
            FIN_EDICION, -FIN_EDICION);
         contador--;
      }
      contador++;
   } while (memoria[contador-1] != FIN_EDICION && contador < MAX_MEMORIA);

   printf("\n*** Se ha completado la carga del programa. ***");
   printf("\n*** Inicia la ejecuci¢n del programa. ***\n");

   // Ciclo de ejecuci¢n del programa
   contador = 0;

   do {
      instruccion = memoria[contador]; // obtener la localidad actual
      codigo = instruccion / 100; // obtener el c¢digo de operaci¢n
      operando = instruccion % 100; // obtener el operando de la instrucci¢n actual

      switch(codigo) {
         case LEER:
            printf("? ");
            scanf("%d", &memoria[operando]);
         break;

         case ESCRIBIR:
            printf("%d", memoria[operando]);
         break;

         case CARGAR:
            acumulador = memoria[operando];
         break;

         case ALMACENAR:
            memoria[operando] = acumulador;
         break;

         case SUMAR:
            acumulador += memoria[operando];
         break;

         case RESTAR:
            acumulador -= memoria[operando];
         break;

         case DIVIDIR:
            acumulador /= memoria[operando];
         break;

         case MULTIPLICAR:
            acumulador *= memoria[operando];
         break;

         case BIFURCAR:
            contador = operando;
         break;

         case BIFURCARNEG:
            if(acumulador < 0) contador = operando;
         break;

         case BIFURCARCERO:
            if(acumulador == 0) contador = operando;
         break;

         case TERMINAR:
            printf("\n*** Ha terminado la ejecuci¢n del programa. ***");
         break;

      }

      contador++; // pasar a la siguiente instrucci¢n
   } while (memoria[contador-1] != TERMINAR && contador < MAX_MEMORIA);

   return 0;
}
