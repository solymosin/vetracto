#include <QMenu>
#include <QMessageBox>

#include "frmcomm.h"
#include "ui_frmcomm.h"

#include "xcomm.h"
#include "ui_xcomm.h"

#include "vtrcodes.h"

frmComm::frmComm(QWidget *parent): QDialog(parent), ui(new Ui::frmComm){
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(close()));
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(kommPopUp()));
}

void frmComm::kommUj(){
    xComm *dlg = new xComm();
    dlg->setWindowTitle("Új elérhetőség");
    if (dlg->exec() == QDialog::Accepted ){
        vtrcodes vc;
        vc.kommRec(tulajID, dlg->ui->comboBox->currentText(), dlg->ui->lineEdit->text());
        TabBetolt(tulajID);
    }
}

void frmComm::kommMod(){
    xComm *dlg = new xComm();
    dlg->setWindowTitle("Elérhetőség módosítása");

    QModelIndex idx;
    idx = ui->tableView->selectionModel()->currentIndex();
    dlg->ui->lineEdit->setText(ui->tableView->model()->data(idx.sibling(idx.row(),1)).toString());
    dlg->ui->comboBox->setCurrentIndex(dlg->ui->comboBox->findText(ui->tableView->model()->data(idx.sibling(idx.row(),0)).toString(), Qt::MatchExactly));
    QString id = ui->tableView->model()->data(idx.sibling(idx.row(),2)).toString();

    if (dlg->exec() == QDialog::Accepted ){
        vtrcodes vc;
        vc.kommMod(id, dlg->ui->comboBox->currentText(), dlg->ui->lineEdit->text());
        TabBetolt(tulajID);
    }
}

void frmComm::kommTorol(){
    QMessageBox msgBox;
    msgBox.setText("Valóban töröljük az adatokat?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

    QModelIndex idx = ui->tableView->selectionModel()->currentIndex();
    QString id = ui->tableView->model()->data(idx.sibling(idx.row(),2)).toString();
    vtrcodes vc;

    switch (ret) {
        case QMessageBox::Yes:
            vc.kommDel(id);
            TabBetolt(tulajID);
            break;
        default:
          break;
    }
}

void frmComm::kommPopUp(){
    QMenu* contextMenu = new QMenu(this);
    QString lab = QString("Új");
    QAction *a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(kommUj()));

    lab = QString("Módosít");
    a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(kommMod()));

    lab = QString("Töröl");
    a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(kommTorol()));

    contextMenu->popup(QCursor::pos());
    contextMenu->exec();
    delete contextMenu;
    contextMenu = 0;
}


void frmComm::TabBetolt(const QString& id){
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Eszköz"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cím"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID"));
    QString sql = QString("select eszkoz, cim, az from ykommunikacio where tulajdonos=%1 order by eszkoz").arg(id);
    model->setQuery(sql);
    ui->tableView->setModel(model);

    ui->tableView->setColumnWidth(1,300);
}


frmComm::~frmComm(){
    delete ui;
}

void frmComm::changeEvent(QEvent *e)
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
