#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<stdlib.h>
using namespace std;
//Estructura del nodo del arbol de Huffman para poder decodificar
struct Nodo                                                                                     
{
    unsigned char dato;
    Nodo* izq;
    Nodo* der;
    Nodo(char c,Nodo* l=NULL,Nodo* r=NULL)
    {
        dato=c;
        izq=l;
        der=r;
    }

};
//Crear el arbol de Huffman utilizando el archivo comprimido
Nodo* CrearArbol(ifstream &input)                                                       
{
    char da;
    input.get(da);
    if(da=='1')
    {
        input.get(da);
        return (new Nodo(da));
    }
    else
    {
        Nodo* izq=CrearArbol(input);
        Nodo* der=CrearArbol(input);
        return(new Nodo(-1,izq,der));
    }
}
//Se hace uso de esta funcion para poder decodificar cada item binario de acuerdo al arbol creado
void decodificar(ifstream &input,string Nom_archivo,Nodo* raiz,long long int Frecuencia_total)              
{
    ofstream output((Nom_archivo.erase(Nom_archivo.size()-4)).c_str(),ios::binary);
    if(!output.good())
    {
        perror("Error:\t");
        //exit(-1);
    }
    bool eof_flag=false;
    char bits;
    Nodo* puntero=raiz;
    while(input.get(bits))
    {
        int contador=7;
        while(contador>=0)
        {
            if(!puntero->izq&&!puntero->der)
            {
                output<<puntero->dato;
                Frecuencia_total--;
                if(!Frecuencia_total)
                {
                    eof_flag=true;
                    break;
                }
                puntero=raiz;
                continue;
            }
            if((bits&(1<<contador)))
            {
                puntero=puntero->der;
                contador--;
            }
            else
            {
                puntero=puntero->izq;
                contador--;
            }
        }
        if(eof_flag)
            break;
    }
    output.close();
}
int main()
{
    string Nom_archivo="codificado.icmbin";
    ifstream abrir_archivo(Nom_archivo.c_str(),ios::binary);                                           
    if(!abrir_archivo.good())                                                                       
    {
        perror("Error con el archivo\t");
    }
    if(Nom_archivo.find(".icmbin")==string::npos)                                                     
    {
        cout<<"Error: El archivo ya esta descomprimido\n\n";
    }
    long long int Frecuencia_total=0;
    char da;
    while(abrir_archivo.get(da))                                                                  
    {
        if(da==',')
            break;
        Frecuencia_total*=10;
        Frecuencia_total+=da-'0';
    }
    Nodo* Arbol_Huffman=CrearArbol(abrir_archivo);                                         
    abrir_archivo.get(da);                                                                       
    decodificar(abrir_archivo,Nom_archivo,Arbol_Huffman,Frecuencia_total);
    abrir_archivo.close();
}