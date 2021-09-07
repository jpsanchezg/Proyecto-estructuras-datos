#include <iostream>
#include "main.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <list>
#include "lista.h"
#include <wchar.h>
#include <locale.h>
#include <sstream>
using namespace std;

int main()
{
    cout << "$";
    string comando;
    list<divipola> DiviLista;
    fstream fout;
    getline(cin, comando);
    string linea;
    setlocale(LC_ALL, "");
    if (comando == "carga_divipola DIVIPOLA_CentrosPoblados")
    {
        fout.open("DIVIPOLA_CentrosPoblados.csv", ios::in); // se lee el archivo .csv
        getline(fout, linea); // se omite la primera linea del archivo que no contiene nada importante
        while (getline(fout, linea))
        {
            divipola nodo;
            stringstream stream(linea); // convertir la cadena a un stream
            getline(stream, nodo.cod_cpob, ',');

            getline(stream, nodo.nom_dept, ',');

            getline(stream, nodo.cod_mpio, ',');

            getline(stream, nodo.nom_mpio, ',');

            getline(stream, nodo.cod_cpob, ',');

            getline(stream, nodo.nom_cpob, ',');

            getline(stream, nodo.tipo, ',');

            getline(stream, nodo.latitud, ',');

            getline(stream, nodo.longitud, ',');

            DiviLista.push_back(nodo);
        }
    }
    for (auto itr = DiviLista.begin(); itr != DiviLista.end(); itr++)
    {
        cout << itr->cod_mpio << "   " << endl;
    }
}