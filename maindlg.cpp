#include "maindlg.h"
#include "ui_maindlg.h"

#include <QDebug>

MainDlg::MainDlg(QWidget *parent) : QDialog(parent), ui(new Ui::MainDlg) {
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowOpacity(0.95);
    this->setFixedSize(this->geometry().size());

    //prepare system tray icon
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/rsc/package.png"));
    trayIcon->setVisible(true);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    //prepare nice wait layer
    waitLayer = new QLabel(this);
    waitLayer->setGraphicsEffect(new QGraphicsBlurEffect());
    waitLayer->setPixmap(this->grab());
    waitLayer->hide();

    //connect minimize and close signals
    connect(ui->titleBar, SIGNAL(closeApp()), this, SLOT(closeApp()));
    connect(ui->titleBar, SIGNAL(minimizeApp()), this, SLOT(minimizeApp()));
    connect(ui->titleBar, SIGNAL(aboutApp()), this, SLOT(about()));

    //show waitLayer while working
    showWaitLayer(true);

    //retrieve once-for-all tmpPath
    tmpDir = FileTools::getInstance()->getTmpPath();

    //retrieve and parse list.xml
    dfh = new DownloadFileHandler(listDotZipPath, tmpDir, false);
    qDebug()<<tmpDir;
    connect(dfh, SIGNAL(fileDownloadFinished()), this, SLOT(parseListDotXml()));
    connect(dfh, SIGNAL(fileDownloadError(QString)), this, SLOT(downloadError(QString)));
    dfh->beginDownload();
}

MainDlg::~MainDlg() {
    delete ui;
    delete dfh;
}


void MainDlg::about() {
    Message::showMessage(this, "About", "This is Tinu, powerful batch installer for OSX.<br><br>It's been developped using Qt5.<br><br>Tinu's website: tinu.deadbird.fr");
}

void MainDlg::closeApp() {
    minimizeApp();

    //TODO: gérer la fermeture et le nettoyage

    //clean everything in tmp folder
    FileTools::getInstance()->clearTmp();

    close();
}

void MainDlg::showApp() {
    this->show();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setStartValue(0.0);
    animation->setEndValue(0.95);
    animation->setDuration(400);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    animation->start();
}

void MainDlg::minimizeApp() {
    //hiding effect
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setStartValue(0.95);
    animation->setEndValue(0.0);
    animation->setDuration(400);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    connect(animation, SIGNAL(finished()), this, SLOT(hideApp()));

    animation->start();
}

void MainDlg::hideApp() {
    this->hide();
}

void MainDlg::downloadError(QString error) {
    Q_UNUSED(error);

    Message::showMessage(this, "Uhoh...", StringDictionnary::getInstance()->getMsg("ER_NO_INTERNET"));
    hasError = true;

    closeApp();
}

void MainDlg::parseListDotXml() {
    //extract ZIP file
    bool extracted = FileTools::getInstance()->unzip(tmpDir, "/list.zip");
    if (!extracted) {
        //TODO: get error message
        hasError = true;
    }

    //verify MD5 sum.
    QString calculatedMd5 = md5::md5FromFile(tmpDir.path()+"/list.xml");
    QFile md5File(tmpDir.path()+"/list.md5");
    if (!md5File.open(QIODevice::ReadOnly)) {
        hasError = true;
    } else {
        QString originalMd5(md5File.readLine());
        if (originalMd5.compare(calculatedMd5)) {
            hasError = true;
        }
    }

    //actually parse XML file
    if (!hasError) {
        XMLParser xml;

        connect(&xml, SIGNAL(hasNewItem(SoftwareEntry*)), this, SLOT(addSoftwareEntry(SoftwareEntry*)));
        connect(&xml, SIGNAL(finished()), this, SLOT(buildTabContent()));

        xml.readFile(tmpDir.path()+"/list.xml");
    }
}

void MainDlg::buildTabContent() {
    //first pass: build tabs
    foreach(SoftwareEntry *s, list) {
        QWidget *where;

        //if tab already exists...
        if (tabs.contains(s->category)) {
            where = tabs[s->category];
        } else {
            where = new QWidget();
            where->setLayout(new QVBoxLayout());
            ui->tab->addTab(where, s->category);
            tabs.insert(s->category, where);
        }

        QLayout *layout = where->layout();

        TabEntry *entry = new TabEntry(where);
        s->entry = entry;
        entry->setName(s->name);
        entry->setIcon(tmpDir.path()+"/"+s->icon);
        entry->setToolTip(QString("<b>%1 %2</b>").arg(s->name).arg(s->version), QString("<b>Size:</b> %1").arg(s->size), s->url);



        layout->addWidget(entry);
    }

    //second pass through tabs to add spacers
    foreach(QWidget *w, tabs) {
        w->layout()->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    }

    showWaitLayer(false);
}

void MainDlg::addSoftwareEntry(SoftwareEntry *s) {
    list.insert(s->name, s);
}

void MainDlg::showWaitLayer(bool activate = true) {
    if (activate) {
        waitLayer->setGeometry(this->geometry());
        waitLayer->show();
    } else {
        waitLayer->setText("");

        QRect begin = waitLayer->geometry();
        QRect end = waitLayer->geometry();
        end.setTop(this->height()-1);

        QPropertyAnimation *animation = new QPropertyAnimation(waitLayer, "geometry");
        animation->setStartValue(begin);
        animation->setEndValue(end);
        animation->setDuration(2000);
        animation->setEasingCurve(QEasingCurve::OutBounce);
        animation->start();

        connect(animation, SIGNAL(finished()), waitLayer, SLOT(hide()));
    }
}

void MainDlg::go() {
    bool somethingWasChecked = false;

    //scan for checked app
    foreach(SoftwareEntry *s, list) {
        //if checked, add to download queue
        if (s->entry->isChecked()) {
            somethingWasChecked = true;
            DownloadQueueHandler::getInstance()->addDownload(s);
        }
    }

    if (somethingWasChecked == false) {
        Message::showMessage(this, "Error", StringDictionnary::getInstance()->getMsg("ER_NOTHING_SELECTED"));
    } else {
        connect(DownloadQueueHandler::getInstance(), SIGNAL(queueCompleted()), this, SLOT(installSoftwareEntries()));
        DownloadQueueHandler::getInstance()->startNextDownload();
    }
}

void MainDlg::installSoftwareEntries() {
    Message::showMessage(this, "Eheh :D", "Download completed!");
}

void MainDlg::mousePressEvent(QMouseEvent *event){
    mpos = event->pos();
}

void MainDlg::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() && Qt::LeftButton) {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}
