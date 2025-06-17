#ifndef CLSBACKUP_H
#define CLSBACKUP_H

#include <string>

class BackupManager {
public:
    bool hacerBackup(const char* archivoOriginal, const char* archivoBackup);
    void backupGeneral();

    bool restaurarArchivo(const char* archivoBackup, const char* archivoOriginal); // NUEVO
    void restaurarGeneral(); // NUEVO

    std::string obtenerFechaActual();
    std::string crearDirectorioBackup();

};

#endif // CLSBACKUP_H
