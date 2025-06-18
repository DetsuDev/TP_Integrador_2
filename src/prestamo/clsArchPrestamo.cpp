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
    Libro libro;
    Prestamo prestamo;
    cout << "DNI DEL SOCIO: ";
    cargarCadena(dniSocio, 9);
    // IMPLEMENTACION USANDO EL ESTADO
    int socioPos = arcSoc.buscarRegistro(dniSocio);
    cout << socioPos;


    if (socioPos != -1) {
        cout << "ISBN DEL LIBRO: ";
        cargarCadena(isbn, 19);

        int ejemplares = libro.getCantidadEjemplares();
        int isbnPos = arcLibr.buscarRegistro(isbn);

        if (isbnPos != -1) { /// Chequea si esta en el registro
            if (ejemplares > 0) { /// chequea si hay unidades disponibles
                cout << "FECHA DEL PRÉSTAMO: ";
                fechaPrestamo.Cargar();
                cout << "FECHA DE DEVOLUCIÓN: ";
                fechaDevolucion.Cargar();

                libro.setCantidadEjemplares(ejemplares -1);
                srand(time(0));
                idPrestamo = rand() % 100000 + 1;
                /// Modifica el objeto en esa posicion
                arcPrest.modificarRegistro(prestamo, socioPos);
                return true;

            } else {
                cout << "NO HAY EJEMPLARES DISPONIBLES" << endl;
                return false;
            }

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

    char idStr[10];
    sprintf(idStr, "%d", idPrestamo);

    cout << " " << espaciarTexto(idStr, MasLargoID)
         << " │ " << espaciarTexto(dniSocio, MasLargoDNI)
         << " │ " << espaciarTexto(isbn, MasLargoISBN)
         << " │ " << fechaPrestamo.getFechaCompleta()
         << " │ " << fechaDevolucion.getFechaCompleta() << "\n";

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




Prestamo ArchivoPrestamo::MostrarBusqueda(int pos) {
    if(pos != -1) {
        MostrarHeader();
        Prestamo obj = leerRegistro(pos);
        /// Muestra el objeto de esa posicon
        obj.Mostrar();
        /// Devuelve el objeto para usarlo en la funcion de Eliminar, el problema es que si no buscamos eliminar no tiene utilidad

        cout << endl;
        return obj;
    } else {
        /// Crea un objeto auxiliar
        Prestamo aux;
        /// Setea el ISBN en -1
        aux.setISBN("-1");
        return aux;
    }
}


void ArchivoPrestamo::Eliminar() {
    cout << "INGRESE EL ID del PRESTAMO a eliminar: ";
    int idPrestamo;
    cin >> idPrestamo;

    int pos = buscarRegistro(idPrestamo);
    if (pos == -1) {
        cout << "PRÉSTAMO NO ENCONTRADO" << endl;
        return;
    }

    Prestamo obj = leerRegistro(pos);

    cout << "ELIMINAR ESTE PRESTAMO? (S/N): ";
    char opc;
    cin >> opc;

    if (opc == 'S' || opc == 's') {
        /// Marcar el préstamo como eliminado
        obj.setIdPrestamo(-1);
        modificarRegistro(obj, pos);
        cout << "PRÉSTAMO ELIMINADO" << endl;

        /// SUMAR CANTIDAD AL LIBRO
        ArchivoLibros arcLibros;
        int posLibro = arcLibros.buscarRegistro(obj.getISBN());

        if (posLibro != -1) {
            Libro lib = arcLibros.leerRegistro(posLibro);
            lib.setCantidadEjemplares(lib.getCantidadEjemplares() + 1);
            arcLibros.modificarRegistro(lib, posLibro);
            cout << "Se devolvió 1 ejemplar al libro con ISBN " << obj.getISBN() << endl;
        } else {
            cout << "ERROR: No se encontró el libro con ISBN: " << obj.getISBN() << endl;
        }
    }
}


// lee el archivo de libros y los muestra en pantalla
void ArchivoPrestamo::Listar() {
    MostrarHeader();
    Prestamo obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++) {
        obj = leerRegistro(i);
        /// Verifica si esta ocupada la direccion para mostrarla
        if (leerRegistro(i).getIdPrestamo() > -1) {
            obj.Mostrar();
        }
    }

}
