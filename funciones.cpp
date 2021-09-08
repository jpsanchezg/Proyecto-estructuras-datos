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

    cout << "\tEl departamento " << nombre << " est� conformado por " << municipios.size() << " municipios y " << poblaciones.size() << " centros poblados " << endl;

    cout << endl;
}
