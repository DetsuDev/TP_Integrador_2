#include <iostream>
#include <cstring>
#include "prestamo/clsArchPrestamo.h"

ArchivoPrestamo::ArchivoPrestamo(const char *n){
    strcpy(nombre, n);
}

Prestamo ArchivoPrestamo::leerRegistro(int pos){
    Prestamo obj;
    FILE *p = fopen(nombre, "rb");
    fseek(p, pos * sizeof obj, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoPrestamo::grabarRegistro(Prestamo obj){
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr){
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoPrestamo::modificarRegistro(Prestamo obj, int pos){
    FILE *p;
    p = fopen(nombre, "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, pos * sizeof obj, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoPrestamo::contarRegistros(){
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr){
        return -1;
    }
    fseek(p, 0, 2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof (Prestamo);
}

int ArchivoPrestamo::buscarRegistro(const char *idPrestamo){
    Prestamo obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        obj = leerRegistro(i);
        if(obj.getIdPrestamo() == *idPrestamo){
            return i;
        }
    }
    return -1;
}
