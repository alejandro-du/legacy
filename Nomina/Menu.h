///////////////////////////////////////////////////////////////////////////////////////////
// Menu.h
///////////////////////////////////////////////////////////////////////////////////////////



#ifndef MENU_H
#define MENU_H



///////////////////////////////////////////////////////////////////////////////////////////
// Encapsula un menú de selección múltiple para el usuario.
///////////////////////////////////////////////////////////////////////////////////////////
class Menu {

    public:

        Menu();  // constructor
        ~Menu(); // destructor

        void Configurar(const char *titulo,      // título del menú
                        char *opciones[],        // cadenas con las opciones
                        const int num_opciones); // número de opciones

        int ObtenerSeleccion();

        static void Centrar(const char *texto);

        
    protected:

        int n_opc;       // número de opciones
        char tit[80];    // cadena con el título
        char op[20][80]; // array de cadenas con las opciones
};



#endif