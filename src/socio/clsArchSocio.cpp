#include <iostream>
#include <cstring>
#include <cstdio>
#include "socio/clsArchSocio.h"
#include "socio/clsSocio.h"
#include "clsFecha.h"
#include "clsDomicilio.h"
#include "funciones.h"

using namespace std;

ArchivoSocios::ArchivoSocios(const char *n) {
    strcpy(nombre, n);
}

Socio ArchivoSocios::leerRegistro(int pos) {
    Socio obj;
    FILE *p = fopen(nombre, "rb");
    fseek(p, pos * sizeof obj, 0);
    if (pos < 0) {
        return obj; // RECREA EL OBJETO PARA QUE NO DEVUELVA BASURA
    }
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoSocios::grabarRegistro(Socio obj) {
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr) {
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoSocios::modificarRegistro(Socio obj, int pos) {
    FILE *p;
    p = fopen(nombre, "rb+");
    if(p == nullptr) {
        return false;
    }
    fseek(p, pos * sizeof obj, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoSocios::contarRegistros() {
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr) {
        return -1;
    }
    fseek(p, 0, 2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof (Socio);
}

int ArchivoSocios::buscarRegistro(const char *dni) {
    Socio obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++) {
        obj = leerRegistro(i);
        if(strcmp(obj.getDni(), dni) == 0) {
            return i;
        }
    }
    return -1;
}

bool Socio::Cargar(ArchivoSocios &arcSoc) {
    cout<<"INGRESE EL DNI: ";
    cargarCadena(dni,9);
        int pos = arcSoc.buscarRegistro(dni);
        bool estadoPos = arcSoc.leerRegistro(pos).getEstado();
        /// Verifica si el objeto de esa posicon esta inactivo/libre
        if (estadoPos==false) {

            cout<<"INGRESE EL NOMBRE: ";
            cargarCadena(nombre,29);
            cout<<"INGRESE EL APELLIDO: ";
            cargarCadena(apellido,29);
            cout<<"INGRESE LA FECHA DE NACIMIENTO: "<<endl;
            fechaNacimiento.Cargar();
            cout<<"INGRESE EL DOMICILIO: "<<endl;
            domicilio.Cargar();
            cout<<"INGRESE EL EMAIL: ";
            cargarCadena(email, 39);
            /// Cambia a true cuando se registra
            estado=true;
            return true;
        } else {
            cout << "DNI: [" << dni << "] YA EXISTENTE." << endl;
            return false;
        }
}

void ArchivoSocios::MostrarHeader() {
    cout << "                                                   ┌───────────────────────────────────────────────────────────┐\n";
    cout << "                                                   │ DOMICLIO                                                  │\n";
    cout << "┌────────────┬────────────┬────────────┬───────────┼────────────┬────────┬───────────┬────────────────┬────────┼──────────────────────────────┐\n";
    cout << "│ DNI        │ NOMBRE     │ APELLIDO   │ F. NAC    │ DIRECCION  │ ALTURA │ lOCALIDAD │ PARTIDO        │ CP     │ EMAIL                        │\n";
    cout << "├────────────┼────────────┼────────────┼───────────┼────────────┼────────┼───────────┼────────────────┼────────┼──────────────────────────────┤\n";
}

void Socio::Mostrar() {
    cout << "│ " << dni << espaciarTexto(dni, 11) << "│ " << nombre << espaciarTexto(nombre, 11) << "│ " << apellido << espaciarTexto(apellido, 11) << "│ ";
    fechaNacimiento.Mostrar();
    cout << "│ ";
    domicilio.Mostrar();
    cout << "│ " << email << espaciarTexto(email, 29) << "│" << endl;
    cout << "├────────────┼────────────┼────────────┼───────────┼────────────┼────────┼───────────┼────────────────┼────────┼──────────────────────────────┤\n";
}

void ArchivoSocios::Eliminar() {
    /// Llama la opcion de buscar y asi obtener el objeto
    Socio obj = Buscar();
    cout << endl;
    if (obj.getEstado())
    {
        cout << "ELIMINAR ESTE SOCIO? (S/N): ";
        char opc;
        cin >> opc;
        if (opc == 'S' || opc == 's') {

            obj.setEstado(false);
            /// "buscarRegistro(obj.getDni())": Obtiene el objeto, consigue su dni, y se lo manda a la funcion de buscar para obtener su posicion.
            modificarRegistro(obj, buscarRegistro(obj.getDni()));
            cout << "SOCIO [" << obj.getDni() << "] ELIMINADO" << endl;
        }
    }

}
Socio ArchivoSocios::Buscar() {
    char dni[10];
    cout << ">> Ingrese DNI socio: ";
    cargarCadena(dni,9);
    /// Busca el dni en el registro y obtiene la posicione
    int pos = buscarRegistro(dni);
    if(pos != -1) {
        Socio obj = leerRegistro(pos);
        MostrarHeader();
        /// Muestra el objeto de esa posicon
        obj.Mostrar();
        /// Devuelve el objeto para usarlo en la funcion de Eliminar, el problema es que si no buscamos eliminar no tiene utilidad
        return obj;
    } else {
        cout << "DNI NO ENCONTRADO." << endl;
        /// Crea un objeto auxiliar
        Socio aux;
        /// Setea el estado en false
        aux.setEstado(false);
        return aux;
    }
}
void ArchivoSocios::Registrar() {
    Socio obj;
    if (obj.Cargar(*this)) {
        grabarRegistro(obj);
    }
}

void ArchivoSocios::Listar() {

    MostrarHeader();
    Socio obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++) {
        obj = leerRegistro(i);
        /// Verifica si el objeto a mostrar esta activo
        if (obj.getEstado()) {
            obj.Mostrar();
        }
    }
}

