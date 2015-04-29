#ifndef FRMDOKI_H
#define FRMDOKI_H

#include <QDialog>

namespace Ui {
    class frmDoki;
}

class frmDoki : public QDialog {
    Q_OBJECT
public:
    frmDoki(QWidget *parent = 0);
    ~frmDoki();
    Ui::frmDoki *ui;

protected:
    void changeEvent(QEvent *e);

private slots:
    void tablabetolto();
    void dokiPopUp();
    void dokiRec();
    void dokiMod();
};

#endif // FRMDOKI_H
