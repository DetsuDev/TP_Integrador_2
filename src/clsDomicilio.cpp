#include <iostream>
#include <cstring>

#include <cstdio>
#include "clsDomicilio.h"
#include "funciones.h"

using namespace std;

void Domicilio::Cargar() {
    cout << "INGRESE LA CALLE: ";
    cargarCadena(calle, 29);
    cout << "INGRESE LA ALTURA: ";
    cin >>altura;
    cout << "INGRESE LA LOCALIDAD: ";
    cargarCadena(localidad, 29);
    cout << "INGRESE EL PARTIDO: ";
    cargarCadena(partido, 29);
    cout << "INGRESE EL CODIGO POSTAL: ";
    cargarCadena(codigoPostal,5);
}

void Domicilio::Mostrar() {
    char alturaStr[10];
    sprintf(alturaStr, "%d", altura);
    cout << calle << espaciarTexto(calle, 11) << "│ " << altura << espaciarTexto(alturaStr, 7) << "│ " << localidad << espaciarTexto(localidad, 10)
         << "│ " << partido << espaciarTexto(partido, 15) << "│ " << codigoPostal << espaciarTexto(codigoPostal, 7);
}

void Domicilio::setCalle(const char *e) {
    strcpy(calle, e);
}

void Domicilio::setAltura(int a) {
    altura = a;
}

void Domicilio::setLocalidad(const char *e) {
    strcpy(localidad, e);
}

void Domicilio::setPartido(const char *e) {
    strcpy(partido, e);
}

void Domicilio::setCodPostal(const char *e) {
    strcpy(codigoPostal, e);
}

const char* Domicilio::getCalle() {
    return calle;
}

int Domicilio::getAltura() {
    return altura;
}

const char* Domicilio::getLocalidad() {
    return localidad;
}

const char* Domicilio::getPartido() {
    return partido;
}

const char* Domicilio::getCodPostal() {
    return codigoPostal;
}
