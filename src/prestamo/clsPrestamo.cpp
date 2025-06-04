#include <iostream>
#include <cstring>
#include "prestamo/clsPrestamo.h"
#include "funciones.h"

using namespace std;

void Prestamo::Cargar() {
    cout << "DNI DEL SOCIO: ";
    cargarCadena(dniSocio, 9);
    cout << "ISBN DEL LIBRO: ";
    cargarCadena(isbn, 19);
    cout << "FECHA DEL PRÉSTAMO: ";
    fechaPrestamo.Cargar();
    cout << "FECHA DE DEVOLUCIÓN: ";
    fechaDevolucion.Cargar();
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

void Prestamo::setIdPrestamo(int id) { idPrestamo = id; }
void Prestamo::setDniSocio(const char *d) { strcpy(dniSocio, d); }
void Prestamo::setISBN(const char *i) { strcpy(isbn, i); }
void Prestamo::setFechaPrestamo(Fecha f) { fechaPrestamo = f; }
void Prestamo::setFechaDevolucion(Fecha f) { fechaDevolucion = f; }

int Prestamo::getIdPrestamo() { return idPrestamo; }
const char* Prestamo::getDniSocio() { return dniSocio; }
const char* Prestamo::getISBN() { return isbn; }
Fecha Prestamo::getFechaPrestamo() { return fechaPrestamo; }
Fecha Prestamo::getFechaDevolucion() { return fechaDevolucion; }
