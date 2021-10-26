#include<iostream>
#include<fstream>
#include<vector>
#include<string>
//#include<time.h>
#include<stdlib.h>
using namespace std;
//Se hace uso solamente de los caracteres de ASCII
#define Char_size 256      
//Estructura del arbol de Huffman                                                                             
struct nodo                                                                                             
{
    unsigned char caracter;
    long long int Frecuencia;
    nodo* izquierda;
    nodo* derecha;
    nodo(unsigned char c,long long int f,nodo* l=NULL,nodo* r=NULL)
    {
        caracter=c;
        Frecuencia=f;
        izquierda=l;
        derecha=r;
    }
};
//Esta funcion se encarga de comparar el nodo recien insertado con otros dos (serian sus hijos) para asi poder escoger el mas pequeño e intercambiarlo 
void Minimo_monticulo(vector<nodo*> &A,int i,int length)                                                     
{
    int menor=i;
    if(2*i+1<=length&&A[2*i+1]->Frecuencia<A[i]->Frecuencia)
    {
        menor=2*i+1;
        if(2*i+2<=length&&A[2*i+2]->Frecuencia<A[2*i+1]->Frecuencia)
            menor=2*i+2;
    }
    else if(2*i+2<=length&&A[2*i+2]->Frecuencia<A[i]->Frecuencia)
        menor=2*i+2;
    if(menor!=i)
    {
        swap(A[i],A[menor]);
        Minimo_monticulo(A,menor,length);
    }
}
//Extrear el minimo del monticulo
nodo* Extraer_menor(vector<nodo*> &A)              
{
    if(A.size()<1)
        return NULL;
    nodo* minimo=A[0];
    A[0]=A.back();
    A.pop_back();
    Minimo_monticulo(A,0,A.size()-1);
    return minimo;

}
//Esta funcion inserta el caracter en el monticulo
void Insertar_min_mon(vector<nodo*> &A,nodo* elemento)                                                  
{
    A.push_back(elemento);
    int i=A.size()-1;
    while(i>0&&A[(i-1)/2]->Frecuencia>A[i]->Frecuencia)
    {
        swap(A[i],A[(i-1)/2]);
        i=(i-1)/2;
    }
}
//con esta funcion se construye el monticulo
void Crear_monticulo(vector<nodo*> &A,int length)
{
    for(int i=(length-1)/2;i>=0;i--)
    {
        Minimo_monticulo(A,i,length);
    }
}
//Esta funcion se encarga de almacenar cada caracter en el vector
void Guardar_car(nodo* raiz,char cod_simple[],int index,vector<long long int> &mapaHuffman)    
{
    if(raiz->izquierda)
    {
        cod_simple[index]='0';
        Guardar_car(raiz->izquierda,cod_simple,index+1,mapaHuffman);

    }
    if(raiz->derecha)
    {
        cod_simple[index]='1';
        Guardar_car(raiz->derecha,cod_simple,index+1,mapaHuffman);
    }
    if(!raiz->izquierda&&!raiz->izquierda)
    {
        for(int i=index;i>=0;i--)
        {
          if(i!=index)
          {
            mapaHuffman[raiz->caracter]*=10;
            mapaHuffman[raiz->caracter]+=cod_simple[i]-'0';
          }
          else
            mapaHuffman[raiz->caracter]=1;
        }
    }
}
//Esta funcion se encarga de almacenar el arbol al archivo
void Guardar_Arbol(ofstream &input,nodo* raiz)                                                         
{
    if(!raiz->izquierda&&!raiz->derecha)
    {
        input<<'1';
        input<<raiz->caracter;
    }
    else
    {
        input<<'0';
        Guardar_Arbol(input,raiz->izquierda);
        Guardar_Arbol(input,raiz->derecha);
    }
}
//En esta funcion se desarrolla el algoritmo de Huffman
nodo* Huffman(long long int Contador[]) 
{
    vector<nodo*>monticulo;
    for(int i=0;i<Char_size;i++)
        if(Contador[i]!=0)
            monticulo.push_back(new nodo(i,Contador[i]));
    Crear_monticulo(monticulo,monticulo.size()-1);
    while(monticulo.size()!=1)
    {
        nodo* Z=new nodo(-1,0,Extraer_menor(monticulo),Extraer_menor(monticulo));
        Z->Frecuencia=Z->izquierda->Frecuencia+Z->derecha->Frecuencia;
        Insertar_min_mon(monticulo,Z);
    }
    return(monticulo[0]);
}
//Con esta funcion se utiliza para poder volver a escribir en un archivo per ya comprimido
void Escrbir_codif(ifstream &input,ofstream &output,vector<long long int > &mapaHuffman)    
{
    char da;
    unsigned char bits;
    long long int contador=0;
    while(input.get(da))
    {
        long long int temp=mapaHuffman[static_cast<unsigned char>(da)];
        while(temp!=1)
        {
          bits<<=1;
          if((temp%10)!=0)
                bits|=1;
          temp/=10;
          contador++;
          if(contador==8)
            {
                output<<bits;
                contador=bits=0;
            }
        }
    }
    while(contador!=8)
    {
        bits<<=1;
        contador++;
    }
    output<<bits;
    output.close();
}
int main(int argc,char *argv[])
{
    vector<long long int > mapaHuffman;             
    mapaHuffman.resize(Char_size);
    long long int Contador[Char_size]={0};                                                          
    ifstream input_file("Datos-ICM-2019.csv",ios::binary);                                          
    if(!input_file.good())                                                                          
    {
        perror("Error con el codigo\t");
    }                                                                 
    char da;
    while(input_file.get(da))                                                                      
        Contador[static_cast<unsigned char>(da)]++;
    input_file.clear();                                                                            
    input_file.seekg(0);                                                                            
    nodo* arbol=Huffman(Contador);                                                                    
    ofstream output_file("codificado.icmbin",ios::binary);                                   
    if(!output_file.good())                                                                         
    {
        perror("Error con el codigo\t");
    }
    output_file<<arbol->Frecuencia;                                                                     
    output_file<<',';
    Guardar_Arbol(output_file,arbol);
    output_file<<' ';
    char cod_simple[16];                                                                         
    Guardar_car(arbol,cod_simple,0,mapaHuffman);                                                
    Escrbir_codif(input_file,output_file,mapaHuffman);                                       
    input_file.close();                                                                             
    output_file.close();                                                                            
}