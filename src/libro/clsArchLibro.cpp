#include <iostream>
#include <cstring>
#include "libro/clsArchLibro.h"
#include "funciones.h"
#include "prestamo/clsArchPrestamo.h"
#include "prestamo/clsPrestamo.h"
#include <vector>

using namespace std;

ArchivoLibros::ArchivoLibros(const char *n) {
    strcpy(nombre, n);
}

Libro ArchivoLibros::leerRegistro(int pos) {
    Libro obj;
    FILE *p = fopen(nombre, "rb");
    fseek(p, pos * sizeof obj, 0);
    if (pos < 0) {
        return obj; /// Recrea el objeto para que no devuelva basura
    }
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoLibros::grabarRegistro(Libro obj) {
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr) {
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoLibros::modificarRegistro(Libro obj, int pos) {
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

int ArchivoLibros::contarRegistros() {
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr) {
        return -1;
    }
    fseek(p, 0, 2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof (Libro);
}

int ArchivoLibros::buscarRegistro(const char *isbn) {
    Libro obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++) {
        obj = leerRegistro(i);
        if(strcmp(obj.getISBN(), isbn) == 0) {
            //if(obj.getISBN() == isbn){
            return i;
        }
    }
    return -1;
}

bool Libro::Cargar(ArchivoLibros &arcLibro) {
    cout << "INGRESE ISBN: ";
    cargarCadena(isbn, 19);

    if (arcLibro.buscarRegistro(isbn) == -1) {
        cout << "INGRESE TÍTULO: ";
        cargarCadena(titulo, 49);
        cout << "INGRESE AUTOR: ";
        cargarCadena(autor, 49);
        cout << "INGRESE AÑO DE PUBLICACIÓN: ";
        cin >> anioPublicacion;
        cout << "INGRESE CANTIDAD DE EJEMPLARES: ";
        cin >> cantidadEjemplares;
        return true;
    } else {
        cout << "ISBN: [" << isbn << "] YA EXISTENTE." << endl;
        return false;
    }
}


void Libro::Mostrar() {
    ArchivoLibros arcLibros;
    vector<int> largos = arcLibros.BuscarMasLargo();
    char anioStr[8];
    sprintf(anioStr, "%i", anioPublicacion);
    char cantEjStr[10];
    sprintf(cantEjStr, "%i", cantidadEjemplares);
    cout << " " << espaciarTexto(isbn, largos[0])
         << " │ " << espaciarTexto(titulo, largos[1])
         << " │ " << espaciarTexto(autor, largos[2])
         << " │ " << espaciarTexto(anioStr, 8)
         << " │ " << espaciarTexto(cantEjStr, 10) << "\n";
}

vector<int> ArchivoLibros::BuscarMasLargo() {

    int MasLargoISBN = strlen("ISBN");
    int MasLargoAutor = strlen("TITULO");
    int MasLargoTitulo = strlen("AUTOR");
    int MasLargoCant = strlen("EJEMPLARES");

    /// Busca en el registro las palabras mas largas, usando como minimo el titulo de columna
        for (int i = 0; i < contarRegistros(); i++) {
            Libro reg = leerRegistro(i);
            int lenISBN = strlen(reg.getISBN());
            int lenAutor = strlen(reg.getAutor());
            int lenTitulo = strlen(reg.getTitulo());
            char cantStr[10];
            sprintf(cantStr, "%i", reg.getCantidadEjemplares());


            int lenCant = strlen(cantStr);

            if (lenISBN > MasLargoISBN) {
                MasLargoISBN = lenISBN;
            }
            if (lenAutor > MasLargoAutor) {
                MasLargoAutor = lenAutor;
            }
            if (lenTitulo > MasLargoTitulo) {
                MasLargoTitulo = lenTitulo;
            }
            if (lenCant > MasLargoCant) {
                MasLargoCant = lenCant;
            }
        }
    return {MasLargoISBN, MasLargoTitulo, MasLargoAutor, MasLargoCant};
}

void ArchivoLibros::MostrarHeader() { /// Muestra el Header de la tabla
    vector<int> largos = BuscarMasLargo(); /// Copia el vector de BuscarMasLargo

    /// Crea un char de cada titulo de fila
    char isbn[] = "ISBN";
    char titulo[] = "TITULO";
    char autor[] = "AUTOR";
    char ejempl[] = "EJEMPLARES";

    /// Arma el titulo de tabla con el (titulo tabla, largo maximo de palabra)
    cout << " " << espaciarTexto(isbn, largos[0])
         << " │ " << espaciarTexto(titulo, largos[1])
         << " │ " << espaciarTexto(autor, largos[2])
         << " │ AÑO PUBL"
         << " │ " << espaciarTexto(ejempl, largos[3]) << "\n";
    cout << "───────────────────────────────────────────────────────────────────────\n";

}



void ArchivoLibros::BuscarISBN(const char* isbn) {
    bool encontrado = false;
    int pos = buscarRegistro(isbn);

    if (pos != -1) { /// Verifica que se encuentre el registro
        if (!encontrado) { /// Verfica que este en false para mostrar el header
            MostrarHeader();
            encontrado = true;/// Setea en true para no volver a mostrarlo

        }
        MostrarBusqueda(pos);
    }
    if (!encontrado) {
        cout << "ISBN NO ENCONTRADO" << endl;
    }
}

void ArchivoLibros::BuscarTitulo(const char* titulo) {
    bool encontrado = false;
    int pos = -1;
    for (int i=0; i < contarRegistros(); i++) { /// Lee todos los registros
        if (strcmp(leerRegistro(i).getTitulo(),titulo) == 0) { /// Verifica que se encuentre el registro
            if (!encontrado) { /// Verfica que este en false para mostrar el header
                MostrarHeader();
                encontrado = true; /// Setea en true para no volver a mostrarlo

            }
            MostrarBusqueda(i); /// Muestra la coincidencia
        }
    }
    if (!encontrado) {
        cout << "TÍTULO NO ENCONTRADO" << endl;
    }
}

void ArchivoLibros::BuscarAutor(const char* autor) {
    bool encontrado = false;
    int pos = -1;
    for (int i=0; i < contarRegistros(); i++) { /// Lee todos los registros
        if (strcmp(leerRegistro(i).getAutor(),autor) == 0) { /// Verifica que se encuentre el registro
            if (!encontrado) { /// Verfica que este en false para mostrar el header
                MostrarHeader();
                encontrado = true;  /// Setea en true para no volver a mostrarlo

            }
            MostrarBusqueda(i);/// Muestra la coincidencia
        }
    }
    if (!encontrado) {
        cout << "AUTOR NO ENCONTRADO" << endl;
    }
}

void ArchivoLibros::BuscarDisponibilidad() {
    MostrarHeader();
    int cant = 0;
    for (int i=0; i < contarRegistros(); i++) { /// Lee todos los registros
        if (leerRegistro(i).getCantidadEjemplares() > 0) {
            MostrarBusqueda(i);
            cant++; /// Cuenta los registros
        }
    }
    if (cant > 0) {
        cout << "Libros distintos en stock: " << cant << endl;
    } else {
        cout << "NO HAY LIBROS EN STOCK" << endl;
    }
}


void ArchivoLibros::Eliminar() {
    /// Llama la opcion de mostrarBusqueda y asi obtener el objeto
    Prestamo prest;
    ArchivoPrestamo arcPrest;
    char isbn[20];
    cout << ">> Ingrese ISBN del libro a eliminar: ";
    cargarCadena(isbn,19);
    int pos = buscarRegistro(isbn);
    int posPrest = arcPrest.buscarISBN(isbn);

    if (buscarRegistro(isbn) > -1) { /// Busca el isbn en el registro
        MostrarHeader();
        Libro obj = MostrarBusqueda(pos);
        cout << endl;
        cout << "ELIMINAR ESTE LIBRO? (S/N): ";
        char opc;
        cin >> opc;
        if (opc == 'S' || opc == 's') {
            /// Busca la posicion en el registro del DNI
            int pos = buscarRegistro(obj.getISBN());
            obj.setISBN("-1");
            obj.setAutor(" ");
            obj.setTitulo(" ");
            obj.setCantidadEjemplares(-1);

        if(posPrest != -1){ /// borra el prestamo que este a nombre de este dni
            prest = arcPrest.leerRegistro(posPrest);
            prest.setIdPrestamo(-1);
            arcPrest.modificarRegistro(prest,posPrest);
        }
            /// Modifica el objeto en esa posicion
            modificarRegistro(obj, pos);
            cout << "LIBRO ELIMINADO " << endl;
        }
    } else {
        cout << "LIBRO INEXISTENTE." << endl;
    }
}

void ArchivoLibros::ModificarEjemplares() {
    char isbn[20];
    int cantEjemp = 0;
    cout << ">> Ingrese ISBN del libro a modificar: ";
    cargarCadena(isbn,19);
    if (buscarRegistro(isbn) > -1) {
        MostrarHeader();
        int pos = buscarRegistro(isbn); /// Busca el isbn
        Libro obj = MostrarBusqueda(pos); /// Muestra el objeto resultante
        cout << endl;
        cout << "DESEA MODIFICAR LAS EXISTENCIAS DE ESTE LIBRO? [s/n]: ";
        char opc;
        cin >> opc;
        if(opc == 's' || opc == 'S') {
            cout << "ingrese cantidad de libros: ";
            cin >> cantEjemp;
            obj.setCantidadEjemplares(cantEjemp); /// Setea la cantidad de ejemplares
            cout << "LIBRO MODIFICADO [" << isbn << "] \n";
            modificarRegistro(obj, pos); /// Modifica el objeto en esa posicion
        } else {
            cout << "Operacion cancelada. \n";
        }
    } else {
        cout << "LIBRO INEXISTENTE." << endl;
    }

}

Libro ArchivoLibros::MostrarBusqueda(int pos) {

    if(pos != -1) {
        char opc;
        int cantEjemp;
        Libro obj = leerRegistro(pos);
        /// Muestra el objeto de esa posicon
        obj.Mostrar();
        /// Devuelve el objeto para usarlo en la funcion de Eliminar, el problema es que si no buscamos eliminar no tiene utilidad

        return obj;
    } else {
        /// Crea un objeto auxiliar
        Libro aux;
        /// Setea el ISBN en -1
        aux.setISBN("-1");
        return aux;
    }
}
// esta funcion crea el objeto libr, luego ejecuta el metodo "Cargar()", luego crea el objeto "ArcLibr" y graba los registros en el archivo de libros

void ArchivoLibros::Registrar() {
    Libro obj;
    if (obj.Cargar(*this)) {
        int posLibre = -1;
        for (int i = 0; i < contarRegistros(); i++) {
            /// Busca la posicion libre (ISBN = -1) y la guarda en una variable
            if (strcmp(leerRegistro(i).getISBN(), "-1") == 0) {
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
void ArchivoLibros::Listar() {
    MostrarHeader();
    Libro obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++) {
        obj = leerRegistro(i);
        /// Verifica si esta ocupada la direccion para mostrarla
        if (strcmp(leerRegistro(i).getISBN(), "-1") != 0) {
            obj.Mostrar();
        }
    }
}

