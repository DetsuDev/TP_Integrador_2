#include "clsFecha.h"
#include "clsDomicilio.h"
#include "socio/clsSocio.h"
#include "socio/clsArchSocio.h"
#include "funciones.h"

using namespace std;

bool Socio::Cargar(ArchivoSocios &arcSoc)
{
    cout<<"INGRESE EL DNI: ";
    cargarCadena(dni,9);

    if (arcSoc.buscarRegistro(dni) == -1)
    {

        cout<<"INGRESE EL NOMBRE: ";
        cargarCadena(nombre,29);
        cout<<"INGRESE EL APELLIDO: ";
        cargarCadena(apellido,29);
        cout<<"INGRESE LA FECHA DE NACIMIENTO: "<<endl;
        fechaNacimiento.Cargar();
        cout<<"INGRESE EL DOMICILIO: "<<endl;
        domicilio.Cargar();
        cout<<"INGRESE EL EMAIL: ";
        cargarCadena(email, 39);
        return true;
    }
    else
    {
        cout << "DNI: [" << dni << "] YA EXISTENTE." << endl;
        return false;
    }

}

void Socio::EliminarSocio()
{
    cout << "INGRESE DNI A ELIMINAR: ";
    cargarCadena(dni,9);
    ArchivoSocios arcSoc;
    //arcSoc.buscarRegistro(dni)

    char buffer[50] = {};

    int pos = arcSoc.buscarRegistro(dni);
    if (pos > -1)
    {
        Socio obj = arcSoc.leerRegistro(pos);

        obj.setEstado(false);
        arcSoc.modificarRegistro(obj, pos);


        cout << "SOCIO [" << dni << "] ELIMINADO" << endl;
    }
    else
    {
        cout << "DNI NO ENCONTRADO." << endl;
    }

}

void Socio::Mostrar()
{
    cout << " DNI: "<<dni<<endl;
    cout << " NOMBRE: "<<apellido<<", "<<nombre<<endl;
    cout << " FECHA DE NACIMIENTO: ";
    fechaNacimiento.Mostrar();
    cout << " DOMICILIO: "<<endl;
    domicilio.Mostrar();
    cout << " EMAIL: "<<email<<endl;
    cout << "────────────────────────────────────────";
    //cout << dni << "| " << apellido << "| " << nombre << "| " << email << endl;

}


void Socio::MostrarBusqueda()
{
    //char dni[9];
    cout << ">> Ingrese DNI socio: ";
    cargarCadena(dni,9);

    ArchivoSocios arcSoc;
    string dniReg = arcSoc.buscarDniRegistro(dni);
    cout << "DNI: " << dniReg;
    cout << endl;
    //obj.Mostrar();

}

// esta funcion crea el objeto obj, luego ejecuta el metodo "Cargar()", luego crea el objeto "obj" y graba los registros en el archivo de socios

void Socio::registrarSocio()
{
    Socio obj;
    ArchivoSocios arcSoc;
    if (obj.Cargar(arcSoc))
    {
        arcSoc.grabarRegistro(obj);
    }
    else
    {
        obj.Cargar(arcSoc);
    }
}

// lee el archivo de socios y los muestra en pantalla


void Socio::listarSocio()
{
    ArchivoSocios arcSoc;
    Socio obj;
    int cantReg = arcSoc.contarRegistros();
    for(int i=0; i<cantReg; i++)
    {

        obj = arcSoc.leerRegistro(i);
        if (obj.getEstado())
        {
            obj.Mostrar();
            cout << endl;
        }
    }
}

void Socio::setEstado(bool e)
{
    estado = e;
}

bool Socio::getEstado()
{
    return estado;
}

void Socio::setDni(const char *i)
{
    strcpy(dni, i);
}
void Socio::setNombre(const char *e)
{
    strcpy(nombre, e);
}
void Socio::setApellido(const char *e)
{
    strcpy(apellido, e);
}
void Socio::setEmail(const char *e)
{
    strcpy(email, e);
}

void Socio::setFechaNacimiento(Fecha f)
{
    fechaNacimiento = f;
}
void Socio::setDomicilio(Domicilio d)
{
    domicilio = d;
}

Domicilio& Socio::getDomicilio()
{
    return domicilio;
}

Fecha& Socio::getFechaNacimiento()
{
    return fechaNacimiento;
}
const char* Socio::getDni()
{
    return dni;
}

const char* Socio::getNombre()
{
    return nombre;
}
