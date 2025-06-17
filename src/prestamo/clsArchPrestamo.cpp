#include <iostream>
#include <cstring>
#include "prestamo/clsArchPrestamo.h"
#include "socio/clsArchSocio.h"
#include "libro/clsArchLibro.h"
#include "funciones.h"
#include <ctime>
#include <vector>

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

int ArchivoPrestamo::buscarRegistro(int idPrestamo) {
    Prestamo obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++) {
        obj = leerRegistro(i);
        if(obj.getIdPrestamo() == idPrestamo) {
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


    if (socioPos != -1) {
        cout << "ISBN DEL LIBRO: ";
        cargarCadena(isbn, 19);

        int isbnPos = arcLibr.buscarRegistro(isbn);
        if (isbnPos != -1) { // CHEQUEA SOLO SI ESTA EN EL REGISTRO, NO SI ESTA ACTIVO
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
vector<int> ArchivoPrestamo::BuscarMasLargo() {

    int MasLargoID = strlen("ID PREST.");
    int MasLargoDNI = strlen("DNI SOCIO");
    int MasLargoISBN = strlen("ISBN");

    for (int i=0; i < contarRegistros(); i++) {
        for (int i = 0; i < contarRegistros(); i++) {
            Prestamo prest = leerRegistro(i);
            char idStr[10];
            sprintf(idStr, "%d", prest);
            int lenID = strlen(idStr);
            int lenDNI = strlen(prest.getDniSocio());
            int lenISBN = strlen(prest.getISBN());

            if (lenID > MasLargoID) {
                MasLargoID = lenID;
            }
            if (lenDNI > MasLargoDNI) {
                MasLargoDNI = lenDNI;
            }
            if (lenISBN > MasLargoISBN) {
                MasLargoISBN = lenISBN;
            }
        }
    }
    return {MasLargoID, MasLargoDNI, MasLargoISBN};
}

void Prestamo::Mostrar() {


    ArchivoPrestamo arcPrestamo;
    vector<int> largos = arcPrestamo.BuscarMasLargo();
    int MasLargoID = largos[0];
    int MasLargoDNI = largos[1];
    int MasLargoISBN = largos[2];

    /*
        char id[] = "ID PREST.";
        char dni[] = "DNI SOCIO";
        char isbn[] = "ISBN";
        char fechaPr[] = "FECHA PR.";
        char fechaDev[] = "FECHA DEV.";*/


    char idStr[10];
    sprintf(idStr, "%d", idPrestamo);

    cout << " " << espaciarTexto(idStr, MasLargoID)
         << " │ " << espaciarTexto(dniSocio, MasLargoDNI)
         << " │ " << espaciarTexto(isbn, MasLargoISBN) << " │ ";
    fechaPrestamo.Mostrar();
    cout << " │ ";
    fechaDevolucion.Mostrar();
    cout << "\n";


    /*
    cout << "│ " << idPrestamo
         << "│ " << dniSocio << espaciarTexto(dniSocio, 11)
         << "│ " << isbn
         << "│ ";
    fechaPrestamo.Mostrar();
    cout << "│ ";
    fechaDevolucion.Mostrar();
    cout << "\n";
    cout << "├────────────┼────────────┼────────────┼───────────┼────────────┤\n";*/
}

void ArchivoPrestamo::MostrarHeader() {
    vector<int> largos = BuscarMasLargo();
    int MarLargoID = largos[0];
    int MasLargoDNI = largos[1];
    int MasLargoISBN = largos[2];
    char id[] = "ID PREST.";
    char dni[] = "DNI SOCIO";
    char isbn[] = "ISBN";
    char fechaPr[] = "FECHA PR.";
    char fechaDev[] = "FECHA DEV.";

    cout << " " << espaciarTexto(id, MarLargoID)
         << " │ " << espaciarTexto(dni, MasLargoDNI)
         << " │ " << espaciarTexto(isbn, MasLargoISBN)
         << " │ " << espaciarTexto(fechaPr, 10)
         << " │ " << espaciarTexto(fechaDev, 9) << "\n";
}



void ArchivoPrestamo::Registrar() {
    Prestamo obj;
    if (obj.Cargar(*this)) {
        int posLibre = -1;
        for (int i = 0; i < contarRegistros(); i++) {
            /// Busca la posicion libre (PRESTAMOID = -1) y la guarda en una variable
            if (leerRegistro(i).getIdPrestamo() > -1) {
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


void ArchivoPrestamo::Eliminar() {
    Prestamo obj;
    /// Llama la opcion de buscar y asi obtener el objeto
    //int idPrestamo;
    cout << "INGRESE EL ID del PRESTAMO: ";
    int idPrestamo;
    cin >> idPrestamo;
    int pos = buscarRegistro(idPrestamo);
    obj = leerRegistro(pos);
    cout << endl;

    if (obj.getIdPrestamo() != -1) {
        cout << "ELIMINAR ESTE PRESTAMO? (S/N): ";
        char opc;
        cin >> opc;
        if (opc == 'S' || opc == 's') {
            /// Busca la posicion en el regsitro del DNI
            int pos = buscarRegistro(obj.getIdPrestamo());
            obj.setIdPrestamo(-1);

            /// Modifica el objeto en esa posicion
            modificarRegistro(obj, pos);
            cout << "PRESTAMO ELIMINADO" << endl;
        }
    }


}

// lee el archivo de libros y los muestra en pantalla
void ArchivoPrestamo::Listar() {
    MostrarHeader();
    Prestamo obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++)
    {
        obj = leerRegistro(i);
        /// Verifica si esta ocupada la direccion para mostrarla
        if (leerRegistro(i).getIdPrestamo() > -1) {
            obj.Mostrar();
        }
    }

}
