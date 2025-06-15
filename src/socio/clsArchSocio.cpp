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
    Socio obj = Buscar();
    cout << endl;
    cout << "ELIMINAR ESTE SOCIO? (S/N): ";
    char opc;
    cin >> opc;
    if (opc == 'S' || opc == 's') {

        obj.setEstado(false);
        modificarRegistro(obj, buscarRegistro(obj.getDni()));
        cout << "SOCIO [" << obj.getDni() << "] ELIMINADO" << endl;
    }
}
Socio ArchivoSocios::Buscar() {
    char dni[10];
    cout << ">> Ingrese DNI socio: ";
    cargarCadena(dni,9);
    int pos = buscarRegistro(dni);
    if(pos != -1) {
        Socio obj = leerRegistro(pos);
        MostrarHeader();
        obj.Mostrar();
        return obj;
    } else {
        cout << "DNI NO ENCONTRADO." << endl;
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
        if (obj.getEstado()) {
            obj.Mostrar();
        }
    }
}

