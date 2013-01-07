// Usuario.cpp



#include "Usuario.h"



bool Usuario::Iniciar()
{
    printf("\n\n\tUsuario: ");
    gets(nombre);

    printf("\n\tContraseña: ");
    gets(password);

    if(nombre[0] == '-')
        return false;
    
    return true;
}


void Usuario::ObtNombre(char *destino)
{
    strcpy(destino, nombre);
}


void Usuario::ObtPassword(char *destino)
{
    strcpy(destino, password);
}
