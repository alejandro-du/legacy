///////////////////////////////////////////////////////////////////////////////////////////
// Docente.cpp
///////////////////////////////////////////////////////////////////////////////////////////



#include "Docente.h"



long Docente::Liquidacion()
{
	long s;
	long descuento = 0;
	
	s = (long) (salario * hd) + (extra * HE_DOCENTE); // calcular liquidación

	if(s < SALARIO_MINIMO) {

		descuento = (long) (s * RET_FUENTE);
	}

	else {

		descuento = (long) ((s * EPS) + (s * PENSION));
	}

	s -= descuento;
	
	return s;
}



int Docente::ObtTipo()
{
	return DOCENTE;
}



void Docente::EstSalario(int s)
{
	salario = s;
}



void Docente::EstHoras(int h)
{
	hd = h;
}



void Docente::Guardar(ofstream file)
{
	file << DOCENTE << endl
		 << nombre << endl
	     << cc << endl
		 << salario << endl
		 << hd << endl
		 << extra << endl;
}