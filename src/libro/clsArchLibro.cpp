#include <iostream>
#include <cstring>
#include "libro/clsArchLibro.h"
#include "funciones.h"

using namespace std;

ArchivoLibros::ArchivoLibros(const char *n)
{
    strcpy(nombre, n);
}

Libro ArchivoLibros::leerRegistro(int pos)
{
    Libro obj;
    FILE *p = fopen(nombre, "rb");
    fseek(p, pos * sizeof obj, 0);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoLibros::grabarRegistro(Libro obj)
{
    FILE *p = fopen(nombre, "ab");
    if(p == nullptr)
    {
        return false;
    }
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoLibros::modificarRegistro(Libro obj, int pos)
{
    FILE *p;
    p = fopen(nombre, "rb+");
    if(p == nullptr)
    {
        return false;
    }
    fseek(p, pos * sizeof obj, 0);
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoLibros::contarRegistros()
{
    FILE *p = fopen(nombre, "rb");
    if(p == nullptr)
    {
        return -1;
    }
    fseek(p, 0, 2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof (Libro);
}

int ArchivoLibros::buscarRegistro(const char *isbn)
{
    Libro obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++)
    {
        obj = leerRegistro(i);
        if(strcmp(obj.getISBN(), isbn) == 0)
        {
            //if(obj.getISBN() == isbn){
            return i;
        }
    }
    return -1;
}

bool Libro::Cargar(ArchivoLibros &arcLibro)
{
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
    }
    else
    {
        cout << "ISBN: [" << isbn << "] YA EXISTENTE." << endl;
        return false;
    }
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
void ArchivoLibros::RegistrarLibro()
{
    Libro obj;
    if (obj.Cargar(*this))
    {
        obj.setEstado(true);

        grabarRegistro(obj);
    }
}

// lee el archivo de libros y los muestra en pantalla
void ArchivoLibros::ListarLibro()
{
    Libro obj;
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++)
    {
        obj = leerRegistro(i);
        if (obj.getEstado())
        {
            obj.Mostrar();
            cout << endl;
        }
    }

}

