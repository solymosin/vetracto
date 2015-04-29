#include "xedialog.h"
#include "ui_xedialog.h"

xEDialog::xEDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xEDialog)
{
    ui->setupUi(this);
}

xEDialog::~xEDialog()
{
    delete ui;
}

void xEDialog::changeEvent(QEvent *e)
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
