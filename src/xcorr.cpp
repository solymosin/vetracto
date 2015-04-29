#include "xcorr.h"
#include "ui_xcorr.h"

#include <QDebug>

xCorr::xCorr(QWidget *parent): QDialog(parent), ui(new Ui::xCorr){
    ui->setupUi(this);

    qDebug() << ss;
}

xCorr::~xCorr()
{
    delete ui;
}

void xCorr::changeEvent(QEvent *e)
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
