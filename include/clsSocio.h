#ifndef CLSSOCIO_H_INCLUDED
#define CLSSOCIO_H_INCLUDED

#include "clsFecha.h"
#include "clsDomicilio.h"
#include "clsSocio.h"
#include <cstring>

class Socio
{

private:
    int dni;
    char nombre[30];
    char apellido[30];
    char email[40];
    Fecha fechaNacimiento;
    Domicilio domicilio;

public:
    int getDni();
    void setDni(int);
    void setEmail(const char *);
    void Cargar();
    void Mostrar();
};

#endif // CLSSOCIO_H_INCLUDED
