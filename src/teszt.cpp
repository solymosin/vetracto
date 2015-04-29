#include "teszt.h"
#include "ui_teszt.h"

teszt::teszt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::teszt)
{
    ui->setupUi(this);
}

teszt::~teszt()
{
    delete ui;
}

void teszt::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
