#include "filetools.h"

FileTools *FileTools::instance = NULL;

bool FileTools::unzip(QDir path, QString file) {
    QProcess p;
    QStringList args;

    args << "-xzf" << path.path()+file;
    p.setWorkingDirectory(path.path());
    p.start("tar", args);
    p.waitForFinished(3000);

    QString p_stdout = p.readAllStandardOutput();
    QString p_stderr = p.readAllStandardError();

    if (p_stderr.contains("error", Qt::CaseInsensitive)) {
        return false;
    }

    return true;
}

bool FileTools::clearTmp() {
    return tmpPath.removeRecursively();
}

QString FileTools::mountDMG(QDir path, QString file) {
    QProcess p;
    QStringList args;

    args << "attach" << path.path()+"/"+file;
    p.setWorkingDirectory(path.path());
    p.start("hdiutil", args);
    p.waitForFinished(3000);

    QString p_stderr = p.readAllStandardError();
    QString p_stdout = p.readAllStandardOutput();

    qDebug()<<p_stderr;
    qDebug()<<"----------------------------------------";
    qDebug()<<p_stdout;
    qDebug()<<"----------------------------------------";

    if (p_stderr.contains("error", Qt::CaseInsensitive)) {
        return "";
    }
    QString volume = p_stdout.split("\t").last().remove("\n");

    return volume;
}

bool FileTools::verifyDMG(QDir path, QString file) {
    QProcess p;
    QStringList args;

    args << "verify" << path.path()+"/"+file;
    p.setWorkingDirectory(path.path());
    p.start("hdiutil", args);
    p.waitForFinished(3000);

    QString p_stderr = p.readAllStandardError();

    if (p_stderr.contains("is INVALID", Qt::CaseInsensitive)) {
        return false;
    }

    return true;
}
