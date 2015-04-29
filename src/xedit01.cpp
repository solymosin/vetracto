#include <QSqlQueryModel>
#include <QDebug>
#include <QMenu>
#include <QSqlQuery>

#include "xedit01.h"
#include "ui_xedit01.h"
#include "xedialog.h"
#include "ui_xedialog.h"

#include "vtrcodes.h"

xEdit01::xEdit01(QWidget *parent): QDialog(parent), ui(new Ui::xEdit01){
    ui->setupUi(this);

    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(tabPopUp()));
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(modosit()));
}


void xEdit01::modosit(){
    xEDialog *dlg = new xEDialog();

    QModelIndex idx;

    idx = ui->tableView->selectionModel()->currentIndex();
    dlg->ui->lineEdit->setText(ui->tableView->model()->data(idx.sibling(idx.row(),0)).toString());
    dlg->ui->comboBox->setCurrentIndex(dlg->ui->comboBox->findText(dlg->ui->lineEdit->text(), Qt::MatchExactly));

    QString rID = ui->tableView->model()->data(idx.sibling(idx.row(),1)).toString();

    QSqlQuery query(csql);
    while (query.next()) {
        dlg->ui->comboBox->addItem(query.value(0).toString());
    }

    if (dlg->exec() == QDialog::Accepted ){
        QString jsql = "";
        QString nVal = dlg->ui->comboBox->currentText();

        if (mtabla=="Ivar"){
            jsql = QString("update xaivar set ivar='%1' where az=%2").arg(nVal).arg(rID);
        } else if (mtabla=="Szín"){
            jsql = QString("update xaszin set szin='%1' where az=%2").arg(nVal).arg(rID);
        } else if (mtabla=="Fajta"){
            jsql = QString("update xafajta set fajta='%1' where az=%2").arg(nVal).arg(rID);
        } else if (mtabla=="Faj"){
            jsql = QString("update xafaj set faj='%1' where az=%2").arg(nVal).arg(rID);
        }

        vtrcodes vc;
        vc.itemEdit(jsql);

        TabBetolt();
    }
}


void xEdit01::tabPopUp(){
    QMenu* contextMenu = new QMenu(this);
    QString lab = QString("Módosít");
    QAction *a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(modosit()));

    contextMenu->popup(QCursor::pos());
    contextMenu->exec();
    delete contextMenu;
    contextMenu = 0;
}


void xEdit01::TabBetolt(){
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setHeaderData(0, Qt::Horizontal, mtabla);
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
    model->setQuery(msql);
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,300);
}


xEdit01::~xEdit01(){
    delete ui;
}

void xEdit01::changeEvent(QEvent *e){
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
