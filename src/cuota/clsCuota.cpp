#include <iostream>
#include <cstring>
#include "cuota/clsCuota.h"

const char* Cuota::getDni(){
    return dni;
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


void Cuota::setDni(const char *i){
    strcpy(dni, i);
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
