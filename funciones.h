#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

bool ExistenciaDepto(string codigo, list<datosDiv> &lista);

bool ExistenciaMun(string codigo, list<datosDiv> &lista);

void Cargar_divipola(list<datosDiv> &departamento, list<datosDiv> &municipio, list<DatosPob> &poblacion);

void cargar_SC(list<SistemaCiudades> &SClista);

void Listar_Departamentos(list<datosDiv> departamento, list<datosDiv> municipio, list<DatosPob> poblacion);

void Listar_Municipios(string codigodepto, list<datosDiv> municipios);

void Listar_Poblaciones(string codigoMunicipio, list<DatosPob> poblacion);

vector<string> Informacion(string codigodepto, list<datosDiv> departamento, list<datosDiv> municipio, list<DatosPob> poblacion);

void estaEnSistema(string codigoMunicipio, list<SistemaCiudades> SClista, list<datosDiv> municipio);

void ayuda(string menuayuda, bool &comandoEncontrado);

void capitalesmenores(list<SistemaCiudades> SClista, list<ciudadescapitales> &CiuCap);

void reporte(list<SistemaCiudades> SClista);

int totalaglomeracionesUrbanas(list<SistemaCiudades> SClista);

int Accion_Aglomeracion(list<Aglomeracion> Aglomeraciones, int indicador, Municipios_Ciudades Elemento, string Funcion);

void Crear_Aglomeraciones(list<SistemaCiudades> SClista, list<Aglomeracion> &Aglomeraciones);

void Crear_Uninodales(list<SistemaCiudades> SClista, list<Municipios_Ciudades> &Ciudades_Uninodales);

#endif