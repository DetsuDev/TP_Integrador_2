#ifndef CLSARCHCUOTAS_H
#define CLSARCHCUOTAS_H

#include "cuota/clsCuota.h"

class ArchivoCuotas {

private:
    char nombre[30];
public:
    ArchivoCuotas(const char *n = "FILES/current/Cuotas.dat");
    Cuota leerRegistro(int pos);
    bool grabarRegistro(Cuota obj);
    bool modificarRegistro(Cuota obj, int pos);
    int contarRegistros();
    int buscarRegistro(int numeroSocio); // Opcional
    void RegistrarCuota();
    void ListarCuota();

};

#endif // CLSARCHCUOTAS_H
