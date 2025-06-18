#ifndef CLSARCHIVOPRESTAMO_H_INCLUDED
#define CLSARCHIVOPRESTAMO_H_INCLUDED

#include "prestamo/clsPrestamo.h"
#include <vector>

using namespace std;

class ArchivoPrestamo {
private:
    char nombre[30];
public:

    vector<int> BuscarMasLargo();

    ArchivoPrestamo(const char *n="FILES/current/Prestamos.dat");
    Prestamo leerRegistro(int);
    bool grabarRegistro(Prestamo);
    bool modificarRegistro(Prestamo, int);
    int contarRegistros();
    int buscarRegistro(int idPrestamo);
    int buscarDni(char*);
    int buscarISBN(const char *);
    void Eliminar();
    void MostrarHeader();
    Prestamo MostrarBusqueda(int pos);


    void Registrar();
    void Listar();
};

#endif // CLSARCHIVOPRESTAMO_H_INCLUDED
