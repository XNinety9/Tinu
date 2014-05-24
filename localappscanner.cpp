#include "localappscanner.h"

#include <QBuffer>

LocalAppScanner* LocalAppScanner::_instance = NULL;

void LocalAppScanner::scanLocalApps() {
    QDirIterator it("/Applications");

    while (it.hasNext()) {
        it.next();

        if (!it.fileInfo().isDir())
            continue;

        if (!it.fileName().compare(".") || !it.fileName().compare(".."))
            continue;

        LocalApp l;
        l.name = it.fileName();
        l.version = getAppVersion(it.filePath());

        localAppList.append(l);
    }

    emit finished();
}

QString LocalAppScanner::getAppVersion(QString appPath) {
    QString version;
    QString fileName = appPath + "/Contents/Info.plist";

    //prepare file
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {

        //transfer file content to buffer
        QByteArray data = file.readAll();
        QBuffer buffer(&data);
        if (buffer.open(QIODevice::ReadOnly)) {
            //create query
            QXmlQuery query(QXmlQuery::XQuery10);
            query.bindVariable("file", &buffer);
            query.setQuery("declare variable $file external; doc($file)/plist/dict/key[node()='CFBundleShortVersionString']/following-sibling::string[1]/node()");

            //execute query
            query.evaluateTo(&version);
            buffer.close();
        }
        file.close();
    }
    return version.remove(QChar('\n'), Qt::CaseInsensitive);
}

