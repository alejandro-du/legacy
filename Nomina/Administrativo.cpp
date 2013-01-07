///////////////////////////////////////////////////////////////////////////////////////////
// Administrativo.cpp
///////////////////////////////////////////////////////////////////////////////////////////



#include "Administrativo.h"
#include <iostream.h>
#include <string.h>



long Operativo::Liquidacion()
{
	long s;

	s = SALARIO_OPERATIVO + (extra * HE_OPERATIVO); // calcular

	return s;
}



int Operativo::ObtTipo()
{
	return OPERATIVO;
}



void Operativo::Guardar(ofstream file)
{
	file << OPERATIVO << endl
		 << nombre << endl
	     << cc << endl
		 << extra << endl;
}



long Tactico::Liquidacion()
{
	long s;

	s = SALARIO_TACTICO + (extra * HE_TACTICO); // calcular

	return s;
}



int Tactico::ObtTipo()
{
	return TACTICO;
}



void Tactico::Guardar(ofstream file)
{
	file << TACTICO << endl
		 << nombre << endl
	     << cc << endl
		 << extra << endl;
}



long Administrador::Liquidacion()
{
	return SALARIO_ADMINISTRADOR;
}



int Administrador::ObtTipo()
{
	return ADMINISTRADOR; // el salario es fijo
}



void Administrador::Guardar(ofstream file)
{
	file << ADMINISTRADOR << endl
		 << nombre << endl
	     << cc << endl;
}