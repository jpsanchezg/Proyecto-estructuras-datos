#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

bool Existencia(string codigo, list<divipola> DiviLista);


void Listar_Departamentos(list<divipola> DiviLista);

void Listar_Municipios(string codigodepto, list<divipola> DiviLista);

void Listar_Poblaciones(string codigoMunicipio, list<divipola> DiviLista);

void Informacion(string codigodepto, list<divipola> DiviLista);

void estaEnSistema(string codigoMunicipio, list<SistemaCiudades> SClista, list<divipola> DiviLista);

void ayuda(string menuayuda,bool &comandoEncontrado);

#endif