///////////////////////////////////////////////////////////////////////////////////////////
//                                                                                       //
//   Archivo fuente: EDIFICIO.CPP                                                        //
//                                                                                       //
//   Programador: Jairo Alejandro Duarte Avenda¤o.                                       //
//                                                                                       //
//   Caracteristicas: Proporciona la definici¢n de funciones miembro para C_Edificio.    //
//                                                                                       //
//   Funcionamiento:                                                                     //
//                                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////



#include "elevador.h"


C_Edificio::C_Edificio(int p = EDIFICIO_PISOS, // n£mero de pisos
                       int d = EDIFICIO_DISTANCIA_PISOS, // distancia entre pisos
                       const C_Tasa &t, // tasa de llegada de pasajeros
                       C_Elevador *e = new C_Elevador) : // elevador utilizado
    pisos(p),
    distancia_pisos(d),
    elevador(e) // asignar objeto elevador correspondiente
{
    tasa = t;
    piso = new C_Piso[pisos];
//    cout<<"\n C_Edificio::C_Edificio()";
}


C_Edificio::~C_Edificio()
{
    delete elevador;
    delete [] piso;
    //cout<<"\n C_Edificio::~C_Edificio()";
}


void C_Edificio::GenerarPersonas()
{
    static int rnd_i;
    static bool ultima_llamada = true;

    if(ultima_llamada) // solo generar cuando se hayan creado las personas
    {
        rnd_i = tasa.minimo + rand() % (tasa.maximo + 1 - tasa.minimo);
        ultima_llamada = tasa.reloj.intervalo;
    }

    if(tasa.reloj.intervalo >= rnd_i) {

        for(int i = 0; i < pisos; i++)
           piso[i].GenerarPersonas(1 + rand() % tasa.num_personas, pisos);

        tasa.reloj.intervalo -= rnd_i;
        GenerarPersonas();
        // DEBUG: tomar en cuenta lo que queda de tiempo en el intervalo
        tasa.reloj.Reset();
        ultima_llamada = true;
    }
    else ultima_llamada = false;


    tasa.reloj.Actualizar();
}


void C_Edificio::AnimarPersonas();
{
    for(int i = 0; i < pisos; i++) {
        piso[i].AnimarPersonas();
    }
}
