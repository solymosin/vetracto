#ifndef XLABOR_H
#define XLABOR_H

#include <QDialog>

namespace Ui {
    class xLabor;
}

class xLabor : public QDialog {
    Q_OBJECT
public:
    xLabor(QWidget *parent = 0);
    ~xLabor();
    Ui::xLabor *ui;

protected:
    void changeEvent(QEvent *e);



};

#endif // XLABOR_H
