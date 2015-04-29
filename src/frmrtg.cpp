#include <QtSql>


#include "frmrtg.h"
#include "ui_frmrtg.h"

frmRTG::frmRTG(QWidget *parent): QDialog(parent), ui(new Ui::frmRTG){
    ui->setupUi(this);

}

frmRTG::~frmRTG()
{
    delete ui;
}

void frmRTG::changeEvent(QEvent *e)
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

void frmRTG::TabBetolt(const QString& id){
    QSqlQueryModel *model1 = new QSqlQueryModel();
    model1->setHeaderData(0, Qt::Horizontal, QObject::tr("Dátum"));
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Sorszám"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Méret"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("Leírás"));
    model1->setHeaderData(4, Qt::Horizontal, QObject::tr("Diagnózis"));
    model1->setHeaderData(5, Qt::Horizontal, QObject::tr("ID"));

//    QString sql = QString("Select alpha.datum, xbvakcinak.oltoanyag, bvakcinazas.sorszama, xdokik.doki, bvakcinazas.az "
//        "From alpha Inner Join xdokik On xdokik.az = alpha.allatorvos Inner Join bvakcinazas On bvakcinazas.alphaaz = alpha.az Inner Join xbvakcinak On xbvakcinak.az = bvakcinazas.vakcina "
//        "Where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(id);
//    model1->setQuery(sql);
    ui->tableView->setModel(model1);
}

