/// Objeto Socio: DNI, Nombre, Direccion, Email, Fecha de Nacimiento
/// Objeto Libro: ISBN, Nombre del libro, Nombre del autor, Fecha de publicacion, cantidad de ejemplares
/// Objeto Prestamos: Libro prestado, Socio al que se le presto, fecha del prestamo, fecha de devolucion
/// Objeto Cuota: Numero de Socio, Fecha de pago, Importe, Mes, Año, Importe

#include <iostream>
#include <cstring>
#include "clsArchSocios.h"
#include "clsSocio.h"
#include "funciones.h"
#include "clsLibro.h"


using namespace std;
void menuPrincipal()
{
    system("chcp 65001 > nul");
    int opc = 0;

    while(true)
    {
        cout << "╔══════════════════════════════════════╗\n";
        cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "╟── REGISTRO ──────────────────────────╣\n";
        cout << "║                                      ║\n";
        cout << "║  [1] Registrar Socio                 ║\n";
        cout << "║  [2] Registrar Libro                 ║\n";
        cout << "║  [3] Registrar Prestamo              ║\n";
        cout << "║  [4] Registrar Cuota                 ║\n";
        cout << "║                                      ║\n";
        cout << "╟── LECTURA ───────────────────────────╣\n";
        cout << "║                                      ║\n";
        cout << "║  [5] Mostrar Lista de Socio          ║\n";
        cout << "║  [6] Mostrar Lista de Libros         ║\n";
        cout << "║  [7] Mostrar Lista de Prestamo       ║\n";
        cout << "║  [8] Mostrar Lista de Cuota          ║\n";
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
            registrarSocio();
            break;
        case 2:
            cargarLibro();
            break;
        case 5:
            listarSocio();
            break;
        case 0:
            return;
        }

        system("pause");


    }
}

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


void registrarSocio()
{
    Socio obj;
    obj.Cargar();
    ArchivoSocios arc;
    arc.grabarRegistro(obj);
}


void listarSocio()
{
    ArchivoSocios arcSoc;
    Socio obj;
    int cantReg = arcSoc.contarRegistros();
    for(int i=0; i<cantReg; i++)
    {
        obj = arcSoc.leerRegistro(i);
        obj.Mostrar();
    }
}

void cargarLibro()
{
    Libro libr;
    libr.Cargar();

}
