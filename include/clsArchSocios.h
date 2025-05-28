#ifndef CLSARCHSOCIOS_H_INCLUDED
#define CLSARCHSOCIOS_H_INCLUDED

#include "clsSocio.h"

class ArchivoSocios{
    private:
        char nombre[30];
    public:
        ArchivoSocios(const char *n="Socios.dat");
        Socio leerRegistro(int);
        bool grabarRegistro(Socio);
        bool modificarRegistro(Socio, int);
        int contarRegistros();
        int buscarRegistro(const char *dni);
};

#endif // CLSARCHSOCIOS_H_INCLUDED
