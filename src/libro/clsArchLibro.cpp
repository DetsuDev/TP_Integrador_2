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
    char anioStr[10];
    sprintf(anioStr, "%d", anioPublicacion);
    char cantEjStr[10];
    sprintf(cantEjStr, "%d", cantidadEjemplares);
    cout << "│ " << isbn << espaciarTexto(isbn, 11) << "│ " << titulo << espaciarTexto(titulo, 11) << "│ " << autor << espaciarTexto(autor, 11) << "│ " << anioStr << espaciarTexto(anioStr, 10) << "│ " << cantEjStr << espaciarTexto(cantEjStr, 11) << "│\n";
    cout << "├────────────┼────────────┼────────────┼───────────┼────────────┤\n";
}

void ArchivoLibros::MostrarHeader() {
    cout << "┌────────────┬────────────┬────────────┬───────────┬────────────┐\n";
    cout << "│ ISBN       │ TITULO     │ AUTOR      │ AÑO PUBL  │ EJEMPLARES │\n";
    cout << "├────────────┼────────────┼────────────┼───────────┼────────────┤\n";

}

void ArchivoLibros::Eliminar() {
    Libro obj = Buscar();
    cout << endl;
    cout << "ELIMINAR ESTE LIBRO? (S/N): ";
    char opc;
    cin >> opc;
    if (opc == 'S' || opc == 's'){
        obj.setEstado(false);
        modificarRegistro(obj, buscarRegistro(obj.getISBN()));
        cout << "LIBRO [" << obj.getISBN() << "] ELIMINADO" << endl;
    }
}

Libro ArchivoLibros::Buscar() {
    char isbn[10];
    cout << ">> Ingrese ISBN libro: ";
    cargarCadena(isbn,9);
    int pos = buscarRegistro(isbn);
    if(pos != -1) {
        Libro obj = leerRegistro(pos);
        MostrarHeader();
        obj.Mostrar();
        return obj;
    } else {
        cout << "DNI NO ENCONTRADO." << endl;
    }
}
// esta funcion crea el objeto libr, luego ejecuta el metodo "Cargar()", luego crea el objeto "ArcLibr" y graba los registros en el archivo de libros
void ArchivoLibros::Registrar()
{
    Libro obj;
    if (obj.Cargar(*this))
    {
        obj.setEstado(true);

        grabarRegistro(obj);
    }
}

// lee el archivo de libros y los muestra en pantalla
void ArchivoLibros::Listar()
{
    Libro obj;
    MostrarHeader();
    int cantReg = contarRegistros();
    for(int i=0; i<cantReg; i++)
    {
        obj = leerRegistro(i);
        if (obj.getEstado())
        {
            obj.Mostrar();
        }
    }

}

