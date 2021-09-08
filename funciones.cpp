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

// esta funcion despliega toda la informacion de los departamentos
void Listar_Departamentos(list<divipola> DiviLista)
{

    list<divipola>::iterator iter;
    vector<string> departamentos;

    cout << endl;

    for (iter = DiviLista.begin(); iter != DiviLista.end(); ++iter)
    {
        if (find(departamentos.begin(), departamentos.end(), iter->cod_dept) == departamentos.end())
        {
            cout << '\t' << iter->cod_dept << '\t' << iter->nom_dept << endl;
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
    vector<string> municipios;

    cout << endl;

    for (iter = DiviLista.begin(); iter != DiviLista.end(); ++iter)
    {
        //cout << "iter->cod_dept" << iter->cod_dept << "codigodepto" << codigodepto << endl;
        if ((iter->cod_dept == codigodepto) && (find(municipios.begin(), municipios.end(), iter->cod_mpio) == municipios.end()))
        {
            cout << '\t' << iter->cod_mpio << '\t' << iter->nom_mpio << endl;
            municipios.push_back(iter->cod_mpio);
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
    vector<string> poblaciones;
    cout << endl;

    for (iter = DiviLista.begin(); iter != DiviLista.end(); ++iter)
    {
        if ((iter->cod_mpio == codigoMunicipio) && (find(poblaciones.begin(), poblaciones.end(), iter->cod_cpob) == poblaciones.end()))
        {
            cout << '\t' << iter->cod_cpob << '\t' << iter->nom_cpob << endl;
            poblaciones.push_back(iter->cod_cpob);
        }
    }
    cout << endl;
}

/*
Funcion para mostrar la informacion del departartamento cargado en la divipola
*/
void Informacion(string codigodepto, list<divipola> DiviLista)
{

    list<divipola>::iterator iter;
    vector<string> municipios;
    vector<string> poblaciones;
    string nombre;

    cout << endl;

    for (iter = DiviLista.begin(); iter != DiviLista.end(); ++iter)
    {
        if ((iter->cod_dept == codigodepto) && (find(municipios.begin(), municipios.end(), iter->cod_mpio) == municipios.end()))
        {
            municipios.push_back(iter->cod_mpio);
        }
        if ((iter->cod_dept == codigodepto) && find(poblaciones.begin(), poblaciones.end(), iter->cod_cpob) == poblaciones.end())
        {
            poblaciones.push_back(iter->cod_cpob);
            nombre = iter->nom_dept;
        }
    }

    cout << "\tEl departamento " << nombre << " esta conformado por " << municipios.size() << " municipios y " << poblaciones.size() << " centros poblados " << endl;

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
    if (menuayuda == "total")
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