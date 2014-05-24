#ifndef MSGDLG_H
#define MSGDLG_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
    class MsgDlg;
}


class MsgDlg : public QDialog {
    Q_OBJECT

public:
    explicit MsgDlg(QWidget *parent = 0, QString title = "", QString message = "", QString buttonText = "Dismiss");
    ~MsgDlg();

private:
    Ui::MsgDlg *ui;
    QPoint mpos;

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
};

class Message {
public:
    static void showMessage(QWidget *parent = 0, QString title = "", QString message = "", QString buttonText = "Dismiss") {
        MsgDlg m(parent, title, message, buttonText);
        m.exec();
    }
};

#endif // MSGDLG_H
