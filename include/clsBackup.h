#ifndef CLSBACKUP_H
#define CLSBACKUP_H

class BackupManager {
public:
    bool hacerBackup(const char* archivoOriginal, const char* archivoBackup);
    void backupGeneral();
};

 #endif // CLSBACKUP_H
