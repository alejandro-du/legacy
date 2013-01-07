///////////////////////////////////////////////////////////////////////////////////////////
// Lista.h
///////////////////////////////////////////////////////////////////////////////////////////



#ifndef LISTA_H
#define LISTA_H



#include "Empleado.h"



class Nodo {

    public:

        Nodo();
        Nodo(Empleado *pDt);
        virtual ~Nodo();
        
        Empleado *pEmpleado;
        Nodo *pSiguiente;
};



class Lista {
    
    public:

        Lista();
        virtual ~Lista();

        bool InsertarNodo(Empleado *pDt);
        bool RemoverNodo(const int indice);
		int Buscar(const char *cedula);
		Nodo *ObtNodo();

    protected:

        Nodo *pPrimero;
};



#endif