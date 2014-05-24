/**
 * @file downloadFileHandler.h
 * @brief Class used to download files from the internet.
 * @author deadbird
 * @date 23rd of january, 2014
 *
 * This class allows you to download stuff from the Internet over http. Specify URL, storage location and you're done.
 * It also provides many signals and slots for convenience.
 *
 */

#ifndef DOWNLOADFILEHANDLER_H
#define DOWNLOADFILEHANDLER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QQueue>

#include <QDebug>

/**
 * @class DownloadFileHandler
 * @brief The DownloadFileHandler class
 *
 * This class allows you to download stuff from the Internet over http. Specify URL, storage location and you're done.
 * It also provides many signals and slots for convenience.
 */
class DownloadFileHandler : public QObject {
    Q_OBJECT
 
public:
    /**
     * @brief Default constructor.
     * @param downloadUrl The web URL of the file to be downloaded.
     * @param storageLocation The place where the file should be downloaded to.
     * @param startImmediately If true, starts the download immediately. If false, use beginDownload to do so.
     */
    DownloadFileHandler(const QUrl &downloadUrl, const QDir &storageLocation, bool startImmediately = false);
    /**
     * @brief Default destructor.
     */
    DownloadFileHandler() : QObject() {}
    /**
     * @brief setFile
     * @param file
     */
    inline void setFile(QFile *file) { pFile = file; }
    inline void setStorageLocation(const QDir &location) { mStorageLocation = location; }
    inline void setDownloadURL(const QUrl &url) { mDownloadUrl = url; }
 
    inline QFile* file() const { return pFile; }
    inline QDir storageLocation() const { return mStorageLocation; }
    inline QUrl downloadUrl() const { return mDownloadUrl; }
 
signals:
    void fileAlreadyExistsError(QString existingFileDisplayName);
    void fileOpeningError(QString errorMessage);
    void fileDownloadError(QString errorMessage);
    void fileDownloadStarted();
    void fileDownloadCancelled();
    void fileDownloadFinished();
    void downloadProgressed(qint64 bytesReceived, qint64 bytesTotal);
    void downloadProgressedPrct(int percent);
 
public slots:
    void setDownloadURLSlot(const QString &url);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void beginDownload();
    void cancelDownload();
    void downloadFinished();
    void downloadReadyRead();
 
private:
    QFile *pFile;                           /*!< QFile used to write downloaded content onto the disk*/
    QDir mStorageLocation;
 
    QUrl mDownloadUrl;
 
    QNetworkReply *pNetworkReply;
    QNetworkAccessManager mNetworkManager;
};

#endif
