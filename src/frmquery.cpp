#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFileDialog>

#include "frmquery.h"
#include "ui_frmquery.h"

frmQuery::frmQuery(QWidget *parent): QDialog(parent), ui(new Ui::frmQuery){
    ui->setupUi(this);

    QDate date = QDate::currentDate();
    int jd = date.toJulianDay()-(date.day()-1);
    ui->dateEdit->setDate(date.fromJulianDay(jd));
    ui->dateEdit_2->setDate(date.fromJulianDay(ui->dateEdit->date().addMonths(1).toJulianDay()-1));

    ui->dateEdit_3->setDate(ui->dateEdit->date());
    ui->dateEdit_4->setDate(ui->dateEdit_2->date());

    ui->tab_2->setDisabled(true);

    connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(setUt()));

}

void frmQuery::setUt(){
    QString dir = QFileDialog::getExistingDirectory(this, tr("Könyvtár beállítása"),"",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit->setText(dir);
}



frmQuery::~frmQuery()
{
    delete ui;
}

void frmQuery::changeEvent(QEvent *e)
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
