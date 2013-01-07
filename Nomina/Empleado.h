///////////////////////////////////////////////////////////////////////////////////////////
// Empleado.h
///////////////////////////////////////////////////////////////////////////////////////////



#ifndef EMPLEADO_H
#define EMPLEADO_H



#include <fstream.h>



// tipos de empleados
#define ADMINISTRADOR 1
#define TACTICO		  2
#define OPERATIVO	  3
#define DOCENTE		  4

// salarios:
#define SALARIO_MINIMO 332000L

#define SALARIO_ADMINISTRADOR   2000000
#define SALARIO_TACTICO         1000000
#define SALARIO_OPERATIVO        500000

#define SALARIO_PREGRADO          15000
#define SALARIO_ESPECIALIZACION   18000
#define SALARIO_MAESTRIA          25000
#define SALARIO_DOCTORADO		  50000

// liquidación de las horas extra:
#define HE_DOCENTE                 8000
#define HE_OPERATIVO            HE_DOCENTE * 3
#define HE_TACTICO              HE_DOCENTE * 3

// porcentajes de descuentos:
#define RET_FUENTE 0.02
#define EPS        0.0375
#define PENSION    0.0425



class Empleado {

	public:

		void ObtNombre(char *dest);
		void ObtCedula(char *dest);
		int ObtHorasExtra();
		
		void EstNombre(char *nombre);
		void EstCedula(char *cedula);
		void EstHorasExtra(int n);

		virtual int ObtTipo() = 0;
		virtual long Liquidacion() = 0;
		virtual void Guardar(ofstream file) = 0;

	protected:

		char nombre[100];
		char cc[30];
		int extra; // horas extra
};



#endif