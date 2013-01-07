///////////////////////////////////////////////////////////////////////////////////////////
// Menu.cpp
///////////////////////////////////////////////////////////////////////////////////////////



#include "Menu.h"
#include <iostream.h>
#include <stdlib.h>
#include <string.h>



#define CLRSCR() cout << "\n\n\n" // definir como clrscr() si no se compila con Visual C++



Menu::Menu()
{
    n_opc = 0;
}



Menu::~Menu()
{
}



///////////////////////////////////////////////////////////////////////////////////////////
// Establece las opciones del men�: t�tulo y cadenas con las opciones
///////////////////////////////////////////////////////////////////////////////////////////
void Menu::Configurar(const char *titulo,     // t�tulo del men�
                      char *opciones[],       // cadenas con las opciones
                      const int num_opciones) // n�mero de opciones
{
    n_opc = num_opciones; // inicializar dato miembro

    // copiar el array de opciones
    for(int i = 0; i < n_opc; i++) { // cada opci�n

        strcpy(op[i], opciones[i]); // copiar el contenido
    }

    strcpy(tit, titulo);
}



///////////////////////////////////////////////////////////////////////////////////////////
// Realiza la selecci�n de una opci�n del usuario
///////////////////////////////////////////////////////////////////////////////////////////
int Menu::ObtenerSeleccion()
{
    char cad[80]; // cadena con la opci�n del usuario
	int opcion;   // n�mero de la opci�n del usuario
    int max = 0;  // longitud de la cadena m�s larga

    // encontrar la longitud de la cadena m�s larga
    for(int i = 0; i < n_opc; i++) { // cada cadena

        int len = strlen(op[i]);
        if(len > max) // la actual es mayor que la anterior?
			max = len;
    }

    max += 4; // sumar longitud de "1 - ", "2 - "...

    do {
        CLRSCR();

        cout << "\n";
        Centrar(tit);
        cout << "\n\n";

        // imprimir el men� de opciones
        for(int i = 0; i < n_opc; i++) { // cada cadena

            char texto[80];
            int l; // longitud de texto

            itoa(i + 1, texto, 10); // numero de la opci�n ("1", "2"...)

            strcat(texto, " - "); // "1 - ", "2 - "...
            strcat(texto, op[i]); // a�adir texto de la opci�n

            l = strlen(texto); // obtener la longitud de la cadena

            if(l < max) { // a�adir espacios si es necesario
                for(int d = 0; d < max - l; d++) strcat(texto, " ");
            }

            Centrar(texto); // imprimir la cadena
            cout << "\n";
        }

        Centrar("    OPCION: ");

		cin.getline(cad, 80);
		opcion = atoi(cad);

    } while(opcion > n_opc || opcion < 1);

    return opcion;
}



///////////////////////////////////////////////////////////////////////////////////////////
// Centra el texto especificado en la pantalla
///////////////////////////////////////////////////////////////////////////////////////////
void Menu::Centrar(const char *texto)
{
    int posicion;

    posicion = (80 - strlen(texto)) / 2; // calcular posicion inicial del texto

	cout << "\n";
    for(int i = 0; i < posicion; i++) cout << " ";

    cout << texto;
}