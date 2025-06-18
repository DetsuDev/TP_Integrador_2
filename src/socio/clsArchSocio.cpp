#include <iostream>
#include <cstring>
#include <cstdio>
#include "socio/clsArchSocio.h"
#include "socio/clsSocio.h"
#include "clsFecha.h"
#include "clsDomicilio.h"
#include "funciones.h"
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
        return obj; /// Recrea el objeto para que no devuelva basura
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


void Socio::Mostrar() {
    ArchivoSocios arcSoc;

    vector<int> largos = arcSoc.BuscarMasLargo();

    char altura[10];
    sprintf(altura, "%d", domicilio.getAltura());

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


    /// Busca en el registro las palabras mas largas, usando como minimo el titulo de columna
    for (int i = 0; i < contarRegistros(); i++) {
        Socio reg = leerRegistro(i);

        int lenDNI = strlen(reg.getDni());
        int lenNombre = strlen(reg.getNombre());
        int lenApellido = strlen(reg.getApellido());
        int lenEmail = strlen(reg.getEmail());

        int lenCalle = strlen(reg.getDomicilio().getCalle());
        char alturaStr[12];
        sprintf(alturaStr, "%d", reg.getDomicilio().getAltura());
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


void ArchivoSocios::MostrarHeader() {  /// Muestra el Header de la tabla
    vector<int> largos = BuscarMasLargo(); /// Copia el vector de BuscarMasLargo

    /// Crea un char de cada titulo de fila
    char dni[] = "DNI";
    char nombre[] = "NOMBRE";
    char apellido[] = "APELLIDO";
    char email[] = "EMAIL";
    char calle[] = "CALLE";
    char altura[] = "ALTURA";
    char localidad[] = "LOCALIDAD";
    char partido[] = "PARTIDO";
    char CodigoPostal[] = "CP";

    /// Arma el titulo de tabla con el (titulo tabla, largo maximo de palabra)
    cout << " " << espaciarTexto(dni, largos[0])
         << " │ " << espaciarTexto(nombre, largos[1])
         << " │ " << espaciarTexto(apellido, largos[2])
         << " │ " << espaciarTexto(calle, largos[3])
         << " │ " << espaciarTexto(altura, largos[4])
         << " │ " << espaciarTexto(localidad, largos[5])
         << " │ " << espaciarTexto(partido, largos[6])
         << " │ " << espaciarTexto(CodigoPostal, largos[7])
         << " │ " << espaciarTexto(email, largos[8])  << "\n";

        cout << "────────────────────────────────────────────────────────────────────────────────────────────────────\n";
}



void ArchivoSocios::BuscarDni(const char* dni) {
    bool encontrado = false;
    int pos = buscarRegistro(dni);
    if (pos != -1) { /// Verifica que se encuentre el registro
        if (!encontrado) { /// Verfica que este en false para mostrar el header
            MostrarHeader();
            encontrado = true; /// Setea en true para no volver a mostrarlo
        }
        MostrarBusqueda(pos);
    }
    if (!encontrado) {
        cout << "DNI NO ENCONTRADO." << endl;
    }
}

void ArchivoSocios::BuscarNombre(const char* nombre, const char* apellido) {
    bool encontrado = false;
    int pos = -1;
    for (int i=0; i < contarRegistros(); i++) { /// Lee todos los registros
        if (strcmp(leerRegistro(i).getNombre(),nombre) == 0
            && strcmp(leerRegistro(i).getApellido(),apellido) == 0) { /// Verifica que se encuentre el registro
            if (!encontrado) {  /// Verfica que este en false para mostrar el header
                MostrarHeader();
                encontrado = true; /// Setea en true para no volver a mostrarlo
            }
            MostrarBusqueda(i); /// Muestra la coincidencia
        }
    }
    if (!encontrado) {
        cout << "DNI NO ENCONTRADO." << endl;
    }
}

void ArchivoSocios::Eliminar() {
    /// Llama la opcion de mostrarBusqueda y asi obtener el objeto
    char dni[10];
    cout << ">> Ingrese DNI socio a eliminar: ";
    cargarCadena(dni,9);
    int pos = buscarRegistro(dni);

    if (buscarRegistro(dni) > -1) { /// Busca el dni en el registro
        MostrarHeader();
        Socio obj = MostrarBusqueda(pos);
        cout << endl;
        cout << "ELIMINAR ESTE SOCIO? (S/N): ";
        char opc;
        cin >> opc;
        if (opc == 'S' || opc == 's') {
            /// Busca la posicion en el regsitro del DNI
            int pos = buscarRegistro(obj.getDni());
            obj.setDni("-1");
            obj.setNombre(" ");
            obj.setApellido(" ");

            /// Modifica el objeto en esa posicion
            modificarRegistro(obj, pos);
            cout << "SOCIO ELIMINADO" << endl;
        }
    } else {
        cout << "SOCIO INEXISTENTE." << endl;
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

/// lee el archivo de libros y los muestra en pantalla
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

