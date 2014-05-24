#ifndef MAINDLG_H
#define MAINDLG_H

#include <QDialog>
#include <QRect>
#include <QLabel>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QString>
#include <QList>
#include <QMap>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QGraphicsBlurEffect>
#include <QPainter>
#include <QProgressBar>

#include "downloadqueuehandler.h"
#include "downloadFileHandler.h"
#include "xmlparser.h"
#include "catalog.h"
#include "tabentry.h"
#include "md5.h"
#include "msgdlg.h"
#include "filetools.h"
#include "stringdictionnary.h"

namespace Ui {
    class MainDlg;
}

class MainDlg : public QDialog {
    Q_OBJECT

public:

    explicit MainDlg(QWidget *parent = 0);
    ~MainDlg();

    bool isMinimized() {return minimized;}

public slots:
    void parseListDotXml();
    void addSoftwareEntry(SoftwareEntry *s);
    void installSoftwareEntries();
    void showWaitLayer(bool activate);
    void downloadError(QString);
    void buildTabContent();
    void go();
    void closeApp();
    void minimizeApp();
    void showApp();
    void hideApp();
    void about();

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::MainDlg *ui;
    QDir tmpDir;

    QSystemTrayIcon *trayIcon;
    QLabel *waitLayer;
    bool minimized;

    const QString listDotZipPath = "http://localhost/list.zip";

    QMap<QString, SoftwareEntry*> list;
    QMap<QString, QWidget*> tabs;
    const QString toolTip = "<table width='200'><tr><td colspan='2'><b><center>%1 %2</center></b></td></tr><tr><td>Size</td><td>%3</td></tr><tr><td>URL</td><td><nobr>%4</nobr></td></tr></table>";

    DownloadFileHandler *dfh;
    DownloadQueueHandler *dqh;

    bool hasError = false;


    QPoint mpos;
};

#endif // MAINDLG_H
