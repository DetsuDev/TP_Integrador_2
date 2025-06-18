#ifndef CLSPRESTAMO_H
#define CLSPRESTAMO_H

#include "clsFecha.h"
using namespace std;

class ArchivoPrestamo;

class Prestamo {
private:
    int idPrestamo;
    char dniSocio[10];
    char isbn[20];
    Fecha fechaPrestamo;
    Fecha fechaDevolucion;
    //string fechaCompleta;


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
    //string setFechaCompleta();
    bool Cargar(ArchivoPrestamo&);
    void Mostrar();
    //void setFechaCompleta(Fecha);

};

#endif // CLSPRESTAMO_H
