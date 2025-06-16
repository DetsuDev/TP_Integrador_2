#ifndef CLSARCHIVOPRESTAMO_H_INCLUDED
#define CLSARCHIVOPRESTAMO_H_INCLUDED

#include "prestamo/clsPrestamo.h"

class ArchivoPrestamo {
private:
    char nombre[30];
public:


    ArchivoPrestamo(const char *n="FILES/current/Prestamos.dat");
    Prestamo leerRegistro(int);
    bool grabarRegistro(Prestamo);
    bool modificarRegistro(Prestamo, int);
    int contarRegistros();
    int buscarRegistro(int idPrestamo);
    void Eliminar();
    void MostrarHeader();


    void RegistrarPrestamo();
    void Listar();
};

#endif // CLSARCHIVOPRESTAMO_H_INCLUDED
