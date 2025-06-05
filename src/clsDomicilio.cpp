#include <iostream>
#include "clsDomicilio.h"
#include "funciones.h"

using namespace std;

void Domicilio::Cargar(){
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

void Domicilio::Mostrar(){
    cout << " DIRECCION: "<<calle<<" "<<altura<<endl;
    cout << " LOCALIDAD: "<<localidad<<endl;
    cout << " PARTIDO: "<<partido<<endl;
    cout << " CODIGO POSTAL: "<<codigoPostal<<endl;
}
