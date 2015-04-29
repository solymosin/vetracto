#ifndef FRMOLT_H
#define FRMOLT_H

#include <QDialog>

namespace Ui {
    class frmOlt;
}

class frmOlt : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(frmOlt)
public:
    explicit frmOlt(QWidget *parent = 0);
    virtual ~frmOlt();
    Ui::frmOlt *m_ui;

protected:
    virtual void changeEvent(QEvent *e);

//public:
//    Ui::frmOlt *m_ui;

public slots:
    void EbVeszettseg();

};

#endif // FRMOLT_H
