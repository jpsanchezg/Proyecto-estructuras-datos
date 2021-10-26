#include <iostream>
#include <wchar.h>
#include <locale.h>
#include <string>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <conio.h>
#include <list>
#include "funciones.h"
#include <vector>

#include <stdio.h>
#include <windows.h>
using namespace std;

bool Existencia_Departamento_Municipio(string Codigo, list<Divipola> &Lista)
{
    list<Divipola>::iterator iter;
    for (iter = Lista.begin(); iter != Lista.end(); ++iter)
    {
        if (iter->Codigo == Codigo)
        {
            return true;
        }
    }
    return false;
}

void Contar_Municipios_Poblaciones(list<Divipola> &Departamentos, string Codigo, int indicador)
{
    list<Divipola>::iterator iter;

    int Codigo1_Auxiliar;
    int Codigo2_Auxiliar;

    for (iter = Departamentos.begin(); iter != Departamentos.end(); iter++)
    {
        Codigo1_Auxiliar = atoi(Codigo.c_str());
        if (indicador == 0)
        {
            Codigo1_Auxiliar = Codigo1_Auxiliar / 1000;
        }
        else if (indicador == 1)
        {
            Codigo1_Auxiliar = Codigo1_Auxiliar / 1000000;
        }
        Codigo2_Auxiliar = atoi(iter->Codigo.c_str());
        if (Codigo1_Auxiliar == Codigo2_Auxiliar)
        {
            if (indicador == 0)
            {
                int Numero_Municipios = atoi(iter->Latitud.c_str());
                Numero_Municipios += 1;
                iter->Latitud = to_string(Numero_Municipios);
            }
            else if (indicador == 1)
            {
                int Numero_Poblaciones = atoi(iter->Longitud.c_str());
                Numero_Poblaciones += 1;
                iter->Longitud = to_string(Numero_Poblaciones);
            }
        }
    }
}

void Cargar_divipola(list<Divipola> &Departamentos, list<Divipola> &Municipios, list<Divipola> &Poblaciones)
{
    string linea;
    fstream fout;
    char delimitador = ',';

    fout.open("DIVIPOLA_CentrosPoblados.csv", ios::in); // se lee el archivo .csv
    getline(fout, linea);                               // se omite la primera linea del archivo que no contiene nada importante
    setlocale(LC_CTYPE, "");
    while (getline(fout, linea))
    {
        Divipola Auxiliar;
        string Auxiliar_Verificacion;

        stringstream stream(linea); // convertir la cadena a un stream

        getline(stream, Auxiliar_Verificacion, delimitador);

        if (Existencia_Departamento_Municipio(Auxiliar_Verificacion, Departamentos) == false)
        {
            Divipola Departamento_Auxiliar;
            Departamento_Auxiliar.Codigo = Auxiliar_Verificacion;

            getline(stream, Departamento_Auxiliar.Nombre, delimitador);

            Departamento_Auxiliar.Longitud = "0";

            Departamento_Auxiliar.Latitud = "0";

            Departamentos.push_back(Departamento_Auxiliar);
        }
        else if (Existencia_Departamento_Municipio(Auxiliar_Verificacion, Departamentos) == true)
        {
            getline(stream, Auxiliar_Verificacion, delimitador);
        }

        getline(stream, Auxiliar_Verificacion, delimitador);

        if (Existencia_Departamento_Municipio(Auxiliar_Verificacion, Municipios) == false)
        {
            Divipola Municipio_Auxiliar;
            Municipio_Auxiliar.Codigo = Auxiliar_Verificacion;

            getline(stream, Municipio_Auxiliar.Nombre, delimitador);

            getline(stream, Auxiliar_Verificacion, delimitador);

            getline(stream, Auxiliar_Verificacion, delimitador);

            getline(stream, Auxiliar_Verificacion, delimitador);

            getline(stream, Municipio_Auxiliar.Latitud, delimitador);

            getline(stream, Municipio_Auxiliar.Longitud, delimitador);

            Municipios.push_back(Municipio_Auxiliar);

            Contar_Municipios_Poblaciones(Departamentos, Municipio_Auxiliar.Codigo, 0);
        }
        else if (Existencia_Departamento_Municipio(Auxiliar_Verificacion, Municipios) == true)
        {
            getline(stream, Auxiliar_Verificacion, delimitador);

            getline(stream, Auxiliar.Codigo, delimitador);

            getline(stream, Auxiliar.Nombre, delimitador);

            getline(stream, Auxiliar_Verificacion, delimitador);

            getline(stream, Auxiliar.Latitud, delimitador);

            getline(stream, Auxiliar.Longitud, delimitador);

            Poblaciones.push_back(Auxiliar);

            Contar_Municipios_Poblaciones(Departamentos, Auxiliar.Codigo, 1);
        }
    }
    fout.close();
}

void cargar_SC(list<SistemaCiudades> &SClista)
{
    string linea;
    fstream fout2;
    char delimitador = ';';
    fout2.open("Datos-ICM-2019.csv", ios::in); // se lee el archivo .csv
    setlocale(LC_ALL, "spanish");
    getline(fout2, linea); // se omite la primera linea del archivo que no contiene nada importante
    while (getline(fout2, linea))

    {
        SistemaCiudades nodo;

        stringstream stream(linea); // convertir la cadena a un stream
        getline(stream, nodo.aglomeracion, delimitador);

        getline(stream, nodo.FuncionCiudades, delimitador);

        getline(stream, nodo.cod_dept, delimitador);

        getline(stream, nodo.nom_mpio, delimitador);

        getline(stream, nodo.divipola, delimitador);

        getline(stream, nodo.anio, delimitador);

        getline(stream, nodo.personas, delimitador);

        getline(stream, nodo.hectareas, delimitador);

        SClista.push_back(nodo);
    }
    fout2.close();
}

void Nombre_Departamento(list<Divipola> Departamentos, string Codigo_Departamento)
{
    list<Divipola>::iterator iter;

    for (iter = Departamentos.begin(); iter != Departamentos.end(); iter++)
    {
        if ((iter->Codigo) == Codigo_Departamento)
        {
            cout << endl;
            cout << "\tEl departamento " << iter->Nombre << " esta conformado por " << iter->Latitud << " municipios y " << iter->Longitud << " centros poblados. " << endl;
            cout << endl;
        }
    }
}

// esta funcion despliega toda la informacion de los departamentos
void Listar_Departamentos(list<Divipola> Departamentos, list<Divipola> Municipios, list<Divipola> Poblaciones)
{

    list<Divipola>::iterator iter;

    cout << endl;
    cout << "    CODIGO"
         << "        "
         << "NOMBRE"
         << "               "
         << "NO. MUNICIPIOS"
         << "    "
         << "NO. POBLACIONES" << endl;
    cout << endl;

    for (iter = Departamentos.begin(); iter != Departamentos.end(); ++iter)
    {
        int Contador_Municipios = 0;
        int Contador_Poblaciones = 0;
        cout << "       " << iter->Codigo << "        " << iter->Nombre << "                   " << iter->Latitud << "                 " << iter->Longitud << endl;
    }
    cout << endl;
}

void Listar_Municipios_Poblaciones(string Codigo, list<Divipola> Lista)
{

    list<Divipola>::iterator iter;

    int Codigo1_Auxiliar;
    int Codigo2_Auxiliar;

    cout << endl;
    cout << "    CODIGO"
         << "       "
         << "NOMBRE"
         << "           "
         << "LATITUD"
         << "           "
         << "LONGITUD" << endl;
    cout << endl;

    for (iter = Lista.begin(); iter != Lista.end(); ++iter)
    {
        Codigo1_Auxiliar = atoi(iter->Codigo.c_str());
        Codigo1_Auxiliar = Codigo1_Auxiliar / 1000;
        Codigo2_Auxiliar = atoi(Codigo.c_str());
        if (Codigo1_Auxiliar == Codigo2_Auxiliar)
        {
            cout << "      " << iter->Codigo << "    " << iter->Nombre << "        " << iter->Latitud << "       " << iter->Longitud << endl;
        }
    }
    cout << endl;
}

/*
funcion para determinar si un municipio esta en el sistema de ciudades usando la divipola para poder
idnetificar a los municipios en la divipola y en el sistema de ciudades
*/
void estaEnSistema(string codigoMunicipio, list<SistemaCiudades> SClista, list<Divipola> Municipios)
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
        list<Divipola>::iterator iter;
        list<SistemaCiudades>::iterator otr;
        for (iter = Municipios.begin(); iter != Municipios.end(); ++iter)
        {
            if (iter->Codigo == codigoMunicipio)
            {
                for (otr = SClista.begin(); otr != SClista.end(); otr++)
                {
                    if (otr->divipola == iter->Codigo)
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

// se desplega el menu de ayuda necesario por si el cliente no responde al comando
void ayuda(string menuayuda, bool &comandoEncontrado)
{
    if (menuayuda == "carga_divipola")
    {
        cout << "CARGA_DIVIPOLA nombre_archivo.csv    " << '\t' << "Carga en una o mas estructuras de datos en memoria el contenido del "
             << "                                                    archivo identificado por nombre_archivo." << endl;
        comandoEncontrado = true;
    }
    cout << endl;
    if (menuayuda == "listar_departamentos")
    {
        cout << "LISTAR_DEPARTAMENTOS   " << '\t' << "Imprime en n lineas (una para cada departamento) la informacion basica del departamento"
             << "                                 que se cargo de la Divipola." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "listar_municipios")
    {
        cout << "LISTAR_MUNICIPIOS codigo_depto   " << '\t' << "Imprime en n lineas (una para cada municipio) la informacion basica del "
             << "                                                departamento que se cargo de la Divipola." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "listar_poblaciones")
    {
        cout << "LISTAR_POBLACIONES codigo_municipio    " << '\t' << "Imprime en n lineas (una para cada municipio) la informacion basica "
             << "                                                     del departamento que se cargo de la Divipola." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "info_sumaria")
    {
        cout << "INFO_SUMARIA codigo_depto   " << '\t' << "Imprime en una lineas la informacion basica del nombre del departamento que "
             << "                                            corresponde al codigo dado como parametro junto con la cantidad de municipios y "
             << "                                        centros poblados que lo conforman" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "carga_SC")
    {
        cout << "CARGA_SC nombre_archivo    " << '\t' << "Carga en una o mas estructuras de datos en memoria el contenido del archivo "
             << "                                            identificado por nombre_archivo con la informacion basica para representar el "
             << "                                          sistema de ciudades." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "esta_en_sistema")
    {
        cout << "ESTA_EN_SISTEMA codigo_municipio   " << '\t' << "Determina si un municipio, con codigo dado por el usuario, existe "
             << "                                                      dentro de las municipios definidos en el Sistema de Ciudades y cargados "
             << "                                                desde el archivo correspondiente." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "aglomeracion")
    {
        cout << "AGLOMERACION   " << '\t' << "El comando debe crear los componentes C2, aglomeraciones urbanas, como componentes del "
             << "                                 sistema de Ciudades, de acuerdo con los datos guardados en memoria" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "uninodal")
    {
        cout << "UNINODAL   " << '\t' << "El comando debe crear los componentes C1, ciudades uninodales, como componentes del sistema "
             << "                            de Ciudades, de acuerdo con los datos guardados en memoria" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "capital_menor")
    {
        cout << "CAPITAL_MENOR  " << '\t' << "El comando debe crear los componentes C3, ciudades capitales menores de cien mil habitantes,"
             << "                            como componentes del sistema de Ciudades, de acuerdo con los datos guardados en memoria" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "reporte")
    {
        cout << "REPORTE    " << '\t' << "El comando debe crear un reporte con los datos del sistema" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "codificar")
    {
        cout << "CODIFICAR nombre_archivo.icmbin    " << '\t' << "El comando debe cargar en memoria la informaci�n completa del �ndice "
             << "                                                   de Ciudades Modernas (ICM) y generar el archivo binario con la correspondiente "
             << "                                         codificaci�n de Huffman con toda la informaci�n que lo compone, almacen�ndolo "
             << "                                          en disco bajo el nombre: nombre_archivo.icmbin" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "decodificar")
    {
        cout << "DECODIFICAR nombre_archivo.icmbin   " << '\t' << "El comando debe cargar en memoria los datos contenidas en el archivo "
             << "                                                   binario nombre_archivo.icmbin , que contiene una codificaci�n Huffman de "
             << "                                               toda la informaci�n que compone el �ndice de Ciudades Modernas y debe "
             << "                                                  mostrarlo decodificado en pantalla" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "salir")
    {
        cout << "SALIR  " << '\t' << "El comando permite finalizar la ejecuci�n del programa" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "general")
    {
        cout << endl;
        cout << "carga_divipola DIVIPOLA_CentrosPoblados.csv    " << '\t' << "Carga en una o mas estructuras de datos en memoria el contenido del "
             << "                                                    archivo identificado por nombre_archivo." << endl;
        cout << endl;
        cout << "listar_departamentos                           " << '\t' << "Imprime en n lineas (una para cada departamento) la informacion basica "
             << "                                                 del departamento que se cargo de la Divipola." << endl;
        cout << endl;
        cout << "LISTAR_MUNICIPIOS codigo_depto                 " << '\t' << "Imprime en n lineas (una para cada municipio) la informacion basica "
             << "                                                    del departamento que se cargo de la Divipola." << endl;
        cout << endl;
        cout << "LISTAR_POBLACIONES codigo_municipio            " << '\t' << "Imprime en n lineas (una para cada municipio) la informacion basica "
             << "                                                    del departamento que se cargo de la Divipola." << endl;
        cout << endl;
        cout << "INFO_SUMARIA codigo_depto                      " << '\t' << "Imprime en una lineas la informacion basica del nombre del          "
             << "                                                    departamento que corresponde al codigo dado como parametro junto con la"
             << "                                                 cantidad de municipios y centros poblados que lo conforman." << endl;
        cout << endl;
        cout << "CARGA_SC nombre_archivo                        " << '\t' << "Carga en una o mas estructuras de datos en memoria el contenido del "
             << "                                                    archivo identificado por nombre_archivo con la informacion basica para "
             << "                                                 representar el sistema de ciudades." << endl;
        cout << endl;
        cout << "ESTA_EN_SISTEMA codigo_municipio               " << '\t' << "Determina si un municipio, con codigo dado por el usuario, existe   "
             << "                                                    dentro de las municipios definidos en el Sistema de Ciudades y cargados"
             << "                                                 desde el archivo correspondiente." << endl;
        cout << endl;
        cout << "AGLOMERACION                                   " << '\t' << "El comando debe crear los componentes C2, aglomeraciones urbanas,   "
             << "                                                    como componentes del sistema de Ciudades, de acuerdo con los datos     "
             << "                                                 guardados en memoria." << endl;
        cout << endl;
        cout << "UNINODAL                                       " << '\t' << "El comando debe crear los componentes C1, ciudades uninodales, como "
             << "                                                    componentes del sistema de Ciudades, de acuerdo con los datos guardados"
             << "                                                 en memoria." << endl;
        cout << endl;
        cout << "CAPITAL_MENOR                                  " << '\t' << "El comando debe crear los componentes C3, ciudades capitales menores"
             << "                                                    de cien mil habitantes, como componentes del sistema de Ciudades, de   "
             << "                                                 acuerdo con los datos guardados en memoria." << endl;
        cout << endl;
        cout << "REPORTE                                        " << '\t' << "El comando debe crear un reporte con los datos del sistema." << endl;
        cout << endl;
        cout << "CODIFICAR nombre_archivo.icmbin                " << '\t' << "El comando debe cargar en memoria la informaci�n completa del �ndice"
             << "                                                    de Ciudades Modernas (ICM) y generar el archivo binario con la        "
             << "                                                  correspondiente codificaci�n de Huffman con toda la informaci�n"
             << "                                                         que lo compone, almacen�ndolo en disco bajo el nombre: "
             << "                                                                 nombre_archivo.icmbin" << endl;
        cout << endl;
        cout << "DECODIFICAR nombre_archivo.icmbin              " << '\t' << "El comando debe cargar en memoria los datos contenidas en el archivo"
             << "                                                    binario nombre_archivo.icmbin , que contiene una codificaci�n Huffman "
             << "                                                  de toda la informaci�n que compone el �ndice de Ciudades Modernas"
             << "                                                       y debe mostrarlo decodificado en pantalla" << endl;
        cout << endl;
        cout << "SALIR                                          " << '\t' << "Termina la ejecucion de la aplicacion." << endl;
        comandoEncontrado = true;
    }
    cout << endl;
}

/*
Funcion del capitales menores  que debe sacar la lista de ciudades con la poblacion menor a 100.000
*/

void capitalesmenores(list<SistemaCiudades> SClista, list<ciudadescapitales> &CiuCap)
{
    list<SistemaCiudades>::iterator iter;
    ciudadescapitales nodoCC;
    int poblacion = 0;
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        poblacion = stoi(iter->personas);
        if (poblacion < 100000)
        {
            nodoCC.funcionCiudades = iter->FuncionCiudades;
            nodoCC.cod_dept = iter->cod_dept;
            nodoCC.nom_mpio = iter->nom_mpio;
            nodoCC.divipola = iter->divipola;
            CiuCap.push_back(nodoCC);
        }
    }
}

int Accion_Aglomeracion(list<Aglomeracion> Aglomeraciones, int indicador, Municipios_Ciudades Elemento, string Funcion)
{
    list<Aglomeracion>::iterator iter;

    for (iter = Aglomeraciones.begin(); iter != Aglomeraciones.end(); iter++)
    {
        if ((iter->Nombre) == Elemento.Nombre_Aglomeracion)
        {
            if (indicador == 0)
            {
                return 1;
            }
            else if (indicador == 1)
            {
                iter->Ciudad_Principal = Elemento;
            }
            else if (indicador == 2)
            {
                (iter->Ciudades_Componentes).push_back(Elemento);
            }
        }
    }
    if (indicador == 0)
    {
        if ((Funcion == "Centro aglomeracion") || (Funcion == "En aglomeracion"))
            return 0;
    }
    else
    {
        return 2;
    }
    return -1;
}

void Crear_Aglomeraciones(list<SistemaCiudades> SClista, list<Aglomeracion> &Aglomeraciones)
{
    list<SistemaCiudades>::iterator iter;
    list<Aglomeracion>::iterator iter_aux;

    Municipios_Ciudades Auxiliar_Componente;
    Aglomeracion Auxiliar;
    int Contador_Aglomeraciones = 0;
    int Contador_Ciudades = 0;

    for (iter = SClista.begin(); iter != SClista.end(); iter++)
    {
        Auxiliar_Componente.Divipola = iter->divipola;
        Auxiliar_Componente.Nombre = iter->nom_mpio;
        Auxiliar_Componente.Personas = iter->personas;
        Auxiliar_Componente.Hectareas = iter->hectareas;
        Auxiliar_Componente.Nombre_Aglomeracion = iter->aglomeracion;

        if ((Accion_Aglomeracion(Aglomeraciones, 0, Auxiliar_Componente, iter->FuncionCiudades)) == 0)
        {
            Auxiliar.Nombre = iter->aglomeracion;
            Aglomeraciones.push_back(Auxiliar);
            Contador_Aglomeraciones += 1;
        }

        if ((iter->FuncionCiudades) == "Centro aglomeracion")
        {
            Accion_Aglomeracion(Aglomeraciones, 1, Auxiliar_Componente, iter->FuncionCiudades);
            Contador_Ciudades += 1;
        }
        else if ((iter->FuncionCiudades) == "En aglomeracion")
        {
            Accion_Aglomeracion(Aglomeraciones, 2, Auxiliar_Componente, iter->FuncionCiudades);
            Contador_Ciudades += 1;
        }
    }
    cout << endl;
    cout << "\tSe crearon " << Contador_Aglomeraciones << " aglomeraciones urbanas, compuestas por " << Contador_Ciudades << " municipios" << endl;
    cout << endl;
}

void Crear_Uninodales(list<SistemaCiudades> SClista, list<Municipios_Ciudades> &Ciudades_Uninodales)
{
    list<SistemaCiudades>::iterator iter;

    Municipios_Ciudades Auxiliar;

    for (iter = SClista.begin(); iter != SClista.end(); iter++)
    {
        if ((iter->FuncionCiudades) == "Uninodal")
        {
            Auxiliar.Divipola = iter->divipola;
            Auxiliar.Nombre = iter->nom_mpio;
            Auxiliar.Personas = iter->personas;
            Auxiliar.Hectareas = iter->hectareas;
            Ciudades_Uninodales.push_back(Auxiliar);
        }
    }
}

/*

Funcion reporte que debe sacar el reporte del documento
*/

int totalaglomeracionesUrbanas(list<SistemaCiudades> SClista, vector<string> &codigosdeptoaglo)
{
    list<SistemaCiudades>::iterator iter;
    int contador = 0;
    setlocale(LC_CTYPE, "Spanich");
    string aglo = "Centro aglomeracion";
    setlocale(LC_CTYPE, "Spanich");

    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {

        setlocale(LC_CTYPE, "Spanich");
        if (iter->FuncionCiudades == aglo)
        {
            codigosdeptoaglo.push_back(iter->aglomeracion);
            contador++;
        }
    }
    return contador;
}
int totalCiudadesuni(list<SistemaCiudades> SClista)
{
    list<SistemaCiudades>::iterator iter;
    int contador = 0;
    setlocale(LC_CTYPE, "Spanich");
    string uni = "Uninodal";
    setlocale(LC_CTYPE, "Spanich");

    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {

        setlocale(LC_CTYPE, "Spanich");
        if (iter->FuncionCiudades == uni)
        {
            contador++;
        }
    }
    return contador;
}

int ciudadesMenores(list<SistemaCiudades> SClista, vector<string> &codigosmunCME)
{
    list<SistemaCiudades>::iterator iter;
    ciudadescapitales nodoCC;
    int contador = 0;
    int poblacion = 0;
    int cien = 100000;
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        poblacion = stoi(iter->personas);
        if (poblacion <= cien && iter->FuncionCiudades == "Fuera SC")
        {
            codigosmunCME.push_back(iter->divipola);
            contador++;
        }
    }
    return contador;
}

int ciudadesMayores(list<SistemaCiudades> SClista, vector<string> &codigosmunCMA)
{
    list<SistemaCiudades>::iterator iter;
    ciudadescapitales nodoCC;
    int contador = 0;
    int poblacion = 0;
    int cien = 100000;
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        poblacion = stoi(iter->personas);
        if (poblacion >= cien && iter->FuncionCiudades == "Fuera SC")
        {
            codigosmunCMA.push_back(iter->divipola);
            contador++;
        }
    }
    return contador;
}

int totalMuniAglo(list<SistemaCiudades> SClista, vector<string> codigosdeptoaglo)
{
    list<SistemaCiudades>::iterator iter;
    list<SistemaCiudades>::iterator iter2;
    vector<string>::iterator viter;
    int contador = 0;
    setlocale(LC_CTYPE, "Spanich");
    string aglo = "Centro aglomeracion";
    setlocale(LC_CTYPE, "Spanich");

    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        for (int i = 0; i < codigosdeptoaglo.size(); i++)
        {
            if (iter->aglomeracion == codigosdeptoaglo[i])
            {
                contador++;
            }
        }
    }
    return contador;
}
int poblaciontotal(list<SistemaCiudades> SClista)
{
    list<SistemaCiudades>::iterator iter;
    int total = 0;
    int pob = 0;
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        pob = stoi(iter->personas);
        total = pob + total;
    }
    return total;
}

int totalpoblaaglo(list<SistemaCiudades> SClista, vector<string> codigosdeptoaglo)
{
    list<SistemaCiudades>::iterator iter;
    list<SistemaCiudades>::iterator iter2;
    int contador = 0;
    int pob = 0;
    setlocale(LC_CTYPE, "Spanich");
    string aglo = "Centro aglomeracion";
    setlocale(LC_CTYPE, "Spanich");
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        for (int i = 0; i < codigosdeptoaglo.size(); i++)
        {
            if (iter->aglomeracion == codigosdeptoaglo[i])
            {
                pob = stoi(iter->personas);
                contador = pob + contador;
            }
        }
    }
    return contador;
}

int totalPoblaUni(list<SistemaCiudades> SClista)
{

    list<SistemaCiudades>::iterator iter;
    int contador = 0;
    int pob = 0;
    setlocale(LC_CTYPE, "Spanich");
    string uni = "Uninodal";
    setlocale(LC_CTYPE, "Spanich");

    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {

        setlocale(LC_CTYPE, "Spanich");
        if (iter->FuncionCiudades == uni)
        {
            pob = stoi(iter->personas);
            contador = pob + contador;
        }
    }
    return contador;
}

int TotalPobCiudMayor(list<SistemaCiudades> SClista)
{
    list<SistemaCiudades>::iterator iter;
    int contador = 0;
    int poblacion = 0;
    int pob = 0;
    int cien = 100000;
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        poblacion = stoi(iter->personas);
        if (poblacion >= cien && iter->FuncionCiudades == "Fuera SC")
        {
            pob = stoi(iter->personas);
            contador = pob + contador;
        }
    }
    return contador;
}

int TotalPobCiudMenor(list<SistemaCiudades> SClista)
{
    list<SistemaCiudades>::iterator iter;
    int contador = 0;
    int poblacion = 0;
    int pob = 0;
    int cien = 100000;
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        poblacion = stoi(iter->personas);
        if (poblacion <= cien && iter->FuncionCiudades == "Fuera SC")
        {
            pob = stoi(iter->personas);
            contador = pob + contador;
        }
    }
    return contador;
}

int totalmunCMayores(list<SistemaCiudades> SClista, vector<string> codigosmunCMA)
{
    list<SistemaCiudades>::iterator iter;
    ciudadescapitales nodoCC;
    int contador = 0;
    for (int i = 0; i < codigosmunCMA.size(); i++)
    {
        for (iter = SClista.begin(); iter != SClista.end(); ++iter)
        {
            if (codigosmunCMA[i] == iter->divipola)
            {
                contador++;
            }
        }
    }

    return contador;
}
int totalmunCMEnores(list<SistemaCiudades> SClista, vector<string> codigosmunCMA)
{
    list<SistemaCiudades>::iterator iter;
    ciudadescapitales nodoCC;
    int contador = 0;
    for (int i = 0; i < codigosmunCMA.size(); i++)
    {
        for (iter = SClista.begin(); iter != SClista.end(); ++iter)
        {
            if (codigosmunCMA[i] == iter->divipola)
            {
                contador++;
            }
        }
    }
    return contador;
}

void reporte(list<SistemaCiudades> SClista)
{
    list<SistemaCiudades>::iterator iter;
    setlocale(LC_CTYPE, "Spanich");
    vector<string> codigosdeptoaglo;
    vector<string> codigosmunCMA;
    vector<string> codigosmunCME;

    float totaglo = totalaglomeracionesUrbanas(SClista, codigosdeptoaglo);
    float totaluni = totalCiudadesuni(SClista);
    float ciudadesmascien = ciudadesMayores(SClista, codigosmunCMA);
    float ciudadesmenoscien = ciudadesMenores(SClista, codigosmunCME);
    int totalMunCMA = totalmunCMayores(SClista, codigosmunCMA);
    int totalMunCME = totalmunCMayores(SClista, codigosmunCME);
    float totalSC = totaglo + totaluni;
    float totalCol = SClista.size();
    float totalmunAglo = totalMuniAglo(SClista, codigosdeptoaglo);
    float totalMuni = totalmunAglo + totaluni;
    int totalpob = poblaciontotal(SClista);
    int totPobAglo = totalpoblaaglo(SClista, codigosdeptoaglo);
    int totPobUni = totalPoblaUni(SClista);
    int totPobCMA = TotalPobCiudMayor(SClista);
    int totPobCME = TotalPobCiudMenor(SClista);
    float totPobMun = totPobAglo + totPobUni;
    float clac = totalMuni / totalCol;
    float calcpob = totPobMun / totalpob;
    float probatot = clac * 100;
    float probapob = calcpob * 100;
    cout << endl;
    cout << "\t\tSistema Ciudades"
         << "\t\t\t\t"
         << "Municipios"
         << "\t"
         << "Poblacion Total"
         << endl;
    cout << endl;
    cout << "\t\t Ciudades que hacen parte del sistema" << endl;
    cout << "\t\t Aglomeraciones urbanas (" << totaglo << ")"
         << "\t\t\t\t" << totalmunAglo << "\t\t" << totPobAglo << endl;
    cout << "\t\t Ciudades Uninodales (" << totaluni << ")"
         << "\t\t\t\t" << totaluni << "\t\t" << totPobUni << endl;
    cout << "\t\t Ciudades furea del sistema" << endl;
    cout << "\t\t Ciudades con mas de cien mil habitantes (" << ciudadesmascien << ")"
         << "\t\t" << totalMunCMA << "\t\t" << totPobCMA << endl;
    cout << "\t\t Ciudades con menos de cien mil habitantes (" << ciudadesmenoscien << ")"
         << "\t" << totalMunCME << "\t\t" << totPobCME << endl;
    cout << "\t\t Total sistema de ciudades (" << totalSC << ")"
         << "\t\t\t\t" << totalMuni << "\t\t" << totPobMun << endl;
    cout << "\t\t % con respecto a colombia (" << totalMuni << ")"
         << "\t\t\t" << probatot << "\t\t" << probapob << endl;
    cout << "\t\t Total colombia "
         << "\t\t\t\t\t" << totalCol << "\t\t" << totalpob << endl;
}
