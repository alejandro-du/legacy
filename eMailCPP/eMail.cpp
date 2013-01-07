// eMail.cpp



#include "Usuario.h"
#include "Servidor.h"
//#include <stdio.h>
#include <ctype.h>



bool Pausa(char *texto);



void main()
{
    Servidor s;
    Usuario usuario;
    char opcion[80];


    printf("\n\n Para salir del programa introdusca \"-1\" como nombre de usuario\n\n");
    
    while (usuario.Iniciar()) {

        int resultado = s.Buscar(usuario);

        if(resultado == -1) { // si no existe el usuario
            
            if(Pausa("\n\tCrear este usuario? (s/n)"))
                s.Crear(usuario);

            else continue;

        }
        
        else if(resultado == 1) {
            printf("\n\n\tLa contraseña es incorrecta.");
            continue;
        }
        
        // menú principal
        do {

            printf("\n\n\tOpciones");
            printf("\n\t1 - Ver mensajes");
            printf("\n\t2 - Enviar mensaje");
            printf("\n\t3 - Salir");
            printf("\n\t    Opción: ");

            gets(opcion);

            switch(opcion[0]) {
                case '1':

                    s.VerMensajes(usuario);

                break;

                case '2':

                    s.EnviarMensaje(usuario);                
                
                break;
            }

        } while (opcion[0] != '3');






    }
}


bool Pausa(char *texto)
{
    char opcion[80];
    
    printf("%s", texto);

    do {

        gets(opcion);
        tolower(opcion[0]);

    } while (opcion[0] != 's' && opcion[0] != 'n');

    return (opcion[0] == 's')? true : false;
}
