#include <string.h>
#include <iostream>
using namespace std;

struct Divipola
{
    int cod_dept;
    string nom_dept;
    int cod_mpio;
    string nom_mpio;
    int cod_cpob;
    string tipo;
    long int latitud;
    long int longitud;
    struct Divipola *izquierdo;
    struct Divipola *derecho;
};
