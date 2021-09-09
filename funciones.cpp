#include <iostream>
#include <wchar.h>
#include <locale.h>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <list>
#include "funciones.h"
#include <vector>
using namespace std;

bool Existencia(string codigo, list<divipola> DiviLista)
{

    list<divipola>::iterator iter;
    for (iter = DiviLista.begin(); iter != DiviLista.end(); ++iter)
    {
        if (iter->cod_dept == codigo)
        {
            return true;
        }
        else if (iter->cod_mpio == codigo)
        {
            return true;
        }
    }
    return false;
}

void Cargar_divipola(list<divipola> &DiviLista)
{
    string linea;
    fstream fout;
    char delimitador = ',';
    fout.open("DIVIPOLA_CentrosPoblados.csv", ios::in); // se lee el archivo .csv
    getline(fout, linea);                               // se omite la primera linea del archivo que no contiene nada importante
    setlocale(LC_CTYPE, "");
    while (getline(fout, linea))
    {
        divipola nodo;
        stringstream stream(linea); // convertir la cadena a un stream
        getline(stream, nodo.cod_dept, delimitador);

        getline(stream, nodo.nom_dept, delimitador);

        getline(stream, nodo.cod_mpio, delimitador);

        getline(stream, nodo.nom_mpio, delimitador);

        getline(stream, nodo.cod_cpob, delimitador);

        getline(stream, nodo.nom_cpob, delimitador);

        getline(stream, nodo.tipo, delimitador);

        getline(stream, nodo.latitud, delimitador);

        getline(stream, nodo.longitud, delimitador);

        DiviLista.push_back(nodo);
    }
    fout.close();
}

void cargar_SC(list<SistemaCiudades> &SClista)
{
    string linea;
    fstream fout2;
    char delimitador = ',';
    fout2.open("Datos-ICM-2019.csv", ios::in); // se lee el archivo .csv
    setlocale(LC_ALL, "spanish");
    getline(fout2, linea); // se omite la primera linea del archivo que no contiene nada importante
    while (getline(fout2, linea))

    {
        SistemaCiudades nodo;

        stringstream stream(linea); // convertir la cadena a un stream
        getline(stream, nodo.aglomeracion, delimitador);

        getline(stream, nodo.FuncionCiudades, delimitador);

        getline(stream, nodo.nom_dept, delimitador);

        getline(stream, nodo.nom_mpio, delimitador);

        getline(stream, nodo.divipola, delimitador);
        SClista.push_back(nodo);
    }
    fout2.close();
}

/*
Funcion para mostrar la informacion del departartamento cargado en la divipola
*/
vector<string> Informacion(string codigodepto, list<divipola> DiviLista)
{

    list<divipola>::iterator iter;
    vector<string> municipios;
    vector<string> poblaciones;
    vector<string> datos = {"", "", ""};

    for (iter = DiviLista.begin(); iter != DiviLista.end(); ++iter)
    {
        if ((iter->cod_dept == codigodepto) && (find(municipios.begin(), municipios.end(), iter->cod_mpio) == municipios.end()))
        {
            municipios.push_back(iter->cod_mpio);
        }
        if ((iter->cod_dept == codigodepto) && find(poblaciones.begin(), poblaciones.end(), iter->cod_cpob) == poblaciones.end())
        {
            poblaciones.push_back(iter->cod_cpob);
            datos[2] = iter->nom_dept;
        }
    }

    datos[0] = to_string(municipios.size());
    datos[1] = to_string(poblaciones.size());

    return datos;
}

// esta funcion despliega toda la informacion de los departamentos
void Listar_Departamentos(list<divipola> DiviLista)
{

    list<divipola>::iterator iter;
    vector<string> departamentos;
    vector<string> datos;

    cout << endl;
    cout << "\tCODIGO" << '\t' << "NOMBRE"
         << "\t\t\t\t\t\t\t\t"
         << "NO. MUNICIPIOS"
         << "\t\t"
         << "NO. POBLACIONES" << endl;
    cout << endl;

    for (iter = DiviLista.begin(); iter != DiviLista.end(); ++iter)
    {
        if (find(departamentos.begin(), departamentos.end(), iter->cod_dept) == departamentos.end())
        {
            datos = Informacion(iter->cod_dept, DiviLista);
            cout << '\t' << iter->cod_dept << '\t' << iter->nom_dept << "\t\t\t\t\t\t\t\t" << datos[0] << "\t\t" << datos[1] << endl;
            departamentos.push_back(iter->cod_dept);
        }
    }
    cout << endl;
}

/*
Esta funcion lista los municipios por el codigo del departamento 
*/
void Listar_Municipios(string codigodepto, list<divipola> DiviLista)
{

    list<divipola>::iterator iter;

    cout << endl;
    cout << "\tCODIGO" << '\t' << "NOMBRE"
         << "\t\t\t"
         << "LATITUD"
         << "\t\t\t"
         << "LONGITUD" << endl;
    cout << endl;

    for (iter = DiviLista.begin(); iter != DiviLista.end(); ++iter)
    {
        if ((iter->cod_dept == codigodepto) && iter->tipo == "CM")
        {
            cout << '\t' << iter->cod_mpio << '\t' << iter->nom_mpio << "\t\t\t" << iter->latitud << "\t\t" << iter->longitud << endl;
        }
    }
    cout << endl;
}

/*
Funcion para listar las poblaciones por el codigo del municipio 
*/
void Listar_Poblaciones(string codigoMunicipio, list<divipola> DiviLista)
{

    list<divipola>::iterator iter;

    cout << endl;
    cout << "\tCODIGO"
         << "\t\t"
         << "NOMBRE"
         << "\t\t\t\t"
         << "LATITUD"
         << "\t\t\t\t"
         << "LONGITUD" << endl;
    cout << endl;

    for (iter = DiviLista.begin(); iter != DiviLista.end(); ++iter)
    {
        if ((iter->cod_mpio == codigoMunicipio) && iter->tipo == "CP")
        {
            cout << '\t' << iter->cod_cpob << '\t' << iter->nom_cpob << "\t\t\t" << iter->latitud << "\t\t" << iter->longitud << endl;
        }
    }
    cout << endl;
}

/*
funcion para determinar si un municipio esta en el sistema de ciudades usando la divipola para poder 
idnetificar a los municipios en la divipola y en el sistema de ciudades
*/
void estaEnSistema(string codigoMunicipio, list<SistemaCiudades> SClista, list<divipola> DiviLista)
{

    bool encontroSCMU = false;
    bool encontroDPMU = false;
    int cod_mpioDi = 0, cod_mpioSC = 0;
    if (SClista.empty())
    {
        cout << "La lista de sistema de ciudades esta vacia primero cargala" << endl;
    }
    if (!SClista.empty())
    {
        list<divipola>::iterator iter;
        list<SistemaCiudades>::iterator otr;
        for (iter = DiviLista.begin(); iter != DiviLista.end(); ++iter)
        {
            if (iter->cod_mpio == codigoMunicipio)
            {
                for (otr = SClista.begin(); otr != SClista.end(); otr++)
                {
                    if (otr->divipola == iter->cod_mpio)
                    {
                        encontroSCMU = true;
                    }
                }
                encontroDPMU = true;
            }
        }
    }
    if (encontroDPMU == true && encontroSCMU == true)
    {
        cout << "El municipio existe y hace parte del SC" << endl;
    }
    if (encontroDPMU == true && encontroSCMU == false)
    {
        cout << "El municipio existe y no hace parte del SC" << endl;
    }
    if (encontroDPMU == false)
    {
        cout << "El municipio no existe" << endl;
    }
}

//se desplega el menu de ayuda necesario por si el cliente no responde al comando
void ayuda(string menuayuda, bool &comandoEncontrado)
{
    if (menuayuda == "carga_divipola")
    {
        cout << "carga_divipola DIVIPOLA_CentrosPoblados.csv           " << '\t' << "Carga en una o mas estructuras de datos en memoria el contenido del archivo identificado por nombre_archivo." << endl;
        comandoEncontrado = true;
    }
    cout << endl;
    if (menuayuda == "listar_departamentos")
    {
        cout << "listar_departamentos                    " << '\t' << "Imprime en n lineas (una para cada departamento) la informacion basica del departamento que se cargo de la Divipola." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "listar_municipios")
    {
        cout << "LISTAR_MUNICIPIOS codigo_depto          " << '\t' << "Imprime en n lineas (una para cada municipio) la informacion basica del departamento que se cargo de la Divipola." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "listar_poblaciones")
    {
        cout << "LISTAR_POBLACIONES codigo_municipio     " << '\t' << "Imprime en n lineas (una para cada municipio) la informacion basica del departamento que se cargo de la Divipola." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "info_sumaria")
    {
        cout << "INFO_SUMARIA codigo_depto               " << '\t' << "Imprime en una lineas la informacion basica del nombre del departamento que corresponde al codigo dado como parametro junto con la cantidad de municipios y centros poblados que lo conforman" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "carga_SC")
    {
        cout << "CARGA_SC nombre_archivo                 " << '\t' << "Carga en una o mas estructuras de datos en memoria el contenido del archivo identificado por nombre_archivo con la "
             << "\n"
             << "informacion basica para representar el sistema de ciudades." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "esta_en_sistema")
    {
        cout << "ESTA_EN_SISTEMA codigo_municipio        " << '\t' << "Determina si un municipio, con codigo dado por el usuario, existe dentro de las municipios definidos en el Sistema de Ciudades y cargados desde el archivo correspondiente." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "general")
    {
        cout << "Lista de todos los comandos:" << endl;
        cout << endl;
        cout << endl;
        cout << "carga_divipola DIVIPOLA_CentrosPoblados.csv           " << '\t' << "Carga en una o mas estructuras de datos en memoria el contenido del archivo identificado por nombre_archivo." << endl;
        cout << endl;
        cout << "listar_departamentos                    " << '\t' << "Imprime en n lineas (una para cada departamento) la informacion basica del departamento que se cargo de la Divipola." << endl;
        cout << endl;
        cout << "LISTAR_MUNICIPIOS codigo_depto          " << '\t' << "Imprime en n lineas (una para cada municipio) la informacion basica del departamento que se cargo de la Divipola." << endl;
        cout << endl;
        cout << "LISTAR_POBLACIONES codigo_municipio     " << '\t' << "Imprime en n lineas (una para cada municipio) la informacion basica del departamento que se cargo de la Divipola." << endl;
        cout << endl;
        cout << "INFO_SUMARIA codigo_depto               " << '\t' << "Imprime en una lineas la informacion basica del nombre del departamento que corresponde al codigo dado como parametro junto con la cantidad de municipios y centros poblados que lo conforman" << endl;
        cout << endl;
        cout << "CARGA_SC nombre_archivo                 " << '\t' << "Carga en una o mas estructuras de datos en memoria el contenido del archivo identificado por nombre_archivo con la "
             << "\n"
             << '\t'
             << "informacion basica para representar el sistema de ciudades." << endl;
        cout << endl;
        cout << "ESTA_EN_SISTEMA codigo_municipio        " << '\t' << "Determina si un municipio, con codigo dado por el usuario, existe dentro de las municipios definidos en el Sistema de Ciudades y cargados desde el archivo correspondiente." << endl;
        cout << endl;
        cout << "SALIR                                           Termina la ejecucion de la aplicacion." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "salir")
    {
        cout << "SALIR                                           Termina la ejecucion de la aplicacion." << endl;
        comandoEncontrado = true;
    }
}