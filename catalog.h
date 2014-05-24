#ifndef CATALOG_H
#define CATALOG_H

#include <QObject>
#include <QMap>

#include <tabentry.h>
#include <downloadfilehandler.h>

class SoftwareEntry {
public:
    QString name;
    QString version;
    QString size;
    QString url;
    QString app_name;
    QString actions;
    QString category;
    QString icon;

    TabEntry *entry;
    DownloadFileHandler *dfh;
};


class Catalog : public QObject
{
    Q_OBJECT
private:
    Catalog(): QObject() {}

public:
    /**
     * @brief getInstance returns an instance of DownloadQueueHandler singleton.
     * @return
     */
    static Catalog* getInstance() {
        if (instance == NULL) {
            instance = new Catalog();
        }
        return instance;
    }

    static void destroy() {
        if (instance != NULL) {
            delete instance;
            instance = NULL;
        }
    }

private:
    static Catalog *instance;
    static QMap<SoftwareEntry, QString> catalog;


signals:

public slots:

};

#endif // CATALOG_H
