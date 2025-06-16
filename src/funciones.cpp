/// Objeto Socio: DNI, Nombre, Direccion, Email, Fecha de Nacimiento
/// Objeto Libro: ISBN, Nombre del libro, Nombre del autor, Fecha de publicacion, cantidad de ejemplares
/// Objeto Prestamos: Libro prestado, Socio al que se le presto, fecha del prestamo, fecha de devolucion
/// Objeto Cuota: Numero de Socio, Fecha de pago, Importe, Mes, Año, Importe

#include <iostream>
#include <cstring>
#include <windows.h>


#include "socio/clsArchSocio.h"

#include "libro/clsArchLibro.h"

#include "prestamo/clsArchPrestamo.h"

#include "cuota/clsArchCuota.h"

#include "funciones.h"

#include "clsExporte.h"

#include "clsBackup.h"

void fijarTamanioConsola(int ancho, int alto) {
    HWND consola = GetConsoleWindow();
    if (consola == NULL) return;

    // Establecer tamaño fijo
    system(("mode con: cols=" + std::to_string(ancho) + " lines=" + std::to_string(alto)).c_str());

    // Evitar redimensionamiento
    LONG style = GetWindowLong(consola, GWL_STYLE);
    style &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX); // Quitar botón maximizar y redimensionamiento
    SetWindowLong(consola, GWL_STYLE, style);
    SetWindowPos(consola, NULL, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

using namespace std;
void menuPrincipal() {
    fijarTamanioConsola(143,30);

    system("title PROYECTO");
    system("chcp 65001 > nul");
    int opc = 0;

    bool menu=true;
    bool subMenu=true;

    while(menu) {
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
        cout << "║  [9] EXPORTAR REPORTES               ║\n";
        cout << "║                                      ║\n";
        cout << "╟──────────────────────────────────────╣\n";
        cout << "║  [0] Salir                           ║\n";
        cout << "╚══════════════════════════════════════╝\n";

        cout << ">> Ingrese opción: ";

        cin >> opc;
        subMenu=true;
        system("cls");

        switch (opc) {
        /// SOCIOS ------------------------------
        case 1:
            while(subMenu) {
                system("cls");
                cout << "╔══════════════════════════════════════╗\n";
                cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
                cout << "╠══════════════════════════════════════╣\n";
                cout << "╟── GESTION SOCIOS ────────────────────╣\n";
                cout << "║                                      ║\n";
                cout << "║  [1] Registrar Socio                 ║\n";
                cout << "║  [2] Mostrar Lista de Socios         ║\n";
                cout << "║  [3] Buscar Socio                    ║\n";
                cout << "║  [4] Eliminar Socio                  ║\n";
                cout << "║                                      ║\n";
                cout << "╟──────────────────────────────────────╣\n";
                cout << "║  [0] Volver                          ║\n";
                cout << "╚══════════════════════════════════════╝\n";
                cout << ">> Ingrese opción: ";
                cin >> opc;
                cout << endl;
                ArchivoSocios obj;
                switch (opc) {
                case 1:
                    cout << "╔══════════════════════════════════════╗\n";
                    cout << "║   REGISTRAR SOCIO                    ║\n";
                    cout << "╚══════════════════════════════════════╝\n";
                    obj.Registrar();
                    system("pause");
                    break;
                case 2:
                    cout << "╔══════════════════════════════════════╗\n";
                    cout << "║   LISTA DE SOCIOS                    ║\n";
                    cout << "╚══════════════════════════════════════╝\n";
                    obj.Listar();
                    system("pause");
                    break;
                case 3:
                    cout << "╔══════════════════════════════════════╗\n";
                    cout << "║   BUSCAR SOCIO                       ║\n";
                    cout << "╟──────────────────────────────────────╣\n";
                    cout << "║                                      ║\n";
                    cout << "║  [1] Buscar por DNI                  ║\n";
                    cout << "║  [2] Buscar por Nombre y Apellido    ║\n";
                    cout << "║                                      ║\n";
                    cout << "╟──────────────────────────────────────╣\n";
                    cout << "║  [0] Volver                          ║\n";
                    cout << "╚══════════════════════════════════════╝\n";
                    cin >> opc;
                    switch (opc)
                    {
                    case 1:
                        char dni[10];
                        cout << ">> Ingrese DNI socio a buscar: ";
                        cargarCadena(dni,9);
                        obj.Buscar(dni, "-1");
                        system("pause");
                        break;
                    case 2:
                        char nombre[29];
                        cout << ">> Ingrese nombre: ";
                        cargarCadena(nombre,29);
                        char apellido[29];
                        cout << "Ingrese apellido: ";
                        cargarCadena(apellido,29);
                        obj.Buscar(nombre, apellido);
                        system("pause");
                        break;
                    case 0:
                        break;
                    }
                    break;
                case 4:
                    cout << "╔══════════════════════════════════════╗\n";
                    cout << "║   ELIMINAR SOCIO                     ║\n";
                    cout << "╚══════════════════════════════════════╝\n";
                    obj.Eliminar();
                    system("pause");
                    break;
                case 0:
                    opc =-1;
                    subMenu=false;
                    break;
                }
            }
        /// LIBROS ------------------------------
        case 2:
            while(subMenu) {
                system("cls");
                cout << "╔══════════════════════════════════════╗\n";
                cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
                cout << "╠══════════════════════════════════════╣\n";
                cout << "╟── GESTION LIBROS ────────────────────╣\n";
                cout << "║                                      ║\n";
                cout << "║  [1] Registrar Libro                 ║\n";
                cout << "║  [2] Mostrar Lista de Libros         ║\n";
                cout << "║  [3] Buscar Libro                    ║\n";
                cout << "║  [4] Eliminar libro                  ║\n";
                cout << "║                                      ║\n";
                cout << "╟──────────────────────────────────────╣\n";
                cout << "║  [0] Volver                          ║\n";
                cout << "╚══════════════════════════════════════╝\n";
                cout << ">> Ingrese opción: ";

                ArchivoLibros obj;
                cin >> opc;
                cout << endl;
                switch (opc) {
                case 1:
                    cout << "╔══════════════════════════════════════╗\n";
                    cout << "║   REGISTRAR LIBRO                    ║\n";
                    cout << "╚══════════════════════════════════════╝\n";
                    obj.Registrar();
                    system("pause");
                    break;
                case 2:
                    cout << "╔══════════════════════════════════════╗\n";
                    cout << "║   LISTA DE LIBROS                    ║\n";
                    cout << "╚══════════════════════════════════════╝\n";
                    obj.Listar();
                    system("pause");
                    break;
                case 3:
                    obj.Buscar();
                    system("pause");
                    break;
                case 4:
                    cout << "╔══════════════════════════════════════╗\n";
                    cout << "║   ELIMINAR LIBRO                     ║\n";
                    cout << "╚══════════════════════════════════════╝\n";
                    obj.Eliminar();
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
            while(subMenu) {
                system("cls");
                cout << "╔══════════════════════════════════════╗\n";
                cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
                cout << "╠══════════════════════════════════════╣\n";
                cout << "╟── GESTION ───────────────────────────╣\n";
                cout << "║                                      ║\n";
                cout << "║  [1] Registrar Prestamo              ║\n";
                cout << "║  [2] Mostrar Lista de Prestamos      ║\n";
                cout << "║  [3] Buscar Prestamo                 ║\n";
                cout << "║  [4] Eliminar Prestamo               ║\n";
                cout << "║                                      ║\n";
                cout << "╟──────────────────────────────────────╣\n";
                cout << "║  [0] Volver                          ║\n";
                cout << "╚══════════════════════════════════════╝\n";
                cout << ">> Ingrese opción: ";

                cin >> opc;
                cout << endl;
                ArchivoPrestamo obj;
                switch (opc) {
                case 1:
                    obj.RegistrarPrestamo();
                    system("pause");
                    break;
                case 2:
                    obj.ListarPrestamo();
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
            while(subMenu) {
                system("cls");
                cout << "╔══════════════════════════════════════╗\n";
                cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
                cout << "╠══════════════════════════════════════╣\n";
                cout << "╟── GESTION ───────────────────────────╣\n";
                cout << "║                                      ║\n";
                cout << "║  [1] Registrar Cuota                 ║\n";
                cout << "║  [2] Mostrar Lista de Cuotas         ║\n";
                cout << "║  [3] Buscar Cuota                    ║\n";
                cout << "║  [4] Eliminar Cuota                  ║\n";
                cout << "║                                      ║\n";
                cout << "╟──────────────────────────────────────╣\n";
                cout << "║  [0] Volver                          ║\n";
                cout << "╚══════════════════════════════════════╝\n";
                cout << ">> Ingrese opción: ";

                cin >> opc;
                cout << endl;
                ArchivoCuotas obj;
                switch (opc) {
                case 1:
                    obj.RegistrarCuota();
                    system("pause");
                    break;
                case 2:
                    obj.ListarCuota();
                    system("pause");
                    break;
                case 0:
                    opc =-1;
                    subMenu=false;
                    break;
                }

            }
        case 8:
            while(subMenu) {
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
                switch (opc) {
                case 1:
                    break;
                case 2:
                    BackupManager backup;
                    backup.backupGeneral();
                    break;
                case 0:
                    opc =-1;
                    subMenu=false;
                    break;
                }
            }
        case 9:
            Exporte exp;
            while(subMenu) {
                system("cls");
                cout << "╔══════════════════════════════════════╗\n";
                cout << "║   SISTEMA DE GESTIÓN DE BIBLIOTECA   ║\n";
                cout << "╠══════════════════════════════════════╣\n";
                cout << "╟── GESTION ───────────────────────────╣\n";
                cout << "║                                      ║\n";
                cout << "║  [1] Generar reporte socios          ║\n";
                cout << "║  [2] Generar reporte libros          ║\n";
                cout << "║  [3] Generar reporte prestamos       ║\n";
                cout << "║                                      ║\n";
                cout << "╟──────────────────────────────────────╣\n";
                cout << "║  [0] Volver                          ║\n";
                cout << "╚══════════════════════════════════════╝\n";
                cout << ">> Ingrese opción: ";

                cin >> opc;
                cout << endl;
                switch (opc) {
                case 1:
                    exp.archExportar("Socio");
                    break;

                case 2:
                    exp.archExportar("Libro");
                    break;

                case 3:
                    exp.archExportar("Prestamo");
                    break;

                case 4:
                    exp.archExportar("Cuota");
                    break;
                case 0:
                    opc =-1;
                    subMenu=false;
                    break;
                }
            }

        case 0:
            if(opc !=-1) {
                menu = false;
            }
            break;
        }

    }
}

/// La funcion obitene la palabra y el ancho deseado, similar la funcion de cargarCadena
string espaciarTexto(char *pal, int ancho)
{
    /// Toma el ancho deseado, y le resta el largo de la palabra
    int espacio = ancho-strlen(pal);
    /// Si el espacio es negativo, pondra uno
    if (espacio < 0) {
            espacio = 1;
    }
    /// Devuelve un string de ' '
    return string(espacio, ' ');
}

/// Esta funcion carga los caracteres recibidios en un vector "palabra", con el tamaño indicado en la variable "tamano".
void cargarCadena(char *palabra, int tamano) {
    int i=0;

    fflush(stdin);
    for (i=0; i<tamano; i++) {
        palabra[i]=cin.get();
        if (palabra[i]=='\n') {
            break;
        }
    }
    palabra[i]='\0';
    fflush(stdin);
}


