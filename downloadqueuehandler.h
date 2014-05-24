#ifndef DOWNLOADQUEUEHANDLER_H
#define DOWNLOADQUEUEHANDLER_H

#include <QObject>
#include <QQueue>

#include "catalog.h"
#include "downloadFileHandler.h"
#include "filetools.h"

class DownloadQueueHandler : public QObject {
    Q_OBJECT
private:
    DownloadQueueHandler(): QObject() {}

public:
    /**
     * @brief getInstance returns an instance of DownloadQueueHandler singleton.
     * @return
     */
    static DownloadQueueHandler* getInstance() {
        if (instance == NULL) {
            instance = new DownloadQueueHandler();
        }
        return instance;
    }

    static void destroy() {
        if (instance != NULL) {
            delete instance;
            instance = NULL;
        }
    }

    void addDownload(SoftwareEntry *entry) {
        if (entry != NULL) {
            queue.enqueue(entry);
        }
    }

    void downloadNext();

private:
    static DownloadQueueHandler *instance;
    QQueue<SoftwareEntry*> queue;

    const int MAX_DOWNLOADS = 3;
    int downloadsRunning;

signals:
    void queueCompleted();
    void queueCanceled();

public slots:
    void startNextDownload();
    void cancelQueue();
};

#endif // DOWNLOADQUEUEHANDLER_H
