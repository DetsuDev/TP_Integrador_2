#ifndef CLSARCHIVOPRESTAMO_H_INCLUDED
#define CLSARCHIVOPRESTAMO_H_INCLUDED

#include "clsPrestamo.h"

class ArchivoPrestamo{
    private:
        char nombre[30];
    public:
        ArchivoPrestamo(const char *n="Prestamos.dat");
        Prestamo leerRegistro(int);
        bool grabarRegistro(Prestamo);
        bool modificarRegistro(Prestamo, int);
        int contarRegistros();
        int buscarRegistro(const char *idPrestamo);
};

#endif // CLSARCHIVOPRESTAMO_H_INCLUDED
