// Servidor.h



#ifndef SERVIDOR_H
#define SERVIDOR_H



#include "Usuario.h"



#define MAX_DIRECTORIO   100
#define MAX_MENSAJE      1000
#define ARCHIVO_PASSWORD "password.~~~"



class Servidor {
    public:
        int Buscar(Usuario u);
        void Crear(Usuario u);
        void EnviarMensaje(Usuario u);
        void VerMensajes(Usuario u);

    private:
        void Ejecutar(char *cmd, char *arg);

};



#endif // ndef SERVIDOR_H

