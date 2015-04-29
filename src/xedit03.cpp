#include "xedit03.h"
#include "ui_xedit03.h"

#include <QtGui>
#include <QAbstractItemModel>
#include <QSqlQuery>

xEdit03::xEdit03(QWidget *parent): QDialog(parent), ui(new Ui::xEdit03){
    ui->setupUi(this);
    QString sql = "select xttelepules.*, xtisz.* from xtisz inner join xttelepules on xtisz.telepules=xttelepules.az order by xttelepules.telepules";
//    QString sql = "Select telepules From xttelepules order by telepules";
    QSqlQuery query(sql);
    while (query.next()) {
        qDebug() << query.value(0).toString();
    }

}

xEdit03::~xEdit03(){
    delete ui;
}
