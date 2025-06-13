#ifndef CLSARCHLIBRO_H_INCLUDED
#define CLSARCHLIBRO_H_INCLUDED

#include "libro/clsLibro.h"

class ArchivoLibros {
private:
    char nombre[30];
public:
    ArchivoLibros(const char *n="FILES/current/Libros.dat");
    Libro leerRegistro(int);
    bool grabarRegistro(Libro);
    bool modificarRegistro(Libro, int);
    int contarRegistros();
    int buscarRegistro(const char *isbn);

    void RegistrarLibro();
    void ListarLibro();
};

#endif // CLSARCHLIBRO_H_INCLUDED



