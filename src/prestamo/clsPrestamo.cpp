#include <iostream>
#include <cstring>
#include "prestamo/clsPrestamo.h"

void Prestamo::setEstado(bool e) {
    estado = e;
}

bool Prestamo::getEstado() {
    return estado;
}

void Prestamo::setIdPrestamo(int id) {
    idPrestamo = id;
}
void Prestamo::setDniSocio(const char *d) {
    strcpy(dniSocio, d);
}
void Prestamo::setISBN(const char *i) {
    strcpy(isbn, i);
}
void Prestamo::setFechaPrestamo(Fecha f) {
    fechaPrestamo = f;
}
void Prestamo::setFechaDevolucion(Fecha f) {
    fechaDevolucion = f;
}

int Prestamo::getIdPrestamo() {
    return idPrestamo;
}
const char* Prestamo::getDniSocio() {
    return dniSocio;
}
const char* Prestamo::getISBN() {
    return isbn;
}
Fecha Prestamo::getFechaPrestamo() {
    return fechaPrestamo;
}
Fecha Prestamo::getFechaDevolucion() {
    return fechaDevolucion;
}

