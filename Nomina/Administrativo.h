///////////////////////////////////////////////////////////////////////////////////////////
// Administrativo.h
///////////////////////////////////////////////////////////////////////////////////////////



#ifndef ADMINISTRATIVO_H
#define ADMINISTRATIVO_H



#include "Empleado.h"



class Administrativo : public Empleado
{
	public:

		int ObtTipo() = 0;
		long Liquidacion() = 0;
		virtual void Guardar(ofstream file) = 0;
};



class Operativo : public Administrativo
{
	public:

		int ObtTipo();
		long Liquidacion();
		void Guardar(ofstream file);

	protected:
		int he; // horas extra
};



class Tactico : public Administrativo
{
	public:

		int ObtTipo();
		long Liquidacion();
		void Guardar(ofstream file);

	protected:
		int he; // horas extra
};



class Administrador : public Administrativo
{
	public:

		int ObtTipo();
		long Liquidacion();
		void Guardar(ofstream file);
};



#endif