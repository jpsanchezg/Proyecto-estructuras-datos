#include <iostream>
#include <wchar.h>
#include <locale.h>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <clocale>
#include <list>
#include "main.h"
#include "funciones.cpp"
#include <vector>
#include <sstream>
#include <windows.h>
#include <stdio.h>

using namespace std;

string aMayuscula(string cadena)
{
    for (int i = 0; i < cadena.length(); i++)
        cadena[i] = toupper(cadena[i]);
    return cadena;
}

int main()
{
    setlocale(LC_CTYPE, "");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    string Entrada;
    list<divipola> DiviLista; // se crea la lista de divipolas
    list<SistemaCiudades> SClista;
    fstream fout; // lectura de los archivos
    fstream fout2;
    string linea;
    string codigodepto;
    string codigoMunicipio;
    bool Salir = false;
    char delimitador = ',';
    bool comandoEncontrado = false;
    do
    {
        comandoEncontrado = false;
        cout << "$";

        getline(cin, Entrada);

        // Vector para guardar los comandos de entrada
        vector<string> tokens;

        // stringstream class check1
        stringstream check1(Entrada);

        string intermediate;

        // Tokenizando la entrada por los espacios' '
        while (getline(check1, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }

        // Buscando si el comando ingresado esta en el menu de comandos
        for (int i = 0; i < tokens.size(); i++)
        {
            if (tokens[i] == "carga_divipola")
            {
                if (tokens[i + 1] == "DIVIPOLA_CentrosPoblados.csv")
                {
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
                else
                {
                    cout << "No se ha encontrado el archivo indicado" << endl;
                    cout << "Dijite ayuda para solucionar su problema" << endl;
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "listar_departamentos")
            {
                if (DiviLista.empty())
                {
                    cout << endl;
                    cout << "\tNo hay departamentos cargados en memoria." << endl;
                    cout << endl;
                }
                else
                {
                    Listar_Departamentos(DiviLista);
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "listar_municipios")
            {
                codigodepto = tokens[i + 1]; // aca recoge el valor del codigo ejemplo listar_municipios 45 este recoge el 45 para luego ser buscado

                if (Existencia(codigodepto, DiviLista) == false)
                {
                    cout << endl;
                    cout << "\tNo hay municipios cargados en memoria para ese departamento." << endl;
                    cout << endl;
                }
                else
                {
                    Listar_Municipios(codigodepto, DiviLista);
                }

                comandoEncontrado = true;
            }
            else if (tokens[i] == "listar_poblaciones")
            {
                codigoMunicipio = tokens[i + 1]; // aca recoge el valor del codigo ejemplo listar_poblaciones 45 este recoge el 45 para luego ser buscado

                if (Existencia(codigoMunicipio, DiviLista) == false)
                {
                    cout << endl;
                    cout << "\tNo hay poblaciones cargadas en memoria para ese municipio." << endl;
                    cout << endl;
                }
                else
                {
                    Listar_Poblaciones(codigoMunicipio, DiviLista);
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "info_sumaria ")
            {
                codigodepto = tokens[i + 1];
                if (Existencia(codigodepto, DiviLista) == false)
                {
                    cout << endl;
                    cout << "\tNo hay informacion cargada en memoria para ese departamento." << endl;
                    cout << endl;
                }
                else
                {
                    Informacion(codigodepto, DiviLista);
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "carga_SC")
            {
                if (tokens[i + 1] == "Datos-ICM-2019.csv")
                {

                    fout2.open("Datos-ICM-2019.csv", ios::in); // se lee el archivo .csv
                    setlocale(LC_ALL, "spanish");
                    getline(fout2, linea);

                    // se omite la primera linea del archivo que no contiene nada importante
                    /*char *str;
                    str = setlocale(LC_ALL, NULL);
                    wcout << "Current locale: " << str << endl;*/
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
                    fout.close();
                    if (SClista.empty() == 0)
                    {
                        cout << "La carga ha sido exitosa" << endl;
                    }
                    if (SClista.empty() == 1)
                    {
                        cout << "La carga no ha sido exitosa" << endl;
                    }
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
                string cadena;
                codigoMunicipio = tokens[i + 1]; // aca recoge el valor del codigo ejemplo esta_en_sistema 45 este recoge el 45 para luego ser buscado
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
                comandoEncontrado = true;
            }
            else if (tokens[i] == "ayuda")
            {
                if (tokens[i + 1] == "carga_divipola")
                {
                    cout << "carga_divipola DIVIPOLA_CentrosPoblados.csv           " << '\t' << "Carga en una o m�s estructuras de datos en memoria el contenido del archivo identificado por nombre_archivo." << endl;
                }
                if (tokens[i + 1] == "listar_departamentos")
                {
                    cout << "listar_departamentos                    " << '\t' << "Imprime en n l�neas (una para cada departamento) la informaci�n b�sica del departamento que se carg� de la Divipola." << endl;
                }
                if (tokens[i + 1] == "listar_municipios")
                {
                    cout << "LISTAR_MUNICIPIOS c�digo_depto          " << '\t' << "Imprime en n l�neas (una para cada municipio) la informaci�n b�sica del departamento que se carg� de la Divipola." << endl;
                }
                if (tokens[i + 1] == "listar_poblaciones")
                {
                    cout << "LISTAR_POBLACIONES c�digo_municipio     " << '\t' << "Imprime en n l�neas (una para cada municipio) la informaci�n b�sica del departamento que se carg� de la Divipola." << endl;
                }
                if (tokens[i + 1] == "info_sumaria")
                {
                    cout << "INFO_SUMARIA c�digo_depto               " << '\t' << "Imprime en una l�nea la informaci�n b�sica del nombre del departamento que corresponde al c�digo dado como par�metro junto con la cantidad de municipios y centros poblados que lo conforman" << endl;
                }
                if (tokens[i + 1] == "carga_SC")
                {
                    cout << "CARGA_SC nombre_archivo                 " << '\t' << "Carga en una o m�s estructuras de datos en memoria el contenido del archivo identificado por nombre_archivo con la informaci�n b�sica para representar el sistema de ciudades." << endl;
                }
                if (tokens[i + 1] == "esta_en_sistema")
                {
                    cout << "ESTA_EN_SISTEMA c�digo_municipio        " << '\t' << "Determina si un municipio, con c�digo dado por el usuario, existe dentro de las municipios definidos en el Sistema de Ciudades y cargados desde el archivo correspondiente." << endl;
                }
                if (tokens[i + 1] == "salir")
                {
                    cout << "SALIR                                           Termina la ejecuci�n de la aplicaci�n." << endl;
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "Salir")
            {
                Salir = true;
                comandoEncontrado = true;
            }
            if (!comandoEncontrado) // si el comando no se encuentra el arroja este error de comando no encontrado
            {
                cout << "Comando no identificado" << endl;
                cout << "Por favor ingrese ayuda para tener mas informacion de los comandos" << endl;
            }
        }
    } while (!Salir);
    return 0;
}
