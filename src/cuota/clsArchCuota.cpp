#include <iostream>
#include <cstring>
#include <cstdio>
#include "cuota/clsArchCuota.h"
#include "cuota/clsCuota.h"
#include "socio/clsArchSocio.h"
#include "funciones.h"
#include <vector>
using namespace std;

ArchivoCuotas::ArchivoCuotas(const char *n) {
    strcpy(nombre, n);
}

Cuota ArchivoCuotas::leerRegistro(int pos) {
    Cuota obj;
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        return obj;
    }
    fseek(p, pos * sizeof obj, 0);
    if (pos < 0) {
        return obj; /// Recrea el objeto para que no devuelva basura
    }
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoCuotas::grabarRegistro(Cuota obj) {
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr) {
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoCuotas::modificarRegistro(Cuota obj, int pos) {
    FILE *p = fopen(nombre, "rb+");
    if(p == nullptr) {
        return false;
    }
    fseek(p, pos * sizeof obj, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoCuotas::contarRegistros() {
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr) {
        return -1;
    }
    fseek(p, 0, 2);
    int tam = ftell(p);
    fclose(p);
    return tam / sizeof(Cuota);
}

int ArchivoCuotas::buscarRegistro(const char *dni) {
    Cuota obj;
    int cantReg = contarRegistros();
    for(int i = 0; i < cantReg; i++) {
        obj = leerRegistro(i);
        if(strcmp(obj.getDni(), dni) == 0) {
            return i;
        }
    }
    return -1;
}

vector<int> ArchivoCuotas::BuscarMasLargo() {
    int MasLargoDNI = strlen("DNI");
    int MasLargoImporte = strlen("IMPORTE");
    int MasLargoMes = strlen("MES");
    int MasLargoAnio = strlen("AÑO");
    int MasLargoFecha = strlen("FECHA PAGO");

    for (int i = 0; i < contarRegistros(); i++) {
        Cuota reg = leerRegistro(i);
        if (strcmp(reg.getDni(), "-1") == 0) continue;

        int lenDNI = strlen(reg.getDni());

        char importeStr[20];
        sprintf(importeStr, "%.2f", reg.getImporte());
        int lenImporte = strlen(importeStr);

        char mesStr[3];
        sprintf(mesStr, "%d", reg.getMes());
        int lenMes = strlen(mesStr);

        char anioStr[5];
        sprintf(anioStr, "%d", reg.getAnio());
        int lenAnio = strlen(anioStr);


        char fechaStr[11];
        sprintf(fechaStr, "%d", reg.getFechaPago().getFechaCompleta());
        int lenFecha = strlen(fechaStr);

        if (lenDNI > MasLargoDNI) {
            MasLargoDNI = lenDNI;
        }
        if (lenImporte > MasLargoImporte) {
            MasLargoImporte = lenImporte;
        }
        if (lenMes > MasLargoMes) {
            MasLargoMes = lenMes;
        }
        if (lenAnio > MasLargoAnio) {
            MasLargoAnio = lenAnio;
        }
        if (lenFecha > MasLargoFecha) {
            MasLargoFecha = lenFecha;
        }
    }

    return {MasLargoDNI, MasLargoImporte, MasLargoMes, MasLargoAnio, MasLargoFecha};
}

void ArchivoCuotas::MostrarHeader() {
    vector<int> largos = BuscarMasLargo();

    char dni[] = "DNI";
    char importe[] = "IMPORTE";
    char mes[] = "MES";
    char anio[] = "AÑO";
    char fecha[] = "FECHA PAGO";

    cout << " " << espaciarTexto(dni, largos[0])
         << " │ " << espaciarTexto(importe, largos[1])
         << " │ " << espaciarTexto(mes, largos[2])
         << " │ " << espaciarTexto(anio, 5)
         << " │ " << espaciarTexto(fecha, largos[4]) << "\n";
}

bool Cuota::Cargar(ArchivoCuotas &arcCuot) {
    ArchivoSocios arcSoc;
    cout << "INGRESE NÚMERO DE DNI: ";
    cargarCadena(dni, 9);

    if (arcSoc.buscarRegistro(dni) != -1) {
        cout << "INGRESE FECHA DE PAGO: " << endl;
        fechaPago.Cargar();

        cout << "INGRESE IMPORTE: ";
        cin >> importe;

        cout << "INGRESE MES: ";
        cin >> mes;

        cout << "INGRESE AÑO: ";
        cin >> anio;

        return true;
    } else {
        cout << "DNI: [" << dni << "] NO EXISTENTE." << endl;
        return false;
    }
}

void Cuota::Mostrar() {
    ArchivoCuotas arcCuot;
    vector<int> largos = arcCuot.BuscarMasLargo();

    char importeStr[20];
    sprintf(importeStr, "%.2f", importe);
    char mesStr[3];
    sprintf(mesStr, "%d", mes);
    char anioStr[5];
    sprintf(anioStr, "%d", anio);

    /*char fechaStr[11];
    sprintf(fechaStr, "%d", fechaPago.getFechaCompleta());*/


    cout << " " << espaciarTexto(dni, largos[0])
         << " │ " << espaciarTexto(importeStr, largos[1])
         << " │ " << espaciarTexto(mesStr, largos[2])
         << " │ " << espaciarTexto(anioStr, largos[3])
         << " │ " <<  fechaPago.getFechaCompleta();
         cout << "\n";
}

void ArchivoCuotas::Eliminar() {
    char dni[10];
    cout << ">> Ingrese DNI para eliminar cuotas: ";
    cargarCadena(dni, 9);
    int pos = buscarRegistro(dni);
    Cuota obj = MostrarBusqueda(pos);
    cout << endl;

    if (strcmp(obj.getDni(), "-1") != 0) {
        cout << "ELIMINAR ESTA CUOTA? (S/N): ";
        char opc;
        cin >> opc;
        if (opc == 'S' || opc == 's') {
            obj.setDni("-1");
            obj.setImporte(0);
            modificarRegistro(obj, pos);
            cout << "CUOTA ELIMINADA" << endl;
        }
    }
}

void ArchivoCuotas::BuscarDni(const char* dni) {
    int pos = -1;
    for (int i = 0; i < contarRegistros(); i++) {
        pos = buscarRegistro(dni);
    }
    MostrarBusqueda(pos);
}

Cuota ArchivoCuotas::MostrarBusqueda(int pos) {
    bool encontrado = false;
    if(pos != -1) {
        Cuota obj = leerRegistro(pos);
        if (!encontrado)
            {
                MostrarHeader();
                encontrado = true;
            }
        obj.Mostrar();
        return obj;
    } else {
        cout << "CUOTA NO ENCONTRADA." << endl;
        Cuota aux;
        aux.setDni("-1");
        return aux;
    }
}

void ArchivoCuotas::Registrar() {
    Cuota obj;
    if (obj.Cargar(*this)) {
        int posLibre = -1;
        for (int i = 0; i < contarRegistros(); i++) {
            if (strcmp(leerRegistro(i).getDni(), "-1") == 0) {
                posLibre = i;
                break;
            }
        }
        if (posLibre != -1) {
            modificarRegistro(obj, posLibre);
        } else {
            grabarRegistro(obj);
        }
    }
}

void ArchivoCuotas::Listar() {
    MostrarHeader();
    Cuota obj;
    int cantReg = contarRegistros();
    for(int i = 0; i < cantReg; i++) {
        obj = leerRegistro(i);
        if (obj.getDni() > 0) {
            obj.Mostrar();
        }
    }
}

void ArchivoCuotas::ListarPorMesAnio(int mes, int anio) {
    MostrarHeader();
    Cuota obj;
    int cantReg = contarRegistros();
    for(int i = 0; i < cantReg; i++) {
        obj = leerRegistro(i);
        if (obj.getDni() > 0 &&
                obj.getMes() == mes &&
                obj.getAnio() == anio) {
            obj.Mostrar();
        }
    }
}
