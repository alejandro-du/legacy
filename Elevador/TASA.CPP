///////////////////////////////////////////////////////////////////////////////////////////
//                                                                                       //
//   Archivo fuente: TASA.CPP                                                            //
//                                                                                       //
//   Programador: Jairo Alejandro Duarte Avenda¤o.                                       //
//                                                                                       //
//   Caracteristicas: Proporciona la definici¢n de funciones miembro para C_Tasa.        //
//                                                                                       //
//   Funcionamiento:                                                                     //
//                                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////



#include "elevador.h"


C_Tasa::C_Tasa(int num = TASA_UNA_PERSONA, int min = TASA_MINIMO, int max = TASA_MAXIMO)
{
    minimo = min;
    maximo = max;
    num_personas = num;
//    cout<<"\n C_Tasa::C_Tasa()";
}


C_Tasa::~C_Tasa()
{
//    cout<<"\n C_Tasa::~C_Tasa()";
}


C_Reloj::C_Reloj()
{
    inicial = time(0);
    Actualizar();
    //cout<<"\n C_Reloj::C_Reloj()";
}


C_Reloj::~C_Reloj()
{
    //cout<<"\n C_Reloj::~C_Reloj()";
}


void C_Reloj::Actualizar()
{
    final = time(0);
    intervalo = final - inicial;
}


void C_Reloj::Reset()
{
    inicial = final;
    final = time(0);
    intervalo = final - inicial;
    //cout<<"\n ::Reset() " <<intervalo;
}
