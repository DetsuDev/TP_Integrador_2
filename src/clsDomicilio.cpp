#include <iostream>
#include <cstring>

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
    cout << " DIRECCION: "<<calle<<" "<<altura<<endl;
    cout << " LOCALIDAD: "<<localidad<<endl;
    cout << " PARTIDO: "<<partido<<endl;
    cout << " CODIGO POSTAL: "<<codigoPostal<<endl;
}

// Setters
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

// Getters
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
