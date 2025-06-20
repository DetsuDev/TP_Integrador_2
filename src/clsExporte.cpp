#include <iostream>
#include "clsExporte.h"
#include <fstream>
#include "socio/clsSocio.h"
#include "socio/clsArchSocio.h"
#include "libro/clsLibro.h"
#include "libro/clsArchLibro.h"
#include "prestamo/clsPrestamo.h"
#include "prestamo/clsArchPrestamo.h"
#include "cuota/clsCuota.h"
#include "cuota/clsArchCuota.h"

using namespace std;
void Exporte::archExportar(std::string claseCls)
{

    if(claseCls == "Socio")
    {
        ArchivoSocios arcSoc;
        Socio obj;
        std::ofstream file("CSV/Socios.csv");

        int cantReg = arcSoc.contarRegistros();
        file << "DNI"
             << "," <<"NOMBRE "
             <<","<< "APELLIDO"
             <<","<< "FECHA NAC. "
             << "," << "CALLE"
             << "," << "ALTURA"
             << "," << "LOCALIDAD"
             << "," << "PARTIDO"
             << "," << "CODIGO POSTAL"
             << "," << "EMAIL"
             <<"\n";
        for(int i=0; i<cantReg; i++)
        {
            obj = arcSoc.leerRegistro(i);
            if(strcmp(obj.getDni(), "-1") != 0)
            {
                file << obj.getDni()
                     << "," << obj.getNombre()
                     << "," << obj.getApellido()
                     << "," << obj.getFechaNacimiento().getDia()<< "/"<< obj.getFechaNacimiento().getMes()<<"/"<< obj.getFechaNacimiento().getAnio()
                     << "," << obj.getDomicilio().getCalle()
                     << "," <<obj.getDomicilio().getAltura()
                     << "," << obj.getDomicilio().getLocalidad()
                     << "," << obj.getDomicilio().getPartido()
                     << "," << obj.getDomicilio().getCodPostal()
                     << "," << obj.getEmail()
                     <<"\n";
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
        file << "ISBN" << "," <<"TITULO" <<"," << "AUTOR" << "," << "A�O PUBLICACION" << "," << "CANTIDAD EJEMPLARES" <<"\n";
        for(int i=0; i<cantReg; i++)
        {
            obj = arcLibr.leerRegistro(i);
            if(strcmp(obj.getISBN(), "-1") != 0)
            {
                file << obj.getISBN()
                     << "," << obj.getTitulo()
                     << "," << obj.getAutor()
                     << "," << obj.getAnioPublicacion()
                     << "," << obj.getCantidadEjemplares()
                     << "\n";
            }
        }
        file.close();


    }

    if(claseCls == "Prestamo")
    {

        ArchivoPrestamo arcPrest;
        Prestamo obj;
        std::ofstream file("CSV/Prestamos.csv");

        int cantReg = arcPrest.contarRegistros();
        file << "DNI"
             << "," <<"ISBN"
             << "," << "FECHA PREST"
             << "," << "FECHA DEV."
             << "\n";
        for(int i=0; i<cantReg; i++)
        {
            obj = arcPrest.leerRegistro(i);
            if(obj.getIdPrestamo() != -1)
            {
                file << obj.getDniSocio()
                     << "," << obj.getISBN()
                     << "," << obj.getFechaPrestamo().getDia() << "/" << obj.getFechaPrestamo().getMes() << "/" << obj.getFechaPrestamo().getAnio()
                     << "," << obj.getFechaDevolucion().getDia() << "/" << obj.getFechaDevolucion().getMes() << "/" << obj.getFechaDevolucion().getAnio()
                     <<"\n";
            }
        }
        file.close();

    }

    if(claseCls == "Cuota")
    {
        ArchivoCuotas arcCuota;
        Cuota obj;
        std::ofstream file("CSV/Cuotas.csv");
        int cantReg = arcCuota.contarRegistros();

        file << "DNI"
             << "," << "FECHA PAGO"
             << "," << "IMPORTE"
             << "," << "MES"
             << "," << "A�O"
             << "\n";

        for(int i=0; i<cantReg; i++)
        {
            obj = arcCuota.leerRegistro(i);
            if((obj.getDni(), "-1") != 0)
            {
                file << obj.getDni()
                     << "," << obj.getImporte()
                     << "," << obj.getFechaPago().getDia() << "/" << obj.getFechaPago().getMes() << "/" << obj.getFechaPago().getAnio()
                     << "," << obj.getMes()
                     << "," << obj.getAnio()
                     << "\n";
            }
        }
        file.close();

    }
cout << "Hecho." << endl;
system("pause");
}


