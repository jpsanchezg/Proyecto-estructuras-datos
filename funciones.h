#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

bool ExistenciaDepto(string codigo, list<datosdept> &lista);

bool ExistenciaMun(string codigo, list<datosMun> &lista);

void Cargar_divipola(list<datosdept> &departamento, list<datosMun> &municipio, list<DatosPob> &poblacion);

void cargar_SC(list<SistemaCiudades> &SClista);

void Listar_Departamentos(list<datosdept> departamento, list<datosMun> municipio, list<DatosPob> poblacion);

void Listar_Municipios(string codigodepto, list<datosdept> departamento, list<datosMun> municipios, list<DatosPob> poblacion);

void Listar_Poblaciones(string codigoMunicipio, list<DatosPob> poblacion);

vector<string> Informacion(string codigodepto, list<datosdept> departamento, list<datosMun> municipio, list<DatosPob> poblacion);

void estaEnSistema(string codigoMunicipio, list<SistemaCiudades> SClista, list<datosMun> municipio);

void ayuda(string menuayuda, bool &comandoEncontrado);

vector<string> buscarpoblacion(string codigomun, string codigopob, list<datosMun> municipio);

#endif