#include <iostream>
#include <cstring>
#include "prestamo/clsArchPrestamo.h"
#include "socio/clsArchSocio.h"
#include "libro/clsArchLibro.h"
#include "funciones.h"
#include <ctime>

using namespace std;

ArchivoPrestamo::ArchivoPrestamo(const char *n) {
    strcpy(nombre, n);
}

Prestamo ArchivoPrestamo::leerRegistro(int pos) {
    Prestamo obj;
    FILE *p = fopen(nombre, "rb");
    fseek(p, pos * sizeof obj, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoPrestamo::grabarRegistro(Prestamo obj) {
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr) {
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoPrestamo::modificarRegistro(Prestamo obj, int pos) {
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

int ArchivoPrestamo::contarRegistros() {
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr) {
        return -1;
    }
    fseek(p, 0, 2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof (Prestamo);
}

int ArchivoPrestamo::buscarRegistro(const char *idPrestamo) {
    Prestamo obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++) {
        obj = leerRegistro(i);
        if(obj.getIdPrestamo() == *idPrestamo) {
            return i;
        }
    }
    return -1;
}

bool Prestamo::Cargar(ArchivoPrestamo &arcPrest) {
    ArchivoSocios arcSoc;
    ArchivoLibros arcLibr;

    cout << "DNI DEL SOCIO: ";
    cargarCadena(dniSocio, 9);

    // IMPLEMENTACION USANDO EL ESTADO
    int socioPos = arcSoc.buscarRegistro(dniSocio);
    cout << socioPos;
    bool socioExiste = arcSoc.leerRegistro(socioPos).getEstado();
    cout << socioExiste;

    if (socioExiste /*&& socioPos > -1*/) {
        cout << "ISBN DEL LIBRO: ";
        cargarCadena(isbn, 19);

        int isbnPos = arcLibr.buscarRegistro(isbn);
        bool isbnExiste = arcSoc.leerRegistro(isbnPos).getEstado();
        if (isbnExiste) { // CHEQUEA SOLO SI ESTA EN EL REGISTRO, NO SI ESTA ACTIVO
            cout << "FECHA DEL PRÉSTAMO: ";
            fechaPrestamo.Cargar();
            cout << "FECHA DE DEVOLUCIÓN: ";
            fechaDevolucion.Cargar();

            srand(time(0));
            idPrestamo = rand() % 100000 + 1;
            return true;
        } else {
            cout << "ISBN NO EXISTENTE" << endl;
            return false;
        }
    } else {
        cout << "DNI NO EXISTENTE" << endl;
        return false;
    }
}

void Prestamo::Mostrar() {
    cout << "ID PRÉSTAMO: " << idPrestamo << endl;
    cout << "DNI SOCIO: " << dniSocio << endl;
    cout << "ISBN LIBRO: " << isbn << endl;
    cout << "FECHA PRÉSTAMO: ";
    fechaPrestamo.Mostrar();
    cout << "FECHA DEVOLUCIÓN: ";
    fechaDevolucion.Mostrar();
}

void ArchivoPrestamo::RegistrarPrestamo() {
    Prestamo obj;

    if (obj.Cargar(*this)) {
        grabarRegistro(obj);
    }
}

void ArchivoPrestamo::ListarPrestamo() {
    Prestamo obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++) {
        obj = leerRegistro(i);
        if (obj.getEstado()) {
            obj.Mostrar();
            cout << endl;
        }
    }
}
