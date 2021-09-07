template <typename T>
struct Nodo // este se usa para crear los arboles con los nodos necesarios 
{
    T datos;
    Nodo *cabeza;
    Nodo *cola;
    Nodo(T da, Nodo *cab, Nodo *col)
    {
        datos = da;
        cabeza = cab;
        cola = col;
    }
};