#ifndef CLSLIBRO_H
#define CLSLIBRO_H

class ArchivoLibros;
class Libro {

private:
    char isbn[20];
    char titulo[50];
    char autor[50];
    int anioPublicacion;
    int cantidadEjemplares;

    bool estado = false;

public:
    void setEstado(bool);
    bool getEstado();

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


    bool Cargar(ArchivoLibros&);
    void Mostrar();
};

#endif // CLSLIBRO_H
