#include "frmrtgrec.h"
#include "ui_frmrtgrec.h"

frmRTGrec::frmRTGrec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmRTGrec)
{
    ui->setupUi(this);
}

frmRTGrec::~frmRTGrec()
{
    delete ui;
}

void frmRTGrec::changeEvent(QEvent *e)
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
