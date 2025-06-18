#ifndef CLSCUOTA_H_INCLUDED
#define CLSCUOTA_H_INCLUDED

#include "clsFecha.h"

class ArchivoCuotas;
class Cuota {
private:
    char dni[10];
    Fecha fechaPago;
    float importe;
    int mes;
    int anio;


public:


    Fecha getFechaPago();
    float getImporte();
    int getMes();
    int getAnio();
    const char* getDni();

    void setDni(const char*);
    void setFechaPago(Fecha f);
    void setImporte(float imp);

    void setMes(int m);
    void setAnio(int a);

    bool Cargar(ArchivoCuotas&);
    void Mostrar();
};

#endif // CLSCUOTA_H_INCLUDED
