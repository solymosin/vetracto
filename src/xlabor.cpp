#include "xlabor.h"
#include "ui_xlabor.h"

xLabor::xLabor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xLabor)
{
    ui->setupUi(this);
}

xLabor::~xLabor()
{
    delete ui;
}

void xLabor::changeEvent(QEvent *e)
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
