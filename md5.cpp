#include "md5.h"

QString md5::md5FromFile(QString file) {
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly)) {
        return QString("");
    }
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(&f);
    QByteArray result = hash.result();

    return QString(result.toHex());
}
