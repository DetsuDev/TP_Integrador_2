/// Objeto Socio: DNI, Nombre, Direccion, Email, Fecha de Nacimiento
/// Objeto Libro: ISBN, Nombre del libro, Nombre del autor, Fecha de publicacion, cantidad de ejemplares
/// Objeto Prestamos: Libro prestado, Socio al que se le presto, fecha del prestamo, fecha de devolucion
/// Objeto Cuota: Numero de Socio, Fecha de pago, Importe, Mes, Año, Importe

#include <iostream>
#include <cstring>

#include "socio/clsSocio.h"

#include "libro/clsLibro.h"

#include "prestamo/clsPrestamo.h"

#include "cuota/clsCuota.h"

#include "funciones.h"


using namespace std;
void menuPrincipal()
{
    system("chcp 65001 > nul");
    int opc = 0;

    bool menu=true;
    bool subMenu=true;

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
        subMenu=true;
        system("cls");

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
                Socio obj;
                switch (opc)
                {
                case 1:
                    cout << "╔══════════════════════════════════════╗\n";
                    cout << "║   REGISTRAR SOCIO                    ║\n";
                    cout << "╚══════════════════════════════════════╝\n";
                    obj.registrarSocio();
                    system("pause");
                    break;
                case 2:
                    cout << "╔══════════════════════════════════════╗\n";
                    cout << "║   LISTA DE SOCIOS                    ║\n";
                    cout << "╚══════════════════════════════════════╝\n";
                    obj.listarSocio();
                    system("pause");
                    break;
                case 3:
                    cout << "╔══════════════════════════════════════╗\n";
                    cout << "║   BUSCAR SOCIO                       ║\n";
                    cout << "╚══════════════════════════════════════╝\n";
                    obj.MostrarBusqueda();
                    system("pause");
                    break;

                case 0:
                    opc =-1;
                    subMenu=false;
                }
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

                Libro obj;
                cin >> opc;
                cout << endl;
                switch (opc)
                {
                case 1:
                    obj.registrarLibro();
                    system("pause");
                    break;
                case 2:
                    obj.listarLibro();
                    system("pause");
                    break;
                case 0:
                    opc =-1;
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
                Prestamo obj;
                switch (opc)
                {
                case 1:
                    obj.registrarPrestamo();
                    system("pause");
                    break;
                case 2:
                    obj.listarPrestamo();
                    system("pause");
                    break;
                case 0:
                    opc =-1;
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
                Cuota obj;
                switch (opc)
                {
                case 1:
                    obj.registrarCuota();
                    system("pause");
                    break;
                case 2:
                    obj.listarCuota();
                    system("pause");
                    break;
                case 0:
                    opc =-1;
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
                    opc =-1;
                    subMenu=false;
                    break;
                }

            }
        case 0:
            if(opc !=-1)
            {
                menu = false;
            }
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

    /* while (i < tamano) {
        palabra[i] = ' ';
        i++;
    }*/

    palabra[i]='\0';
    fflush(stdin);
}


