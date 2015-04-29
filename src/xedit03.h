#ifndef XEDIT03_H
#define XEDIT03_H

#include <QDialog>

namespace Ui {
    class xEdit03;
}

class xEdit03 : public QDialog
{
    Q_OBJECT

public:
    explicit xEdit03(QWidget *parent = 0);
    ~xEdit03();

private:
    Ui::xEdit03 *ui;
};

#endif // XEDIT03_H
