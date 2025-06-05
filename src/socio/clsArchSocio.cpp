#include <iostream>
#include <cstring>
#include "socio/clsArchSocio.h"

using namespace std;

ArchivoSocios::ArchivoSocios(const char *n){
    strcpy(nombre, n);
}

Socio ArchivoSocios::leerRegistro(int pos){
    Socio obj;
    FILE *p = fopen(nombre, "rb");
    fseek(p, pos * sizeof obj, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoSocios::grabarRegistro(Socio obj){


    FILE *p = fopen(nombre, "ab");
    if(p == nullptr){
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoSocios::modificarRegistro(Socio obj, int pos){
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

int ArchivoSocios::contarRegistros(){
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr){
        return -1;
    }
    fseek(p, 0, 2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof (Socio);
}


int ArchivoSocios::buscarRegistro(const char *dni){
    Socio obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++){
        obj = leerRegistro(i);
        if(strcmp(obj.getDni(), dni) == 0){
            return i;
        }
    }
    return -1;
}

string ArchivoSocios::buscarDniRegistro(const char *dni){
        int pos = buscarRegistro(dni);
        if (pos == -1) {
            return "DNI NO ENCONTRADO.";
        }

        Socio obj = leerRegistro(pos);
        return string(obj.getDni());
}
