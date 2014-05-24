#include "msgdlg.h"
#include "ui_msgdlg.h"



MsgDlg::MsgDlg(QWidget *parent, QString title, QString message, QString buttonText) :
    QDialog(parent),
    ui(new Ui::MsgDlg)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::SplashScreen);
    this->setWindowOpacity(0.90);
    ui->title->setText(title);
    ui->text->setText(message);
    ui->button->setText(buttonText);
}

MsgDlg::~MsgDlg()
{
    delete ui;
}


void MsgDlg::mousePressEvent(QMouseEvent *event){
    mpos = event->pos();
}

void MsgDlg::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() && Qt::LeftButton) {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}
