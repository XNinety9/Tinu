#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();

public slots:
    void minimize();
    void quit();
    void about();

signals:
    void minimizeApp();
    void closeApp();
    void aboutApp();

private:
    Ui::TitleBar *ui;
    QPoint mpos;
};

#endif // TITLEBAR_H
