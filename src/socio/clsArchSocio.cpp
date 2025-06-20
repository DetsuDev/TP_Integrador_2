#include <iostream>
#include <cstring>
#include <cstdio>
#include "socio/clsArchSocio.h"
#include "socio/clsSocio.h"
#include "clsFecha.h"
#include "clsDomicilio.h"
#include "funciones.h"
#include "prestamo/clsArchPrestamo.h"
#include "prestamo/clsPrestamo.h"
#include <vector>
using namespace std;

ArchivoSocios::ArchivoSocios(const char *n) {
    strcpy(nombre, n);
}

Socio ArchivoSocios::leerRegistro(int pos) {
    Socio obj;
    FILE *p = fopen(nombre, "rb");
    fseek(p, pos * sizeof obj, 0);
    if (pos < 0) {
        return obj; // RECREA EL OBJETO PARA QUE NO DEVUELVA BASURA
    }
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoSocios::grabarRegistro(Socio obj) {
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr) {
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoSocios::modificarRegistro(Socio obj, int pos) {
    FILE *p;
    p = fopen(nombre, "rb+");
    if(p == nullptr) {
        return false;
    }
    fseek(p, pos * sizeof obj, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoSocios::contarRegistros() {
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr) {
        return -1;
    }
    fseek(p, 0, 2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof (Socio);
}

int ArchivoSocios::buscarRegistro(const char *dni) {
    Socio obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++) {
        obj = leerRegistro(i);
        if(strcmp(obj.getDni(), dni) == 0) {
            return i;
        }
    }
    return -1;
}

bool Socio::Cargar(ArchivoSocios &arcSoc) {
    cout<<"INGRESE EL DNI: ";
    cargarCadena(dni,9);
    if (arcSoc.buscarRegistro(dni) == -1) {

        cout<<"INGRESE EL NOMBRE: ";
        cargarCadena(nombre,29);
        cout<<"INGRESE EL APELLIDO: ";
        cargarCadena(apellido,29);
        cout<<"INGRESE LA FECHA DE NACIMIENTO: " << endl;
        fechaNacimiento.Cargar();
        cout<<"INGRESE EL DOMICILIO: " << endl;
        domicilio.Cargar();
        cout<<"INGRESE EL EMAIL: ";
        cargarCadena(email, 39);
        return true;
    } else {
        cout << "DNI: [" << dni << "] YA EXISTENTE." << endl;
        return false;
    }
}
vector<int> ArchivoSocios::BuscarMasLargo() {
    int MasLargoDNI = strlen("DNI");
    int MasLargoNombre = strlen("NOMBRE");
    int MasLargoApellido = strlen("APELLIDO");
    int MasLargoEmail = strlen("EMAIL");

    int MasLargoCalle = strlen("CALLE");
    int MasLargoAltura = strlen("ALTURA");
    int MasLargoLocalidad = strlen("LOCALIDAD");
    int MasLargoPartido = strlen("PARTIDO");
    int MasLargoCodPostal = strlen("CP");

    for (int i = 0; i < contarRegistros(); i++) {
        Socio reg = leerRegistro(i);

        int lenDNI = strlen(reg.getDni());
        int lenNombre = strlen(reg.getNombre());
        int lenApellido = strlen(reg.getApellido());
        int lenEmail = strlen(reg.getEmail());

        int lenCalle = strlen(reg.getDomicilio().getCalle());
        char alturaStr[12];
        sprintf(alturaStr, "%i", reg.getDomicilio().getAltura());
        int lenAltura = strlen(alturaStr);
        int lenLocalidad = strlen(reg.getDomicilio().getLocalidad());
        int lenPartido = strlen(reg.getDomicilio().getPartido());
        int lenCodPostal = strlen(reg.getDomicilio().getCodPostal());

        if (lenDNI > MasLargoDNI) {
            MasLargoDNI = lenDNI;
        }
        if (lenNombre > MasLargoNombre) {
            MasLargoNombre = lenNombre;
        }
        if (lenApellido > MasLargoApellido) {
            MasLargoApellido = lenApellido;
        }
        if (lenEmail > MasLargoEmail) {
            MasLargoEmail = lenEmail;
        }

        if (lenCalle > MasLargoCalle) {
            MasLargoCalle = lenCalle;
        }
        if (lenAltura > MasLargoAltura) {
            MasLargoAltura = lenAltura;
        }
        if (lenLocalidad > MasLargoLocalidad) {
            MasLargoLocalidad = lenLocalidad;
        }
        if (lenPartido > MasLargoPartido) {
            MasLargoPartido = lenPartido;
        }
        if (lenCodPostal > MasLargoCodPostal) {
            MasLargoCodPostal = lenCodPostal;
        }
    }

    return {
        MasLargoDNI, MasLargoNombre, MasLargoApellido,
        MasLargoCalle, MasLargoAltura, MasLargoLocalidad, MasLargoPartido, MasLargoCodPostal, MasLargoEmail};
}



void ArchivoSocios::MostrarHeader() {
    vector<int> largos = BuscarMasLargo();

    char dni[] = "DNI";
    char nombre[] = "NOMBRE";
    char apellido[] = "APELLIDO";
    char email[] = "EMAIL";
    char calle[] = "CALLE";
    char altura[] = "ALTURA";
    char localidad[] = "LOCALIDAD";
    char partido[] = "PARTIDO";
    char CodigoPostal[] = "CP";

    cout << " " << espaciarTexto(dni, largos[0])
         << " │ " << espaciarTexto(nombre, largos[1])
         << " │ " << espaciarTexto(apellido, largos[2])
         << " │ " << espaciarTexto(calle, largos[3])
         << " │ " << espaciarTexto(altura, largos[4])
         << " │ " << espaciarTexto(localidad, largos[5])
         << " │ " << espaciarTexto(partido, largos[6])
         << " │ " << espaciarTexto(CodigoPostal, largos[7])
         << " │ " << espaciarTexto(email, largos[8])  << "\n";
}

void Socio::Mostrar() {
    ArchivoSocios arcSoc;

    vector<int> largos = arcSoc.BuscarMasLargo();

    char altura[10];
    sprintf(altura, "%i", domicilio.getAltura());

    cout << " " << espaciarTexto(dni, largos[0])
         << " │ " << espaciarTexto(nombre, largos[1])
         << " │ " << espaciarTexto(apellido, largos[2])
         << " │ " << espaciarTexto(domicilio.getCalle(), largos[3])
         << " │ " << espaciarTexto(altura, largos[4])
         << " │ " << espaciarTexto(domicilio.getLocalidad(), largos[5])
         << " │ " << espaciarTexto(domicilio.getPartido(), largos[6])
         << " │ " << espaciarTexto(domicilio.getCodPostal(), largos[7])
         << " │ " << espaciarTexto(email, largos[8]) << "\n";
}

void ArchivoSocios::Eliminar() {
    /// Llama la opcion de buscar y asi obtener el objeto
    Prestamo prest;
    ArchivoPrestamo arcPrest;
    char dni[10];
    cout << ">> Ingrese DNI socio a eliminar: ";
    cargarCadena(dni,9);
    int pos = buscarRegistro(dni);
    Socio obj = MostrarBusqueda(pos);
    cout << endl;
    int posPrest = arcPrest.buscarDni(dni);

    if (strcmp(obj.getDni(), "-1") != 0) {
        if(posPrest != -1){
            cout << "ATENCION, SE BORRARAN TODOS LOS PRESTAMOS" << endl;
        }
        cout << "ELIMINAR ESTE SOCIO? (S/N): ";
        char opc;
        cin >> opc;
        if (opc == 'S' || opc == 's') {
            /// Busca la posicion en el regsitro del DNI
            int pos = buscarRegistro(obj.getDni());
            obj.setDni("-1");
            obj.setNombre(" ");
            obj.setApellido(" ");

        if(posPrest != -1){ /// borra el prestamo que este a nombre de este dni
            prest = arcPrest.leerRegistro(posPrest);
            prest.setIdPrestamo(-1);
            arcPrest.modificarRegistro(prest,posPrest);
        }
            /// Modifica el objeto en esa posicion
            modificarRegistro(obj, pos);
            cout << "SOCIO ELIMINADO" << endl;
        }
    }
}

void ArchivoSocios::BuscarDni(const char* dni) {
    MostrarHeader();
    int pos = -1;
    for (int i=0; i < contarRegistros(); i++) {
        pos = buscarRegistro(dni);
    }
    MostrarBusqueda(pos);
}

void ArchivoSocios::BuscarNombre(const char* nombre, const char* apellido) {

    MostrarHeader();
    int pos = -1;
    for (int i=0; i < contarRegistros(); i++) {
        if (strcmp(leerRegistro(i).getNombre(),nombre) == 0 && strcmp(leerRegistro(i).getApellido(),apellido) == 0) {
            /// Consigue la posicion en el registro gracias al DNI
            pos = buscarRegistro(leerRegistro(i).getDni());
            MostrarBusqueda(pos);
        }
    }
}

Socio ArchivoSocios::MostrarBusqueda(int pos) {
    /// Busca el dni o el nombre en el registro y obtiene la posicione
    if(pos != -1) {
        Socio obj = leerRegistro(pos);
        /// Muestra el objeto de esa posicon
        obj.Mostrar();
        /// Devuelve el objeto para usarlo en la funcion de Eliminar, el problema es que si no buscamos eliminar no tiene utilidad
        return obj;

    } else {
        cout << "SOCIO NO ENCONTRADO." << endl;
        /// Crea un objeto auxiliar
        Socio aux;
        /// Setea el estado en false
        aux.setDni("-1");
        return aux;
    }
}
void ArchivoSocios::Registrar() {
    Socio obj;
    if (obj.Cargar(*this)) {
        int posLibre = -1;
        for (int i = 0; i < contarRegistros(); i++) {
            /// Busca la posicion libre (DNI = -1) y la guarda en una variable
            if (strcmp(leerRegistro(i).getDni(), "-1") == 0) {
                posLibre = i;
                break;
            }
        }
        /// Verifica si existe posicion libre
        if (posLibre != -1) {
            /// Escribe en esa posicion
            modificarRegistro(obj, posLibre);
        } else {
            /// Si no la encuentra, guarda en una nueva posicion
            grabarRegistro(obj);
        }
    }
}

void ArchivoSocios::Listar() {

    MostrarHeader();
    Socio obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++) {
        obj = leerRegistro(i);
        /// Verifica si esta ocupada la direccion para mostrarla
        if (strcmp(leerRegistro(i).getDni(), "-1") != 0) {
            obj.Mostrar();
        }
    }
}

