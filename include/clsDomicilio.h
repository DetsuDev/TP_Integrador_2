#ifndef CLSDOMICILIO_H_INCLUDED
#define CLSDOMICILIO_H_INCLUDED

class Domicilio {
private:
    char calle[30];
    int altura;
    char localidad[30];
    char partido[30];
    char codigoPostal[6];

public:
    void Cargar();
    void Mostrar();

    // Setters
    void setCalle(const char *);
    void setAltura(int);
    void setLocalidad(const char *);
    void setPartido(const char *);
    void setCodPostal(const char *);

    // Getters
    const char* getCalle();
    int getAltura();
    const char* getLocalidad();
    const char* getPartido();
    const char* getCodPostal();
};

#endif // CLSDOMICILIO_H_INCLUDED
