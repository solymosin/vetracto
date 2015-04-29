#include <QSqlQueryModel>
#include <QMenu>

#include "frmdoki.h"
#include "ui_frmdoki.h"
#include "xdoki.h"
#include "ui_xdoki.h"

#include "vtrcodes.h"


frmDoki::frmDoki(QWidget *parent): QDialog(parent), ui(new Ui::frmDoki){
    ui->setupUi(this);
    tablabetolto();
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(dokiPopUp()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(accept()));
//    ui->buttonBox->addButton(tr("OK"), QDialogButtonBox::AcceptRole);
//    box->addButton(tr("OK"), QDialogButtonBox::AcceptRole);

//    ui->buttonBox->setStandardButtons(QDialogButtonBox::Ok, QDialogButtonBox::AcceptRole );
//    ui->buttonBox->buttonRole(QDialogButtonBox::AcceptRole);
}


void frmDoki::dokiRec(){
    xDoki dlg(this);
    dlg.setWindowTitle("Új állatorvos rögzítése");

    if( dlg.exec() == QDialog::Accepted ){
        vtrcodes vc;
        QString aktiv = "igen";

        if (dlg.ui->checkBox_2->isChecked()==false){
            aktiv = "nem";
        }
        vc.dokiRec(dlg.ui->lineEdit_3->text(), dlg.ui->lineEdit_4->text(), aktiv);
        tablabetolto();
    }
}

void frmDoki::dokiMod(){
    QModelIndex idx;
    QString id = "";

    idx = ui->tableView->selectionModel()->currentIndex();

    xDoki dlg(this);
    dlg.setWindowTitle("Adatok módosítása");
    dlg.ui->lineEdit_3->setText(ui->tableView->model()->data(idx.sibling(idx.row(),0)).toString());
    dlg.ui->lineEdit_4->setText(ui->tableView->model()->data(idx.sibling(idx.row(),1)).toString());
    if (ui->tableView->model()->data(idx.sibling(idx.row(),2)).toString()=="igen"){
        dlg.ui->checkBox_2->setChecked(true);
    } else {
        dlg.ui->checkBox_2->setChecked(false);
    }
    id = ui->tableView->model()->data(idx.sibling(idx.row(),3)).toString();

    if( dlg.exec() == QDialog::Accepted ){
        vtrcodes vc;
        QString aktiv = "igen";

        if (dlg.ui->checkBox_2->isChecked()==false){
            aktiv = "nem";
        }
        vc.dokiMod(dlg.ui->lineEdit_3->text(), dlg.ui->lineEdit_4->text(), aktiv, id);
        tablabetolto();
    }
}


void frmDoki::dokiPopUp(){
    QMenu* contextMenu = new QMenu(this);
    QString lab = QString("Új állatorvos rögzítése");
    QAction *a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(dokiRec()));
    lab = QString("Adatok módosítása");
    a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(dokiMod()));
    contextMenu->popup(QCursor::pos());
    contextMenu->exec();
    delete contextMenu;
    contextMenu = 0;
}


void frmDoki::tablabetolto(){
    QSqlQueryModel *model1 = new QSqlQueryModel();
    model1->setHeaderData(0, Qt::Horizontal, QObject::tr("Név"));
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Telefon"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Aktív"));
    model1->setHeaderData(4, Qt::Horizontal, QObject::tr("ID"));

    QString sql = QString("select doki, telefon, aktiv, az from xdokik");
    model1->setQuery(sql);
    ui->tableView->setModel(model1);
}



frmDoki::~frmDoki()
{
    delete ui;
}

void frmDoki::changeEvent(QEvent *e)
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
