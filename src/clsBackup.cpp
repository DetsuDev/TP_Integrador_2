#include "clsBackup.h"
#include <fstream>
#include <iostream>
#include <direct.h>
#include <windows.h>
#include <ctime>
#include <vector>

using namespace std;

string BackupManager::obtenerFechaActual()
{
    time_t t = time(nullptr);
    struct tm* now = localtime(&t);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", now);

    return string(buffer);
}


string BackupManager::crearDirectorioBackup() {
    const std::string& basePath = "FILES/backup/";
    //_mkdir(basePath.c_str());  // Crea carpeta "backups" si no existe

    string fecha = obtenerFechaActual();
    string ruta = basePath + "/" + fecha;
    string comando = "mkdir \"" + ruta + "\"";
    system(comando.c_str()); // Crea carpeta con fecha

    return ruta;
}

bool BackupManager::hacerBackup(const char* archivoOriginal, const char* archivoBackup)
{
    ifstream origen(archivoOriginal, ios::binary);
    ofstream destino(archivoBackup, ios::binary);

    if (!origen || !destino)
    {
        cout << "Error al abrir archivos para backup: " << archivoOriginal << endl;
        return false;
    }

    destino << origen.rdbuf();
    origen.close();
    destino.close();
    return true;
}

void BackupManager::backupGeneral()
{
    string bufferRuta;
    bool ok = true;
    bufferRuta = crearDirectorioBackup() + "/Socios.bkp";
    ok &= hacerBackup("FILES/current/Socios.dat",bufferRuta.c_str());
    bufferRuta = crearDirectorioBackup() + "/Libros.bkp";
    ok &= hacerBackup("FILES/current/Libros.dat",bufferRuta.c_str());
    bufferRuta = crearDirectorioBackup() + "/Prestamos.bkp";
    ok &= hacerBackup("FILES/current/Prestamos.dat",bufferRuta.c_str());
    bufferRuta = crearDirectorioBackup() + "/Cuotas.bkp";
    ok &= hacerBackup("FILES/current/Cuotas.dat",bufferRuta.c_str());

    if (ok) cout << "Backup general completado correctamente." << endl;
    else cout << "Ocurrieron errores durante el backup." << endl;

    system("pause");
}

// NUEVO: función para restaurar archivos

bool BackupManager::restaurarArchivo(const char* archivoBackup, const char* archivoOriginal)
{
    ifstream origen(archivoBackup, ios::binary);
    ofstream destino(archivoOriginal, ios::binary);

    if (!origen || !destino)
    {
        cout << "Error al abrir archivos para restaurar: " << archivoBackup << endl;
        return false;
    }

    destino << origen.rdbuf();
    origen.close();
    destino.close();
    return true;
}

void BackupManager::restaurarGeneral()
{
    string ruta = "FILES\\backup\\*"; // ¡IMPORTANTE: terminar en \\*
    string ruta2= "FILES/backup/";
    WIN32_FIND_DATA datos;
    HANDLE hFind = FindFirstFile(ruta.c_str(), &datos);
    bool bandera = true;
    int contador = 0;
    string nombre_backups[10];

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "No se pudo abrir el directorio.\n";
        system("pause");
    }

    do {
        // Ignorar "." y ".."
        if (datos.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            string nombre = datos.cFileName;
            if (nombre != "." && nombre != "..") {
                if(bandera){
                cout << "backups disponibles: " << endl << endl;
                bandera = false;
                }
                contador++;
                nombre_backups[contador] = nombre;
                cout << endl << contador << "_ " << nombre << endl;
            }
        }
    } while (FindNextFile(hFind, &datos));
    if(contador == 0){
        cout << "No se encontraron archivos para restaurar." << endl << endl;
        system("pause");
        return;
    }
    cout << endl;
    FindClose(hFind);
    cout << "¿Desea restaurar una copia anterior? (S/N): ";
    char opcion;
    cin >> opcion;
    if (opcion != 'S' && opcion != 's')
    {
        cout << "Restauración cancelada." << endl;
        return;
    }
    cout << "Indique el indice de backup a restaurar: ";
    int opcion2;
    cin >> opcion2;

    if((opcion2 > contador )| (opcion2 < 0)){
        cout << "Opcion invalida."<< endl;
        system("pause");
        return;
    }
    else{
        string rutaBackup = ruta2 + nombre_backups[opcion2];
        string bufferRuta;
    bool ok = true;
    bufferRuta = rutaBackup + "/Socios.bkp";
    ok &= restaurarArchivo(bufferRuta.c_str(), "FILES/current/Socios.dat");
    bufferRuta = rutaBackup + "/Libros.bkp";
    ok &= restaurarArchivo(bufferRuta.c_str(), "FILES/current/Libros.dat");
    bufferRuta = rutaBackup + "/Prestamos.bkp";
    ok &= restaurarArchivo(bufferRuta.c_str(), "FILES/current/Prestamos.dat");
    bufferRuta = rutaBackup + "/Cuotas.bkp";
    ok &= restaurarArchivo(bufferRuta.c_str(), "FILES/current/Cuotas.dat");

    if (ok) cout << "Restauración general completada correctamente." << endl;
    else cout << "Ocurrieron errores durante la restauración." << endl;
    }


    system("pause");
}
