// Servidor.cpp



#include "Servidor.h"



int Servidor::Buscar(Usuario u)
{
    char nombre[MAX_NOMBRE + 12],
         password[MAX_PASSWORD],
         passwordArchivo[MAX_PASSWORD];

    FILE *file;

    u.ObtNombre(nombre); // obtener el nombre del usuario
    u.ObtPassword(password);

    strcat(nombre, "\\");
    strcat(nombre, ARCHIVO_PASSWORD);
    
    file = fopen(nombre, "r"); // intentar abrir el archivo de password

    if(!file)
        return -1; // no existe el archivo => no existe el usuario

    fgets(passwordArchivo, MAX_PASSWORD, file);

    if(strcmp(passwordArchivo, password) != 0) { // contraseña incorrecta
        fclose(file);
        return 1;
    }
    
    fclose(file);
    
    return 0;
}


void Servidor::Crear(Usuario u)
{
    char nombre[MAX_NOMBRE], password[MAX_PASSWORD];
    char archivo[100];
    FILE *file;

    u.ObtNombre(nombre);
    u.ObtPassword(password);

    Ejecutar("mkdir", nombre);

    strcpy(archivo, nombre);
    strcat(archivo, "\\");
    strcat(archivo, ARCHIVO_PASSWORD);

    file = fopen(archivo, "w"); // crear el archivo para guardar el password

    fputs(password, file);

    fclose(file);
}


void Servidor::EnviarMensaje(Usuario u)
{
    char directorio[MAX_NOMBRE],
         destino[MAX_NOMBRE + 10],
         numero[3],
         mensaje[MAX_MENSAJE];

    FILE *file;
    int i;
    
    printf("\n\n\tDestino: ");

    gets(directorio);

    for(i = 0; i <= 999; i++) {

        strcpy(destino, directorio);

        sprintf(numero, "%03d", i);

        strcat(destino, "\\");
        strcat(destino, "msg");
        strcat(destino, numero);
        strcat(destino, ".msg");
        
        file = fopen(destino, "r");

        if(file == NULL)
            break;

        else fclose(file);
    }

    if(i > 999) {
        printf("\n\n\tEl destinatario no puede recibir más mensajes.");
        return;
    }

    file = fopen(destino, "w");

    if(file == NULL) {
        printf("\n\n\tEl mensaje no pudo ser enviado.\n");
        return;
    }

    printf("\n\tMensaje: ");
    gets(mensaje);

    fputs(mensaje, file);

    fclose(file);
}


void Servidor::VerMensajes(Usuario u)
{
    char archivo[MAX_NOMBRE + 10],
         numero[3],
         mensaje[MAX_MENSAJE];

    FILE *file;
        
    for(int i = 0; i <= 999; i++) {

        u.ObtNombre(archivo);
    
        sprintf(numero, "%03d", i);

        strcat(archivo, "\\");
        strcat(archivo, "msg");
        strcat(archivo, numero);
        strcat(archivo, ".msg");

        file = fopen(archivo, "r");

        if(file == NULL)
            continue;

        fgets(mensaje, MAX_MENSAJE, file);

        printf("\n\n----------------------------------------------------------------------");
        printf("\nMensaje %d:", i);
        printf("\n  %s", mensaje);
        printf("\n\n\tPresione ENTER para continuar...");
        getchar();

        fclose(file);
    }
}


void Servidor::Ejecutar(char *cmd, char *arg)
{
    char linea[100];

    strcpy(linea, cmd);
    strcat(linea, " ");
    strcat(linea, arg);

    system(linea);
}