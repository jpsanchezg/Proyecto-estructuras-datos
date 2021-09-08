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
                    Cargar_divipola(DiviLista);
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
                    cargar_SC(SClista);
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
                if (Existencia(codigoMunicipio, DiviLista) == false)
                {
                    cout << endl;
                    cout << "\tNo hay informacion cargada en memoria para ese municipio." << endl;
                    cout << endl;
                }
                else
                {
                    estaEnSistema(codigoMunicipio, SClista, DiviLista);
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "ayuda")
            {
                string menuayuda = tokens[i + 1];
                ayuda(menuayuda, comandoEncontrado);
            }
            else if (tokens[i] == "Salir")
            {
                Salir = true;
                comandoEncontrado = true;
            }
            if (!comandoEncontrado) // si el comando no se encuentra el arroja este error de comando no encontrado
            {
                cout << "Comando no identificado" << endl;
                cout << "Por favor ingrese ayuda con el comando que necesita ayuda con el comando  (ayuda listar_departamentos) o "
                     << "\n "
                     << "dijite ayuda general para ver todos los comandos disponibles para ayudarlo para tener mas informacion de los comandos " << endl;
                tokens.clear();
            }
            else
            {
                tokens.clear(); // esto borra el contenido de tokens para que no siga ejecutando el comando del for y asi termine con lo assignado
            }
        }
    } while (!Salir);
    return 0;
}
