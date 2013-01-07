///////////////////////////////////////////////////////////////////////////////////////////
// Lista.cpp
///////////////////////////////////////////////////////////////////////////////////////////



#include "Lista.h"
#include <string.h>



#define SAFE_DELETE(p) if(p != NULL) delete p



Nodo::Nodo()
{
    pEmpleado = NULL;
    pSiguiente = NULL;
}



Nodo::~Nodo()
{
    SAFE_DELETE(pEmpleado);
}



Nodo::Nodo(Empleado *pDt)
{
    pEmpleado = pDt; // asignar el objeto al nodo
    pSiguiente = NULL;
}



Lista::Lista()
{
    pPrimero = NULL; // sin elementos
}



Lista::~Lista()
{
    // eliminar todos los nodos
    while(RemoverNodo(0));
}



///////////////////////////////////////////////////////////////////////////////////////////
// Agrega un nodo con el empleado dado, al principio de la lista
///////////////////////////////////////////////////////////////////////////////////////////
bool Lista::InsertarNodo(Empleado *pDt)
{
	Nodo *p= new Nodo(pDt);

	if(pPrimero == NULL) {
		pPrimero = p;
	}

	else {
		p->pSiguiente = pPrimero;
		pPrimero = p;
	}

    return true;
}



///////////////////////////////////////////////////////////////////////////////////////////
// Elimina el nodo especificado
///////////////////////////////////////////////////////////////////////////////////////////
bool Lista::RemoverNodo(const int indice)
{
    Nodo *pARemover, *pAnterior;

    if(pPrimero == NULL) // si está vacía
        return false;

    pARemover = pPrimero;
    pAnterior = pPrimero;
    
    if(indice == 0)
        pPrimero = pPrimero->pSiguiente;

    for(int i = 0; i < indice; i++) {
        
        if(pARemover == NULL) // si el indice es incorrecto
            return false;

        pAnterior = pARemover;

        pARemover = pARemover->pSiguiente;
    }

    pAnterior->pSiguiente = pARemover->pSiguiente;

    SAFE_DELETE(pARemover);

    return true;
}



///////////////////////////////////////////////////////////////////////////////////////////
// Devuelve el índice del nodo que contenga el empleado con la cédula solicitada
///////////////////////////////////////////////////////////////////////////////////////////
int Lista::Buscar(const char *cedula)
{
	Nodo *p = pPrimero;
	char cad[30];
	int i = 0;

	while(p) {
	
		pPrimero->pEmpleado->ObtCedula(cad);

		if(strcmp(cedula, cad) == 0)
			return i;

		p = p->pSiguiente;
		i++;
	}

	return -1;
}



///////////////////////////////////////////////////////////////////////////////////////////
// Devuelve el primer nodo de la lista
///////////////////////////////////////////////////////////////////////////////////////////
Nodo* Lista::ObtNodo()
{
	return pPrimero;
}