///////////////////////////////////////////////////////////////////////////////////////////
// Nomina.h
///////////////////////////////////////////////////////////////////////////////////////////



#ifndef NOMINA_H
#define NOMINA_H



#include "Lista.h"
#include "Empleado.h"
#include "Docente.h"
#include "Administrativo.h"



class Nomina {

    public:

        Nomina();
		~Nomina();
		bool Nuevo(char *archivo);   // crea un archivo para guardar los datos
        bool Cargar(char *archivo);  // carga el archivo con los datos
		bool Guardar(char *archivo); // guarda los datos en el archivo
        void AgregarAdministrador(); // agrega un administrador
        void AgregarOperativo();	 
        void AgregarTactico();		 
        void AgregarDocente();		 
        void EliminarEmpleado();
		void Listado();
		void Total();
		void TotalAdministrativos();
		void TotalTacticos();
		void TotalOperativos();
		void TotalDocentes();

    protected:

		Lista *lista; // lista enlazada de empleados
};



#endif