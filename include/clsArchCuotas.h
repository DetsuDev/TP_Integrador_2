#ifndef CLSARCHCUOTAS_H
#define CLSARCHCUOTAS_H

#include "clsCuota.h"

class ArchivoCuotas {
private:
    char nombre[30];
public:
    ArchivoCuotas(const char *n = "Cuotas.dat");
    Cuota leerRegistro(int pos);
    bool grabarRegistro(Cuota obj);
    bool modificarRegistro(Cuota obj, int pos);
    int contarRegistros();
    int buscarRegistroPorSocio(int numeroSocio); // Opcional
};

#endif // CLSARCHCUOTAS_H
