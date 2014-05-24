#ifndef MYQAPPLICATION_H
#define MYQAPPLICATION_H

#include <QApplication>

class MyQApplication : public QApplication {
    Q_OBJECT
public:
    explicit MyQApplication(int & argc, char ** argv);
    void onClickOnDock();

signals:
    void dockIconClicked();
};

#endif // MYQAPPLICATION_H
