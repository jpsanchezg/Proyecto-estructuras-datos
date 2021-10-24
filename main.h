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

struct datosDiv
{
    string codigoDept;
    string codigoMun;
    string codigoPob;
    string nombre;
    string tipo;
    string latitud;
    string longitud;
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

struct Municipios_Ciudades
{
    string Nombre_Aglomeracion;
    string Nombre;
    string Divipola;
    string Personas;
    string Hectareas;
};

struct Aglomeracion
{
    string Nombre;
    Municipios_Ciudades Ciudad_Principal;
    list<Municipios_Ciudades> Ciudades_Componentes;
};
