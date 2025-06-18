#include <iostream>
#include <cstring>
#include "prestamo/clsPrestamo.h"
#include "clsFecha.h"



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

/*void Prestamo::setFechaCompleta(Fecha obj){
    Fecha fecha;
    sprintf(fecha.fechaCompleta, "%02d/%02d/%04d", dia, mes, anio);
}*/
