#ifndef CLSLIBRO_H
#define CLSLIBRO_H

class Libro
{
private:
    char isbn[20];
    char titulo[50];
    char autor[50];
    int anioPublicacion;
    int cantidadEjemplares;

public:
    void Cargar();
    void Mostrar();

    void setISBN(const char *);
    void setTitulo(const char *);
    void setAutor(const char *);
    void setAnioPublicacion(int);
    void setCantidadEjemplares(int);

    const char* getISBN();
    const char* getTitulo();
    const char* getAutor();
    int getAnioPublicacion();
    int getCantidadEjemplares();
};

#endif // CLSLIBRO_H
