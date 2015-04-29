#include "xcomm.h"
#include "ui_xcomm.h"

xComm::xComm(QWidget *parent): QDialog(parent), ui(new Ui::xComm){
    ui->setupUi(this);

    ui->comboBox->addItem("E-mail");
    ui->comboBox->addItem("Telefon");

}

xComm::~xComm()
{
    delete ui;
}

void xComm::changeEvent(QEvent *e)
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
