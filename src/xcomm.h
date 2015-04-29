#ifndef XCOMM_H
#define XCOMM_H

#include <QDialog>

namespace Ui {
    class xComm;
}

class xComm : public QDialog {
    Q_OBJECT
public:
    xComm(QWidget *parent = 0);
    ~xComm();
    Ui::xComm *ui;

protected:
    void changeEvent(QEvent *e);

};

#endif // XCOMM_H
