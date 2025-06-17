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
    cout << "Esta acción restaurará los archivos desde el backup y puede sobrescribir datos actuales." << endl;
    cout << "¿Desea continuar? (S/N): ";
    char opcion;
    cin >> opcion;
    if (opcion != 'S' && opcion != 's')
    {
        cout << "Restauración cancelada." << endl;
        return;
    }

    bool ok = true;

    ok &= restaurarArchivo("FILES/backup/Socios.bkp", "FILES/current/Socios.dat");
    ok &= restaurarArchivo("FILES/backup/Libros.bkp", "FILES/current/Libros.dat");
    ok &= restaurarArchivo("FILES/backup/Prestamos.bkp", "FILES/current/Prestamos.dat");
    ok &= restaurarArchivo("FILES/backup/Cuotas.bkp", "FILES/current/Cuotas.dat");

    if (ok) cout << "Restauración general completada correctamente." << endl;
    else cout << "Ocurrieron errores durante la restauración." << endl;

    system("pause");
}
