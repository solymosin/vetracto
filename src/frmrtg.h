#ifndef FRMRTG_H
#define FRMRTG_H

#include <QDialog>

namespace Ui {
    class frmRTG;
}

class frmRTG : public QDialog {
    Q_OBJECT
public:
    frmRTG(QWidget *parent = 0);
    ~frmRTG();
    Ui::frmRTG *ui;

protected:
    void changeEvent(QEvent *e);

//private:
//    Ui::frmRTG *ui;

private slots:
    void TabBetolt(const QString& id);

};

#endif // FRMRTG_H
