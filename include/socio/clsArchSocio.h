#ifndef CLSARCHSOCIOS_H_INCLUDED
#define CLSARCHSOCIOS_H_INCLUDED
#include <iostream>
#include <cstring>
#include "socio/clsSocio.h"

class ArchivoSocios {
private:
    char nombre[30];
public:
    ArchivoSocios(const char *n="FILES/current/Socios.dat");
    Socio leerRegistro(int pos);
    bool grabarRegistro(Socio obj);
    bool modificarRegistro(Socio obj, int pos);
    int contarRegistros();
    int buscarRegistro(const char* dni);

    // Lógica de negocio
    void Mostrar();
    void Registrar();
    void Eliminar();
    void Listar();
    Socio Buscar();
    void MostrarHeader();

    //void buscarRegistro();
};

#endif // CLSARCHSOCIOS_H_INCLUDED
