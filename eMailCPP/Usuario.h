// Usuario.h



#ifndef USUARIO_H
#define USUARIO_H



#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define MAX_PASSWORD 100
#define MAX_NOMBRE  100



class Usuario {
    public:
        bool Iniciar();
        void ObtNombre(char *destino);
        void ObtPassword(char *destino);
    
    
    private:
        char password[MAX_PASSWORD];
        char nombre[MAX_NOMBRE];
};



#endif // ndef USUARIO_H
