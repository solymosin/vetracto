#ifndef FRMMEGJ_H
#define FRMMEGJ_H

#include <QDialog>

namespace Ui {
    class frmMegj;
}

class frmMegj : public QDialog {
    Q_OBJECT
public:
    frmMegj(QWidget *parent = 0);
    ~frmMegj();
    Ui::frmMegj *ui;

protected:
    void changeEvent(QEvent *e);



};

#endif // FRMMEGJ_H
