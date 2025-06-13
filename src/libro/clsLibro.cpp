#include <iostream>
#include <cstring>
#include "libro/clsLibro.h"

void Libro::setISBN(const char *i) {
    strcpy(isbn, i);
}
void Libro::setTitulo(const char *t) {
    strcpy(titulo, t);
}
void Libro::setAutor(const char *a) {
    strcpy(autor, a);
}
void Libro::setAnioPublicacion(int a) {
    anioPublicacion = a;
}
void Libro::setCantidadEjemplares(int c) {
    cantidadEjemplares = c;
}
void Libro::setEstado(bool e) {
    estado = e;
}

bool Libro::getEstado() {
    return estado;
}

const char* Libro::getISBN() {
    return isbn;
}
const char* Libro::getTitulo() {
    return titulo;
}
const char* Libro::getAutor() {
    return autor;
}
int Libro::getAnioPublicacion() {
    return anioPublicacion;
}
int Libro::getCantidadEjemplares() {
    return cantidadEjemplares;
}
