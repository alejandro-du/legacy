///////////////////////////////////////////////////////////////////////////////////////////
// Empleado.cpp
///////////////////////////////////////////////////////////////////////////////////////////



#include "Empleado.h"
#include <string.h>
#include <iostream.h>



void Empleado::EstNombre(char *nombre)
{
	strcpy(this->nombre, nombre);
}



void Empleado::EstCedula(char *cedula)
{
	strcpy(cc, cedula);
}



void Empleado::EstHorasExtra(int n)
{
	extra = n;
}



void Empleado::ObtNombre(char *dest)
{
	strcpy(dest, nombre);
}



void Empleado::ObtCedula(char *dest)
{
	strcpy(dest, cc);
}



int Empleado::ObtHorasExtra()
{
	return extra;
}