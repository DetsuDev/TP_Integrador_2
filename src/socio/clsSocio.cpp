#include <iostream>
#include <cstring>
#include "socio/clsSocio.h"
#include "socio/clsArchSocio.h"
#include "funciones.h"

using namespace std;

bool Socio::Cargar()
{
    ArchivoSocios arcSoc;
    cout<<"INGRESE EL DNI: ";
    cargarCadena(dni,9);

    if (arcSoc.buscarRegistro(dni) == -1)
    {

        cout<<"INGRESE EL NOMBRE: ";
        cargarCadena(nombre,29);
        cout<<"INGRESE EL APELLIDO: ";
        cargarCadena(apellido,29);
        cout<<"INGRESE LA FECHA DE NACIMIENTO: "<<endl;
        fechaNacimiento.Cargar();
        cout<<"INGRESE EL DOMICILIO: "<<endl;
        domicilio.Cargar();
        cout<<"INGRESE EL EMAIL: ";
        cargarCadena(email, 39);
        return true;
    }
    else
    {
        cout << "DNI: [" << dni << "] YA EXISTENTE." << endl;
        return false;
    }

}


void Socio::Mostrar()
{
    //cout << dni << "| " << apellido << "| " << nombre << "| " << email << endl;
    cout << " DNI: "<<dni<<endl;
    cout << " NOMBRE: "<<apellido<<", "<<nombre<<endl;
    cout << " FECHA DE NACIMIENTO: ";
    fechaNacimiento.Mostrar();
    cout << " DOMICILIO: "<<endl;
    domicilio.Mostrar();
    cout << " EMAIL: "<<email<<endl;
    cout << "────────────────────────────────────────";
}

/*cout << "╔══════════════════════════════════════╗\n";
cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
cout << "╠══════════════════════════════════════╣\n";
cout << "╟── GESTION ───────────────────────────╣\n";
cout << "║                                      ║\n";
cout << "║  [1] Restaurar BACKUP                ║\n";
cout << "║  [2] Generar BACKUP                  ║\n";
cout << "║                                      ║\n";
cout << "╟──────────────────────────────────────╣\n";
cout << "║  [0] Volver                          ║\n";
cout << "╚══════════════════════════════════════╝\n";*/


void Socio::MostrarBusqueda()
{
    char dni[9];
    cout << ">> Ingrese DNI socio: ";
    cin >> dni;

    ArchivoSocios arcSoc;
    string dniReg = arcSoc.buscarDniRegistro(dni);
    cout << "DNI: " << dniReg;
    cout << endl;
    //obj.Mostrar();

}

// esta funcion crea el objeto obj, luego ejecuta el metodo "Cargar()", luego crea el objeto "obj" y graba los registros en el archivo de socios

void Socio::registrarSocio()
{
    Socio obj;
    ArchivoSocios arcSoc;
    if (obj.Cargar())
    {
        arcSoc.grabarRegistro(obj);
    }
    else
    {
        obj.Cargar();
    }
}

// lee el archivo de socios y los muestra en pantalla


void Socio::listarSocio()
{
    ArchivoSocios arcSoc;
    Socio obj;
    int cantReg = arcSoc.contarRegistros();
    for(int i=0; i<cantReg; i++)
    {
        obj = arcSoc.leerRegistro(i);
        obj.Mostrar();
        cout << endl;
    }
}

void Socio::setEmail(const char *e)
{
    strcpy(email, e);
}

void Socio::setDni(const char *i)
{
    strcpy(dni, i);
}

const char* Socio::getDni()
{
    return dni;
}
