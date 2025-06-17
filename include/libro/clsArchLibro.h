#ifndef CLSARCHLIBRO_H_INCLUDED
#define CLSARCHLIBRO_H_INCLUDED

#include "libro/clsLibro.h"
#include <vector>

using namespace std;

class ArchivoLibros {
private:
    char nombre[30];
public:
    ArchivoLibros(const char *n="FILES/current/Libros.dat");
    Libro leerRegistro(int);
    Libro modificarLibros();
    bool grabarRegistro(Libro);
    bool modificarRegistro(Libro, int);
    int contarRegistros();
    int buscarRegistro(const char *isbn);

    void Mostrar();
    void Registrar();
    void Eliminar();
    void Listar();


    vector<int> BuscarMayor();
    Libro MostrarBusqueda(int pos);
    void BuscarISBN(const char* isbn);
    void BuscarTitulo(const char* titulo);
    void BuscarAutor(const char* autor);
    void BuscarCantEjemp(int cantidad);
    void MostrarHeader();
};

#endif // CLSARCHLIBRO_H_INCLUDED



