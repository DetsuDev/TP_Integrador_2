#include <iostream>
using namespace std;
#include "clsExporte.h"
#include <fstream>

class Exporte{

private:
    char socioFile[30] = {"FILES\current\Socios.dat"};
    char libroFile[30] = {"FILES\current\Socios.dat"};
    char prestamoFile[30] = {"FILES\current\Socios.dat"};
    char cuotaFile[30] = {"FILES\current\Socios.dat"};
public:

    void exportarArchivo(char nombreArchivo[30]){

        switch(nombreArchivo){
        case socioFile:
            Socio obj;
            ArchivosSocios arcSoc;
            ofstream file("CSV\Socios.csv");

            int cantReg = arcSoc.contarRegistros();
            for(int i=0; i<cantReg; i++)
            {
                obj = arcSoc.leerRegistro(i);
                file << obj;
                cout << endl;
            }


            break;

        case libroFile:
            break;

        case prestamoFile:
            break;

        case cuotaFile:
            break;


        }


   }


};
