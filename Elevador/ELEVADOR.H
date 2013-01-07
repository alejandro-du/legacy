///////////////////////////////////////////////////////////////////////////////////////////
//                                                                                       //
//   Archivo fuente: ELEVADOR.H                                                          //
//                                                                                       //
//   Programador: Jairo Alejandro Duarte Avenda¤o.                                       //
//                                                                                       //
//   Caracteristicas: Proporciona declaraciones de clases.                               //
//                                                                                       //
//   Funcionamiento:                                                                     //
//                                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////



#ifndef _ELEVADOR_DEF_ // Protecci¢n contra re-compilaci¢n
#define _ELEVADOR_DEF_


#include <time.h>


///////////////////////////////////////////////////////////////////////////////////////////
// Constantes para constructores por defecto                                             //
///////////////////////////////////////////////////////////////////////////////////////////

#define EDIFICIO_PISOS             20
#define EDIFICIO_DISTANCIA_PISOS   250

#define TASA_MINIMO                25
#define TASA_MAXIMO                60
#define TASA_UNA_PERSONA           3

#define ELEVADOR_CAPACIDAD         5
#define ELEVADOR_VELOCIDAD         40
#define ELEVADOR_TIEMPO_ESPERA     30
#define ELEVADOR_DESTINOS_MAX      EDIFICIO_PISOS

#define PERSONA_CAMINANDO          1


///////////////////////////////////////////////////////////////////////////////////////////
// Declaraci¢n de clases                                                                 //
///////////////////////////////////////////////////////////////////////////////////////////

class C_Reloj {
    public:

    C_Reloj();
    ~C_Reloj();

    void Actualizar(); // calcula el nuevo intervalo
    void Reset(); // empieza a contabilizar otro intervalo

    int inicial, final; // tiempos
    int intervalo;
};


class C_Tasa {
    public:

    C_Tasa(int num = TASA_UNA_PERSONA, int min = TASA_MINIMO, int max = TASA_MAXIMO);
    ~C_Tasa();

    int num_personas; // numero m ximo de personas que llegan en el intervalo
    int minimo;       // intervalo de tiempo en el que llegan m ximo "num_personas"
    int maximo;
    C_Reloj reloj;
};


class C_Persona {
    public:

    C_Persona(int dest = 1);
    ~C_Persona();

/*    void Camina();        // acercarse al elevador
    void PresionaBoton(); // oprime el bot¢n correspondiente
    void Entra();         // entra al elevador
    void Sale();
    void CambiaActitud(int nueva_actitud);*/

    int actitud; // situaci¢n en la que se encuentra (esperando, caminando, etc.)
    int destino; // piso al que desea llegar
    int posicion;
};


class C_Nodo_Personas {
    public:

    C_Nodo_Personas();

    void AgregarPersona(int destino = 1);
    void Eliminar(); // elimina la lista completa

    C_Persona *persona; // dato
    C_Nodo_Personas *sig; // siguiente
};


class C_Elevador {
    public:

    C_Elevador(int cap = ELEVADOR_CAPACIDAD,
               int v = ELEVADOR_VELOCIDAD,
               int t = ELEVADOR_TIEMPO_ESPERA,
               int max_d = ELEVADOR_DESTINOS_MAX);

    C_Elevador::~C_Elevador();

    void DeterminaDireccion();
    void SeMueve();
    void AbrePuerta();
    void CierraPuerta();
    void AnunciaLlegada();

//    private:
    int capacidad; // en n£mero de personas
    int velocidad; // en cm/s
    int tiempo_espera; // antes de cerrar la puerta autom ticamente (en s)
    int piso;
    bool direccion;
    int num_pasajeros;
    int max_destinos;
    int *destino; // contiene los destinos introducidos
    C_Persona **pasajero; // array con punteros a todos los pasajeros
};


class C_Boton {
    public:

    void Presionar();
    void Restaurar();

    bool estado;
};


class C_Puerta {
    public:

    bool estado; // abierta/cerrada
    int tiempo; // tiempo que tarda en abrirse o cerrarse

};


class C_Piso {
    public:

    C_Piso();
    ~C_Piso();

    void GenerarPersonas(int num, int max_pisos); // genera num personas, destino aleatorio

    int numero;
    int num_personas; // total de personas en el piso
    C_Nodo_Personas lista; // lista enlazada de las personas generadas
    C_Boton boton; // bot¢n para llamar al elevador
    C_Puerta puerta;
};


class C_Edificio {
    public:

    C_Edificio::C_Edificio(int p = EDIFICIO_PISOS, // n£mero de pisos
                           int d = EDIFICIO_DISTANCIA_PISOS, // distancia entre pisos
                           const C_Tasa &t = C_Tasa(TASA_UNA_PERSONA,
                                                    TASA_MINIMO,
                                                    TASA_MAXIMO),
                           C_Elevador *e = new C_Elevador); // elevador utilizado

    ~C_Edificio();
    void GenerarPersonas(); // genera personas en cada piso seg£n la tasa de llegada

//    private:
    const int pisos;
    const int distancia_pisos; // en cm
    int tasa_llegada;

    const C_Elevador *elevador; // elevador asignado
    C_Piso *piso; // almacena un array con cada piso
    C_Tasa tasa; // tasa de llegada de personas al elevador por piso
};



#endif // ndef _ELEVADOR_
