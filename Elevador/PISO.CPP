///////////////////////////////////////////////////////////////////////////////////////////
//                                                                                       //
//   Archivo fuente: PISO.CPP                                                            //
//                                                                                       //
//   Programador: Jairo Alejandro Duarte Avenda¤o.                                       //
//                                                                                       //
//   Caracteristicas: Proporciona la definici¢n de funciones miembro para C_Piso         //
//                                                                                       //
//   Funcionamiento:                                                                     //
//                                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////



#include "elevador.h"


//int C_Piso::cont_pisos = 0;


C_Piso::C_Piso()
{
    static int cont_pisos = 0; // contador interno
    numero = cont_pisos;
    cont_pisos++;
    //cout<<"\n C_Piso::C_Piso";
    num_personas = 0;
}


C_Piso::~C_Piso()
{
    lista.Eliminar();
    //cout<<"\n C_Piso::~C_Piso()";
}


void C_Piso::GenerarPersonas(int num, int max_pisos)
{
    for(int i = 0; i < num; i++) {
        lista.AgregarPersona(rand() % (max_pisos - 1));
        num_personas++;
        //cout<<" "<<numero;
    }
}


void C_Piso::AnimarPersonas()
{
    C_Nodo_Personas *p = lista;

    while(p != NULL) {
        p->persona->Animar();
        p = p->siguiente;
    }
}
