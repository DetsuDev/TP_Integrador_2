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
    bool estado = true;
    Fecha fechaNacimiento;
    Domicilio domicilio;

public:
    const char* getDni();
    Fecha& getFechaNacimiento();
    Domicilio& getDomicilio();
    void setEstado(bool);
    bool getEstado();
    void setDni(const char *);
    void setNombre(const char *);
    void setApellido(const char *);
    void setEmail(const char *);
    void setFechaNacimiento(Fecha f);
    void setDomicilio(Domicilio d);
    bool Cargar(ArchivoSocios&);
    void EliminarSocio();
    void Mostrar();
    void MostrarBusqueda();
    void registrarSocio();
    void listarSocio();
};

#endif // CLSSOCIO_H_INCLUDED
