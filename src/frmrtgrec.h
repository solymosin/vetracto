#ifndef FRMRTGREC_H
#define FRMRTGREC_H

#include <QDialog>

namespace Ui {
    class frmRTGrec;
}

class frmRTGrec : public QDialog {
    Q_OBJECT
public:
    frmRTGrec(QWidget *parent = 0);
    ~frmRTGrec();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::frmRTGrec *ui;
};

#endif // FRMRTGREC_H
