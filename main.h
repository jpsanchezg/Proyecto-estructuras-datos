#include <string.h>
#include <iostream>
using namespace std;

struct divipola //estructura para la lista divipola
{
    string cod_dept;
    string nom_dept;
    string cod_mpio;
    string nom_mpio;
    string cod_cpob;
    string nom_cpob;
    string tipo;
    string latitud;
    string longitud;
};

struct DatosPob
{
    string codigoDept;
    string codigoMun;
    string codigoPob;
    string nombre;
    string tipo;
    string latitud;
    string longitud;
};

struct datosMun
{
    string codigo;
    string nombre;
    string codigoIdent; //lista hacia adelante
    string codigoatrs;
    string tipo;
    string latitud;
    string longitud;
    list<DatosPob> poblaciones = list<DatosPob>();
};

struct datosdept
{
    string codigo;
    string nombre;
    string codigoIdent; //lista hacia adelante
    string codigoatrs;
    string latitud;
    string longitud;
    list<datosMun> Municipios = list<datosMun>();
    datosdept()
    {
    }
};
struct SistemaCiudades //estructura para la lista de sistema de ciudades
{
    string aglomeracion;
    string FuncionCiudades;
    string nom_dept;
    string nom_mpio;
    string divipola;
};
