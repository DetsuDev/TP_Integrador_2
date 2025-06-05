#ifndef CLSARCHSOCIOS_H_INCLUDED
#define CLSARCHSOCIOS_H_INCLUDED

#include "socio/clsSocio.h"

class ArchivoSocios{
    private:
        char nombre[30];
    public:
        ArchivoSocios(const char *n="FILES/current/Socios.dat");
        Socio leerRegistro(int);
        int buscarRegistro(const char *dni);
        std::string buscarDniRegistro(const char *dni);
        bool grabarRegistro(Socio);
        bool modificarRegistro(Socio, int);
        int contarRegistros();

        //void buscarRegistro();
};

#endif // CLSARCHSOCIOS_H_INCLUDED
