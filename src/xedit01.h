#ifndef XEDIT01_H
#define XEDIT01_H

#include <QDialog>

namespace Ui {
    class xEdit01;
}

class xEdit01 : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(xEdit01)

public:
    xEdit01(QWidget *parent = 0);
    ~xEdit01();    
    QString msql, csql, mtabla;
    Ui::xEdit01 *ui;


protected:
    void changeEvent(QEvent *e);

public slots:
    void TabBetolt();
    void tabPopUp();
    void modosit();

};

#endif // XEDIT01_H
