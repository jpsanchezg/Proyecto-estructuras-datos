#include <iostream>
#include <locale.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <list>
#include "main.h"

#include <sstream>

using namespace std;

int main()
{

    setlocale(LC_CTYPE, "Spanish");

    string Entrada;
    string Comando;
    string Auxiliar;

    bool Salir = false;
    do
    {

        cout << "$";
        //cin.ignore();
        getline(cin, Entrada);
        Separar_Cadena(Entrada, Comando, Auxiliar);
        list<divipola> DiviLista; // se crea la lista 
        fstream fout; // lectura de los archivos
        string linea;
        setlocale(LC_CTYPE, "Spanish");
        char delimitador = ',';

        if (Comando == "carga_divipola DIVIPOLA_CentrosPoblados")
        {
            fout.open("DIVIPOLA_CentrosPoblados.csv", ios::in); // se lee el archivo .csv
            getline(fout, linea);                               // se omite la primera linea del archivo que no contiene nada importante
            while (getline(fout, linea))
            {
                divipola nodo;
                stringstream stream(linea); // convertir la cadena a un stream
                getline(stream, nodo.cod_cpob, delimitador);

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
        }
        else if (Comando == "listar_departamentos")
        {
        }
        else if (Comando == "listar_municipios codigo_depto")
        {
        }
        else if (Comando == "listar_poblaciones codigo_municipio")
        {
        }
        else if (Comando == "info_sumaria codigo_depto")
        {
        }
        else if (Comando == "carga_SC nombre_archivo")
        {
        }
        else if (Comando == "esta_en_sistema codigo_municipio")
        {
        }
        else if (Comando == "Ayuda")
        {
            cout << endl;
            cout << "carga_divipola nombre_archivo          ... " << '\t' << "Carga en una estructura de datos en memoria el contenido del archivo identificado por nombre_archivo." << endl;
            cout << "listar_departamentos                   ... " << '\t' << "Imprime en n l�neas (una para cada departamento) la informaci�n b�sica del departamento que se carg� de la Divipola." << endl;
            cout << "listar_municipios codigo_depto         ... " << '\t' << "Imprime en n l�neas (una para cada municipio) la informaci�n b�sica del departamento que se carg� de la Divipola." << endl;
            cout << "listar_poblaciones codigo_municipio    ... " << '\t' << "Imprime en n l�neas (una para cada municipio) la informaci�n b�sica del departamento que se carg� de la Divipola." << endl;
            cout << "info_sumaria codigo_depto              ... " << '\t' << "Imprime en una l�nea la informaci�n b�sica del nombre del departamento que corresponde al c�digo dado como par�metro junto con la cantidad de municipios y centros poblados que lo conforman" << endl;
            cout << "carga_SC nombre_archivo                ... " << '\t' << "Carga en una o m�s estructuras de datos en memoria el contenido del archivo identificado por nombre_archivo con la informaci�n b�sica para representar el sistema de ciudades." << endl;
            cout << "esta_en_sistema codigo_municipio       ... " << '\t' << "Determina si un municipio, con c�digo dado por el usuario, existe dentro de las municipios definidos en el Sistema de Ciudades y cargados desde el archivo correspondiente." << endl;
            /* cout << "" << endl;
            cout << "" << endl;
            cout << "" << endl;
            cout << "" << endl;
            cout << "" << endl;
            cout << "" << endl;
            cout << "" << endl;
            cout << "" << endl;
            cout << "" << endl;
            cout << "" << endl;
            cout << "" << endl;*/
            cout << "Salir                                  ... Termina la ejecuci�n de la aplicaci�n." << endl;
            cout << endl;
        }
        else if (Comando == "Salir")
        {
            Salir = true;
        }
        else
        {
            cout << "Comando no identificado" << endl;
        }

    } while (!Salir);
    return 0;
}

void Separar_Cadena(string Entrada, string &Comando, string &Auxiliar)
{
    int Posicion;
    string Delimitador = " ";
    Posicion = Entrada.find(Delimitador);
    if (Posicion == -1)
    {
        Comando = Entrada;
    }
    else
    {
        Comando = Entrada.substr(0, Posicion);
        Auxiliar = Entrada.substr(Posicion + 1, Entrada.length());
    }
};