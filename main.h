#include <string.h>
#include <iostream>
using namespace std;

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
    string codigoIdent; // lista hacia adelante
    string codigoatrs;
    string tipo;
    string latitud;
    string longitud;
};

struct datosdept
{
    string codigo;
    string nombre;
    string codigoIdent; // lista hacia adelante
    string codigoatrs;
    string latitud;
    string longitud;
    datosdept()
    {
    }
};
struct SistemaCiudades // estructura para la lista de sistema de ciudades
{
    string aglomeracion;
    string FuncionCiudades;
    string cod_dept;
    string nom_mpio;
    string divipola;
    string anio;
    string personas;
    string hectareas;
};

struct ciudadescapitales
{
    string funcionCiudades;
    string cod_dept;
    string nom_mpio;
    string divipola;
};