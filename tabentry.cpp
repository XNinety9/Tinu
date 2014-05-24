#include "tabentry.h"
#include "ui_tabentry.h"
#include <QDebug>

TabEntry::TabEntry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabEntry) {
    ui->setupUi(this);

    ui->progressBar->hide();
    ui->progressBar->setRange(0, 100);

    tooltip = new StemedTooltip(this);
}

TabEntry::~TabEntry() {
    delete ui;
}


void TabEntry::setName(QString name) {
    ui->checkBox->setText(name);
}

void TabEntry::setIcon(QString icon) {
    ui->label->setPixmap(QPixmap(icon));
}

bool TabEntry::isChecked() {
    return ui->checkBox->isChecked();
}

void TabEntry::setProgressValue(int value) {
    value = (value>100? 100:value);
    qDebug()<<"Updating progress bar with "<<value;
    ui->progressBar->setValue(value);
}

void TabEntry::showProgressBar(bool visible) {
    ui->progressBar->setVisible(visible);
}

void TabEntry::showStatusText(QString text) {
    showProgressBar(false);
    ui->status->setText(text);
}

bool TabEntry::event(QEvent *ev) {
    if (ev->type() == QEvent::ToolTip) {
        tooltip->showWindow();
        return true;
    } else if (ev->type() == QEvent::Leave) {
        qDebug()<<"hover leave";
        tooltip->hideWindow();
    }
    return false;
}

void TabEntry::setToolTip(QString name, QString size, QString url) {
    tooltip->setName(name);
    tooltip->setUrl(url);
    tooltip->setSize(size);
}
