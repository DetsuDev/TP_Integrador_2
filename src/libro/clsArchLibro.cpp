#include <iostream>
#include <cstring>
#include "libro/clsArchLibro.h"

ArchivoLibros::ArchivoLibros(const char *n){
    strcpy(nombre, n);
}

Libro ArchivoLibros::leerRegistro(int pos){
    Libro obj;
    FILE *p = fopen(nombre, "rb");
    fseek(p, pos * sizeof obj, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoLibros::grabarRegistro(Libro obj){
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr){
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoLibros::modificarRegistro(Libro obj, int pos){
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

int ArchivoLibros::contarRegistros(){
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr){
        return -1;
    }
    fseek(p, 0, 2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof (Libro);
}

int ArchivoLibros::buscarRegistro(const char *isbn){
    Libro obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        obj = leerRegistro(i);
        if(obj.getISBN() == isbn){
            return i;
        }
    }
    return -1;
}


