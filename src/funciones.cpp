/// Objeto Socio: DNI, Nombre, Direccion, Email, Fecha de Nacimiento
/// Objeto Libro: ISBN, Nombre del libro, Nombre del autor, Fecha de publicacion, cantidad de ejemplares
/// Objeto Prestamos: Libro prestado, Socio al que se le presto, fecha del prestamo, fecha de devolucion
/// Objeto Cuota: Numero de Socio, Fecha de pago, Importe, Mes, Año, Importe

#include <iostream>
#include <cstring>

#include "socio/clsSocio.h"
#include "socio/clsArchSocio.h"

#include "libro/clsLibro.h"
#include "libro/clsArchLibro.h"

#include "prestamo/clsPrestamo.h"
#include "prestamo/clsArchPrestamo.h"

#include "cuota/clsCuota.h"
#include "cuota/clsArchCuota.h"

#include "funciones.h"


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
        cout << "║  [1] Gestionar Socios                ║\n";
        cout << "║  [2] Gestionar Libros                ║\n";
        cout << "║  [3] Gestionar Prestamos             ║\n";
        cout << "║  [4] Gestionar Cuotas                ║\n";
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

        bool subMenu=true;

        switch (opc)
        {
        /// SOCIOS ------------------------------
        case 1:
            while(subMenu)
            {
                system("cls");
                cout << "╔══════════════════════════════════════╗\n";
                cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
                cout << "╠══════════════════════════════════════╣\n";
                cout << "╟── GESTION SOCIOS ────────────────────╣\n";
                cout << "║                                      ║\n";
                cout << "║  [1] Registrar Socio                 ║\n";
                cout << "║  [2] Mostrar Lista de Socios         ║\n";
                cout << "║  [3] Buscar Socio                    ║\n";
                cout << "║                                      ║\n";
                cout << "╟──────────────────────────────────────╣\n";
                cout << "║  [0] Volver                          ║\n";
                cout << "╚══════════════════════════════════════╝\n";
                cout << ">> Ingrese opción: ";
                cin >> opc;
                cout << endl;
                switch (opc)
                {
                case 1:
                    registrarSocio();
                    break;
                case 2:
                    listarSocio();
                    system("pause");
                    break;
                case 3:
                    buscarSocio();
                case 0:
                    subMenu=false;
                    break;
                }
                opc = = -1;
            }
        /// LIBROS ------------------------------
        case 2:
            while(subMenu)
            {
                system("cls");
                cout << "╔══════════════════════════════════════╗\n";
                cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
                cout << "╠══════════════════════════════════════╣\n";
                cout << "╟── GESTION LIBROS ────────────────────╣\n";
                cout << "║                                      ║\n";
                cout << "║  [1] Registrar Libro                 ║\n";
                cout << "║  [2] Mostrar Lista de Libros         ║\n";
                cout << "║                                      ║\n";
                cout << "╟──────────────────────────────────────╣\n";
                cout << "║  [0] Volver                          ║\n";
                cout << "╚══════════════════════════════════════╝\n";
                cout << ">> Ingrese opción: ";

                cin >> opc;
                cout << endl;
                switch (opc)
                {
                case 1:
                    registrarLibro();
                    break;
                case 2:
                    listarLibro();
                    system("pause");
                    break;
                case 0:
                    subMenu=false;
                    break;
                }

            }
        /// PRESTAMOS ------------------------------
        case 3:
            while(subMenu)
            {
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
                cout << ">> Ingrese opción: ";

                cin >> opc;
                cout << endl;
                switch (opc)
                {
                case 1:
                    registrarPrestamo();
                    break;
                case 2:
                    listarPrestamo();
                    system("pause");
                    break;
                case 0:
                    subMenu=false;
                    break;
                }

            }
        /// CUOTA ------------------------------
        case 4:
            while(subMenu)
            {
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
                cout << ">> Ingrese opción: ";

                cin >> opc;
                cout << endl;
                switch (opc)
                {
                case 1:
                    registrarCuota();
                    break;
                case 2:
                    listarCuota();
                    system("pause");
                    break;
                case 0:
                    subMenu=false;
                    break;
                }

            }
            case 8:
                while(subMenu)
                {
                    system("cls");
                    cout << "╔══════════════════════════════════════╗\n";
                    cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
                    cout << "╠══════════════════════════════════════╣\n";
                    cout << "╟── GESTION ───────────────────────────╣\n";
                    cout << "║                                      ║\n";
                    cout << "║  [1] Restaurar BACKUP                ║\n";
                    cout << "║  [2] Generar BACKUP                  ║\n";
                    cout << "║                                      ║\n";
                    cout << "╟──────────────────────────────────────╣\n";
                    cout << "║  [0] Volver                          ║\n";
                    cout << "╚══════════════════════════════════════╝\n";
                    cout << ">> Ingrese opción: ";

                    cin >> opc;
                    cout << endl;
                    switch (opc)
                    {
                    case 1:
                        break;
                    case 2:
                        break;
                    case 0:
                        subMenu=false;
                        break;
                    }

            }
                case 0:
                       menu = false;
                       break;


        }

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
    ArchivoSocios arc;

    obj.Cargar();
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

void buscarSocio()
{

    char dni[9];
    cout << ">> Ingrese DNI socio: ";
    cin >> dni;

    ArchivoSocios arcSoc;
    int pos = arcSoc.buscarRegistro(dni);

    if (pos == -1)
    {
        cout << "Socio no encontrado." << endl;
    }
    else
    {
        Socio obj = arcSoc.leerRegistro(pos);
        obj.Mostrar();
    }

    system("pause");

}

// esta funcion crea el objeto libr, luego ejecuta el metodo "Cargar()", luego crea el objeto "ArcLibr" y graba los registros en el archivo de libros
void registrarLibro()
{
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

void registrarPrestamo(){
    Prestamo prest;
    ArchivoPrestamo archPrest;

    prest.Cargar();
    archPrest.grabarRegistro(prest);
}

void listarPrestamo(){
    ArchivoPrestamo archPrest;
    Prestamo prest;


    int cantReg = archPrest.contarRegistros();

    for(int i=0; i<cantReg; i++)
    {
        prest = archPrest.leerRegistro(i);
        prest.Mostrar();
        cout << endl;
    }


}

void registrarCuota(){

    Cuota cuota;
    ArchivoCuotas archCuot;

    cuota.Cargar();
    archCuot.grabarRegistro(cuota);
}

void listarCuota(){

    ArchivoCuotas archCuot;
    Cuota cuota;

    int cantReg = archCuot.contarRegistros();

    for(int i=0; i<cantReg; i++)
    {
        cuota = archCuot.leerRegistro(i);
        cuota.Mostrar();
        cout << endl;
    }

}
