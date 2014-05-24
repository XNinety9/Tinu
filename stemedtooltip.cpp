#include "stemedtooltip.h"
#include "ui_stemedtooltip.h"

StemedTooltip::StemedTooltip(QWidget *parent) :
    QWidget(),
    ui(new Ui::StemedTooltip) {
    ui->setupUi(this);

    _parent = parent;
    this->setWindowOpacity(0.95);

    this->setWindowFlags(Qt::FramelessWindowHint);
}

StemedTooltip::~StemedTooltip() {
    delete ui;
}

void StemedTooltip::paintEvent(QPaintEvent *) {
    QStyleOption qso;
    qso.initFrom(this);

    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &qso, &p, this);          //needed for QWidget subclass to support stylesheets
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);

    //create nice rounded rectangle
    QPainterPath path;

    //add stem
    QPainterPath stemPath;
    QPolygon stem;

    path.addRect(QRectF(0, 0, this->width()-STEM_HEIGHT, this->height()));
    stem.append(QPoint(this->width() - STEM_HEIGHT, (this->height()/2) - (STEM_WIDTH/2)));
    stem.append(QPoint(this->width(), this->height()/2));
    stem.append(QPoint(this->width() - STEM_HEIGHT, (this->height()/2) + (STEM_WIDTH/2)));
    QRegion maskedRegion(path.toFillPolygon().toPolygon());
    stemPath.addPolygon(stem);

    maskedRegion += stemPath.toFillPolygon().toPolygon();

    setMask(maskedRegion);
}

void StemedTooltip::showWindow() {
    //update pos according to parent's
    QRect parentPos = this->_parent->geometry();
    QPoint p = _parent->mapToGlobal(QPoint(parentPos.left(), parentPos.top()));

    int x = p.x() - (WIDTH + 28);
    int y = p.y() - (HEIGHT/2);


    this->setGeometry(x, y, WIDTH, HEIGHT);

    this->show();
}

void StemedTooltip::hideWindow() {
    qDebug()<<"hide window!";
    this->hide();
}

void StemedTooltip::setName(QString name) {
    ui->name->setText(name);
}

void StemedTooltip::setSize(QString size) {
    ui->size->setText(size);
}

void StemedTooltip::setUrl(QString url) {
    ui->url->setText(url);
}
