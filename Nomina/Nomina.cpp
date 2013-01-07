///////////////////////////////////////////////////////////////////////////////////////////
// Nomina.cpp
///////////////////////////////////////////////////////////////////////////////////////////



#include "Nomina.h"
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>



///////////////////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////////////////
Nomina::Nomina()
{
	lista = new Lista; // crear una nueva lista
}



///////////////////////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////////////////////
Nomina::~Nomina()
{
	delete lista; // liberar la memoria
}



///////////////////////////////////////////////////////////////////////////////////////////
// Crea el archivo especificado
///////////////////////////////////////////////////////////////////////////////////////////
bool Nomina::Nuevo(char *archivo)
{
	ofstream file(archivo); // crear el objeto para el archivo con el nombre solicitado

	if(!file) // verificar
		return false;

    return true;
}



///////////////////////////////////////////////////////////////////////////////////////////
// Carga el archivo de nómina especificado
///////////////////////////////////////////////////////////////////////////////////////////
bool Nomina::Cargar(char *archivo)
{
	Administrador *a;
	Tactico *t;
	Operativo *o;
	Docente *d;
	Nodo *p = lista->ObtNodo(); // obtener el primer nodo de la lista enlazada
	ifstream file(archivo); // manejador del archivo
	int tipo, // tipo de empleado
		n;
	char nombre[100],
		 cedula[30],
		 cad[100];

	if(!file) // verificar
		return false;

	delete lista; // eliminar la lista antigua
	lista = new Lista; // crear una nueva (vacía)

	while(file.getline(cad, 100)) { // mientras no se llegue al final del archivo

		tipo = atoi(cad); // convertir de cadena a entero
		file.getline(nombre, 100); // leer el nombre
		file.getline(cedula, 30); // leer la cédula

		switch(tipo) { // según el tipo de empleado

			case DOCENTE:
				d = new Docente; // instanciar un objeto nuevo

				// establecer atributos
				d->EstNombre(nombre);
				d->EstCedula(cedula);

				file.getline(cad, 100); // leer salario
				n = atoi(cad); // convertir a int
				d->EstSalario(n); // establecer el atributo

				file.getline(cad, 100); // leer horas dictadas
				n = atoi(cad); // convertir a int
				d->EstHoras(n); // establecer el atributo
				
				file.getline(cad, 100); // leer horas extra
				n = atoi(cad); // // convertir a int
				d->EstHorasExtra(n); // establecer el atributo

				lista->InsertarNodo(d); // agregar el empleado a la lista
			break;

			case ADMINISTRADOR:
				a = new Administrador; // crear un objeto nuevo
				
				// establecer atributos
				a->EstNombre(nombre);
				a->EstCedula(cedula);

				lista->InsertarNodo(a); // agregar el empleado a la lista

			break;

			case TACTICO:
				t = new Tactico; // crear un objeto nuevo

				// establecer atributos
				t->EstNombre(nombre);
				t->EstCedula(cedula);

				file.getline(cad, 100);
				n = atoi(cad);
				t->EstHorasExtra(n);

				lista->InsertarNodo(t); // agregar el empleado a la lista
			break;

			case OPERATIVO:
				o = new Operativo; // crear un objeto nuevo

				// establecer atributos
				o->EstNombre(nombre);
				o->EstCedula(cedula);

				file.getline(cad, 100);
				n = atoi(cad);
				o->EstHorasExtra(n);

				lista->InsertarNodo(o); // agregar el empleado a la lista
			break;

			default:
				return false;
			break;
		}
	}

	cout << "\n Archivo <" << archivo << "> cargado.";

    return true;
}



///////////////////////////////////////////////////////////////////////////////////////////
// Guarda los datos en el archivo de nómina especificado
///////////////////////////////////////////////////////////////////////////////////////////
bool Nomina::Guardar(char *archivo)
{
	Empleado *emp;
	Nodo *p = lista->ObtNodo();
	ofstream file(archivo); // abrir el archivo

	if(!file) // verificar
		return false;

	while(p) { // mientras el empleado no sea nulo (no se llegue al final de la lista)

		emp = p->pEmpleado; // obtener el empleado del nodo actual

		emp->Guardar(file); // llamar al método adecuado
		
		p = p->pSiguiente; // pasar al siguiente nodo
	}

	cout << "\n Archivo <" << archivo << "> guardado.";
	cout << endl << "\n <Presione ENTER para continuar>";
	cin.get();

    return true;
}



///////////////////////////////////////////////////////////////////////////////////////////
// Añade un administrador a la lista de empleados
///////////////////////////////////////////////////////////////////////////////////////////
void Nomina::AgregarAdministrador()
{
	Administrador *e = new Administrador;
	char cad[100];

	cout << " C.C.: ";
	cin.getline(cad, 30);

	if(lista->Buscar(cad) != -1) { // verificar que no exista
		cout << "\n Este registro ya existe en la nomina.";
		cout << endl << "\n <Presione ENTER para continuar>";
		cin.get();
		return;
	}

	e->EstCedula(cad);

	cout << " Nombre: ";
	cin.getline(cad, 100);

	e->EstNombre(cad);
	lista->InsertarNodo(e); // agregar el nuevo empleado a la lista
}



///////////////////////////////////////////////////////////////////////////////////////////
// Añade un operativo a la lista de empleados
///////////////////////////////////////////////////////////////////////////////////////////
void Nomina::AgregarOperativo()
{
	Operativo *e = new Operativo;
	char cad[100];
	int n;

	cout << " C.C.: ";
	cin.getline(cad, 30);

	if(lista->Buscar(cad) != -1) { // verificar que no exista
		cout << "\n Este registro ya existe en la nomina.";
		cout << endl << "\n <Presione ENTER para continuar>";
		cin.get();
		return;
	}

	e->EstCedula(cad);

	cout << " Nombre: ";
	cin.getline(cad, 100);

	e->EstNombre(cad);

	cout << " Horas extra: ";
	cin.getline(cad, 30);
	n = atoi(cad);

	e->EstHorasExtra(n);

	lista->InsertarNodo(e); // agregar el nuevo empleado a la lista
}



///////////////////////////////////////////////////////////////////////////////////////////
// Añade un tactico a la lista de empleados
///////////////////////////////////////////////////////////////////////////////////////////
void Nomina::AgregarTactico()
{
	Tactico *e = new Tactico;
	char cad[100];
	int n;

	cout << " C.C.: ";
	cin.getline(cad, 30);

	if(lista->Buscar(cad) != -1) { // verificar que no exista
		cout << "\n Este registro ya existe en la nomina.";
		cout << endl << "\n <Presione ENTER para continuar>";
		cin.get();
		return;
	}

	e->EstCedula(cad);

	cout << " Nombre: ";
	cin.getline(cad, 100);

	e->EstNombre(cad);

	cout << " Horas extra: ";
	cin.getline(cad, 30);
	n = atoi(cad);

	e->EstHorasExtra(n);

	lista->InsertarNodo(e); // agregar el nuevo empleado a la lista
}



///////////////////////////////////////////////////////////////////////////////////////////
// Añade un docente a la lista de empleados
///////////////////////////////////////////////////////////////////////////////////////////
void Nomina::AgregarDocente()
{
	Docente *e = new Docente;
	char cad[100];
	int n;

	cout << " C.C.: ";
	cin.getline(cad, 30);

	if(lista->Buscar(cad) != -1) { // verificar que no exista
		cout << "\n Este registro ya existe en la nomina.";
		cout << endl << "\n <Presione ENTER para continuar>";
		cin.get();
		return;
	}

	e->EstCedula(cad);

	cout << " Nombre: ";
	cin.getline(cad, 100);

	e->EstNombre(cad);

	// solicitar el título del docente
	cout << " Titulo (1 - Pregrado 2 - Especializacion 3 - Maestria 4 - Doctorado) ? ";
	cin.getline(cad, 30);
	n = atoi(cad);

	// establecer el salario según el título
	if(n == 1)
		n = SALARIO_PREGRADO;

	else if(n == 2)
		n = SALARIO_ESPECIALIZACION;

	else if(n == 3)

		n = SALARIO_MAESTRIA;
	
	else if(n == 4)
		n = SALARIO_DOCTORADO;

	e->EstSalario(n);

	cout << " Horas dictadas: ";
	cin.getline(cad, 30);
	n = atoi(cad);

	e->EstHoras(n);

	cout << " Horas extra: ";
	cin.getline(cad, 30);
	n = atoi(cad);

	e->EstHorasExtra(n);

	lista->InsertarNodo(e); // agregar el nuevo empleado a la lista
}



///////////////////////////////////////////////////////////////////////////////////////////
// Elimina un empleado la lista
///////////////////////////////////////////////////////////////////////////////////////////
void Nomina::EliminarEmpleado()
{
	char cad[30];
	int i;

	cout << "\n Cedula: ";
	cin.getline(cad, 30); // solicitud

	i = lista->Buscar(cad); // buscar y obtener el índice delntro de la lista

	if(i != -1) // si se encontró
	{
		if(lista->RemoverNodo(i)) { // remover y verificar
			cout << "\n El registro ha sido eliminado.";
		}

		else {
			cout << "\n No se pudo eliminar el registro.";
		}
	}

	else { // si no se encontró
		cout << "\n El registro solicitado no existe.";
	}

	cout << endl << "\n <Presione ENTER para continuar>";
	cin.get();
}



///////////////////////////////////////////////////////////////////////////////////////////
// Imprime la liquidación de cada empleado
///////////////////////////////////////////////////////////////////////////////////////////
void Nomina::Listado()
{
	Empleado *emp;
	Nodo *p = lista->ObtNodo(); // obtener el primer nodo de la lista enlazada
	long salario,
		 total = 0;
	int  n = 0;
	char nombre[100],
		 cedula[30];

	cout << "\n\n\n";

	if(!p) {

		cout << " No hay registros.";
		cout << endl << "\n <Presione ENTER para continuar>";
		cin.get();
		return;
	}

	// imprimir cabecera
	cout << " ------------------------------------------------------------------------------\n";
	cout << " | Nombre                                       Cedula      Liquidacion       |\n";
	cout << " ------------------------------------------------------------------------------\n";
	
	do { // para cada nodo

		if(n > 19) { // si ya se imprimieron más de 19 empleados

			n = 0; // volver a comenzar
			cout << endl << " <Presione ENTER para continuar>";
			cin.get();

			// imprimir cabecera nuevamente
			cout << " ------------------------------------------------------------------------------\n";
			cout << " | Nombre                                       Cedula      Liquidacion       |\n";
			cout << " ------------------------------------------------------------------------------\n";
		}

		emp = p->pEmpleado; // obtener el empleado del nodo actual

		// obtener datos
		emp->ObtNombre(nombre);
		emp->ObtCedula(cedula);
		
		salario = emp->Liquidacion(); // obtener liquidación
		total += salario; // sumar al total

		// imprimir datos
		cout << "   ";
		cout.setf(ios::left);
		cout.width(45);
		cout << nombre;
		cout.width(12);
		cout << cedula << flush;
		cout << salario << "\n";

		p = p->pSiguiente; // pasar al siguiente nodo

		n++; // siguiente línea

	} while (p); // mientras no se llegue al final de la lista enlazada
	
	// imprimir el total al finalizar la lista
	cout << endl;
	cout << "                                                    Total: $" << total;

	cout << endl << "\n <Presione ENTER para continuar>";
	cin.get();
}



///////////////////////////////////////////////////////////////////////////////////////////
// Imprime la liquidación total de la nómina
///////////////////////////////////////////////////////////////////////////////////////////
void Nomina::Total()
{
	Empleado *emp;
	Nodo *p = lista->ObtNodo();
	int i = 0;
	long salario,
		 total = 0;

	for(i = 0; p; i++) { // cada nodo

		emp = p->pEmpleado; // obtener el empleado

		salario = emp->Liquidacion(); // obtener liquidación
		total += salario; // sumar al total

		p = p->pSiguiente; // pasar al siguiente nodo
	}

	if(i) { // si se imprimió al menos un empleado
		cout << "\n\n Liquidacion para " << i << " empleados.";
		cout << "\n\n Total: $" << total;
	}

	else {
		cout << "\n No hay registros.";
	}

	cout << endl << "\n <Presione ENTER para continuar>";
	cin.get();
}



///////////////////////////////////////////////////////////////////////////////////////////
// Imprime la liquidación total de empleados administrativos
///////////////////////////////////////////////////////////////////////////////////////////
void Nomina::TotalAdministrativos()
{
	Empleado *emp;
	Nodo *p = lista->ObtNodo();
	int i = 0;
	long salario,
		 total = 0;

	while(p) {

		emp = p->pEmpleado;

		if(emp->ObtTipo() == ADMINISTRADOR) {
			i++;

			salario = emp->Liquidacion();
			total += salario;
		}

		p = p->pSiguiente;
	}

	if(i) {
		cout << "\n\n Liquidacion para " << i << " empleados administrativos.";
		cout << "\n\n Total: $" << total;
	}

	else {
		cout << "\n No hay registros de este tipo.";
	}

	cout << endl << "\n <Presione ENTER para continuar>";
	cin.get();
}



///////////////////////////////////////////////////////////////////////////////////////////
// Imprime la liquidación total de empleados tacticos
///////////////////////////////////////////////////////////////////////////////////////////
void Nomina::TotalTacticos()
{
	Empleado *emp;
	Nodo *p = lista->ObtNodo();
	int i = 0;
	long salario,
		 total = 0;

	while(p) {

		emp = p->pEmpleado;

		if(emp->ObtTipo() == TACTICO) {
			i++;

			salario = emp->Liquidacion();
			total += salario;
		}

		p = p->pSiguiente;
	}

	if(i) {
		cout << "\n\n Liquidacion para " << i << " empleados tacticos.";
		cout << "\n\n Total: $" << total;
	}

	else {
		cout << "\n No hay registros de este tipo.";
	}

	cout << endl << "\n <Presione ENTER para continuar>";
	cin.get();
}



///////////////////////////////////////////////////////////////////////////////////////////
// Imprime la liquidación total de empleados operativos
///////////////////////////////////////////////////////////////////////////////////////////
void Nomina::TotalOperativos()
{
	Empleado *emp;
	Nodo *p = lista->ObtNodo();
	int i = 0;
	long salario,
		 total = 0;

	while(p) {

		emp = p->pEmpleado;

		if(emp->ObtTipo() == OPERATIVO) {
			i++;

			salario = emp->Liquidacion();
			total += salario;
		}

		p = p->pSiguiente;
	}

	if(i) {
		cout << "\n\n Liquidacion para " << i << " empleados operativos.";
		cout << "\n\n Total: $" << total;
	}

	else {
		cout << "\n No hay registros de este tipo.";
	}

	cout << endl << "\n <Presione ENTER para continuar>";
	cin.get();
}



///////////////////////////////////////////////////////////////////////////////////////////
// Imprime la liquidación total de los docentes
///////////////////////////////////////////////////////////////////////////////////////////
void Nomina::TotalDocentes()
{
	Empleado *emp;
	Nodo *p = lista->ObtNodo();
	int i = 0;
	long salario,
		 total = 0;

	while(p) {

		emp = p->pEmpleado;

		if(emp->ObtTipo() == DOCENTE) {
			i++;

			salario = emp->Liquidacion();
			total += salario;
		}

		p = p->pSiguiente;
	}

	if(i) {
		cout << "\n\n Liquidacion para " << i << " docentes.";
		cout << "\n\n Total: $" << total;
	}

	else {
		cout << "\n No hay registros de este tipo.";
	}

	cout << endl << "\n <Presione ENTER para continuar>";
	cin.get();
}