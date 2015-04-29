#include <QtSql>


#include "frmtulall.h"
#include "ui_frmtulall.h"


frmTulAll::frmTulAll(QWidget *parent): QDialog(parent), m_ui(new Ui::frmTulAll){
    m_ui->setupUi(this);

    connect(m_ui->pushButton, SIGNAL(clicked()), SLOT(accept()));
    connect(m_ui->pushButton_2, SIGNAL(clicked()), this, SLOT(reject()));

    m_ui->comboBox->addItem("");
    QString sql = "select xttelepules.telepules from xtisz inner join xttelepules on xtisz.telepules=xttelepules.az where aktiv=1 order by xttelepules.telepules";
//    QString sql = "Select telepules From xttelepules order by telepules";
    QSqlQuery query(sql);
    while (query.next()) {
        m_ui->comboBox->addItem(query.value(0).toString());
    }

    query.exec("Select distinct hivonev From yallat");   
    while (query.next()) {
        m_ui->comboBox_3->addItem(query.value(0).toString());
    }

    query.exec("Select faj From xafaj");
    while (query.next()) {
        m_ui->comboBox_4->addItem(query.value(0).toString());
    }
    
    m_ui->comboBox->setCurrentIndex(-1);
    m_ui->comboBox_3->setCurrentIndex(-1);
    m_ui->comboBox_4->setCurrentIndex(-1);

    connect(m_ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(HelyseghezKeres(QString)));
    connect(m_ui->comboBox_4, SIGNAL(currentIndexChanged(QString)), this, SLOT(FajhozKeres(QString)));
    connect(m_ui->comboBox_5, SIGNAL(currentIndexChanged(QString)), this, SLOT(FajtahozKeres(QString)));

}

frmTulAll::~frmTulAll()
{
    delete m_ui;
}

void frmTulAll::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void frmTulAll::HelyseghezKeres(const QString& helyseg)
{

    QString sql = QString("Select distinct xtutca.utca "
        "From xttelepules Inner Join xtisz On xttelepules.az = xtisz.telepules Inner Join ytulajdonos On xtisz.az = ytulajdonos.helyseg Inner Join xtutca On xtutca.az = ytulajdonos.utca "
        "Where xttelepules.telepules = '%1' order by xtutca.utca").arg(helyseg);
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    while (query.next()) {
        m_ui->comboBox_2->addItem(query.value(record.indexOf("utca")).toString());
    }

    sql = QString("Select xtisz.isz "
        "From xtisz Inner Join xttelepules On xttelepules.az = xtisz.telepules "
        "Where xttelepules.telepules = '%1' Order by xtisz.isz limit 1").arg(helyseg);
    query.exec(sql);
    record = query.record();
    query.first();
    m_ui->lineEdit_2->setText(query.value(record.indexOf("isz")).toString());

}


void frmTulAll::FajhozKeres(const QString& faj)
{
    m_ui->comboBox_5->clear();
    m_ui->comboBox_7->clear();

    QString sql = QString("Select distinct xafajta.fajta "
        "From xafaj Inner Join xafajta On xafaj.az = xafajta.faj "
        "Where xafaj.faj = '%1'").arg(faj);
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    while (query.next()) {
        m_ui->comboBox_5->addItem(query.value(record.indexOf("fajta")).toString());
    }

    sql = QString("Select distinct xaivar.ivar "
        "From xafaj Inner Join xafajta On xafaj.az = xafajta.faj Inner Join yallat On xafajta.az = yallat.fajta Inner Join xaivar On xaivar.az = yallat.ivar "
        "Where xafaj.faj = '%1'").arg(faj);
    query.exec(sql);
    record = query.record();
    while (query.next()) {
        m_ui->comboBox_7->addItem(query.value(record.indexOf("ivar")).toString());
    }

    m_ui->comboBox_5->setCurrentIndex(-1);
    m_ui->comboBox_7->setCurrentIndex(-1);
}

void frmTulAll::FajtahozKeres(const QString& fajta)
{
    m_ui->comboBox_6->clear();

    QString sql = QString("Select distinct xaszin.szin "
        "From xafajta Inner Join yallat On xafajta.az = yallat.fajta Inner Join xaszin On xaszin.az = yallat.szin "
        "Where xafajta.fajta = '%1'").arg(fajta);
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    while (query.next()) {
        m_ui->comboBox_6->addItem(query.value(record.indexOf("szin")).toString());
    }

    m_ui->comboBox_6->setCurrentIndex(-1);
}


