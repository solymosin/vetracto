#ifndef XEDIALOG_H
#define XEDIALOG_H

#include <QDialog>

namespace Ui {
    class xEDialog;
}

class xEDialog : public QDialog {
    Q_OBJECT
public:
    xEDialog(QWidget *parent = 0);
    ~xEDialog();
    Ui::xEDialog *ui;

protected:
    void changeEvent(QEvent *e);


};

#endif // XEDIALOG_H
