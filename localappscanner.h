#ifndef LOCALAPPSCANNER_H
#define LOCALAPPSCANNER_H

#include <QString>
#include <QList>
#include <QDir>
#include <QDirIterator>
#include <QXmlQuery>
#include <QAbstractMessageHandler>

#include <QDebug>

class LocalApp {
public:
    QString name;
    QString version;
};

class LocalAppScanner : public QObject {
    Q_OBJECT

private:
    LocalAppScanner(QObject *parent=0) : QObject(parent) {}
    ~LocalAppScanner() {}

private:
    static LocalAppScanner* _instance;

public:
    static LocalAppScanner* getInstance() {
        if (_instance == (LocalAppScanner*)NULL)
            _instance = new LocalAppScanner();
        return _instance;
    }

    static void kill() {
        if (_instance != (LocalAppScanner*)NULL) {
            delete _instance;
            _instance =  (LocalAppScanner*)NULL;
        }
    }

public slots:
    void scanLocalApps();

signals:
    void finished();

private:
    QList<LocalApp> localAppList;
    QString getAppVersion(QString appPath);
};


#endif // LOCALAPPSCANNER_H
