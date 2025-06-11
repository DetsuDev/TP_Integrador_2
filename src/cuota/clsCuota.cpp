#include <iostream>
#include <cstring>
#include "cuota/clsCuota.h"
#include "cuota/clsArchCuota.h"
#include "funciones.h"

using namespace std;

void Cuota::Cargar() {
    cout << "INGRESE NÚMERO DE SOCIO: ";
    cin >> numeroSocio;

    cout << "INGRESE FECHA DE PAGO: " << endl;
    fechaPago.Cargar();

    cout << "INGRESE IMPORTE: ";
    cin >> importe;

    cout << "INGRESE MES: ";
    cin >> mes;

    cout << "INGRERE AÑO: ";
    cin >> anio;
}

void Cuota::Mostrar() {
    cout << "NÚMERO DE SOCIO: " << numeroSocio << endl;
    cout << "FECHA DE PAGO: ";
    fechaPago.Mostrar();
    cout << "IMPORTE: $" << importe << endl;
    cout << "MES: " << mes << " - AÑO: " << anio << endl;
}




void Cuota::registrarCuota()
{

    Cuota cuota;
    ArchivoCuotas archCuot;

    cuota.Cargar();
    archCuot.grabarRegistro(cuota);
}

void Cuota::listarCuota()
{

    ArchivoCuotas archCuot;
    Cuota cuota;

    int cantReg = archCuot.contarRegistros();

    for(int i=0; i<cantReg; i++)
    {
        cuota = archCuot.leerRegistro(i);
        cuota.Mostrar();
        cout << endl;
    }

}


// Getters
int Cuota::getNumeroSocio() { return numeroSocio; }
Fecha Cuota::getFechaPago() { return fechaPago; }
float Cuota::getImporte() { return importe; }
int Cuota::getMes() { return mes; }
int Cuota::getAnio() { return anio; }

// Setters
void Cuota::setNumeroSocio(int num) { numeroSocio = num; }
void Cuota::setFechaPago(Fecha f) { fechaPago = f; }
void Cuota::setImporte(float imp) { importe = imp; }
void Cuota::setMes(int m) { mes = m; }
void Cuota::setAnio(int a) { anio = a; }
