#include <iostream>
#include <cstring>
#include "socio/clsSocio.h"
#include "funciones.h"

#include "socio/clsArchSocio.h"
using namespace std;

void Socio::Cargar(){
    cout<<"INGRESE EL DNI: ";
    cargarCadena(dni,9);
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
}


/*




cout << "║  [0] Volver                          ║\n";
cout << "╚══════════════════════════════════════╝\n";



cout << "╟──────────────────────────────────────╣\n";
cout << "║                                      ║\n";
cout << "║  DNI: " << dni << "\n";
cout << "║  DNI: " << dni << "\n";
cout << "║                                      ║\n";
cout << "╟──────────────────────────────────────╣\n";
*/

void Socio::Mostrar(){
    cout << dni << "| " << apellido << "| " << nombre << "| " << email << endl;
    /*cout << " DNI: "<<dni<<endl;
    cout << " NOMBRE: "<<apellido<<", "<<nombre<<endl;
    cout << " FECHA DE NACIMIENTO: ";
    fechaNacimiento.Mostrar();
    cout << " DOMICILIO: "<<endl;
    domicilio.Mostrar();
    cout << " EMAIL: "<<email<<endl;*/
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

void Socio::setEmail(const char *e){ strcpy(email, e); }

void Socio::setDni(const char *i) { strcpy(dni, i); }

const char* Socio::getDni(){ return dni; }
