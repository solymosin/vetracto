#ifndef FRMQUERY_H
#define FRMQUERY_H

#include <QDialog>

namespace Ui {
    class frmQuery;
}

class frmQuery : public QDialog {
    Q_OBJECT
public:
    frmQuery(QWidget *parent = 0);
    ~frmQuery();
    Ui::frmQuery *ui;

protected:
    void changeEvent(QEvent *e);

//private:
//    Ui::frmQuery *ui;

private slots:
    void setUt();

};

#endif // FRMQUERY_H
