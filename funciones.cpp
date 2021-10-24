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

bool ExistenciaDepto(string codigo, list<datosdept> &lista)
{

    list<datosdept>::iterator iter;
    for (iter = lista.begin(); iter != lista.end(); ++iter)
    {
        if (iter->codigo == codigo)
        {
            return true;
        }
        else if (iter->codigo == codigo)
        {
            return true;
        }
    }
    return false;
}

bool ExistenciaMun(string codigo, list<datosMun> &lista)
{

    list<datosMun>::iterator iter;
    for (iter = lista.begin(); iter != lista.end(); ++iter)
    {
        if (iter->codigo == codigo)
        {
            return true;
        }
        else if (iter->codigo == codigo)
        {
            return true;
        }
    }
    return false;
}

void Cargar_divipola(list<datosdept> &departamento, list<datosMun> &municipio, list<DatosPob> &poblacion)
{
    string linea;
    fstream fout;
    char delimitador = ',';
    setlocale(LC_CTYPE, "Spanich");
    fout.open("DIVIPOLA_CentrosPoblados.csv", ios::in); // se lee el archivo .csv
    setlocale(LC_ALL, "spanish");
    getline(fout, linea); // se omite la primera linea del archivo que no contiene nada importante
    while (getline(fout, linea))
    {
        datosdept nododept;

        datosMun nodomun;
        DatosPob nodopob;

        stringstream stream(linea); // convertir la cadena a un stream

        getline(stream, nododept.codigo, delimitador);

        getline(stream, nododept.nombre, delimitador);

        getline(stream, nodomun.codigo, delimitador);

        nododept.codigoIdent = nodomun.codigo;

        getline(stream, nodomun.nombre, delimitador);

        getline(stream, nodopob.codigoPob, delimitador);

        nodomun.codigoIdent = nodopob.codigoPob;
        nodomun.codigoatrs = nododept.codigo;
        nodopob.codigoMun = nodomun.codigo;
        getline(stream, nodopob.nombre, delimitador);
        nododept.codigoatrs = nodopob.codigoPob;
        getline(stream, nodopob.tipo, delimitador);

        getline(stream, nodopob.latitud, delimitador);
        nododept.latitud = nodopob.latitud;
        nodomun.latitud = nodopob.latitud;

        getline(stream, nodopob.longitud, delimitador);
        nodomun.tipo = nodopob.tipo;
        nodopob.codigoDept = nododept.codigo;
        nododept.longitud = nodopob.longitud;
        nodomun.longitud = nodopob.longitud;
        departamento.push_back(nododept);
        municipio.push_back(nodomun);
        poblacion.push_back(nodopob);
    }
    fout.close();
}

void cargar_SC(list<SistemaCiudades> &SClista)
{
    string linea;
    fstream fout2;
    char delimitador = ';';
    setlocale(LC_ALL, "spanish");
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

/*
Funcion para mostrar la informacion del departartamento cargado en la divipola
*/
vector<string> Informacion(string codigodepto, list<datosdept> departamento, list<datosMun> municipio, list<DatosPob> poblacion)
{

    list<datosdept>::iterator iter;
    list<datosMun>::iterator iter1;
    list<DatosPob>::iterator iter2;
    list<datosMun>::iterator iter3;
    vector<string> municipios;
    vector<string> poblaciones;
    vector<string> datos = {"", "", ""};

    for (iter = departamento.begin(); iter != departamento.end(); ++iter)
    {
        // cout << iter1->codigoIdent << endl;
        if (iter->codigo == codigodepto)
        {
            for (iter1 = municipio.begin(); iter1 != municipio.end(); ++iter1)
            {
                if (iter->codigoIdent == iter1->codigo && (find(municipios.begin(), municipios.end(), iter1->codigo) == municipios.end()))
                {
                    municipios.push_back(iter1->codigo);
                    // cout << iter2->codigo << endl;
                    // cout << iter1->codigoIdent << endl;
                }
            }
            for (iter2 = poblacion.begin(); iter2 != poblacion.end(); ++iter2)
            {
                if (iter->codigoIdent == iter2->codigoMun && (find(poblaciones.begin(), poblaciones.end(), iter2->codigoPob) == poblaciones.end()))
                {
                    poblaciones.push_back(iter2->codigoPob);
                }
            }
        }
    }
    datos[0] = to_string(municipios.size());
    datos[1] = to_string(poblaciones.size());

    return datos;
}

// esta funcion despliega toda la informacion de los departamentos
void Listar_Departamentos(list<datosdept> departamento, list<datosMun> municipio, list<DatosPob> poblacion)
{

    list<datosdept>::iterator iter;
    list<datosMun>::iterator iter1;
    list<DatosPob>::iterator iter2;
    vector<string> departamentos;
    vector<string> datos;

    cout << endl;
    cout << "    CODIGO"
         << "        "
         << "NOMBRE"
         << "               "
         << "NO. MUNICIPIOS"
         << "    "
         << "NO. POBLACIONES" << endl;
    cout << endl;

    for (iter = departamento.begin(); iter != departamento.end(); ++iter)
    {
        if (find(departamentos.begin(), departamentos.end(), iter->codigo) == departamentos.end())
        {
            // cout << iter->codigo << endl;

            datos = Informacion(iter->codigo, departamento, municipio, poblacion); // el lento esta aca
            setlocale(LC_ALL, "");
            cout << "    " << iter->codigo << "        " << iter->nombre << "                 " << datos[0] << "             " << datos[1] << endl;
            departamentos.push_back(iter->codigo);
        }
    }
    cout << endl;
}

/*
Esta funcion lista los municipios por el codigo del departamento
*/
void Listar_Municipios(string codigodepto, list<datosdept> departamento, list<datosMun> municipios, list<DatosPob> poblacion)
{

    list<datosdept>::iterator iter;
    list<datosMun>::iterator iter2;
    list<DatosPob>::iterator iterG;
    cout << endl;
    cout << "    CODIGO"
         << "    "
         << "NOMBRE" << endl;
    cout << endl;

    for (iter2 = municipios.begin(); iter2 != municipios.end(); ++iter2)
    {
        if (iter2->codigoatrs == codigodepto && iter2->tipo == "CM")
        {
            cout << "    " << iter2->codigo << "    " << iter2->nombre << endl;
        }
    }
}

/*
Funcion para listar las poblaciones por el codigo del municipio
*/
void Listar_Poblaciones(string codigoMunicipio, list<DatosPob> poblacion)
{
    list<DatosPob>::iterator iter2;
    cout << endl;
    cout << "\tCODIGO"
         << "\t\t"
         << "NOMBRE"
         << "\t\t\t\t"
         << "LATITUD"
         << "\t\t\t\t"
         << "LONGITUD" << endl;
    cout << endl;

    for (iter2 = poblacion.begin(); iter2 != poblacion.end(); ++iter2)
    {
        if (iter2->codigoMun == codigoMunicipio)
        {
            if (iter2->tipo == "CP")
            {
                cout << '\t' << iter2->codigoPob << '\t' << iter2->nombre << "\t\t\t" << iter2->latitud << "\t\t" << iter2->longitud << endl;
            }
        }
    }

    cout << endl;
}

/*
funcion para determinar si un municipio esta en el sistema de ciudades usando la divipola para poder
idnetificar a los municipios en la divipola y en el sistema de ciudades
*/
void estaEnSistema(string codigoMunicipio, list<SistemaCiudades> SClista, list<datosMun> municipio)
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
        list<datosMun>::iterator iter;
        list<SistemaCiudades>::iterator otr;
        for (iter = municipio.begin(); iter != municipio.end(); ++iter)
        {
            if (iter->codigo == codigoMunicipio)
            {
                for (otr = SClista.begin(); otr != SClista.end(); otr++)
                {
                    if (otr->divipola == iter->codigo)
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