#ifndef CLSARCHIVOPRESTAMO_H_INCLUDED
#define CLSARCHIVOPRESTAMO_H_INCLUDED

#include "clsPrestamo.h"

class ArchivoPrestamo{
    private:
        char nombre[30];
    public:
        ArchivoPrestamo(const char *n="Prestamos.dat");
        Libro leerRegistro(int);
        bool grabarRegistro(Libro);
        bool modificarRegistro(Libro, int);
        int contarRegistros();
        int buscarRegistro(const char *isbn);
};

#endif // CLSARCHIVOPRESTAMO_H_INCLUDED
