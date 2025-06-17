#ifndef CLS_SOCIO_H
#define CLS_SOCIO_H

#include "clsFecha.h"
#include "clsDomicilio.h"

class ArchivoSocios;  // Declaración adelantada

class Socio {
private:
    char dni[10];
    char nombre[30];
    char apellido[30];
    char email[40];
    Fecha fechaNacimiento;
    Domicilio domicilio;
    bool estado = false;

public:
    void setEstado(bool);
    bool getEstado();

    void setDni(const char*);
    void setNombre(const char*);
    void setApellido(const char*);
    void setEmail(const char*);
    void setFechaNacimiento(Fecha);
    void setDomicilio(Domicilio);

    const char* getDni();
    const char* getNombre();
    const char* getApellido();
    const char* getEmail();
    Fecha& getFechaNacimiento();
    Domicilio& getDomicilio();

    bool Cargar(ArchivoSocios &);
    void Mostrar();
};

#endif // CLS_SOCIO_H
