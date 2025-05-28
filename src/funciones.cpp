/// Objeto Socio: DNI, Nombre, Direccion, Email, Fecha de Nacimiento
/// Objeto Libro: ISBN, Nombre del libro, Nombre del autor, Fecha de publicacion, cantidad de ejemplares
/// Objeto Prestamos: Libro prestado, Socio al que se le presto, fecha del prestamo, fecha de devolucion
/// Objeto Cuota: Numero de Socio, Fecha de pago, Importe, Mes, Año, Importe

#include <iostream>
#include <cstring>
#include "clsArchSocios.h"
#include "clsArchLibro.h"
#include "clsSocio.h"
#include "funciones.h"
#include "clsLibro.h"


using namespace std;
void menuPrincipal()
{
    system("chcp 65001 > nul");
    int opc = 0;

    bool menu=true;
    while(menu)
    {
        system("cls");
        cout << "╔══════════════════════════════════════╗\n";
        cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "╟── REGISTRO ──────────────────────────╣\n";
        cout << "║                                      ║\n";
        cout << "║  [1] Gestionar Socio                 ║\n";
        cout << "║  [2] Gestionar Libro                 ║\n";
        cout << "║  [3] Gestionar Prestamo              ║\n";
        cout << "║  [4] Gestionar Cuota                 ║\n";
        cout << "║                                      ║\n";
        cout << "╟── SISTEMA ───────────────────────────╣\n";
        cout << "║                                      ║\n";
        cout << "║  [8] RESTAURACION                    ║\n";
        cout << "║  [9] EXPORTAR/IMPORTAR               ║\n";
        cout << "║                                      ║\n";
        cout << "╟──────────────────────────────────────╣\n";
        cout << "║  [0] Salir                           ║\n";
        cout << "╚══════════════════════════════════════╝\n";

        cout << ">> Ingrese opción: ";

        cin >> opc;
        system("cls");


        switch (opc)
        {
        case 1:
        bool subMenu=true;
        while(subMenu)
        {
            system("cls");
            cout << "╔══════════════════════════════════════╗\n";
            cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
            cout << "╠══════════════════════════════════════╣\n";
            cout << "╟── GESTION ───────────────────────────╣\n";
            cout << "║                                      ║\n";
            cout << "║  [1] Registrar Socio                 ║\n";
            cout << "║  [2] Mostrar Lista de Socioo         ║\n";
            cout << "║                                      ║\n";
            cout << "╟──────────────────────────────────────╣\n";
            cout << "║  [0] Volver                          ║\n";
            cout << "╚══════════════════════════════════════╝\n";
            cin >> opc;
                switch (opc)
                {
                case 1:
                    registrarSocio();
                    break;
                case 2:
                    listarSocio();
                    break;
                case 0:
                    menu=false;
                    break;
                }
        }
        case 2:
            system("cls");
            cout << "╔══════════════════════════════════════╗\n";
            cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
            cout << "╠══════════════════════════════════════╣\n";
            cout << "╟── GESTION ───────────────────────────╣\n";
            cout << "║                                      ║\n";
            cout << "║  [1] Registrar Libro                 ║\n";
            cout << "║  [2] Mostrar Lista de Libros         ║\n";
            cout << "║                                      ║\n";
            cout << "╟──────────────────────────────────────╣\n";
            cout << "║  [0] Volver                          ║\n";
            cout << "╚══════════════════════════════════════╝\n";
            registrarLibro();
            listarLibro();
            break;
        case 5:
            system("cls");
            cout << "╔══════════════════════════════════════╗\n";
            cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
            cout << "╠══════════════════════════════════════╣\n";
            cout << "╟── GESTION ───────────────────────────╣\n";
            cout << "║                                      ║\n";
            cout << "║  [1] Registrar Prestamo              ║\n";
            cout << "║  [2] Mostrar Lista de Prestamos      ║\n";
            cout << "║                                      ║\n";
            cout << "╟──────────────────────────────────────╣\n";
            cout << "║  [0] Volver                          ║\n";
            cout << "╚══════════════════════════════════════╝\n";
            break;
        case 6:
            system("cls");
            cout << "╔══════════════════════════════════════╗\n";
            cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
            cout << "╠══════════════════════════════════════╣\n";
            cout << "╟── GESTION ───────────────────────────╣\n";
            cout << "║                                      ║\n";
            cout << "║  [1] Registrar Cuota                 ║\n";
            cout << "║  [2] Mostrar Lista de Cuotas         ║\n";
            cout << "║                                      ║\n";
            cout << "╟──────────────────────────────────────╣\n";
            cout << "║  [0] Volver                          ║\n";
            cout << "╚══════════════════════════════════════╝\n";
            break;
        case 0:
            return;
        }

        system("pause");


    }
}

// Esta funcion carga los caracteres recibidios en un vector "palabra", con el tamaño indicado en la variable "tamano".

void cargarCadena(char *palabra, int tamano)
{
    int i=0;

    fflush(stdin);
    for (i=0; i<tamano; i++)
    {
        palabra[i]=cin.get();
        if (palabra[i]=='\n')
        {
            break;
        }
    }
    palabra[i]='\0';
    fflush(stdin);
}


// esta funcion crea el objeto obj, luego ejecuta el metodo "Cargar()", luego crea el objeto "obj" y graba los registros en el archivo de socios

void registrarSocio()
{
    Socio obj;
    obj.Cargar();
    ArchivoSocios arc;
    arc.grabarRegistro(obj);
}

// lee el archivo de socios y los muestra en pantalla


void listarSocio()
{
    ArchivoSocios arcSoc;
    Socio obj;
    int cantReg = arcSoc.contarRegistros();
    for(int i=0; i<cantReg; i++)
    {
        obj = arcSoc.leerRegistro(i);
        obj.Mostrar();
        cout << endl;
    }
}


// esta funcion crea el objeto libr, luego ejecuta el metodo "Cargar()", luego crea el objeto "ArcLibr" y graba los registros en el archivo de libros
void registrarLibro(){
    Libro libr;
    libr.Cargar();
    ArchivoLibros ArcLibr;
    ArcLibr.grabarRegistro(libr);

}

// lee el archivo de libros y los muestra en pantalla
void listarLibro()
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
