#include "maindlg.h"


#include <QApplication>
#include <QCoreApplication>
#include <QTimer>
#include <QString>
#include <QObject>

#include <localappscanner.h>
#include "myqapplication.h"

#include "filetools.h"


int main(int argc, char *argv[]) {
    //test area
    /*FileTools::mountDMG(QDir("/Applications/MAMP/htdocs/apps"), "Sublime Text Build 3047.dmg");

    return 0;*/
    //end of test area

    MyQApplication a(argc, argv);
    LocalAppScanner *appScanner = LocalAppScanner::getInstance();

    MainDlg w;
    a.connect(&a, SIGNAL(dockIconClicked()), &w, SLOT(showApp()));
    w.show();

    //set timer to launch scan
    QTimer::singleShot(0, appScanner, SLOT(scanLocalApps()));

    return a.exec();
}
