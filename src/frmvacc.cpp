#include <QtSql>
#include <QDate>

#include "frmvacc.h"
#include "ui_frmvacc.h"
#include "frmolt.h"
#include "ui_frmolt.h"
#include "vtrcodes.h"


frmVacc::frmVacc(const QString &id, QWidget *parent) : QDialog(parent), m_ui(new Ui::frmVacc){
    m_ui->setupUi(this);

    connect(m_ui->toolButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_ui->toolButton_2, SIGNAL(clicked()), this, SLOT(frmOltBetolt()));

    connect(m_ui->toolButton_3, SIGNAL(clicked()), this, SLOT(Torol()));

//    connect(m_ui->pushButton, SIGNAL(clicked()), this, SLOT(EbVeszettseg()));

    connect(m_ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(Tab02Unselect()));
    connect(m_ui->tableView_2, SIGNAL(clicked(QModelIndex)), this, SLOT(Tab01Unselect()));

}

frmVacc::~frmVacc()
{
    delete m_ui;
}

void frmVacc::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void frmVacc::Torol()
{
    QModelIndex idx;

    idx = m_ui->tableView->selectionModel()->currentIndex();
    QString vid = m_ui->tableView->model()->data(idx.sibling(idx.row(),4)).toString();

    idx = m_ui->tableView_2->selectionModel()->currentIndex();
    QString fid = m_ui->tableView_2->model()->data(idx.sibling(idx.row(),3)).toString();

    if (fid=="" && vid!=""){
        QString sql = QString("delete from bvakcinazas where az = %1").arg(vid);
        QSqlQuery query(sql);
    }

    if (fid!="" && vid==""){
        QString sql = QString("delete from bfereghajtas where az = %1").arg(fid);
        QSqlQuery query(sql);
    }

    TabBetolt(allat_az);
}


void frmVacc::frmOltBetolt()
{
    frmOlt dlg(this);

    QDate date = QDate::currentDate();

    QString sql = "select oltoanyag from xbvakcinak where aktiv = 1 order by oltoanyag";
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    while (query.next()) {
        dlg.m_ui->comboBox->addItem(query.value(record.indexOf("oltoanyag")).toString());
    }

    sql = "select fereghajto from xbfereghajtok where aktiv = 1 order by fereghajto";
    query.exec(sql);
    record = query.record();
    while (query.next()) {
        dlg.m_ui->comboBox_2->addItem(query.value(record.indexOf("fereghajto")).toString());
    }

    int i = date.year();
    sql = QString("Select max(bvakcinazas.sorszama) as id "
        "From bvakcinazas Inner Join alpha On alpha.az = bvakcinazas.alphaaz Inner Join xdokik On xdokik.az = alpha.allatorvos "
        "Where bvakcinazas.tipus = 1 And xdokik.doki = '%1' And  date(alpha.datum) between '%2-01-01' and '%2-12-31'").arg(doki).arg(i);
    query.exec(sql);
    record = query.record();
    query.first();
    QString id = query.value(record.indexOf("id")).toString();
    bool ok;
    int newid = id.toInt(&ok, 10)+1;

    dlg.m_ui->comboBox->setCurrentIndex(-1);
    dlg.m_ui->comboBox_2->setCurrentIndex(-1);
    dlg.m_ui->lineEdit->setText(QString("%1").arg(newid));
    dlg.m_ui->lineEdit->setVisible(false);
    dlg.m_ui->label_2->setVisible(false);
    dlg.m_ui->dateEdit->setDate(date);


    if( dlg.exec() == QDialog::Accepted )
    {
        vtrcodes vc;
        QString datum = dlg.m_ui->dateEdit->date().toString("yyyy-MM-dd");
        QString alphaID = vc.alphaIDentify(doki, allat_az, datum);
        QString vakcina = dlg.m_ui->comboBox->currentText();
        QString fereghajto = dlg.m_ui->comboBox_2->currentText();

//        m_ui->lineEdit->setText(alphaID);

        if (fereghajto!=""){
            QString fID = vc.fereghajtoIDentify(fereghajto);
            vc.fereghajtasRec(alphaID, fID);
        }

        if (vakcina!=""){
            QString vID = vc.vakcinaIDentify(vakcina);
            int vakcinatipus = 1;
            int sorszam = 0;
            if(dlg.m_ui->checkBox->checkState()==false){
                vakcinatipus = 2;
            }

            if (vakcinatipus == 1){
                sorszam = newid;
            }
            vc.vakcinazasRec(alphaID, vID, vakcinatipus, sorszam);
        }

        TabBetolt(allat_az);
    }
}

void frmVacc::TabBetolt(const QString& id){
    QSqlQueryModel *model1 = new QSqlQueryModel();
    QSqlQueryModel *model2 = new QSqlQueryModel();
    model1->setHeaderData(0, Qt::Horizontal, QObject::tr("Dátum"));
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Oltóanyag"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Sorszám"));
    model1->setHeaderData(3, Qt::Horizontal, QObject::tr("Állatorvos"));
    model1->setHeaderData(4, Qt::Horizontal, QObject::tr("ID"));

    QString sql = QString("Select alpha.datum, xbvakcinak.oltoanyag, bvakcinazas.sorszama, xdokik.doki, bvakcinazas.az "
        "From alpha Inner Join xdokik On xdokik.az = alpha.allatorvos Inner Join bvakcinazas On bvakcinazas.alphaaz = alpha.az Inner Join xbvakcinak On xbvakcinak.az = bvakcinazas.vakcina "
        "Where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(id);
    model1->setQuery(sql);
    m_ui->tableView->setModel(model1);

    model2->setHeaderData(0, Qt::Horizontal, QObject::tr("Dátum"));
    model2->setHeaderData(1, Qt::Horizontal, QObject::tr("Féreghajtó"));
    model2->setHeaderData(2, Qt::Horizontal, QObject::tr("Állatorvos"));
    model2->setHeaderData(3, Qt::Horizontal, QObject::tr("ID"));
    sql = QString("Select alpha.datum, xbfereghajtok.fereghajto, xdokik.doki, bfereghajtas.az "
        "From alpha Inner Join xdokik On xdokik.az = alpha.allatorvos Inner Join bfereghajtas On bfereghajtas.alphaaz = alpha.az Inner Join xbfereghajtok On xbfereghajtok.az = bfereghajtas.fereghajto "
        "where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(id);
    model2->setQuery(sql);
    m_ui->tableView_2->setModel(model2);
}


void frmVacc::Tab01Unselect()
{
    m_ui->tableView->selectionModel()->clear();
}

void frmVacc::Tab02Unselect()
{
    m_ui->tableView_2->selectionModel()->clear();
}


void frmVacc::EbVeszettseg()
{
//    m_ui->lineEdit->setText("");
//
//    QModelIndex idx1, idx2;
//
//    idx1 = m_ui->tableView->selectionModel()->currentIndex();
//    QString vid = m_ui->tableView->model()->data(idx1.sibling(idx1.row(),4)).toString();
//
//    idx2 = m_ui->tableView_2->selectionModel()->currentIndex();
//    QString fid = m_ui->tableView_2->model()->data(idx2.sibling(idx2.row(),3)).toString();
//
//    if (fid=="" & vid!="")
//        m_ui->lineEdit->setText("vakcina");
//
//    if (fid!="" & vid=="")
//        m_ui->lineEdit->setText("féreg");
//
//    if (m_ui->tableView->focusWidget() ==true)
//        m_ui->lineEdit->setText("egyes");
//    m_ui->lineEdit->setText(this->focusPreviousChild()
}

