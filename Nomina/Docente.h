///////////////////////////////////////////////////////////////////////////////////////////
// Docente.h
///////////////////////////////////////////////////////////////////////////////////////////



#ifndef DOCENTE_H
#define DOCENTE_H



#include "Empleado.h"
#include <fstream.h>



class Docente : public Empleado {

	public:

		int ObtTipo();
		long Liquidacion();
		void EstSalario(int s);
		void EstHoras(int h);
		void Guardar(ofstream file);

	//protected:
		int hd; // horas dictadas
		int salario; // salario según el título del docente
};



#endif