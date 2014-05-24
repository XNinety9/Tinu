#ifndef TABENTRY_H
#define TABENTRY_H

#include <QWidget>
#include <QImage>
#include <QEvent>

#include "stemedtooltip.h"

namespace Ui {
class TabEntry;
}

class TabEntry : public QWidget {
    Q_OBJECT

private:
    bool event(QEvent *);

public:
    explicit TabEntry(QWidget *parent = 0);
    ~TabEntry();

    void setName(QString);
    void setIcon(QString);
    void setTooltipText(QString text) {tooltipText = text;}
    void showProgressBar(bool visible);

    bool isChecked();

    void setToolTip(QString name, QString size, QString url);

public slots:
    void setProgressValue(int value);
    void showStatusText(QString text);

private:
    Ui::TabEntry *ui;
    QString tooltipText;
    StemedTooltip *tooltip;
};

#endif // TABENTRY_H
