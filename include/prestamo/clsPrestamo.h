#ifndef CLSPRESTAMO_H
#define CLSPRESTAMO_H

#include "clsFecha.h"

class Prestamo {
private:
    int idPrestamo;
    char dniSocio[10];
    char isbn[20];
    Fecha fechaPrestamo;
    Fecha fechaDevolucion;

public:
    void Cargar();
    void Mostrar();

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

    void registrarPrestamo();
    void listarPrestamo();



};

#endif // CLSPRESTAMO_H
