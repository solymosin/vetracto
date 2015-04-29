#include "xdoki.h"
#include "ui_xdoki.h"

xDoki::xDoki(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xDoki)
{
    ui->setupUi(this);
}

xDoki::~xDoki()
{
    delete ui;
}

void xDoki::changeEvent(QEvent *e)
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
