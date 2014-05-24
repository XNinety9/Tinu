#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QString>
#include <QDebug>
#include <QDomDocument>
#include <QFile>


#include "catalog.h"

class XMLParser : public QObject {
    Q_OBJECT

public:
    XMLParser(QObject *parent = 0);
    bool readFile(const QString &fileName);

private:
    QList<SoftwareEntry> *_liste;

signals:
    void finished();
    void hasNewItem(SoftwareEntry *s);
};

#endif // XMLPARSER_H
