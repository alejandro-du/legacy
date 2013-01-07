///////////////////////////////////////////////////////////////////////////////////////////
//                                                                                       //
//   Archivo fuente: PERSONA.CPP                                                         //
//                                                                                       //
//   Programador: Jairo Alejandro Duarte Avenda¤o.                                       //
//                                                                                       //
//   Caracteristicas: Proporciona la definici¢n de funciones miembro para C_Persona.     //
//                                                                                       //
//   Funcionamiento:                                                                     //
//                                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////



#include "elevador.h"


C_Persona::C_Persona(int dest = 1)
{
    destino = dest;
    posicion = 0;
    actitud = PERSONA_CAMINANDO;
    //cout<<"\n C_Persona::C_Persona";
}


C_Persona::~C_Persona()
{
//    static int cont = 1;
    //cout<<"\n C_Persona::~C_Persona() "<<cont;
//    cont++;
}


C_Persona::Animar();
{
    //Camina();
    switch(actitud) {
//        case PERSONA_CAMINANDO:
//        break;
          case PERSONA_ESPERANDO:

          break;

          case PERSONA_LLEGO_AL_ELEVADOR:
          break;


    }


}



C_Nodo_Personas::C_Nodo_Personas()
{
    persona = NULL; // el dato del £ltimo elemento siempre es NULL
    sig = NULL;
}


void C_Nodo_Personas::AgregarPersona(int destino = 1)
{
    C_Nodo_Personas *nuevo = new C_Nodo_Personas; // crear nuevo a insertar
    C_Nodo_Personas *temp;

    nuevo->persona = new C_Persona; // crear objeto

    temp = sig;
    sig = nuevo;
    nuevo->sig = temp;
}


void C_Nodo_Personas::Eliminar()
{
    C_Nodo_Personas *p, *temp;

    p = temp = sig; // apuntar al primer elemento

    while (p != NULL) { // (p->persona != NULL) tambi‚n es v lido
        delete p->persona; // borrar el dato
        temp = p->sig; // guardar el siguiente antes de eliminar el nodo
        delete p; // borrar el nodo
        p = temp; // apuntar al siguiente elemento
    }
}