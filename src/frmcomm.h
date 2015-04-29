#ifndef FRMCOMM_H
#define FRMCOMM_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
    class frmComm;
}

class frmComm : public QDialog {
    Q_OBJECT
public:
    frmComm(QWidget *parent = 0);
    ~frmComm();
    Ui::frmComm *ui;
    QString tulajID;

protected:
    void changeEvent(QEvent *e);

public slots:
    void TabBetolt(const QString&);
    void kommPopUp();
    void kommUj();
    void kommMod();
    void kommTorol();

};

#endif // FRMCOMM_H
