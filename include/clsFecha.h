#ifndef CLSFECHA_H_INCLUDED
#define CLSFECHA_H_INCLUDED

#include <vector>

using namespace std;
class Fecha{
    private:
        int dia, mes, anio;
    public:
        Fecha(int d=1, int m=1, int a=1900);
        void setDia(int);
        void setMes(int);
        void setAnio(int);
        int getDia();
        int getMes();
        int getAnio();
        void Cargar();
        string getFechaCompleta();
};

#endif // CLSFECHA_H_INCLUDED
