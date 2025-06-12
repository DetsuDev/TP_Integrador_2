#include <iostream>
#include <cstring>
#include "prestamo/clsPrestamo.h"
#include "prestamo/clsArchPrestamo.h"
#include "funciones.h"
#include <cstdlib>
#include <ctime>
#include "socio/clsArchSocio.h"
#include "socio/clsSocio.h"
#include "libro/clsArchLibro.h"
#include "libro/clsLibro.h"

using namespace std;

void Prestamo::Cargar()
{
    cout << "DNI DEL SOCIO: ";
    cargarCadena(dniSocio, 9);
    ArchivoSocios arcSoc;
    ArchivoLibros arcLibr;
    Socio obj;
    Libro libr;

    int cantReg = arcSoc.contarRegistros();
    bool existe = false;
    cout << dniSocio;
    system("pause");
    for(int i = 0; i < cantReg; i++)
    {
        obj = arcSoc.leerRegistro(i);
        if(strcmp(obj.getDni(), dniSocio) == 0) // strcmp compara caracter por caracter
        {
            existe = true;
        }

    }
    if(!existe)
    {
        cout << "no existe!" << endl;
        system("pause");
    }
    else
    {
        cantReg = arcLibr.contarRegistros();
        existe = false;
        cout << "ISBN DEL LIBRO: ";
        cargarCadena(isbn, 19);
        for(int i = 0; i < cantReg; i++)
        {
            libr = arcLibr.leerRegistro(i);
            if(strcmp(libr.getISBN(), isbn) == 0)
            {
                existe = true;
            }
            if(!existe)
            {
                cout << "no existe el libro" << endl;
                system("pause");
            }
            else
            {
                cout << "FECHA DEL PRÉSTAMO: ";
                fechaPrestamo.Cargar();
                cout << "FECHA DE DEVOLUCIÓN: ";
                fechaDevolucion.Cargar();

                srand(time(0));
                idPrestamo = rand() % 100000 + 1;

            }
        }

    }
}

void Prestamo::Mostrar()
    {
        cout << "ID PRÉSTAMO: " << idPrestamo << endl;
        cout << "DNI SOCIO: " << dniSocio << endl;
        cout << "ISBN LIBRO: " << isbn << endl;
        cout << "FECHA PRÉSTAMO: ";
        fechaPrestamo.Mostrar();
        cout << "FECHA DEVOLUCIÓN: ";
        fechaDevolucion.Mostrar();
    }


    void Prestamo::registrarPrestamo()
    {
        Prestamo prest;
        ArchivoPrestamo archPrest;

        prest.Cargar();
    }

    void Prestamo::listarPrestamo()
    {
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


    void Prestamo::setIdPrestamo(int id)
    {
        idPrestamo = id;
    }
    void Prestamo::setDniSocio(const char *d)
    {
        strcpy(dniSocio, d);
    }
    void Prestamo::setISBN(const char *i)
    {
        strcpy(isbn, i);
    }
    void Prestamo::setFechaPrestamo(Fecha f)
    {
        fechaPrestamo = f;
    }
    void Prestamo::setFechaDevolucion(Fecha f)
    {
        fechaDevolucion = f;
    }

    int Prestamo::getIdPrestamo()
    {
        return idPrestamo;
    }
    const char* Prestamo::getDniSocio()
    {
        return dniSocio;
    }
    const char* Prestamo::getISBN()
    {
        return isbn;
    }
    Fecha Prestamo::getFechaPrestamo()
    {
        return fechaPrestamo;
    }
    Fecha Prestamo::getFechaDevolucion()
    {
        return fechaDevolucion;
    }

