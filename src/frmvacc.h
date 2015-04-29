#ifndef FRMVACC_H
#define FRMVACC_H

#include <QDialog>

namespace Ui {
    class frmVacc;
}

class frmVacc : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(frmVacc)

public:
    explicit frmVacc(const QString &id, QWidget *parent = 0);
    virtual ~frmVacc();
    QString doki;
    QString allat_az;
    Ui::frmVacc *m_ui;

protected:
    virtual void changeEvent(QEvent *e);

//private:
//    Ui::frmVacc *m_ui;

public slots:
    void frmOltBetolt();
    void EbVeszettseg();
    void Torol();
    void Tab01Unselect();
    void Tab02Unselect();
    void TabBetolt(const QString&);    

};

#endif // FRMVACC_H
