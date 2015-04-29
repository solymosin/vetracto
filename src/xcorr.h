#ifndef XCORR_H
#define XCORR_H

#include <QDialog>

namespace Ui {
    class xCorr;
}

class xCorr : public QDialog {
    Q_OBJECT
public:
    xCorr(QWidget *parent = 0);
    ~xCorr();
    QString ss;
    Ui::xCorr *ui;

protected:
    void changeEvent(QEvent *e);


};

#endif // XCORR_H
