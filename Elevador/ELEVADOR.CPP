///////////////////////////////////////////////////////////////////////////////////////////
//                                                                                       //
//   Archivo fuente: ELEVADOR.CPP                                                        //
//                                                                                       //
//   Programador: Jairo Alejandro Duarte Avenda¤o.                                       //
//                                                                                       //
//   Caracteristicas: Proporciona la definici¢n de funciones miembro para C_Elevador.    //
//                                                                                       //
//   Funcionamiento:                                                                     //
//                                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////



#include "elevador.h"


C_Elevador::C_Elevador(int cap = ELEVADOR_CAPACIDAD,
                       int v = ELEVADOR_VELOCIDAD,
                       int t = ELEVADOR_TIEMPO_ESPERA,
                       int max_d = ELEVADOR_DESTINOS_MAX)
{
    capacidad = cap;
    velocidad = v;
    tiempo_espera = t;
    max_destinos = max_d;

    num_pasajeros = 0; // no hay pasajeros (elevador vac¡o)
    piso = 1; // comenzar en el primer piso

    pasajero = new C_Persona*[cap]; // preparar el array de punteros a C_Persona
    //cout<<"\n C_Elevador::C_Elevador()";
}


C_Elevador::~C_Elevador()
{
    for(int i = 0; i < num_pasajeros; i++) delete pasajero[i]; // borrar pasajeros
    delete [] pasajero; // borrar array
    //cout<<"\n C_Elevador::~C_Elevador()";
}
