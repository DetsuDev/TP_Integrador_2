#include <iostream>
#include <cstring>
#include "clsSocio.h"
#include "funciones.h"

using namespace std;

void Socio::Cargar(){
    cout<<"INGRESE EL DNI: ";
    cin>>dni;
    cout<<"INGRESE EL NOMBRE: ";
    cargarCadena(nombre,29);
    cout<<"INGRESE EL APELLIDO: ";
    cargarCadena(apellido,29);
    cout<<"INGRESE LA FECHA DE NACIMIENTO: "<<endl;
    fechaNacimiento.Cargar();
    cout<<"INGRESE EL DOMICILIO: "<<endl;
    domicilio.Cargar();
    //cout<<"INGRESE EL TELEFONO: ";
    //cargarCadena(telefono, 19);
    cout<<"INGRESE EL EMAIL: ";
    cargarCadena(email, 39);
}

void Socio::Mostrar(){
    cout<<"DNI: "<<dni<<endl;
    cout<<"NOMBRE: "<<apellido<<", "<<nombre<<endl;
    cout<<"FECHA DE NACIMIENTO: ";
    fechaNacimiento.Mostrar();
    cout<<"DOMICILIO: "<<endl;
    domicilio.Mostrar();
    //cout<<"TELEFONO: "<<telefono<<endl;
    cout<<"EMAIL: "<<email<<endl;
}

void Socio::setEmail(const char *e){
    strcpy(email, e);
}

int Socio::getDni(){
    return dni;
}

