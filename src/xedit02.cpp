#include <QtGui>
#include <QAbstractItemModel>
#include <QSqlQuery>

#include "xedit02.h"
#include "ui_xedit02.h"
//#include "checkitem.h"


xEdit02::xEdit02(QWidget *parent): QDialog(parent), ui(new Ui::xEdit02){
    ui->setupUi(this);
}

void xEdit02::chI(QString sql){
    model = new QStandardItemModel(0,2);
    QSqlQuery query(sql);
    while (query.next()) {
        item = new QStandardItem(query.value(0).toString());
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        if (query.value(1).toInt()==1){
            item->setData(QVariant(Qt::Checked), Qt::CheckStateRole);
        } else {
            item->setData(QVariant(Qt::Unchecked), Qt::CheckStateRole);
        }        
        item->setData(QVariant(query.value(2).toString()), Qt::AccessibleTextRole);
        model->appendRow(item);
    }
    ui->listView->setModel(model);
    ui->listView->setViewMode(QListView::ListMode);
}


xEdit02::~xEdit02(){
    delete ui;
}


void xEdit02::changeEvent(QEvent *e){
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
