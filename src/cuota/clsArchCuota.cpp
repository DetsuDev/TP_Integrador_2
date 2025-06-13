#include <iostream>
#include <cstring>
#include "cuota/clsArchCuota.h"
#include "funciones.h"

using namespace std;

ArchivoCuotas::ArchivoCuotas(const char *n)
{
    strcpy(nombre, n);
}

Cuota ArchivoCuotas::leerRegistro(int pos)
{
    Cuota obj;
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return obj;
    fseek(p, pos * sizeof obj, SEEK_SET);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoCuotas::grabarRegistro(Cuota obj)
{
    FILE *p = fopen(nombre, "ab");
    if (p == nullptr) return false;
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoCuotas::modificarRegistro(Cuota obj, int pos)
{
    FILE *p = fopen(nombre, "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof obj, SEEK_SET);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoCuotas::contarRegistros()
{
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int tam = ftell(p);
    fclose(p);
    return tam / sizeof(Cuota);
}

int ArchivoCuotas::buscarRegistro(int numeroSocio)
{
    Cuota obj;
    int cant = contarRegistros();
    for (int i = 0; i < cant; i++)
    {
        obj = leerRegistro(i);
        if (obj.getNumeroSocio() == numeroSocio)
        {
            return i;
        }
    }
    return -1;
}

bool Cuota::Cargar(ArchivoCuotas &arcCuot)
{
    cout << "INGRESE NÚMERO DE SOCIO: ";
    cin >> numeroSocio;

    if (arcCuot.buscarRegistro(numeroSocio) == -1)
    {
        cout << "INGRESE FECHA DE PAGO: " << endl;
        fechaPago.Cargar();

        cout << "INGRESE IMPORTE: ";
        cin >> importe;

        cout << "INGRESE MES: ";
        cin >> mes;

        cout << "INGRERE AÑO: ";
        cin >> anio;
        return true;
    }
    else
    {
        cout << "NUMERO SOCIO: [" << numeroSocio << "] YA EXISTENTE." << endl;
        return false;
    }
}

void Cuota::Mostrar()
{
    cout << "NÚMERO DE SOCIO: " << numeroSocio << endl;
    cout << "FECHA DE PAGO: ";
    fechaPago.Mostrar();
    cout << "IMPORTE: $" << importe << endl;
    cout << "MES: " << mes << " - AÑO: " << anio << endl;
}




void ArchivoCuotas::RegistrarCuota()
{

    Cuota obj;
    if (obj.Cargar(*this))
    {
        obj.setEstado(true);

        grabarRegistro(obj);
    }
}

void ArchivoCuotas::ListarCuota()
{
    Cuota obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++)
    {
        obj = leerRegistro(i);
        if (obj.getEstado())
        {
            obj.Mostrar();
            cout << endl;
        }
    }

}

