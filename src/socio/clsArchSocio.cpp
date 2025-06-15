#include <iostream>
#include <cstring>
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

    if (arcSoc.buscarRegistro(dni) == -1) {
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
        estado=true;
        return true;
    } else {
        cout << "DNI: [" << dni << "] YA EXISTENTE." << endl;
        return false;
    }
}

void Socio::Mostrar() {

    char nombreCompleto[60];

    strcpy(nombreCompleto, nombre);
    strcat(nombreCompleto, ", ");
    strcat(nombreCompleto, apellido);


/*
    char domCompleto[60];

    strcpy(domCompleto, domicilio.getCalle());
    strcat(domCompleto, ", ");
    strcat(domCompleto, domicilio.getAltura());
    strcat(domCompleto, ", ");
    strcat(domCompleto, domicilio.getLocalidad());
    strcat(domCompleto, ", ");
    strcat(domCompleto, domicilio.getPartido());*/

    //string nombreCompleto = string(nombre) + ", " + string(apellido);
    cout << " " << dni << espaciarTexto(dni, 10) << "│ " << nombreCompleto << espaciarTexto(nombreCompleto, 20) << "│ "; fechaNacimiento.Mostrar(); cout << "│ " << email << endl;

    cout << "───────────┼─────────────────────┼───────────┼───────────────────";
    //domicilio.Mostrar();
}
void ArchivoSocios::EliminarSocio() {
    char dni[10];
    cout << "INGRESE DNI A ELIMINAR: ";
    cargarCadena(dni,9);
    int pos = buscarRegistro(dni);
    if (pos > -1) {
        Socio obj = leerRegistro(pos);
        obj.setEstado(false);
        modificarRegistro(obj, pos);
        cout << "SOCIO [" << dni << "] ELIMINADO" << endl;
    } else {
        cout << "DNI NO ENCONTRADO." << endl;
    }
}
void ArchivoSocios::MostrarBusqueda() {
    char dni[10];
    cout << ">> Ingrese DNI socio: ";
    cargarCadena(dni,9);
    int pos = buscarRegistro(dni);
    if(pos != -1) {
        Socio obj = leerRegistro(pos);
        obj.Mostrar();
        cout << endl;
    } else {
        cout << "DNI NO ENCONTRADO." << endl;
    }
}

void ArchivoSocios::RegistrarSocio() {
    Socio obj;
    if (obj.Cargar(*this)) {
        grabarRegistro(obj);
    }
}

void ArchivoSocios::ListarSocios() {

    cout << " DNI       │ NOMBRE              │ F. NAC    │ EMAIL       \n";
    cout << "───────────┼─────────────────────┼───────────┼───────────────────\n";
    Socio obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++) {
        obj = leerRegistro(i);
        if (obj.getEstado()) {
            obj.Mostrar();
            cout << endl;
        }
    }
    //cout << "╚════════════╩══════════════╩══════════════╩════════════════════╩════════════════════╝\n";
}
