#include <iostream>
#include <fstream>
#include <string.h>
#include <list>
#include <iterator>
#include <stdlib.h>

using namespace std;

struct SC
{
    string agl;
    string depto;
    string mun;
    int divipola;
};

struct CPob
{
    int codDpto;
    int codMuni;
    int codCentroP;
    long lat;
    long longi;
    string nombreCentroP;
};

struct muni
{
    int codDpto;
    int codMuni;
    string nombMuni;
    double lat;
    double longi;
    list<CPob> CPoblados = list<CPob>();
};

struct dpto
{
    int codDpto;
    string nombDpto;
    int lat;
    int longi;
    list<muni> municipios = list<muni>();
    dpto()
    {
    }
};

list<SC> leerSC()
{
    list<SC> ciud;
    ifstream entrada;
    entrada.open("Datos-ICM-2019.csv", ios::in);
    if (!entrada.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    else
    {
        while (!entrada.eof())
        {
            SC temp;
            char *linea = new char[2000];
            entrada.getline(linea, 2000, '\n');
            char *ptr = strtok(linea, ";");
            //cout<<"ALG: "<<ptr<<endl;
            temp.agl = ptr;
            ptr = strtok(NULL, ";");
            ptr = strtok(NULL, ";");
            //cout<<"DPTO: "<<ptr<<endl;
            temp.depto = ptr;
            ptr = strtok(NULL, ";");
            //cout<<"MUN: "<<ptr<<endl;
            temp.mun = ptr;
            ptr = strtok(NULL, ";");
            //cout<<"DIVIPOLA: "<<ptr<<endl;
            temp.divipola = stoi(ptr);
            ciud.push_front(temp);
        }
    }
    //cout<<ciud.front().mun<<endl;
    cout << "Se cargaron correctamente " << ciud.size() << " municipios" << endl;
    return ciud;
}

list<CPob> leerCentros(int codigo)
{
    list<CPob> centros;
    ifstream entrada;
    entrada.open("DIVIPOLA_CentrosPoblados.csv", ios::in);
    if (!entrada.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    else
    {
        while (!entrada.eof())
        {
            CPob temp;
            char *linea = new char[200];
            entrada.getline(linea, 200, '\n');
            char *ptr = strtok(linea, ",");
            temp.codDpto = stoi(ptr);
            ptr = strtok(NULL, ",");
            ptr = strtok(NULL, ",");
            if (codigo == stoi(ptr))
            {
                //cout<<ptr<<" CODIGO MUN"<<endl;
                temp.codMuni = stoi(ptr);
                ptr = strtok(NULL, ",");
                ptr = strtok(NULL, ",");
                //cout<<ptr<<" CODIGO CP"<<endl;
                temp.codCentroP = stoi(ptr);
                ptr = strtok(NULL, ",");
                //cout<<ptr<<" NOMB CP"<<endl;
                temp.nombreCentroP = ptr;
                ptr = strtok(NULL, ",");
                ptr = strtok(NULL, ",");
                //cout<<ptr<<" LAT"<<endl;
                temp.lat = stol(ptr);
                ptr = strtok(NULL, ",");
                //cout<<ptr<<" CODIGO LONG"<<endl;
                temp.longi = stol(ptr);
                centros.push_front(temp);
            }
        }
    }
    //cout<<centros.front().codCentroP;
    return centros;
}

list<muni> leerMunicipios(int codigo)
{
    list<muni> munTemp;
    ifstream entrada;
    entrada.open("DIVIPOLA_Municipios.csv", ios::in);
    if (!entrada.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    else
    {
        while (!entrada.eof())
        {
            char *linea = new char[200];
            entrada.getline(linea, 200, '\n');
            char *ptr = strtok(linea, ";");
            if (codigo == stoi(ptr))
            {
                muni temp;
                //cout<<ptr<<endl;
                temp.codDpto = stoi(ptr);
                ptr = strtok(NULL, ";");
                ptr = strtok(NULL, ";");
                temp.codMuni = stoi(ptr);
                ptr = strtok(NULL, ";");
                temp.nombMuni = ptr;
                ptr = strtok(NULL, ";");
                ptr = strtok(NULL, ";");
                temp.lat = stod(ptr);
                ptr = strtok(NULL, ";");
                temp.longi = stod(ptr);
                //cout<<temp.nombMuni<<endl;
                //cout<<"valor codigo: "<<temp.codMuni<<" = ";
                temp.CPoblados = leerCentros(temp.codMuni);
                //cout<<"Pasó CP"<<endl;
                munTemp.push_front(temp);
            }
        }
    }
    //cout<<munTemp.front().codMuni;
    //cout<<"salir Mun"<<endl;
    entrada.close();
    return munTemp;
}

list<dpto> leerDepartamentos()
{
    list<dpto> dptos;
    ifstream entrada;
    entrada.open("DIVIPOLA_CentrosPoblados.csv", ios::in);
    if (!entrada.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    else
    {
        while (!entrada.eof())
        {
            dpto temp;
            char *linea = new char[500];
            entrada.getline(linea, 500, '\n');
            //cout<<linea<<endl;
            char *ptr = strtok(linea, ";");
            temp.codDpto = stoi(ptr);
            ptr = strtok(NULL, ";");
            temp.nombDpto = ptr;
            ptr = strtok(NULL, ";");
            temp.lat = stol(ptr);
            ptr = strtok(NULL, ";");
            temp.longi = stol(ptr);
            temp.municipios = leerMunicipios(temp.codDpto);
            dptos.push_front(temp);
        }
    }
    entrada.close();
    int mun = 0, cp = 0;

    list<dpto>::iterator it;
    list<muni>::iterator it1;
    for (it = dptos.begin(); it != dptos.end(); ++it)
    {
        mun += it->municipios.size();
        for (it1 = it->municipios.begin(); it1 != it->municipios.end(); ++it1)
        {
            cp += it1->CPoblados.size();
        }
    }
    cout << "Se cargaron correctamente " << dptos.size() << " departamentos, " << mun << " municipios y " << cp << " centros poblados" << endl;
    return dptos;
}

void listarDepartamentos(list<dpto> d)
{
    cout << "Departamentos: " << endl;
    list<dpto>::iterator it;
    for (it = d.begin(); it != d.end(); ++it)
        cout << it->nombDpto << endl;
    cout << '\n';
}
void listarMunicipios(list<dpto> d, int cdpto)
{
    list<dpto>::iterator it;
    list<muni>::iterator it1;
    for (it = d.begin(); it != d.end(); ++it)
    {
        if (it->codDpto == cdpto)
        {
            cout << "\tDepartamento: " << it->nombDpto << endl;
            for (it1 = it->municipios.begin(); it1 != it->municipios.end(); ++it1)
            {
                cout << "\tNombre Municipio: " << it1->nombMuni << " Codigo Municipio: " << it1->codMuni << endl;
            }
            return;
        }
    }
    cout << "\tno hay nada que mostrar" << endl;
}
void listarPoblaciones(list<dpto> d, int cmun)
{
    list<dpto>::iterator it;
    list<muni>::iterator it1;
    list<CPob>::iterator it2;
    for (it = d.begin(); it != d.end(); ++it)
    {
        for (it1 = it->municipios.begin(); it1 != it->municipios.end(); ++it1)
        {
            if (it1->codMuni == cmun)
            {
                cout << "Municipio: " << it1->nombMuni << endl;
                for (it2 = it1->CPoblados.begin(); it2 != it1->CPoblados.end(); ++it2)
                    cout << "Nombre Centro: " << it2->nombreCentroP << " Codigo Centro: " << it2->codCentroP << endl;
                return;
            }
        }
    }
}

bool infoSumaria(list<dpto> d, int codigo)
{
    list<dpto>::iterator i;
    for (i = d.begin(); i != d.end(); i++)
    {
        if (i->codDpto == codigo)
        {
            cout << "El departamento de " << i->nombDpto << endl;
            cout << "Tiene " << i->municipios.size() << " municipios";
            list<muni>::iterator j;
            int a = 0;
            for (j = i->municipios.begin(); j != i->municipios.end(); ++j)
            {
                a = a + j->CPoblados.size();
            }
            cout << " y " << a << " centros poblados" << endl;
            return true;
        }
    }
    return false;
}

string ExisteMunSC(list<SC> sc, int b)
{
    list<SC>::iterator it;
    for (it = sc.begin(); it != sc.end(); ++it)
    {
        if (it->divipola == b)
            return it->mun;
    }
    return "0";
}

void menu()
{
    //int a = 0;
    char *opcion = new char[100];
    list<dpto> d;
    list<muni> m;
    list<SC> sc;
    //cout<<"Hola"<<endl;

    while (true)
    {
        cout << "$";
        cin >> opcion;
        char *ptr = strtok(opcion, " ");
        if (strcmp(opcion, "Carga_divipola") == 0)
        {
            d = leerDepartamentos();
            cout << "hola" << endl;
        }
        if (strcmp(opcion, "listar_departamentos") == 0)
        {
            listarDepartamentos(d);
            if (d.empty())
                cout << "\tNo hay nada que mostrar" << endl;
        }
        if (strcmp(ptr, "listar_municipios") == 0)
        {
            ptr = strtok(NULL, "\n");
            listarMunicipios(d, stoi(ptr));
        }
        if (strcmp(ptr, "listar_poblaciones") == 0)
        {
            ptr = strtok(NULL, "\n");
            listarPoblaciones(d, stoi(ptr));
        }
        if (strcmp(ptr, "info_sumaria") == 0)
        {
            ptr = strtok(NULL, "\n");
            if (!infoSumaria(d, stoi(ptr)))
                cout << "no hay información de este departamento" << endl;
        }
        if (strcmp(ptr, "carga_SC") == 0)
        {
            sc = leerSC();
        }
        if (strcmp(ptr, "esta_en_sistema") == 0)
        {
            ptr = strtok(NULL, "\n");
            string n = ExisteMunSC(sc, stoi(ptr));
            if (n == "0")
            {
                cout << "El municipio no se encuentra en el sistema de ciudades" << endl;
            }
            else
                cout << "El municipio " << n << " hace parte del sistema de ciudades" << endl;
        }
        if (strcmp(opcion, "salir") == 0)
        {
            exit(1);
        }
        if (strcmp(ptr, "ayuda") == 0)
        {
            cout << "\t COMANDOS DISPONIBLES" << endl;
            cout << "\tCargar_divipola nombre_archivo" << endl;
            cout << "\tListar_departamentos" << endl;
            cout << "\tListar_municipios codigo_Depto" << endl;
            cout << "\tListar_centros codigo_municipio" << endl;
            cout << "\tInfo_sumaria codigo_Departamento" << endl;
            cout << "\tCarga_SC nombre_archivo" << endl;
            cout << "\tEsta_en_sistema codigo_municipio" << endl;
            cout << "\tsalir" << endl;
        }
    }
}

int main()
{
    menu();

    return 0;
}