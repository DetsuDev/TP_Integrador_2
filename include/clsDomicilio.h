#ifndef CLSDOMICILIO_H_INCLUDED
#define CLSDOMICILIO_H_INCLUDED

class Domicilio{
    private:
        char calle[30];
        int altura;
        char localidad[30];
        char partido[30];
        char codigoPostal[6];
    public:
        void Cargar();
        void Mostrar();
};

#endif // CLSDOMICILIO_H_INCLUDED
