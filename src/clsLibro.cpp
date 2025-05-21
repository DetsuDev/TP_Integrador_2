#include <iostream>
#include <cstring>
#include "clsLibro.h"
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
