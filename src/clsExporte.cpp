#include <iostream>
#include "clsExporte.h"
#include <fstream>
#include "socio/clsSocio.h"
#include "socio/clsArchSocio.h"
#include "libro/clsLibro.h"
#include "libro/clsArchLibro.h"
#include "prestamo/clsPrestamo.h"
#include "prestamo/clsArchPrestamo.h"
void Exporte::archExportar(std::string claseCls)
{

    if(claseCls == "Socio")
    {
        ArchivoSocios arcSoc;
        Socio obj;
        std::ofstream file("CSV/Socios.csv");

        int cantReg = arcSoc.contarRegistros();
        file << "DNI" << "," <<"NOMBRE " << "\n";
        for(int i=0; i<cantReg; i++)
        {
            obj = arcSoc.leerRegistro(i);
            if(obj.getEstado() == true)
            {
                file << obj.getDni() <<"," << obj.getNombre() << "\n";
            }
        }
        file.close();

    }

    if(claseCls == "Libro")
    {
        ArchivoLibros arcLibr;
        Libro obj;
        std::ofstream file("CSV/Libros.csv");

        int cantReg = arcLibr.contarRegistros();
        file << "ISBN" << "," <<"NOMBRE LIBRO " << "\n";
        for(int i=0; i<cantReg; i++)
        {
            obj = arcLibr.leerRegistro(i);
            //if(obj.getEstado() == true)
            //  {
            file << obj.getISBN() <<"," << obj.getTitulo() << "\n";
            //  }
        }
        file.close();


    }

    if(claseCls == "Prestamo")
    {

        ArchivoPrestamo arcPrest;
        Prestamo obj;
        std::ofstream file("CSV/Prestamos.csv");

        int cantReg = arcPrest.contarRegistros();
        file << "DNI" << "," <<"ISBN" << ","<< "FECHA PREST" <<"\n";
        for(int i=0; i<cantReg; i++)
        {
            obj = arcPrest.leerRegistro(i);
            //if(obj.getEstado() == true)
            //  {
            file << obj.getDniSocio() << "," << obj.getISBN() << "\n";
            //  }
        }
        file.close();

    }

    if(claseCls == "Cuota")
    {

    }
    cout << "Hecho." << endl;
    system("pause");

}
