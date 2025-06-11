#include <iostream>
#include <cstring>
#include "libro/clsLibro.h"
#include "libro/clsArchLibro.h"
#include "funciones.h"

using namespace std;

void Libro::Cargar()
{
    cout << "INGRESE ISBN: ";
    cargarCadena(isbn, 19);
    cout << "INGRESE TÍTULO: ";
    cargarCadena(titulo, 49);
    cout << "INGRESE AUTOR: ";
    cargarCadena(autor, 49);
    cout << "INGRESE AÑO DE PUBLICACIÓN: ";
    cin >> anioPublicacion;
    cout << "INGRESE CANTIDAD DE EJEMPLARES: ";
    cin >> cantidadEjemplares;
}

void Libro::Mostrar()
{
    cout << "ISBN: " << isbn << endl;
    cout << "TÍTULO: " << titulo << endl;
    cout << "AUTOR: " << autor << endl;
    cout << "AÑO DE PUBLICACIÓN: " << anioPublicacion << endl;
    cout << "CANTIDAD DE EJEMPLARES: " << cantidadEjemplares << endl;
}

// esta funcion crea el objeto libr, luego ejecuta el metodo "Cargar()", luego crea el objeto "ArcLibr" y graba los registros en el archivo de libros
void Libro::registrarLibro()
{
    Libro libr;
    libr.Cargar();
    ArchivoLibros ArcLibr;
    ArcLibr.grabarRegistro(libr);

}

// lee el archivo de libros y los muestra en pantalla
void Libro::listarLibro()
{
    ArchivoLibros arcLibr;
    Libro libr;
    //libr.Cargar();
    int cantReg = arcLibr.contarRegistros();
    for(int i=0; i<cantReg; i++)
    {
        libr = arcLibr.leerRegistro(i);
        libr.Mostrar();
        cout << endl;
    }

}

void Libro::setISBN(const char *i) { strcpy(isbn, i); }
void Libro::setTitulo(const char *t) { strcpy(titulo, t); }
void Libro::setAutor(const char *a) { strcpy(autor, a); }
void Libro::setAnioPublicacion(int a) { anioPublicacion = a; }
void Libro::setCantidadEjemplares(int c) { cantidadEjemplares = c; }

const char* Libro::getISBN() { return isbn; }
const char* Libro::getTitulo() { return titulo; }
const char* Libro::getAutor() { return autor; }
int Libro::getAnioPublicacion() { return anioPublicacion; }
int Libro::getCantidadEjemplares() { return cantidadEjemplares; }
