#ifndef FRMLABOR_H
#define FRMLABOR_H

#include <QDialog>

namespace Ui {
    class frmLabor;
}

class frmLabor : public QDialog {
    Q_OBJECT
public:
    frmLabor(QWidget *parent = 0);
    ~frmLabor();
    Ui::frmLabor *ui;
    QString trsz, doki;

protected:
    void changeEvent(QEvent *e);

public slots:
    void kielolt();
    void betolt(QString trsz, QString datum);

private slots:
    void elozmeny();
    void tablaPopUp();
    void sorTorol();

};

#endif // FRMLABOR_H
