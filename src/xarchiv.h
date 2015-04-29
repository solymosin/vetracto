#ifndef XARCHIV_H
#define XARCHIV_H

#include <QDialog>

namespace Ui {
    class xArchiv;
}

class xArchiv : public QDialog {
    Q_OBJECT
public:
    xArchiv(QWidget *parent = 0);
    ~xArchiv();
    Ui::xArchiv *ui;

protected:
    void changeEvent(QEvent *e);

private slots:
    void setUt();
};

#endif // XARCHIV_H
