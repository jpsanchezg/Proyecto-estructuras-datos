#include <iostream>
#include <main.h>
using namespace std;

int main(){
    Divipola *documento = insertarenOrden

}

Divipola *NuevoNodo()
{
    Divipola *node = (Divipola *)malloc(sizeof(nodo<T>));
    node->dato = data;
    node->izquierdo = node->derecho = NULL;
    return (node);
}

Divipola *insertarenOrden(Divipola *raiz, T i, T n)
{
    // Base case for recursion
    if (i < n)
    {
        nodo<T> *temp = NuevoNodo<T>(arreglo[i]);
        raiz = temp;

        // se inserta el nodo de la izquierda
        raiz->izquierdo = insertarenOrden(arreglo, raiz->izquierdo, 2 * i + 1, n);

        //  se inserta el nodo de la derecha
        raiz->derecho = insertarenOrden(arreglo, raiz->derecho, 2 * i + 2, n);
    }
    return raiz;
}