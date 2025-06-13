#include "clsBackup.h"
#include <fstream>
#include <iostream>
using namespace std;

bool BackupManager::hacerBackup(const char* archivoOriginal, const char* archivoBackup) {
    ifstream origen(archivoOriginal, ios::binary);
    ofstream destino(archivoBackup, ios::binary);

    if (!origen || !destino) {
        cout << "❌ Error al abrir archivos para backup: " << archivoOriginal << endl;
        return false;
    }

    destino << origen.rdbuf();
    origen.close();
    destino.close();
    return true;
}

void BackupManager::backupGeneral() {
    bool ok = true;

    ok &= hacerBackup("FILES/current/Socios.dat", "FILES/backup/Socios.bkp");
    ok &= hacerBackup("FILES/current/Libros.dat", "FILES/backup/Libros.bkp");
    ok &= hacerBackup("FILES/current/Prestamos.dat", "FILES/backup/Prestamos.bkp");
    ok &= hacerBackup("FILES/current/Cuotas.dat", "FILES/backup/Cuotas.bkp");

    if (ok) cout << "✅ Backup general completado correctamente." << endl;
    else cout << "⚠️ Ocurrieron errores durante el backup." << endl;

    system("pause");
}

// NUEVO: función para restaurar archivos

bool BackupManager::restaurarArchivo(const char* archivoBackup, const char* archivoOriginal) {
    ifstream origen(archivoBackup, ios::binary);
    ofstream destino(archivoOriginal, ios::binary);

    if (!origen || !destino) {
        cout << "Error al abrir archivos para restaurar: " << archivoBackup << endl;
        return false;
    }

    destino << origen.rdbuf();
    origen.close();
    destino.close();
    return true;
}

void BackupManager::restaurarGeneral() {
    cout << "Esta acción restaurará los archivos desde el backup y puede sobrescribir datos actuales." << endl;
    cout << "¿Desea continuar? (S/N): ";
    char opcion;
    cin >> opcion;
    if (opcion != 'S' && opcion != 's') {
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
