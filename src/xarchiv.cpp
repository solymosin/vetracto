#include <QFileDialog>

#include "xarchiv.h"
#include "ui_xarchiv.h"

xArchiv::xArchiv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xArchiv)
{
    ui->setupUi(this);

    connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(setUt()));
}


void xArchiv::setUt(){
    QString dir = QFileDialog::getExistingDirectory(this, tr("Könyvtár beállítása"),"",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit->setText(dir);
}

xArchiv::~xArchiv()
{
    delete ui;
}

void xArchiv::changeEvent(QEvent *e)
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
