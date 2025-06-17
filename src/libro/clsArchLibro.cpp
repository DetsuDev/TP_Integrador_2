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
    cout << "│ " << isbn << espaciarTexto(isbn, 11)
    << "│ " << titulo << espaciarTexto(titulo, 11)
    << "│ " << autor << espaciarTexto(autor, 11)
    << "│ " << anioStr << espaciarTexto(anioStr, 10)
    << "│ " << cantEjStr << espaciarTexto(cantEjStr, 11) << "│\n";
    cout << "├────────────┼────────────┼────────────┼───────────┼────────────┤\n";
}

void ArchivoLibros::MostrarHeader() {
    Libro obj;
    for (int i=0; i < contarRegistros(); i++) {
        if (strcmp(leerRegistro(i).getISBN(), "-1") != 0) {
        cout << "┌────────────┬────────────┬────────────┬───────────┬────────────┐\n";
        cout << "│ ISBN       │ TITULO     │ AUTOR      │ AÑO PUBL  │ EJEMPLARES │\n";
        cout << "├────────────┼────────────┼────────────┼───────────┼────────────┤\n";
        break;
        }
    }
}

void ArchivoLibros::Eliminar() {
    /// Llama la opcion de buscar y asi obtener el objeto
    Libro obj = Buscar();
    cout << endl;

    if (strcmp(obj.getISBN(), "-1") != 0) {
    cout << "ELIMINAR ESTE LIBRO? (S/N): ";
    char opc;
    cin >> opc;
    if (opc == 'S' || opc == 's'){
            /// Busca la posicion en el regsitro del DNI
            int pos = buscarRegistro(obj.getISBN());
            obj.setISBN("-1");

            /// Modifica el objeto en esa posicion
        modificarRegistro(obj, pos);
            cout << "LIBRO ELIMINADO " << endl;
    }
    }
}

Libro ArchivoLibros::modificarLibros(){
    Libro obj;
    int ejemplares;
    cout << "Ingrese la nueva cantidad de ejemplares: ";
    cin >> ejemplares;
    obj.setCantidadEjemplares(ejemplares);

    return obj;
}


Libro ArchivoLibros::Buscar() {
    string opc;
    char isbn[10];
    cout << ">> Ingrese ISBN libro: ";
    cargarCadena(isbn,9);
    /// Busca el isbn en el registro y obtiene la posicione
    int pos = buscarRegistro(isbn);
    if(pos != -1) {
        Libro obj = leerRegistro(pos);
        MostrarHeader();
        /// Muestra el objeto de esa posicon
        obj.Mostrar();
        /// Devuelve el objeto para usarlo en la funcion de Eliminar, el problema es que si no buscamos eliminar no tiene utilidad
        cout << endl;
        cout << "DESEA MODIFICAR LAS EXISTENCIAS DE ESTE LIBRO? [s/n]: ";
        cin >> opc;
        if(opc == "s" || opc == "S"){
        }
        else{
            return obj;
        }
    } else {
        cout << "LIBRO NO ENCONTRADO." << endl;
        /// Crea un objeto auxiliar
        Libro aux;
        /// Setea el estado en false
        aux.setISBN("-1");
        return aux;
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

