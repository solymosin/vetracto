#include <QtSql>
#include <QMenu>
#include <QPushButton>

#include "frmlabor.h"
#include "ui_frmlabor.h"
#include "xlabor.h"
#include "ui_xlabor.h"

#include "vtrcodes.h"

frmLabor::frmLabor(QWidget *parent): QDialog(parent), ui(new Ui::frmLabor){
    ui->setupUi(this);

    connect(ui->treeWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(kielolt()));
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(elozmeny()));
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(tablaPopUp()));
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(close()));

}


void frmLabor::tablaPopUp(){
    QMenu* contextMenu = new QMenu(this);
    QString lab = QString("Töröl");
    QAction *a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(sorTorol()));

    contextMenu->popup(QCursor::pos());
    contextMenu->exec();
    delete contextMenu;
    contextMenu = 0;
}

void frmLabor::sorTorol(){
    vtrcodes vc;

    QModelIndex idx = ui->tableView->selectionModel()->currentIndex();
    QString litem = ui->tableView->model()->data(idx.sibling(idx.row(),4)).toString();
    QString datum;

    vc.laborDel(litem);
    if (ui->comboBox_2->currentText()==""){
        datum = ui->dateEdit->date().toString("yyyy-MM-dd");
    } else {
        datum = ui->comboBox_2->currentText();
    }

    betolt(trsz, datum);
}


void frmLabor::elozmeny(){
    betolt(trsz, ui->comboBox_2->currentText());
}


void frmLabor::betolt(QString trsz, QString datum){
    QSqlQueryModel *model1 = new QSqlQueryModel();
    model1->setHeaderData(0, Qt::Horizontal, QObject::tr("Paraméter"));
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Érték"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Kutya"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("Macska"));
    model1->setHeaderData(4, Qt::Horizontal, QObject::tr("id"));

    QString sql = QString("select xblabor.parameter, blabor.ertek, xblabor.kutya, xblabor.macska, blabor.az "
        "From alpha Inner Join blabor On alpha.az = blabor.alphaaz "
        "Inner Join xblabor On xblabor.az = blabor.vizsgalat "
        "Where alpha.torzsszam = %1 and alpha.datum = '%2' "
        "order by xblabor.parameter").arg(trsz).arg(datum);
    model1->setQuery(sql);
    ui->tableView->setModel(model1);
}




void frmLabor::kielolt(){
    xLabor dlg(this);
    dlg.setWindowTitle("Paraméter rögzítése");

    dlg.ui->label_3->setText(ui->treeWidget->currentItem()->text(1));
    dlg.ui->label_5->setText(ui->treeWidget->currentItem()->text(3));
    dlg.ui->label_7->setText(ui->treeWidget->currentItem()->text(4));
    QString pid = ui->treeWidget->currentItem()->text(5);
    QString datum;

    if(dlg.exec()==QDialog::Accepted){
        vtrcodes vc;
        if (ui->comboBox_2->currentText()==""){
            datum = ui->dateEdit->date().toString("yyyy-MM-dd");
        } else {
            datum = ui->comboBox_2->currentText();
        }
        QString alphaID = vc.alphaIDentify(doki, trsz, datum);
        vc.laborRec(alphaID,pid,dlg.ui->lineEdit->text());
        betolt(trsz, datum);
    }

}


frmLabor::~frmLabor()
{
    delete ui;
}

void frmLabor::changeEvent(QEvent *e)
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
