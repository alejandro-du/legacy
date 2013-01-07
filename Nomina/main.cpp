///////////////////////////////////////////////////////////////////////////////////////////
// Menu.cpp
///////////////////////////////////////////////////////////////////////////////////////////



#include "Menu.h"
#include "Nomina.h"
#include <iostream.h>



///////////////////////////////////////////////////////////////////////////////////////////
// Punto de entrada de la aplicación
///////////////////////////////////////////////////////////////////////////////////////////
void main()
{
    int opcion;    // número de la opción del usuari
    Nomina nomina; // objeto con la funcionalidad de la nómina
    Menu menu;	   // manejador del menú
    
	char *principal[] = {"CARGAR", // cadenas con las opciones del menú principal
                         "GUARDAR",
                         "AGREGAR EMPLEADO",
						 "ELIMINAR EMPLEADO",
						 "REPORTE NOMINA",
                         "SALIR"};

    if(!nomina.Cargar("Nomina.dat")) { // si no existe el archivo

        // crearlo
        if(!nomina.Nuevo("Nomina.dat")) { // si no se puede crear
            cout << "\nError: No se puede crear el archivo <Nomina.dat>.";
            return; // salir del programa
        }

        // abrirlo
        if(!nomina.Cargar("Nomina.dat")) { // si definitivamente no se puede
            cout << "\nError: No se puede abrir el archivo <Nomina.dat>.";
            return; // salir del programa
        }
    }

    menu.Configurar("MENU PRINCIPAL", principal, 6); // pasar las opciones al menú

    do {

        opcion = menu.ObtenerSeleccion();

        switch(opcion) { // llamar al método seleccionado por el usuario

            case 1:
                nomina.Cargar("Nomina.dat");
            break;

            case 2:
                nomina.Guardar("Nomina.dat");
            break;

            case 3:	{
			    
				Menu m; // submenú
				char *agregar[] = {"Administrador", // cadenas con las opciones
						           "Operativo",
								   "Tactico",
								   "Docente",
								   "Menu principal"};

			    m.Configurar("AGREGAR EMPLEADO", agregar, 5); // pasar las opciones al menú

			    do {

					opcion = m.ObtenerSeleccion();

					switch(opcion) { // llamar al metodo requerido

						case 1:
							nomina.AgregarAdministrador();
						break;

						case 2:
							nomina.AgregarOperativo();
						break;

						case 3:
							nomina.AgregarTactico();
						break;

						case 4:
							nomina.AgregarDocente();
						break;
					}

				} while(opcion != 5);

				opcion = 3; // reestablecer el valor anterior
			}
			break;

            case 4:
				nomina.EliminarEmpleado();
			break;
            
			case 5: {

				Menu m; // submenú
				char *reporte[] = {"Listado", // cadenas de opciones
					               "Total",
					               "Administrativos",
						           "Operativos",
								   "Tacticos",
								   "Docentes",
								   "Menu principal"};

			    m.Configurar("REPORTE NOMINA", reporte, 7);

				do {

					opcion = m.ObtenerSeleccion();

					switch(opcion) { // llamar el método apropiado

						case 1:
							nomina.Listado();
						break;

						case 2:
							nomina.Total();
						break;

						case 3:
							nomina.TotalAdministrativos();
						break;

						case 4:
							nomina.TotalOperativos();
						break;

						case 5:
							nomina.TotalTacticos();
						break;

						case 6:
							nomina.TotalDocentes();
						break;
					}

				} while(opcion != 7);

				opcion = 5; // reestablecer el valor anterior
			}
            break;
        }

    } while(opcion != 6);

	
	char cad[80];
	cout << "\n Desea guardar los datos en el archivo? (S/N) ";
	cin.getline(cad, 80);

	if(cad[0] == 's' || cad[0] == 'S') {
		nomina.Guardar("Nomina.dat");
	}
}