#ifndef XDOKI_H
#define XDOKI_H

#include <QDialog>

namespace Ui {
    class xDoki;
}

class xDoki : public QDialog {
    Q_OBJECT
public:
    xDoki(QWidget *parent = 0);
    ~xDoki();
    Ui::xDoki *ui;

protected:
    void changeEvent(QEvent *e);


};

#endif // XDOKI_H
