#ifndef MD5_H
#define MD5_H

#include <QString>
#include <QCryptographicHash>
#include <QFile>

/**
 * @class md5
 * @brief The md5 class is used to compute the MD5 sum of a file, just by providing the path to it.
 *
 * md5 class contains a static method that allows you to compute the MD5 sum of a file just by providing a QString containing
 * the path to this file.
 */
class md5 {
public:
    /**
     * @brief md5FromFile computes the MD5 sum of a file.
     * @param file The path to the file.
     * @return Returns a QString containing the MD5 sum.
     */
    static QString md5FromFile(QString file);
};

#endif // MD5_H
