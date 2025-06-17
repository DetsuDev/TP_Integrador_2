#include <iostream>
#include <cstring>
#include "libro/clsArchLibro.h"
#include "funciones.h"
#include <vector>

using namespace std;

ArchivoLibros::ArchivoLibros(const char *n) {
    strcpy(nombre, n);
}

Libro ArchivoLibros::leerRegistro(int pos) {
    Libro obj;
    FILE *p = fopen(nombre, "rb");
    fseek(p, pos * sizeof obj, 0);
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

    if (arcLibro.buscarRegistro(isbn) == -1)
    {
        cout << "INGRESE TÍTULO: ";
        cargarCadena(titulo, 49);
        cout << "INGRESE AUTOR: ";
        cargarCadena(autor, 49);
        cout << "INGRESE AÑO DE PUBLICACIÓN: ";
        cin >> anioPublicacion;
        cout << "INGRESE CANTIDAD DE EJEMPLARES: ";
        cin >> cantidadEjemplares;
        return true;
<<<<<<< Updated upstream
    }
    else
    {
=======
    } else {
>>>>>>> Stashed changes
        cout << "ISBN: [" << isbn << "] YA EXISTENTE." << endl;
        return false;
    }
}


void Libro::Mostrar() {
    ArchivoLibros arcLibros;
    vector<int> largos = arcLibros.BuscarMayor();
    int MasLargoISBN = largos[0];
    int MasLargoTitulo = largos[1];
    int MasLargoAutor = largos[2];
    char anioStr[8];
    sprintf(anioStr, "%d", anioPublicacion);
    char cantEjStr[10];
    sprintf(cantEjStr, "%d", cantidadEjemplares);
<<<<<<< Updated upstream
    cout << "│ " << isbn << espaciarTexto(isbn, 11)
         << "│ " << titulo << espaciarTexto(titulo, 11)
         << "│ " << autor << espaciarTexto(autor, 11)
         << "│ " << anioStr << espaciarTexto(anioStr, 10)
         << "│ " << cantEjStr << espaciarTexto(cantEjStr, 11) << "│\n";
    cout << "├────────────┼────────────┼────────────┼───────────┼────────────┤\n";
}

void ArchivoLibros::MostrarHeader()
{
    for (int i=0; i < contarRegistros(); i++)
    {
        if (strcmp(leerRegistro(i).getISBN(), "-1") != 0)
        {
            cout << "┌────────────┬────────────┬────────────┬───────────┬────────────┐\n";
            cout << "│ ISBN       │ TITULO     │ AUTOR      │ AÑO PUBL  │ EJEMPLARES │\n";
            cout << "├────────────┼────────────┼────────────┼───────────┼────────────┤\n";
=======
    cout << "│ " << espaciarTexto(isbn, MasLargoISBN)
         << " │ " << espaciarTexto(titulo, MasLargoTitulo)
         << " │ " << espaciarTexto(autor, MasLargoAutor)
         << " │ " << espaciarTexto(anioStr, 8)
         << " │ " << espaciarTexto(cantEjStr, 10) << " │\n";
}

vector<int> ArchivoLibros::BuscarMayor() {

    int MasLargoISBN = -1;
    int MasLargoAutor = -1;
    int MasLargoTitulo = -1;
    int MasLargoCant = -1;


    for (int i=0; i < contarRegistros(); i++) {
        for (int i = 0; i < contarRegistros(); i++) {
            Libro reg = leerRegistro(i);
            int lenISBN = strlen(reg.getISBN());
            int lenAutor = strlen(reg.getAutor());
            int lenTitulo = strlen(reg.getTitulo());
            char cantStr[10];
            sprintf(cantStr, "%d", reg.getCantidadEjemplares());


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
    }
    return {MasLargoISBN, MasLargoTitulo, MasLargoAutor, MasLargoCant};
}

void ArchivoLibros::MostrarHeader() {
    vector<int> largos = BuscarMayor();
    int MasLargoISBN = largos[0];
    int MasLargoTitulo = largos[1];
    int MasLargoAutor = largos[2];
    int MasLargoCant = largos[3];
    char isbn[] = "ISBN";
    char titulo[] = "TITULO";
    char autor[] = "AUTOR";
    char ejempl[] = "EJEMPLARES";

    for (int i = 0; i < contarRegistros(); i++) {
        if (strcmp(leerRegistro(i).getISBN(), "-1") != 0) {
            cout << "│ " << espaciarTexto(isbn, MasLargoISBN)
                 << " │ " << espaciarTexto(titulo, MasLargoTitulo)
                 << " │ " << espaciarTexto(autor, MasLargoAutor)
                 << " │ AÑO PUBL"
                 << " │ " << espaciarTexto(ejempl, MasLargoCant) << " │ \n";
>>>>>>> Stashed changes
            break;
        }
    }
}

void ArchivoLibros::Eliminar()
{
    /// Llama la opcion de buscar y asi obtener el objeto
    char isbn[20];
    cout << ">> Ingrese ISBN del libro a eliminar: ";
    cargarCadena(isbn,19);
    int pos = buscarRegistro(isbn);

    Libro obj = MostrarBusqueda(pos);
    cout << endl;

<<<<<<< Updated upstream
    if (strcmp(obj.getISBN(), "-1") != 0)
    {
        cout << "ELIMINAR ESTE LIBRO? (S/N): ";
        char opc;
        cin >> opc;
        if (opc == 'S' || opc == 's')
        {
=======
    if (strcmp(obj.getISBN(), "-1") != 0) {
        cout << "ELIMINAR ESTE LIBRO? (S/N): ";
        char opc;
        cin >> opc;
        if (opc == 'S' || opc == 's') {
>>>>>>> Stashed changes
            /// Busca la posicion en el regsitro del DNI
            int pos = buscarRegistro(obj.getISBN());
            obj.setISBN("-1");
            obj.setAutor(" ");
            obj.setTitulo(" ");
            obj.setCantidadEjemplares(-1);

            /// Modifica el objeto en esa posicion
            modificarRegistro(obj, pos);
            cout << "LIBRO ELIMINADO " << endl;
        }
    }
}



void ArchivoLibros::BuscarISBN(const char* isbn)
{
    bool encontrado = false;
    /// Busca el isbn en el registro y obtiene su posicion
    int pos = buscarRegistro(isbn);

    if (pos != -1)
    {
        Libro obj = MostrarBusqueda(pos);
        modificarRegistro(obj,pos);
    }
    else
    {
        cout << "ISBN NO ENCONTRADO" << endl;
    }
}

void ArchivoLibros::BuscarTitulo(const char* titulo)
{
    bool encontrado = false;
    int pos = -1;
    for (int i=0; i < contarRegistros(); i++)
    {
        if (strcmp(leerRegistro(i).getTitulo(),titulo) == 0)
        {
            MostrarBusqueda(i);
            encontrado = true;
        }
    }
    if (!encontrado)
    {
        cout << "TÍTULO NO ENCONTRADO" << endl;
    }
}

void ArchivoLibros::BuscarAutor(const char* autor)
{
    bool encontrado = false;
    int pos = -1;
    for (int i=0; i < contarRegistros(); i++)
    {
        if (strcmp(leerRegistro(i).getAutor(),autor) == 0)
        {
            MostrarBusqueda(i);
            encontrado = true;
        }
    }
    if (!encontrado)
    {
        cout << "AUTOR NO ENCONTRADO" << endl;
    }
}

void ArchivoLibros::BuscarCantEjemp(int cant)
{

    bool encontrado = false;
    for (int i=0; i < contarRegistros(); i++)
    {
        if (leerRegistro(i).getCantidadEjemplares() > cant)
        {
            /// Consigue la posicion en el registro gracias al ISBN
            MostrarBusqueda(i);
        }
    }
    if (!encontrado)
    {
        cout << "NO HAY DISPONIBILIDAD" << endl;
    }
}

Libro ArchivoLibros::MostrarBusqueda(int pos)
{
    if(pos != -1)
    {
        char opc;
        int cantEjemp;
        Libro obj = leerRegistro(pos);
        MostrarHeader();
        /// Muestra el objeto de esa posicon
        obj.Mostrar();
        /// Devuelve el objeto para usarlo en la funcion de Eliminar, el problema es que si no buscamos eliminar no tiene utilidad
        cout << endl;
        cout << "DESEA MODIFICAR LAS EXISTENCIAS DE ESTE LIBRO? [s/n]: ";
        cin >> opc;
        if(opc == 's' || opc == 'S')
        {
            cout << "ingrese cantidad de libros: ";
            cin >> cantEjemp;
            obj.setCantidadEjemplares(cantEjemp);
            return obj;
<<<<<<< Updated upstream
        }
        else
        {
=======
        } else {
>>>>>>> Stashed changes
            return obj;
        }
    }
    else
    {
        /// Crea un objeto auxiliar
        Libro aux;
        /// Setea el ISBN en -1
        aux.setISBN("-1");
        return aux;
    }
}
// esta funcion crea el objeto libr, luego ejecuta el metodo "Cargar()", luego crea el objeto "ArcLibr" y graba los registros en el archivo de libros
<<<<<<< Updated upstream
void ArchivoLibros::Registrar()
{
    Libro obj;
    if (obj.Cargar(*this))
    {
        int posLibre = -1;
        for (int i = 0; i < contarRegistros(); i++)
        {
            /// Busca la posicion libre (ISBN = -1) y la guarda en una variable
            if (strcmp(leerRegistro(i).getISBN(), "-1") == 0)
            {
=======
void ArchivoLibros::Registrar() {
    Libro obj;
    if (obj.Cargar(*this)) {
        int posLibre = -1;
        for (int i = 0; i < contarRegistros(); i++) {
            /// Busca la posicion libre (ISBN = -1) y la guarda en una variable
            if (strcmp(leerRegistro(i).getISBN(), "-1") == 0) {
>>>>>>> Stashed changes
                posLibre = i;
                break;
            }
        }
        /// Verifica si existe posicion libre
<<<<<<< Updated upstream
        if (posLibre != -1)
        {
            /// Escribe en esa posicion
            modificarRegistro(obj, posLibre);
        }
        else
        {
=======
        if (posLibre != -1) {
            /// Escribe en esa posicion
            modificarRegistro(obj, posLibre);
        } else {
>>>>>>> Stashed changes
            /// Si no la encuentra, guarda en una nueva posicion
            grabarRegistro(obj);
        }
    }
}

// lee el archivo de libros y los muestra en pantalla
<<<<<<< Updated upstream
void ArchivoLibros::Listar()
{
=======
void ArchivoLibros::Listar() {
>>>>>>> Stashed changes
    MostrarHeader();
    Libro obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++)
    {
        obj = leerRegistro(i);
        /// Verifica si esta ocupada la direccion para mostrarla
<<<<<<< Updated upstream
        if (strcmp(leerRegistro(i).getISBN(), "-1") != 0)
        {
=======
        if (strcmp(leerRegistro(i).getISBN(), "-1") != 0) {
>>>>>>> Stashed changes
            obj.Mostrar();
        }
    }

}

