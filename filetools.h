#ifndef FILETOOLS_H
#define FILETOOLS_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QProcess>
#include <QDebug>

class FileTools : public QObject {
    Q_OBJECT
private:
    FileTools(): QObject() {
        //init inner vars
        tmpPath = QDir::temp();
        tmpPath.mkdir("tinu");
        tmpPath.cd("tinu");
    }

public:
    static FileTools* getInstance() {
        if (instance == NULL) {
            instance = new FileTools();
        }
        return instance;
    }

    static void destroy() {
        if (instance != NULL) {
            delete instance;
            instance = NULL;
        }
    }

    /**
     * @brief getTmpPath returns a once-for-all path to a temporary dir. As FileTools is a singleton, you won't have to bother about this path's unicity.
     * @return QDir pointing to a temporary folder.
     */
    QDir getTmpPath() {return tmpPath;}
    /**
     * @brief unzip a file.
     * @param path Path where the file to  unzip is located.
     * @param file The name of the file to unzip.
     * @return Returns true if no error has been detected.
     */
    static bool unzip(QDir path, QString file);
    static QString mountDMG(QDir path, QString file);
    static bool verifyDMG(QDir path, QString file);
    bool clearTmp();


private:
    static FileTools *instance;
    QDir tmpPath;

signals:

public slots:

};

#endif // FILETOOLS_H
