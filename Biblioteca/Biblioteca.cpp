////////////////////////////////////////////////////////////////////////////////////////
//  PROYECTO FINAL DE PROGRAMACI‡N GRUPO 7
//  UNIVERSIDAD DISTRITAL FRANCISCO JOSê DE CALDAS
//
//  Autores: Alejandro Duarte
//           AndrÇs Fautoque
//
//  Compiladores: DJGPP C++, Borland C++
////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////
//  ARCHIVOS DE CABECERA
////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <assert.h>



////////////////////////////////////////////////////////////////////////////////////////
//  MACROS Y CONSTANTES
////////////////////////////////////////////////////////////////////////////////////////

#define liberar_mem(p) if(p != NULL) delete p // libera memoria din†mica

#define LIBRO   0  // constantes para cada tipo de art°culo
#define REVISTA 1
#define VIDEO   2
#define CDROM   3

#define MAX_ARTICULOS 1000 // n£mero m†ximo de art°culos
#define MAX_STR       200  // logitud m†xima para una cadena

typedef char BOOL; // valor falso o verdadero
#define TRUE  1    // valores para BOOL
#define FALSE 0

////////////////////////////////////////////////////////////////////////////////////////
//  PROTOTIPOS DE FUNCIONES
////////////////////////////////////////////////////////////////////////////////////////

int menu(const char *titulo, char *opciones[], const int num_opciones);
void centrar(const char *texto);
int presionar_una_tecla();
int BuscarTitulo(char *s, const int tipo);

void AgregarArticulo(int tipo);
void EliminarArticulo(int tipo);
void PrestarArticulo(int tipo);
void DevolverArticulo(int tipo);
void BuscarArticulo(int tipo);



////////////////////////////////////////////////////////////////////////////////////////
//  DECLARACION DE CLASES
////////////////////////////////////////////////////////////////////////////////////////

// Clase base para C_Libro, C_Revista, etc.
// Contiene atributos comunes a todos los objetos de la biblioteca.
// Define las funciones para Prestar o Devolver un art°culo
class C_Articulo {

    public:
        C_Articulo();

    private:

    BOOL estado; // prestado o no
    char titulo[MAX_STR]; // cadena con el titulo del art°culo (libro, revista, etc.)
    char tema[MAX_STR]; // cadena con el tema del art°culo

    protected:

    int id; // tipo de objeto: LIBRO, REVISTA, etc.

    public:

    // funciones "Set":
    void EstablecerTitulo(char *s) { strcpy(titulo, s); };
    void EstablecerTema(char *s) { strcpy(tema, s); };
    // funciones para comparar la correspondencia de una cadena con un atributo:
    BOOL CompararTitulo(char *s) { return (strcmp(s, titulo))? FALSE : TRUE; };
    BOOL CompararTema(char *s) { return (strcmp(s, tema))? FALSE : TRUE; };

    BOOL Prestado() { return estado; }; // esta prestado?
    int Tipo() { return id; }; // retornar tipo de objeto
    void Prestar(); // cambiar el estado del objeto = TRUE, prestado
    void Devolver(); // cambiar el estado a FALSE
    virtual void Consultar();  // imprime los datos en pantalla
};


// Define los atributos propios de un libro.
// Se hereda de C_Articulo.
class C_Libro : public C_Articulo {

    private:

    char autor[MAX_STR]; // cadena con el nombre del autor del libro
    char editorial[MAX_STR]; // cadena con la editorial del libro
    char edicion[MAX_STR]; // cadena con la edici¢n del libro (primera, II, III, etc)

    public:

    C_Libro();
    // funciones "set":
    void EstablecerAutor(char *s) { strcpy(autor, s); };
    void EstablecerEditorial(char *s) { strcpy(editorial, s); };
    void EstablecerEdicion(char *s) { strcpy(edicion, s); };
    // funci¢n para comparar la correspondencia de una cadena con un atributo:

    void Consultar(); // imprime los datos del objeto en pantalla
};


class C_Revista : public C_Articulo {

    private:

    char editorial[MAX_STR];
    char edicion[MAX_STR];
    char fecha[MAX_STR]; // de publicaci¢n

    public:

    C_Revista();
    // funciones "set":
    void EstablecerEditorial(char *s) { strcpy(editorial, s); };
    void EstablecerEdicion(char *s) { strcpy(edicion, s); };
    void EstablecerFecha(char *s) { strcpy(fecha, s); };

    void Consultar();
};


class C_Video : public C_Articulo {

    private:

    char duracion[MAX_STR];
    char formato[MAX_STR]; // VHS, BETA, etc

    public:
    C_Video();
    // funciones "set":
    void EstablecerDuracion(char *s) { strcpy(duracion, s); };
    void EstablecerFormato(char *s) { strcpy(formato, s); };

    void Consultar();
};


class C_Cdrom : public C_Articulo {

    private:

    char editores[MAX_STR];

    public:
    C_Cdrom();
    // funciones "set":
    void EstablecerEditores(char *s) { strcpy(editores, s); };

    void Consultar();
};



////////////////////////////////////////////////////////////////////////////////////////
//  DECLARACION DE VARIABLES GLOBALES
////////////////////////////////////////////////////////////////////////////////////////

// Se crea un array de punteros a C_Articulo, en el cual se instanciar†n nuevos objetos
// del tipo espec°fico (C_Libro, C_Revista, etc.) para luego llamar a las funciones
// polim¢rficamente. Por ejemplo, para crear un nuevo libro se escribe:
// art°culo[i] = new C_Libro, esto crea un objeto del tipo C_Libro en la posici¢n i
// del array de punteros.
C_Articulo *articulo[MAX_ARTICULOS]; // array con punteros a objetos



////////////////////////////////////////////////////////////////////////////////////////
//  main()
//  Funci¢n principal del programa.
//  Maneja el men£.
////////////////////////////////////////////////////////////////////////////////////////
main()
{
    char *principal[] = {"LIBROS",   // array de cadenas con las opciones del men£
                         "REVISTAS",
                         "VIDEOS",
                         "CD-ROM",
                         "SALIR"};

    char *sub_menu[] = {"A§adir",    // array con las opciones de los submenus
                        "Eliminar",
                        "Prestar",
                        "Devolver",
                        "Buscar",
                        "Men£ principal"};

    char *titulo[] = {"M E N U   L I B R O S",    // t°tulos para los submenus
                      "M E N U   R E V I S T A S",
                      "M E N U   V I D E O S",
                      "M E N U   C D - R O M" };

    int opcion; // selecci¢n del usuario

    for(;;) { // men£ principal, se interrumpe con "break"
        // obtener la opci¢n del men£ introducida por el usuario
        opcion = menu("M E N U   P R I N C I P A L", principal, 5);

        if (opcion == 5) break; // si se eligi¢ SALIR interrumpir for(;;)

        int tipo = opcion -1; // encontrar el id del articulo (tipo)

        do { // submen£
            opcion = menu(titulo[tipo], sub_menu, 6); // obtener entrada

            switch(opcion) { // verificar cada caso
                case 1: // 1 - A§adir
                    AgregarArticulo(tipo);
                break;

                case 2: // 2 - Eliminar
                    EliminarArticulo(tipo);
                break;

                case 3: // 3 - Prestar
                    PrestarArticulo(tipo);
                break;

                case 4: // 4 - Devolver
		    DevolverArticulo(tipo);
                break;

                case 5: // 5 - Buscar
                    BuscarArticulo(tipo);
                break;
            }
        } while(opcion != 6); // volver al men£ principal
    }

    // liberar la memoria usada por los objetos
    for(int i = 0; i < MAX_ARTICULOS; i++) liberar_mem(articulo[i]);

    return 0;
}



////////////////////////////////////////////////////////////////////////////////////////
//  AgregarArticulo()
//  Agrega un art°culo del tipo especificado al array.
//  Esta funci¢n busca el primer puntero vacio (NULL) en el array de objetos y
//  lo direcciona a uno nuevo mediante "new" llamando al constructor polimorficamente
//  para cargar los atributos del objeto.
////////////////////////////////////////////////////////////////////////////////////////
void AgregarArticulo(int tipo)
{
    int i; // indice dentro del array del libro a insertar

    for(i = 0; i < MAX_ARTICULOS; i++) // buscar posici¢n vac°a en el array
        if(articulo[i] == NULL) break; // encontro uno vacio?, interrumpir la busqueda

    assert(i < MAX_ARTICULOS); // se agot¢ el espacio?

    clrscr(); // borrar la pantalla
    printf("\n"); // salto de l°nea

    switch(tipo) {
        case LIBRO:
            centrar("A • A D I R   L I B R O");
	    printf("\n\n\n");
	    articulo[i] = new C_Libro; // asignar un libro nuevo
	break;

	case REVISTA:
            centrar("A • A D I R   R E V I S T A");
            printf("\n\n\n");
            articulo[i] = new C_Revista; // asignar una revista nueva
        break;

	case VIDEO:
            centrar("A • A D I R   V I D E O");
            printf("\n\n\n");
            articulo[i] = new C_Video; // asignar un video nuevo
        break;

	case CDROM:
            centrar("A • A D I R   C D - R O M");
            printf("\n\n\n");
            articulo[i] = new C_Cdrom; // asignar un CD nuevo
        break;
    }
    assert(articulo[i]); // no debe ser un puntero nulo
}



////////////////////////////////////////////////////////////////////////////////////////
//  EliminarArticulo()
//  Elimina un art°culo del tipo dado.
//  Esta funci¢n solicita el t°tulo del art°culo y lo elimina al encontrar una
//  correspondencia, se libera la memoria y se asigna el valor NULL al puntero.
////////////////////////////////////////////////////////////////////////////////////////
void EliminarArticulo(int tipo)
{
    clrscr(); // borrar la pantalla
    printf("\n");

    char s[MAX_STR]; // cadena con la introducci¢n del usuario
    int i = 0; // indice del arreglo correspondiente al articulo solicitado
    // array de cadenas con cada t°tulo
    char *titulo[] = {"E L I M I N A R   L I B R O",
                      "E L I M I N A R   R E V I S T A",
                      "E L I M I N A R   V I D E O",
                      "E L I M I N A R   C D - R O M" };

    centrar(titulo[tipo]); // imprimir titulo correspondiente
    printf("\n\n\n");

    printf("\tT°tulo a eliminar: ");
    scanf("%s", s); // obtener cadena a buscar

    i = BuscarTitulo(s, tipo); // buscar art°culo correspondiente

    if(i == MAX_ARTICULOS) { // no hay correspondencias
        printf("\n\a NO SE ENCONTRARON CORRESPONDENCIAS.");
    }
    else { // articulo encontrado, proceder a eliminarlo
        articulo[i]->Consultar();
        printf("\n ®Desea eliminar este art°culo? (S/N)\n");
        int borrar = getch();
        if(tolower(borrar) == 's') { // si esta seguro de eliminar
            if(articulo[i]->Prestado()) // si estaba prestado, mostrar advertencia
                printf("\n El art°culo se encontraba prestado !");

            liberar_mem(articulo[i]); // liberar la memoria usada
            articulo[i] = NULL; // ajustar puntero a NULL (ya no apunta a nada v†lido)
            printf("\n Art°culo eliminado de la base de datos.");
        }
    }
    presionar_una_tecla(); // pausa
}



////////////////////////////////////////////////////////////////////////////////////////
//  PrestarArticulo()
//  Cambia la variable estado llamando a la funcion Prestar.
////////////////////////////////////////////////////////////////////////////////////////
void PrestarArticulo(int tipo)
{
    // array de cadenas con cada t°tulo
    char *titulo[] = {"P R E S T A R   L I B R O",
                      "P R E S T A R   R E V I S T A",
                      "P R E S T A R   V I D E O",
                      "P R E S T A R   C D - R O M" };

    clrscr(); // borrar la pantalla
    printf("\n");
    centrar(titulo[tipo]); // imprimir el t°tulo correspondiente
    printf("\n\n\n");

    char s[MAX_STR]; // cadena con la introducci¢n del usuario
    int i; // indice del array

    printf("\tT°tulo: "); // solicitud
    scanf("%s", s);

    i = BuscarTitulo(s, tipo); // buscar indice

    if(i == MAX_ARTICULOS) { // no hay correspondencias
        printf("\n\a NO SE ENCONTRARON CORRESPONDENCIAS.");
        presionar_una_tecla(); // pausa
    }
    else articulo[i]->Prestar(); // llamar a funci¢n miembro de C_Articulo
}



////////////////////////////////////////////////////////////////////////////////////////
//  DevolverArticulo()
//  Cambia la variable estado, llamando a la funcion miembro Devolver de C_Articulo.
////////////////////////////////////////////////////////////////////////////////////////
void DevolverArticulo(int tipo)
{
    // array de cadenas con cada t°tulo
    char *titulo[] = {"D E V O L V E R   L I B R O",
                      "D E V O L V E R   R E V I S T A",
                      "D E V O L V E R   V I D E O",
                      "D E V O L V E R   C D - R O M" };

    clrscr(); // borrar la pantalla
    printf("\n");
    centrar(titulo[tipo]); // imprimir t°tulo correspondiente
    printf("\n\n\n");

    char s[MAX_STR]; // introducci¢n del usuario
    int i;

    printf("\tT°tulo: "); // solicitud
    scanf("%s", s);


    i = BuscarTitulo(s, tipo);

    if(i == MAX_ARTICULOS) { // no hay correspondencias
        printf("\n\a NO SE ENCONTRARON CORRESPONDENCIAS.");
        presionar_una_tecla(); // pausa
    }
    else articulo[i]->Devolver(); // llamar a funci¢n miembro de C_Articulo
}



////////////////////////////////////////////////////////////////////////////////////////
//  ConsultarArticulo()
//  Muestra datos del art°culo.
//  Se visualiza un men£ con las opciones de busqueda, luego se procede a buscar el
//  objeto, y se presentan sus datos llamando a la funci¢n Consultar.
////////////////////////////////////////////////////////////////////////////////////////
void BuscarArticulo(int tipo)
{
    int opcion; // opci¢n de busqueda (por t°tulo o por tema)
    char s[MAX_STR]; // t°tulo a buscar
    BOOL encontrado = FALSE; // se logro encontrar el art°culo?
    int i;

    char *titulo[] = {"B U S C A R   L I B R O",
                      "B U S C A R   R E V I S T A",
                      "B U S C A R   V I D E O",
                      "B U S C A R   C D - R O M" };


    char *opciones[] = {"Por t°tulo", "Por tema"}; // opciones de busqueda
    opcion = menu(titulo[tipo], opciones, 2); // mostrar submen£

    if(opcion == 1) { // buscar por t°tulo?
        printf("\tT°tulo: ");
    }
    else if(opcion == 2) { // buscar por tema?
        printf("\tTema: ");
    }

    scanf("%s", s); // introducci¢n del usuario

    for(i = 0; i < MAX_ARTICULOS; i++) { // buscar en cada registro
        if(articulo[i] && articulo[i]->Tipo() == tipo) { // si es un registro v†lido
            // verificar opci¢n de busqueda (por t°tulo o por tema)
            if((opcion == 1 && articulo[i]->CompararTitulo(s)) || // por t°tulo
               (opcion == 2 && articulo[i]->CompararTema(s))) {   // por tema

                encontrado = TRUE; // se pudo encontrar
                printf("\n");
                printf("----------------------------------------------------------------");
                articulo[i]->Consultar(); // imprimir los datos del objeto (polimorfico)
                presionar_una_tecla(); // pausa
            }
        }
    }

    if(!encontrado) { // no hay correspondencias
        printf("\n\a NO SE ENCONTRARON CORRESPONDENCIAS.");
	presionar_una_tecla(); // pausar ejecuci¢n del programa
    }
}



////////////////////////////////////////////////////////////////////////////////////////
//  BuscarTitulo()
//  Busca el art°culo con el titulo y el tipo dado.
//  Retorna el indice correspondiente al objeto buscado, o MAX_ARTICULOS si no lo
//  encuentra.
////////////////////////////////////////////////////////////////////////////////////////
int BuscarTitulo(char *s, const int tipo)
{
    int i; // indice del array de objetos

    for(i = 0; i < MAX_ARTICULOS; i++) { // buscar en cada registro
    // verificar si el objeto no es NULL y comparar la cadena con el t°tulo
        if(articulo[i] && articulo[i]->CompararTitulo(s)) { // encontr¢ el objeto?
            if(articulo[i]->Tipo() == tipo) break;; // interrumpir la busqueda
	 }
    }
    return i; // devolver el indice
}



////////////////////////////////////////////////////////////////////////////////////////
//  C_Articulo::C_Articulo()
//  Constructor.
//  Inicializa desde el teclado los atributos del objeto.
////////////////////////////////////////////////////////////////////////////////////////
C_Articulo::C_Articulo()
{
    char s[MAX_STR];

    printf("\tT°tulo: "); // solicitar t°tulo
    scanf("%s", s); // extraer cadena desde el teclado
    EstablecerTitulo(s); // asignar la cadena al atributo correspondiente

    printf("\n\tTema: ");
    scanf("%s", s);
    EstablecerTema(s);

    estado = FALSE; // al ser creado no se encuentra prestado
}



////////////////////////////////////////////////////////////////////////////////////////
//  Articulo::Consultar()
//  Imprime los datos del articulo.
////////////////////////////////////////////////////////////////////////////////////////
void C_Articulo::Consultar()
{
    // imprimir datos miembro
    printf("\n\tTITULO: %s", titulo);
    printf("\n\tTEMA: %s", tema);
    printf("\n\tESTADO: ");
    // imprimir una cadena seg£n el estado del objeto
    (Prestado()) ? printf("PRESTADO") : printf("LIBRE");
}



////////////////////////////////////////////////////////////////////////////////////////
//  Articulo::Prestar()
//  Cambia a TRUE el estado si el objeto no se ecuentra prestado (si estado != TRUE).
////////////////////////////////////////////////////////////////////////////////////////
void C_Articulo::Prestar()
{
    if(!Prestado()) { // esta prestado?
        estado = TRUE; // prestar
        printf("\n Prestamo realizado con Çxito."); // mostrar confirmaci¢n
    }
    else { // ya est† prestado
        printf("\n\a EL ARTICULO NO SE ENCUENTRA DISPONIBLE.");
    }
    presionar_una_tecla(); // pausa
}



////////////////////////////////////////////////////////////////////////////////////////
//  Articulo::Devolver()
//  Cambia a FALSE el atributo estado.
////////////////////////////////////////////////////////////////////////////////////////
void C_Articulo::Devolver()
{
    if(Prestado()) { // esta prestado?
        estado = FALSE; // devolver
        printf("\n Devoluci¢n realizada con Çxito.");
    }
    else { // no se puede devolver si no estaba prestado
        printf("\n\a EL ARTICULO NO SE ENCONTRABA PRESTADO.");
    }
    presionar_una_tecla(); // pausa de ejecuci¢n
}



////////////////////////////////////////////////////////////////////////////////////////
//  C_Libro::C_Libro()
//  Constructor.
//  Carga desde el teclado los atributos del objeto.
//  Establece el identificador id de la clase base a LIBRO.
////////////////////////////////////////////////////////////////////////////////////////
C_Libro::C_Libro()
{
    char s[MAX_STR]; // cadena con la introducci¢n del usuario

    printf("\n\tAutor: "); // solicitud
    scanf("%s", s);        // entrada del usuario
    EstablecerAutor(s);    // inicializar atributo

    printf("\n\tEditorial: ");
    scanf("%s", s);
    EstablecerEditorial(s);

    printf("\n\tEdici¢n: ");
    scanf("%s", s);
    EstablecerEdicion(s);

    id = LIBRO; // ajustar identificador (tipo de objeto)
}



////////////////////////////////////////////////////////////////////////////////////////
//  Libro::Consultar()
//  Imprime los datos del libro.
////////////////////////////////////////////////////////////////////////////////////////
void C_Libro::Consultar()
{
    C_Articulo::Consultar(); // clase base (imprimir titulo, tema)
    // imprimir datos miembro
    printf("\n\tAutor: %s", autor);
    printf("\n\tEditorial: %s", editorial);
    printf("\n\tEdici¢n: %s", edicion);
}



////////////////////////////////////////////////////////////////////////////////////////
//  C_Revista::C_Revista()
//  Constructor.
//  Carga desde el teclado los atributos del objeto.
//  Establece el identificador id de la clase base a REVISTA.
////////////////////////////////////////////////////////////////////////////////////////
C_Revista::C_Revista()
{
    char s[MAX_STR]; // cadena con la introducci¢n del usuario

    printf("\n\tEditorial: "); // solicitud
    scanf("%s", s);            // entrada del usuario
    EstablecerEditorial(s);    // inicializar miembro

    printf("\n\tEdicion: ");
    scanf("%s", s);
    EstablecerEdicion(s);

    printf("\n\tFecha de publicaci¢n: ");
    scanf("%s", s);
    EstablecerFecha(s);

    id = REVISTA; // ajustar identificador (tipo de objeto)
}



////////////////////////////////////////////////////////////////////////////////////////
//  C_Revista::Consultar()
//  Imprime los datos de la revista.
////////////////////////////////////////////////////////////////////////////////////////
void C_Revista::Consultar()
{
    C_Articulo::Consultar(); // clase base (imprimir titulo, tema)
    // imprimir datos miembro
    printf("\n\tEditorial: %s", editorial);
    printf("\n\tEdici¢n: %s", edicion);
    printf("\n\tFecha de publicaci¢n: %s", fecha);
}



////////////////////////////////////////////////////////////////////////////////////////
//  C_Video::C_Video()
//  Constructor.
//  Carga desde el teclado los atributos del objeto.
//  Establece el identificador id de la clase base a VIDEO.
////////////////////////////////////////////////////////////////////////////////////////
C_Video::C_Video()
{
    char s[MAX_STR]; // cadena con la introducci¢n del usuario

    printf("\n\tDuraci¢n: "); // solicitud
    scanf("%s", s);           // entrada del usuario
    EstablecerDuracion(s);    // inicializar dato

    printf("\n\tFormato: ");
    scanf("%s", s);
    EstablecerFormato(s);

    id = VIDEO; // ajustar identificador (tipo de objeto)
}



////////////////////////////////////////////////////////////////////////////////////////
//  C_Video::Consultar()
//  Imprime los datos del video.
////////////////////////////////////////////////////////////////////////////////////////
void C_Video::Consultar()
{
    C_Articulo::Consultar(); // clase base (imprimir titulo, tema)
    // imprimir datos miembro
    printf("\n\tDuraci¢n: %s", duracion);
    printf("\n\tFormato: %s", formato);
}



////////////////////////////////////////////////////////////////////////////////////////
//  C_Cdrom::C_Cdrom()
//  Constructor.
//  Carga desde el teclado los atributos del objeto.
//  Establece el identificador id de la clase base a CDROM.
////////////////////////////////////////////////////////////////////////////////////////
C_Cdrom::C_Cdrom()
{
    char s[MAX_STR]; // cadena con la introducci¢n del usuario

    printf("\n\tEditores: "); // solicitud
    scanf("%s", s);           // entrada del usuario
    EstablecerEditores(s);    // inicializar dato

    id = CDROM; // ajustar identificador (tipo de objeto)
}



////////////////////////////////////////////////////////////////////////////////////////
//  C_Cdrom::Consultar()
//  Imprime los datos del CD-ROM.
////////////////////////////////////////////////////////////////////////////////////////
void C_Cdrom::Consultar()
{
    C_Articulo::Consultar(); // clase base (imprimir titulo, tema)
    // imprimir datos miembro
    printf("\n\tEditores: %s", editores);
}



////////////////////////////////////////////////////////////////////////////////////////
//  menu()
//  Visualiza en la pantalla un men£ con los parametros dados y devuelve la selecci¢n
//  del usuario.
//  - titulo: cadena con el t°tulo del men£
//  - texto_opcion: array de cadenas con cada opci¢n
//  - num_opciones: n£mero de opciones a visualizar
//  Ejecuta un bucle hasta que se introdusca una opci¢n v†lida.
//  Devuelve la opci¢n introducida por el usuario.
////////////////////////////////////////////////////////////////////////////////////////
int menu(const char *titulo, char *texto_opcion[], const int num_opciones)
{
    int opcion; // introduci¢n del usuario
    int max = 0; // longitud del la cadena m†s larga a imprimir en las opciones

    // encontrar la longitud de la cadena m†s larga
    for(int i = 0; i < num_opciones; i++) {
        int len = strlen(texto_opcion[i]);
        if(len > max) max = len;
    }

    max += 4; // sumar longitud de la cadena "1 - ", "2 - "...

    do { // ejecutar hasta que se introdusca una opci¢n v†lida
        clrscr(); // limpiar pantalla

        printf("\n");
        centrar(titulo); // imprimir t°tulo del men£
        printf("\n\n\n");

        // imprimir opciones
        for(int i = 0; i < num_opciones; i++) { // por cada opci¢n
            char texto[80]; // texto de la opci¢n a presentar
            int l; // longitud de texto
            // convertir a cadena con el n£mero de la opci¢n ("1", "2"...)
            itoa(i + 1, texto, 10);

            strcat(texto, " - "); // agregar. texto: "1 - ", "2 - "...etc.
            strcat(texto, texto_opcion[i]); // a§adir texto de la opci¢n (par†metro)

            l = strlen(texto); // calcular longitud
            // a§adir espacios si es necesario para alinear a la izquierda
            if(l < max) {
                for(int d = 0; d < max - l; d++) strcat(texto, " ");
            }

            centrar(texto); // imprimir opci¢n
            printf("\n");
        }
        centrar("    OPCI‡N: "); // solicitud
        scanf("%d", &opcion);    // introducci¢n del usuario

    } while(opcion > num_opciones || opcion < 1); // mientras sea v†lida la opci¢n

    return opcion; // retornar opci¢n introducida
}



////////////////////////////////////////////////////////////////////////////////////////
//  centrar()
//  Imprime *texto centrado en la pantalla.
////////////////////////////////////////////////////////////////////////////////////////
void centrar(const char *texto)
{
    int posicion; // inicial del texto a centrar

    posicion = (80 - strlen(texto)) / 2; // calcular posicion inicial del texto

    printf("\n");
    for(int i = 0; i < posicion; i++) printf(" "); // insertar espacios

    printf("%s", texto); // imprimir texto
}



////////////////////////////////////////////////////////////////////////////////////////
//  presionar_una_tecla()
//  Realiza una pausa en el programa.
////////////////////////////////////////////////////////////////////////////////////////
int presionar_una_tecla()
{
    printf("\n (Presione una tecla para continuar)\n");
    return getch();
}
