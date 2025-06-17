#include <iostream>
#include <cstring>
#include "clsFecha.h"

#include "funciones.h"


using namespace std;

Fecha::Fecha(int d, int m, int a) {
    dia = d;
    mes = m;
    anio = a;
}
void Fecha::setDia(int d) {
    dia = d;
}
void Fecha::setMes(int m) {
    mes = m;
}
void Fecha::setAnio(int a) {
    anio = a;
}
int Fecha::getDia() {
    return dia;
}
int Fecha::getMes() {
    return mes;
}
int Fecha::getAnio() {
    return anio;
}
void Fecha::Cargar() {
    cout<<"DIA: ";
    cin>>dia;
    cout<<"MES: ";
    cin>>mes;
    cout<<"ANIO: ";
    cin>>anio;
}
void Fecha::Mostrar() {

    /// Convierte los INT a CHAR
    char diaStr[3];
    char mesStr[3];
    char anioStr[5];
    sprintf(diaStr, "%d", dia);
    sprintf(mesStr, "%d", mes);
    sprintf(anioStr, "%d", anio);

    /// Los concatena para crear la fecha completa
    char fechaCompleta[11];
    strcpy(fechaCompleta, diaStr);
    strcat(fechaCompleta, "/");
    strcat(fechaCompleta, mesStr);
    strcat(fechaCompleta, "/");
    strcat(fechaCompleta, anioStr);


    cout << espaciarTexto(fechaCompleta, 10);
}
