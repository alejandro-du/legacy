///////////////////////////////////////////////////////////////////////////////////////////
// Menu.h
///////////////////////////////////////////////////////////////////////////////////////////



#ifndef MENU_H
#define MENU_H



///////////////////////////////////////////////////////////////////////////////////////////
// Encapsula un men� de selecci�n m�ltiple para el usuario.
///////////////////////////////////////////////////////////////////////////////////////////
class Menu {

    public:

        Menu();  // constructor
        ~Menu(); // destructor

        void Configurar(const char *titulo,      // t�tulo del men�
                        char *opciones[],        // cadenas con las opciones
                        const int num_opciones); // n�mero de opciones

        int ObtenerSeleccion();

        static void Centrar(const char *texto);

        
    protected:

        int n_opc;       // n�mero de opciones
        char tit[80];    // cadena con el t�tulo
        char op[20][80]; // array de cadenas con las opciones
};



#endif