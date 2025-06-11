#ifndef CLSCUOTA_H_INCLUDED
#define CLSCUOTA_H_INCLUDED

#include "clsFecha.h"

class Cuota {
private:
    int numeroSocio;
    Fecha fechaPago;
    float importe;
    int mes;
    int anio;

public:
    void Cargar();
    void Mostrar();

    // Getters
    int getNumeroSocio();
    Fecha getFechaPago();
    float getImporte();
    int getMes();
    int getAnio();

    // Setters
    void setNumeroSocio(int num);
    void setFechaPago(Fecha f);
    void setImporte(float imp);
    void setMes(int m);
    void setAnio(int a);

    void registrarCuota();
    void listarCuota();
};

#endif // CLSCUOTA_H_INCLUDED
