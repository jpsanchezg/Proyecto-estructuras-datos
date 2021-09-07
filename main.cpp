#include <iostream>
#include <locale.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <list>
#include "main.h"
#include <vector>

#include <sstream>

using namespace std;

int main()
{

    setlocale(LC_CTYPE, "Spanish");

    string Entrada;
    string Comando;
    string Auxiliar;
    list<divipola> DiviLista; // se crea la lista
    fstream fout;             // lectura de los archivos
    string linea;
    string codigodepto;
    string codigoMunicipio;
    bool Salir = false;
    setlocale(LC_CTYPE, "Spanish");
    char delimitador = ',';
    bool comandoEncontrado = false;
    do
    {
        comandoEncontrado = false;
        cout << "$";
        //cin.ignore();
        getline(cin, Entrada);

        // Vector of string to save tokens
        vector<string> tokens;

        // stringstream class check1
        stringstream check1(Entrada);

        string intermediate;

        // Tokenizing w.r.t. space ' '
        while (getline(check1, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }

        // Printing the token vector
        for (int i = 0; i < tokens.size(); i++)
        {
            if (tokens[i] == "carga_divipola")
            {
                if (tokens[i + 1] == "DIVIPOLA_CentrosPoblados")
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
                else
                {
                    cout << "No se ha encontrado el archivo indicado" << endl;
                    cout << "Dijite ayuda para solucionar su problema" << endl;
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "listar_departamentos")
            {

                comandoEncontrado = true;
            }
            else if (tokens[i] == "listar_municipios")
            {
                codigodepto = tokens[i + 1];
                cout << codigodepto << endl;
                comandoEncontrado = true;
            }
            else if (tokens[i] == "listar_poblaciones ")
            {
                codigoMunicipio = tokens[i + 1];
                comandoEncontrado = true;
            }
            else if (tokens[i] == "info_sumaria ")
            {
                codigodepto = tokens[i + 1];
                comandoEncontrado = true;
            }
            else if (tokens[i] == "carga_SC nombre_archivo")
            {
                if (tokens[i + 1] == "Datos-ICM-2019")
                {
                }
                else
                {
                    cout << "No se ha encontrado el archivo indicado" << endl;
                    cout << "Dijite ayuda para solucionar su problema" << endl;
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "esta_en_sistema")
            {
                codigoMunicipio = tokens[i + 1];
                comandoEncontrado = true;
            }
            else if (tokens[i] == "Ayuda")
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
                comandoEncontrado = true;
            }
            else if (tokens[i] == "Salir")
            {
                Salir = true;
                comandoEncontrado = true;
            }
            if (!comandoEncontrado)
            {
                cout << "Comando no identificado" << endl;
            }
        }
    } while (!Salir);
    return 0;
}