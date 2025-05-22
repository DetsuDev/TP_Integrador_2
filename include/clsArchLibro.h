#ifndef CLSARCHLIBRO_H_INCLUDED
#define CLSARCHLIBRO_H_INCLUDED

#include "clsLibro.h"

class ArchivoLibros{
    private:
        char nombre[30];
    public:
        ArchivoLibros(const char *n="Libros.dat");
        Libro leerRegistro(int);
        bool grabarRegistro(Libro);
        bool modificarRegistro(Libro, int);
        int contarRegistros();
        int buscarRegistro(const char *isbn);
};

#endif // CLSARCHLIBRO_H_INCLUDED



