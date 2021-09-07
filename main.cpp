#include <iostream>
#include "main.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <list>
#include "lista.h"
#define Divipola "DIVIPOLA_CentrosPoblados.csv"
#define SM "Datos-ICM-2019.xlsb"
using namespace std;

int main()
{

    list<divipola> DiviLista;
    fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open(Divipola, ios::out | ios::app);

    DiviLista = llenarListaConDatos<divipola>();

    divipola nodo;
    nodo.latitud = 19999;
    nodo.cod_cpob = 1;
    nodo.cod_dept = 2;
    nodo.cod_mpio = 3;
    nodo.longitud = 4;
    nodo.nom_dept = "hola";
    nodo.nom_mpio = "como estas";
    nodo.tipo = "tm";
    DiviLista.push_back(nodo);
    for (auto itr = DiviLista.begin(); itr != DiviLista.end(); itr++)
    {
        cout << itr->nom_mpio << " ";
    }
}
