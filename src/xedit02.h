#ifndef XEDIT02_H
#define XEDIT02_H

#include <QDialog>
#include <QStandardItemModel>
#include "checkitem.h"

namespace Ui {
    class xEdit02;
}

class xEdit02 : public QDialog {
    Q_OBJECT
public:
    xEdit02(QWidget *parent = 0);
    ~xEdit02();
    Ui::xEdit02 *ui;
    QStandardItemModel *model;
    QStandardItem *item;

protected:
    void changeEvent(QEvent *e);

public slots:
    void chI(QString sql);

};

#endif // XEDIT02_H
