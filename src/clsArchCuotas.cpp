#include <iostream>
#include <cstring>
#include "clsArchCuotas.h"

ArchivoCuotas::ArchivoCuotas(const char *n) {
    strcpy(nombre, n);
}

Cuota ArchivoCuotas::leerRegistro(int pos) {
    Cuota obj;
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return obj;
    fseek(p, pos * sizeof obj, SEEK_SET);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoCuotas::grabarRegistro(Cuota obj) {
    FILE *p = fopen(nombre, "ab");
    if (p == nullptr) return false;
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoCuotas::modificarRegistro(Cuota obj, int pos) {
    FILE *p = fopen(nombre, "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof obj, SEEK_SET);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoCuotas::contarRegistros() {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int tam = ftell(p);
    fclose(p);
    return tam / sizeof(Cuota);
}

int ArchivoCuotas::buscarRegistroPorSocio(int numeroSocio) {
    Cuota obj;
    int cant = contarRegistros();
    for (int i = 0; i < cant; i++) {
        obj = leerRegistro(i);
        if (obj.getNumeroSocio() == numeroSocio) {
            return i;
        }
    }
    return -1;
}
