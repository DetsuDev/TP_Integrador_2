#include <iostream>
#include <cstring>
#include "clsFecha.h"
#include "clsDomicilio.h"
#include "socio/clsSocio.h"

void Socio::setEstado(bool e) {
    estado = e;
}

bool Socio::getEstado() {
    return estado;
}

void Socio::setDni(const char *i) {
    strcpy(dni, i);
}

void Socio::setNombre(const char *e) {
    strcpy(nombre, e);
}

void Socio::setApellido(const char *e) {
    strcpy(apellido, e);
}

void Socio::setEmail(const char *e) {
    strcpy(email, e);
}

void Socio::setFechaNacimiento(Fecha f) {
    fechaNacimiento = f;
}

void Socio::setDomicilio(Domicilio d) {
    domicilio = d;
}

Domicilio& Socio::getDomicilio() {
    return domicilio;
}

Fecha& Socio::getFechaNacimiento() {
    return fechaNacimiento;
}

const char* Socio::getDni() {
    return dni;
}

const char* Socio::getNombre() {
    return nombre;
}
