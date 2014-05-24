#ifndef STEMEDTOOLTIP_H
#define STEMEDTOOLTIP_H

#include <QWidget>
#include <QToolTip>
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>

namespace Ui {
class StemedTooltip;
}

class StemedTooltip : public QWidget
{
    Q_OBJECT

public:
    explicit StemedTooltip(QWidget *parent = 0);
    ~StemedTooltip();

    void setName(QString name);
    void setSize(QString size);
    void setUrl(QString url);

private:
    Ui::StemedTooltip *ui;
    void paintEvent(QPaintEvent *);

    const int STEM_HEIGHT = 10;
    const int STEM_WIDTH = 20;          //should be 2*STEM_WIDTH and even.
    const int WIDTH = 250;
    const int HEIGHT = 80;

    QWidget *_parent;

public slots:
    void showWindow();
    void hideWindow();
};

#endif // STEMEDTOOLTIP_H

