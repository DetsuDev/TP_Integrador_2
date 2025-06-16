#ifndef CLSPRESTAMO_H
#define CLSPRESTAMO_H

#include "clsFecha.h"

class ArchivoPrestamo;

class Prestamo {
private:
    int idPrestamo;
    char dniSocio[10];
    char isbn[20];
    Fecha fechaPrestamo;
    Fecha fechaDevolucion;


public:
    void setEstado(bool);
    bool getEstado();

    void setIdPrestamo(int);
    void setDniSocio(const char *);
    void setISBN(const char *);
    void setFechaPrestamo(Fecha);
    void setFechaDevolucion(Fecha);

    int getIdPrestamo();
    const char* getDniSocio();
    const char* getISBN();
    Fecha getFechaPrestamo();
    Fecha getFechaDevolucion();

    bool Cargar(ArchivoPrestamo&);
    void Mostrar();


};

#endif // CLSPRESTAMO_H
