#ifndef CLSBACKUP_H
#define CLSBACKUP_H

class BackupManager {
public:
    bool hacerBackup(const char* archivoOriginal, const char* archivoBackup);
    void backupGeneral();

    bool restaurarArchivo(const char* archivoBackup, const char* archivoOriginal); // NUEVO
    void restaurarGeneral(); // NUEVO
};

#endif // CLSBACKUP_H
