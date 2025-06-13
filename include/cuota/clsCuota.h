#ifndef CLSCUOTA_H_INCLUDED
#define CLSCUOTA_H_INCLUDED

#include "clsFecha.h"

class ArchivoCuotas;
class Cuota {
private:
    int numeroSocio;
    Fecha fechaPago;
    float importe;
    int mes;
    int anio;

    bool estado = false;

public:
    void setEstado(bool);
    bool getEstado();

    int getNumeroSocio();
    Fecha getFechaPago();
    float getImporte();
    int getMes();
    int getAnio();

    void setNumeroSocio(int num);
    void setFechaPago(Fecha f);
    void setImporte(float imp);
    void setMes(int m);
    void setAnio(int a);

    bool Cargar(ArchivoCuotas&);
    void Mostrar();
};

#endif // CLSCUOTA_H_INCLUDED
