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
    if (arcSoc.buscarRegistro(dni) == -1) {

        cout<<"INGRESE EL NOMBRE: ";
        cargarCadena(nombre,29);
        cout<<"INGRESE EL APELLIDO: ";
        cargarCadena(apellido,29);
        cout<<"INGRESE LA FECHA DE NACIMIENTO: " << endl;
        fechaNacimiento.Cargar();
        cout<<"INGRESE EL DOMICILIO: " << endl;
        domicilio.Cargar();
        cout<<"INGRESE EL EMAIL: ";
        cargarCadena(email, 39);
        return true;
    } else {
        cout << "DNI: [" << dni << "] YA EXISTENTE." << endl;
        return false;
    }
}

void ArchivoSocios::MostrarHeader() {
    Socio obj;
    for (int i=0; i < contarRegistros(); i++) {
        if (strcmp(leerRegistro(i).getDni(), "-1") != 0) {
            cout << "                                                   ┌───────────────────────────────────────────────────────────┐\n";
            cout << "                                                   │ DOMICLIO                                                  │\n";
            cout << "┌────────────┬────────────┬────────────┬───────────┼────────────┬────────┬───────────┬────────────────┬────────┼──────────────────────────────┐\n";
            cout << "│ DNI        │ NOMBRE     │ APELLIDO   │ F. NAC    │ DIRECCION  │ ALTURA │ LOCALIDAD │ PARTIDO        │ CP     │ EMAIL                        │\n";
            cout << "├────────────┼────────────┼────────────┼───────────┼────────────┼────────┼───────────┼────────────────┼────────┼──────────────────────────────┤\n";
            break;
        }
    }
}

void Socio::Mostrar() {

    cout << "│ " << dni << espaciarTexto(dni, 11)
         << "│ " << nombre << espaciarTexto(nombre, 11)
         << "│ " << apellido << espaciarTexto(apellido, 11)
         << "│ ";
    fechaNacimiento.Mostrar();
    cout << "│ ";
    domicilio.Mostrar();
    cout << "│ " << email << espaciarTexto(email, 29) << "│" << endl;
    cout << "├────────────┼────────────┼────────────┼───────────┼────────────┼────────┼───────────┼────────────────┼────────┼──────────────────────────────┤\n";
}

void ArchivoSocios::Eliminar() {
    /// Llama la opcion de buscar y asi obtener el objeto
    char dni[10];
    cout << ">> Ingrese DNI socio a eliminar: ";
    cargarCadena(dni,9);
    int pos = buscarRegistro(dni);
    Socio obj = Buscar(dni, "-1");
    cout << endl;

    if (strcmp(obj.getDni(), "-1") != 0) {
        cout << "ELIMINAR ESTE SOCIO? (S/N): ";
        char opc;
        cin >> opc;
        if (opc == 'S' || opc == 's') {
            /// Busca la posicion en el regsitro del DNI
            int pos = buscarRegistro(obj.getDni());
            obj.setDni("-1");

            /// Modifica el objeto en esa posicion
            modificarRegistro(obj, pos);
            cout << "SOCIO ELIMINADO" << endl;
        }
    }
}

Socio ArchivoSocios::Buscar(const char* pal1, const char* pal2) {
    int pos=-1;

    if (strcmp(pal1, "-1") != 0 && strcmp(pal2, "-1") == 0 )
    {
        pos = buscarRegistro(pal1);
    }
    else if (strcmp(pal1, "-1") != 0 || strcmp(pal2, "-1") != 0)
    {
        for (int i=0; i < contarRegistros(); i++) {
            if (strcmp(leerRegistro(i).getNombre(),pal1) == 0 && strcmp(leerRegistro(i).getApellido(),pal2) == 0) {
                /// Consigue la posicion en el registro gracias al DNI
                pos = buscarRegistro(leerRegistro(i).getDni());
                break;
            }
        }
    }
    /// Busca el dni o el nombre en el registro y obtiene la posicione
    if(pos != -1) {
        Socio obj = leerRegistro(pos);
        MostrarHeader();
        /// Muestra el objeto de esa posicon
        obj.Mostrar();
        /// Devuelve el objeto para usarlo en la funcion de Eliminar, el problema es que si no buscamos eliminar no tiene utilidad
        return obj;

    } else {
        cout << "SOCIO NO ENCONTRADO." << endl;
        /// Crea un objeto auxiliar
        Socio aux;
        /// Setea el estado en false
        aux.setDni("-1");
        return aux;
    }
/*
    int pos=-1;
    /// opc = 1, Buscar por dni
    /// opc = 2, Buscar por Nombre
    if (opc == 1) {
        char dni[10];
        cout << ">> Ingrese DNI socio: ";
        cargarCadena(dni,9);
        pos = buscarRegistro(dni);
    } else {
        char nombre[29];
        cout << ">> Ingrese Nombre socio: ";
        cargarCadena(nombre,29);
        char apellido[29];
        cout << "Ingrese apellido: ";
        cargarCadena(apellido,29);
        /// Busca en todos los registros si coinciden nombre y apellido
        for (int i=0; i < contarRegistros(); i++) {
            if (strcmp(leerRegistro(i).getNombre(),nombre) == 0 && strcmp(leerRegistro(i).getApellido(),apellido) == 0) {
                /// Consigue la posicion en el registro gracias al DNI
                pos = buscarRegistro(leerRegistro(i).getDni());
                break;
            }
        }

    }*/
}
void ArchivoSocios::Registrar() {
    Socio obj;
    if (obj.Cargar(*this)) {
        int posLibre = -1;
        for (int i = 0; i < contarRegistros(); i++) {
                /// Busca la posicion libre (DNI = -1) y la guarda en una variable
            if (strcmp(leerRegistro(i).getDni(), "-1") == 0) {
                posLibre = i;
                break;
            }
        }
        /// Verifica si existe posicion libre
        if (posLibre != -1) {
        /// Escribe en esa posicion
            modificarRegistro(obj, posLibre);
        } else {
        /// Si no la encuentra, guarda en una nueva posicion
            grabarRegistro(obj);
        }
    }
}

void ArchivoSocios::Listar() {

    MostrarHeader();
    Socio obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++) {
        obj = leerRegistro(i);
        /// Verifica si esta ocupada la direccion para mostrarla
        if (strcmp(leerRegistro(i).getDni(), "-1") != 0){
            obj.Mostrar();
        }
    }
}

