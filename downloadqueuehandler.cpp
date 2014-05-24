#include "downloadqueuehandler.h"

DownloadQueueHandler *DownloadQueueHandler::instance = NULL;

void DownloadQueueHandler::startNextDownload() {
    //check if queue is empty
    if (queue.isEmpty()) {
        emit queueCompleted();
        return;
    }

    //retrieve latest software entry
    SoftwareEntry *s = queue.dequeue();
    s->dfh = new DownloadFileHandler(s->url, FileTools::getInstance()->getTmpPath(), false);
    s->entry->showProgressBar(true);

    //connect signals
    connect(s->dfh, SIGNAL(downloadProgressedPrct(int)), s->entry, SLOT(setProgressValue(int)));
    connect(s->dfh, SIGNAL(fileDownloadFinished()), this, SLOT(startNextDownload()));

    //start download
    s->dfh->beginDownload();
}

void DownloadQueueHandler::cancelQueue() {
    queue.clear();
    emit queueCanceled();
}

