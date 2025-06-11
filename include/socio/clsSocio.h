#ifndef CLSSOCIO_H_INCLUDED
#define CLSSOCIO_H_INCLUDED

#include "clsFecha.h"
#include "clsDomicilio.h"
#include <cstring>

class ArchivoSocios;

class Socio
{

private:
    char dni[10];
    char nombre[30];
    char apellido[30];
    char email[40];
    Fecha fechaNacimiento;
    Domicilio domicilio;

public:
    const char* getDni();
    void setDni(const char *);
    void setEmail(const char *);
    bool Cargar(ArchivoSocios&);
    void EliminarSocio();
    void Mostrar();
    void MostrarBusqueda();
    void registrarSocio();
    void listarSocio();
};

#endif // CLSSOCIO_H_INCLUDED
