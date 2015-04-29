#include "frmmegj.h"
#include "ui_frmmegj.h"

frmMegj::frmMegj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMegj)
{
    ui->setupUi(this);
}

frmMegj::~frmMegj()
{
    delete ui;
}

void frmMegj::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
