#include <iostream>
#include "clsExporte.h"
#include <fstream>
#include "socio/clsSocio.h"

#include "socio/clsArchSocio.h"
void Exporte::archExportar(std::string claseCls)
{

    if(claseCls == "Socio")
    {
        ArchivoSocios arcSoc;
        Socio obj;
        std::ofstream file("CSV/Socios.csv");

        int cantReg = arcSoc.contarRegistros();
        file << "DNI" << "\n";
        for(int i=0; i<cantReg; i++)
        {
            obj = arcSoc.leerRegistro(i);
            if(obj.getEstado() == true){
            file << obj.getDni() <<"," << obj.getNombre() << "\n";
            }
        }
        file.close();

    }
    cout << "Hecho." << endl;
    system("pause");

}
