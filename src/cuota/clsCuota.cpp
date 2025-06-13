#include <iostream>
#include <cstring>
#include "cuota/clsCuota.h"


int Cuota::getNumeroSocio() {
    return numeroSocio;
}
Fecha Cuota::getFechaPago() {
    return fechaPago;
}
float Cuota::getImporte() {
    return importe;
}
int Cuota::getMes() {
    return mes;
}
int Cuota::getAnio() {
    return anio;
}
void Cuota::setEstado(bool e) {
    estado = e;
}

bool Cuota::getEstado() {
    return estado;
}

void Cuota::setNumeroSocio(int num) {
    numeroSocio = num;
}
void Cuota::setFechaPago(Fecha f) {
    fechaPago = f;
}
void Cuota::setImporte(float imp) {
    importe = imp;
}
void Cuota::setMes(int m) {
    mes = m;
}
void Cuota::setAnio(int a) {
    anio = a;
}
