#ifndef FRMTULALL_H
#define FRMTULALL_H

#include <QDialog>
#include <QtSql>

namespace Ui {
    class frmTulAll;
}

class frmTulAll : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(frmTulAll)

public:
    explicit frmTulAll(QWidget *parent = 0);
    virtual ~frmTulAll();
    Ui::frmTulAll *m_ui;

protected:
    virtual void changeEvent(QEvent *e);

//private:
//    Ui::frmTulAll *m_ui;

private slots:
    void HelyseghezKeres(const QString&);
    void FajhozKeres(const QString&);
    void FajtahozKeres(const QString&);
};

#endif // FRMTULALL_H

