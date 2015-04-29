#include <QtSql>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSignalMapper>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextTableCell>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QHeaderView>
#include <QDesktopServices>

#include "frmmain.h"
#include "ui_frmmain.h"
#include "frmkezel.h"
#include "ui_frmkezel.h"
#include "frmsurg.h"
#include "ui_frmsurg.h"
#include "frmtulall.h"
#include "ui_frmtulall.h"
#include "frmvacc.h"
#include "ui_frmvacc.h"
#include "xabout.h"
#include "ui_xabout.h"
#include "frmquery.h"
#include "ui_frmquery.h"
#include "frmdoki.h"
#include "ui_frmdoki.h"
#include "frmlabor.h"
#include "ui_frmlabor.h"
#include "frmmegj.h"
#include "ui_frmmegj.h"
//#include "frmsettings.h"
//#include "ui_frmsettings.h"
//#include "frmnorberg.h"
//#include "ui_frmnorberg.h"
#include "frmimporter.h"
#include "ui_frmimporter.h"
#include "settingwizard.h"
#include "ui_settingwizard.h"
#include "xarchiv.h"
#include "ui_xarchiv.h"
#include "frmcomm.h"
#include "ui_frmcomm.h"
#include "xcomm.h"
#include "ui_xcomm.h"
//#include "frmtpa.h"
//#include "ui_frmtpa.h"
//#include "frmkozostangens.h"
//#include "ui_frmkozostangens.h"

#include "xedit01.h"
#include "ui_xedit01.h"
#include "xedit02.h"
#include "ui_xedit02.h"
#include "xedit03.h"
#include "ui_xedit03.h"

//#include "teszt.h"
//#include "ui_teszt.h"

#include "vtrcodes.h"
#include "textedit.h"
//#include "proba.h"
//#include "ui_proba.h"



frmMain::frmMain(QWidget *parent): QMainWindow(parent), ui(new Ui::frmMainClass){
    ui->setupUi(this);

    QApplication::setApplicationVersion("1.098");

    /*kozepre teszi a nyito kepernyot*/
    QRect available_geom = QDesktopWidget().availableGeometry();
    QRect current_geom =  frameGeometry();

    setGeometry(available_geom.width() / 2 - current_geom.width() / 2,
        available_geom.height() / 2 - current_geom.height() / 2,
        current_geom.width(),
        current_geom.height());
    /********************************/

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "vetracto", "qvtr");
    settings.beginGroup("vtr");
    settings.beginGroup("program");
    if(settings.contains("kezelnapok")){
        kezelnapok = settings.value("kezelnapok").toInt();
    } else {
        kezelnapok = 10;
    }
    settings.endGroup();
    settings.endGroup();


//    connect(ui->pushButton, SIGNAL(clicked()), this , SLOT(kiir()));
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(kiir()));
    connect(ui->actionKezel_s, SIGNAL(triggered()), this, SLOT(frmKezelBetolt()));
    connect(ui->actionKil_p, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionJ_tulajdonos_s_llat_r_gz_t_se, SIGNAL(triggered()), this, SLOT(ujTulajAllat()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(AllatBetoltoTrsz()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(TrszDel(QString)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(TulajAllatai(QString)));
    connect(ui->actionVakcin_z_s, SIGNAL(triggered()), this, SLOT(frmVaccBetolt()));
    connect(ui->actionJelent_sek, SIGNAL(triggered()), this, SLOT(EditorNyit()));
    connect(ui->actionSeb_szet, SIGNAL(triggered()), this, SLOT(SurgBetolt()));
    connect(ui->actionN_vjegy, SIGNAL(triggered()), this, SLOT(About()));
    connect(ui->action_j_llat_r_gz_t_se_a_tulajdonoshoz, SIGNAL(triggered()), this, SLOT(TulajhozAllat()));
    connect(ui->actionAdatok_m_dos_t_sa, SIGNAL(triggered()), this, SLOT(TulajAllatmodosit()));
    connect(ui->actionLista, SIGNAL(triggered()), this, SLOT(QueryList()));
    connect(ui->action_llatorvosok, SIGNAL(triggered()), this, SLOT(frmDokikBetolt()));
    connect(ui->treeWidget_2, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(elozmenyFabol()));
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(idTulAllbol()));
    connect(ui->actionLabor, SIGNAL(triggered()), this, SLOT(laborLap()));
    connect(ui->groupBox, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(tulajPopUp()));
    connect(ui->groupBox_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(allatPopUp()));
    connect(ui->actionBe_ll_t_sok, SIGNAL(triggered()), this, SLOT(vtrSettings()));
    connect(ui->actionNorberger, SIGNAL(triggered()), this, SLOT(norberger()));
    connect(ui->actionTPA, SIGNAL(triggered()), this, SLOT(tpa()));
    connect(ui->actionK_z_s_tangens, SIGNAL(triggered()), this, SLOT(comtan()));
    connect(ui->actionImport_MySQL, SIGNAL(triggered()), this, SLOT(MySQLimporter()));
    connect(ui->actionAdatb_zis, SIGNAL(triggered()), this, SLOT(dbCleaner()));
    connect(ui->actionArchiv_l_s, SIGNAL(triggered()), this, SLOT(archival()));
//    connect(ui->actionTelep_l_s, SIGNAL(triggered()), this, SLOT(telepKorr()));


    connect(ui->menuKarbantart_s, SIGNAL(triggered(QAction*)), this, SLOT(dataKorr1(QAction*)));
//    connect(ui->actionIvar, SIGNAL(triggered()), this, SLOT(dataKorr1()));

    ui->actionImport_MySQL->setEnabled(true);
    //ui->actionNorberger->setVisible(false);

    ui->mainToolBar->addAction(ui->actionKil_p);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionJ_tulajdonos_s_llat_r_gz_t_se);
    ui->mainToolBar->addAction(ui->actionAdatok_m_dos_t_sa);
    ui->mainToolBar->addAction(ui->action_j_llat_r_gz_t_se_a_tulajdonoshoz);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionVakcin_z_s);
    ui->mainToolBar->addAction(ui->actionKezel_s);
    ui->mainToolBar->addAction(ui->actionSeb_szet);
    ui->mainToolBar->addAction(ui->actionLabor);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionLista);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString("%1/vtrdb.db").arg(QApplication::applicationDirPath()));

    db.open();
    vtrcodes vc;
    vc.dbkontroll();
    db.close();

//    qDebug() << db.driver()->hasFeature(QSqlDriver::BLOB);
//    http://lists.trolltech.com/pipermail/qt-interest/2009-May/006422.html

    betolt01();
}


void frmMain::allatDel(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("Figyelmezzünk!");
    msgBox.setInformativeText("Valóban töröljük az aktuális egyedet?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes){
        db.open();
        db.transaction();
        vtrcodes vc;
        vc.delAllat(ui->lineEdit->text());
        db.commit();
        db.close();
        ui->lineEdit->setText("");
    }
}

void frmMain::telepKorr(){
    db.open();
    xEdit03 *dlg = new xEdit03();
    if (dlg->exec() == QDialog::Rejected ){

    }
    db.close();
}



void frmMain::dataKorr1(QAction *action){
    QString kulcs = action->text();

    if (kulcs=="Ivar" || kulcs=="Szín" || kulcs=="Fajta" || kulcs=="Faj"){
        db.open();
        xEdit01 *dlg = new xEdit01();

        if (kulcs=="Ivar"){
            dlg->setWindowTitle("Ivar adatok javítása");
            dlg->msql = "select ivar, az from xaivar order by ivar";
            dlg->csql = "select distinct ivar from xaivar order by ivar";
            dlg->mtabla = "Ivar";
        } else if (kulcs=="Szín"){
            dlg->setWindowTitle("Szín adatok javítása");
            dlg->msql = "select szin, az from xaszin order by szin";
            dlg->csql = "select distinct szin from xaszin order by szin";
            dlg->mtabla = "Szín";
        } else if (kulcs=="Fajta"){
            dlg->setWindowTitle("Fajta adatok javítása");
            dlg->msql = "select fajta, az from xafajta order by fajta";
            dlg->csql = "select distinct fajta from xafajta order by fajta";
            dlg->mtabla = "Fajta";
        } else if (kulcs=="Faj"){
            dlg->setWindowTitle("Faj adatok javítása");
            dlg->msql = "select faj, az from xafaj order by faj";
            dlg->csql = "select distinct faj from xafaj order by faj";
            dlg->mtabla = "Faj";
        }

        dlg->TabBetolt();

        if (dlg->exec() == QDialog::Rejected ){
            QApplication::setOverrideCursor( Qt::WaitCursor );

            db.transaction();
            vtrcodes vc;
            if (kulcs=="Ivar"){
                vc.ivarCleaner();
            } else if (kulcs=="Szín"){
                vc.szinCleaner();
            } else if (kulcs=="Fajta"){
                vc.fajtaCleaner();
            } else if (kulcs=="Faj"){
                vc.fajCleaner();
            }

            db.commit();
            QApplication::restoreOverrideCursor();
        }
        db.close();
    } else if (kulcs=="Vakcina" || kulcs=="Féreghajtó" || kulcs=="Település"){
        db.open();
        xEdit02 *dlg = new xEdit02();
        QString sqlu = "";
        QSqlQuery query;

        if (kulcs=="Vakcina"){
            dlg->setWindowTitle("Aktuális vakcinák megadása");
            dlg->chI("select oltoanyag, aktiv, az from xbvakcinak order by oltoanyag");
            sqlu = "update xbvakcinak set aktiv=%1 where az=%2";
        } else if (kulcs=="Féreghajtó"){
            dlg->setWindowTitle("Aktuális féreghajtók megadása");
            dlg->chI("select fereghajto, aktiv, az from xbfereghajtok order by fereghajto");
            sqlu = "update xbfereghajtok set aktiv=%1 where az=%2";
        } else if (kulcs=="Település"){
            dlg->setWindowTitle("Aktuális települések megadása");
            dlg->chI("select telepules, aktiv, az from xttelepules order by telepules");
            sqlu = "update xttelepules set aktiv=%1 where az=%2";
        }

        if (dlg->exec() == QDialog::Accepted ){
            QApplication::setOverrideCursor( Qt::WaitCursor );
            db.transaction();
            for (int i=0; i!=dlg->model->rowCount(); i++){
                int ch = 0;
                if (dlg->model->itemFromIndex(dlg->model->index(i,0))->checkState()==2){
                    ch = 1;
                }
                QString az = dlg->model->itemFromIndex(dlg->model->index(i,0))->accessibleText();
                query.exec(sqlu.arg(ch).arg(az));
            }
            db.commit();
            QApplication::restoreOverrideCursor();
        }
        db.close();
    }
}


void frmMain::tulajKomm(){
//    db.open();

    frmComm *dlg = new frmComm();
    dlg->setWindowTitle("Tulajdonos elérhetősége");

    QString sql = QString("select tulajdonos from yallat where torzsszam=%1").arg(ui->lineEdit->text());
    QSqlQuery query(sql);
    query.first();
    dlg->tulajID = query.value(0).toString();
    dlg->TabBetolt(query.value(0).toString());

    if (dlg->exec() == QDialog::Accepted ){

    }

    db.close();
}


void frmMain::archival(){
    xArchiv *dlg = new xArchiv();
    dlg->setWindowTitle("Archiválás");

    if (dlg->exec() == QDialog::Accepted ){
        QApplication::setOverrideCursor( Qt::WaitCursor );
        vtrcodes vc;
        vc.archivalMind(dlg->ui->lineEdit->text());
        QApplication::restoreOverrideCursor();
    }
}

void frmMain::dbCleaner(){
    QApplication::setOverrideCursor( Qt::WaitCursor );
    db.open();
    vtrcodes vc;
    vc.dbclean();
    db.close();
    QApplication::restoreOverrideCursor();
}


void frmMain::MySQLimporter(){
    frmImporter *dlg = new frmImporter();
    dlg->setWindowTitle("MySQL trafo");

    if (dlg->exec() == QDialog::Accepted ){

    }
}

void frmMain::tpa(){
//    frmTPA *dlg = new frmTPA();
//    dlg->setWindowTitle("TPA");

//    if (dlg->exec() == QDialog::Accepted ){

//    }
}

void frmMain::comtan(){
//    frmKozosTangens *dlg = new frmKozosTangens();
//    dlg->setWindowTitle("Közös tangens");
//
//    if (dlg->exec() == QDialog::Accepted ){
//
//    }
}

void frmMain::norberger(){
//    frmNorberg *dlg = new frmNorberg();
//    dlg->setWindowTitle("Norberger");

//    if (dlg->exec() == QDialog::Accepted ){

//    }
}


void frmMain::vtrSettings(){
    settingWizard *dlg = new settingWizard();

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "vetracto", "qvtr");

    settings.beginGroup("vtr");
    settings.beginGroup("rendelo");
    QString kulcs = "neve";
    if(settings.contains(kulcs)){
        dlg->ui->lineEdit->setText(settings.value(kulcs).toString());
    }
    kulcs = "cime";
    if(settings.contains(kulcs)){
        dlg->ui->lineEdit_2->setText(settings.value(kulcs).toString());
    }
    kulcs = "www";
    if(settings.contains(kulcs)){
        dlg->ui->lineEdit_3->setText(settings.value(kulcs).toString());
    }
    settings.endGroup();
    settings.beginGroup("program");
    kulcs = "kezelnapok";
    if(settings.contains(kulcs)){
        dlg->ui->spinBox->setValue(settings.value(kulcs).toInt());
    } else {
        dlg->ui->spinBox->setValue(10);
    }
    settings.endGroup();
    settings.endGroup();

    if (dlg->exec() == QDialog::Accepted ){
        settings.beginGroup("vtr");
        settings.beginGroup("rendelo");
        settings.setValue("neve", dlg->ui->lineEdit->text());
        settings.setValue("cime", dlg->ui->lineEdit_2->text());
        settings.setValue("www",  dlg->ui->lineEdit_3->text());
        settings.endGroup();
        settings.beginGroup("program");
        settings.setValue("kezelnapok", dlg->ui->spinBox->value());
        settings.endGroup();
        settings.endGroup();

        kezelnapok = dlg->ui->spinBox->value();
        betolt01();
    }
}


void frmMain::tulajMegjegyz(){
    if(ui->lineEdit->text()==0){
        return;
    }

    frmMegj dlg(this);
    dlg.setWindowTitle("Megjegyzések a tulajdonoshoz");

    QString sql = QString("select tulajdonos from yallat where torzsszam=%1").arg(ui->lineEdit->text());
    QSqlQuery query(sql);
    query.first();
    QString tulid = query.value(0).toString();

    sql = QString("select megjegyzes from ytmegjegyzes where tulajszam=%1").arg(tulid);
    query.exec(sql);
    query.first();
    dlg.ui->plainTextEdit->setPlainText(query.value(0).toString());

    if(dlg.exec()==QDialog::Accepted){
        db.transaction();
        vtrcodes vc;
        vc.tulajMegjegyzRec(tulid, dlg.ui->plainTextEdit->toPlainText());
        db.commit();
    }
    db.close();
}

void frmMain::tulajPopUp(){
    QMenu* contextMenu = new QMenu(this);
    QString lab = QString("Megjegyzés");
    QAction *a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(tulajMegjegyz()));

    lab = QString("Elérhetőség");
    a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(tulajKomm()));

    lab = QString("E-mail küldése");
    a = contextMenu->addAction(lab);
    a->setDisabled(true);
    connect(a, SIGNAL(triggered()), this, SLOT(sendEmail()));

    db.open();

    QString sql = QString("select tulajdonos from yallat where torzsszam=%1").arg(ui->lineEdit->text());
    QSqlQuery query(sql);
    query.first();
    QString tulid = query.value(0).toString();

    sql = QString("select count(cim) vane from ykommunikacio where tulajdonos=%1 and eszkoz='E-mail'").arg(tulid);
    query.exec(sql);
    query.first();
    QString van = query.value(0).toString();

    if (van!="0"){
        a->setEnabled(true);
    }

//    db.close();

    contextMenu->popup(QCursor::pos());
    contextMenu->exec();
    delete contextMenu;
    contextMenu = 0;
}

void frmMain::sendEmail(){
    QApplication::setOverrideCursor( Qt::WaitCursor );
    if(ui->lineEdit->text()==0){
        return;
    }

    db.open();

    QString sql = QString("select tulajdonos from yallat where torzsszam=%1").arg(ui->lineEdit->text());
    QSqlQuery query(sql);
    query.first();
    QString tulid = query.value(0).toString();

    sql = QString("select cim from ykommunikacio where tulajdonos=%1 and eszkoz='E-mail'").arg(tulid);
    query.exec(sql);
    query.first();
    QString cim = query.value(0).toString();
    QString email = QString("mailto:%1").arg(cim);
    QUrl url = QUrl(email);
    QDesktopServices::openUrl(url);

    db.close();
    QApplication::restoreOverrideCursor();
}

void frmMain::allatMegjegyz(){
    if(ui->lineEdit->text()==0){
        return;
    }

    db.open();
    frmMegj dlg(this);
    dlg.setWindowTitle("Megjegyzések az állathoz");

    QString sql = QString("select megjegyzes from yamegjegyzes where torzsszam=%1").arg(ui->lineEdit->text());
    QSqlQuery query(sql);
    query.first();
    dlg.ui->plainTextEdit->setPlainText(query.value(0).toString());

    if(dlg.exec()==QDialog::Accepted){
        vtrcodes vc;
        vc.allatMegjegyzRec(ui->lineEdit->text(), dlg.ui->plainTextEdit->toPlainText());
    }

    db.close();
}

void frmMain::allatPopUp(){
    QMenu* contextMenu = new QMenu(this);
    QString lab = QString("Megjegyzés");
    QAction *a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(allatMegjegyz()));

    contextMenu->addSeparator();
    lab = QString("Állat törlése");
    a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(allatDel()));

    contextMenu->popup(QCursor::pos());
    contextMenu->exec();
    delete contextMenu;
    contextMenu = 0;
}



void frmMain::laborLap(){
    if(kontroll()!=0){
        return;
    }

    db.open();
    frmLabor dlg(this);
    dlg.setWindowTitle("Laborvizsgálatok");

    QStringList cimkek;
    cimkek << "Típus" << "Paraméter" << "Mértékegység" << "Kutya" << "Macska" << "id";
    dlg.ui->treeWidget->setColumnCount(5);
    dlg.ui->treeWidget->setHeaderLabels(cimkek);

    QTreeWidgetItem *bio = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Biokémia")));
    QString sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'Biokémia' order by parameter";
    QSqlQuery query(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        bio->addChild(new QTreeWidgetItem(sor));
    }

    QTreeWidgetItem *ver = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Vérkép")));
    sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'Vérkép' order by parameter";
    query.exec(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        ver->addChild(new QTreeWidgetItem(sor));
    }

    QTreeWidgetItem *belsar = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Bélsár")));
    sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'bélsár vizsgálat' order by parameter";
    query.exec(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        belsar->addChild(new QTreeWidgetItem(sor));
    }

    QTreeWidgetItem *borkaparek = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Bőrkaparék")));
    sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'bőrkaparék vizsgálat' order by parameter";
    query.exec(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        borkaparek->addChild(new QTreeWidgetItem(sor));
    }

    QTreeWidgetItem *szerologia = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Szerológia")));
    sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'szerológia' order by parameter";
    query.exec(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        szerologia->addChild(new QTreeWidgetItem(sor));
    }

    QTreeWidgetItem *testuri = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Testűri folyadék")));
    sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'testűri folyadék vizsgálata' order by parameter";
    query.exec(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        testuri->addChild(new QTreeWidgetItem(sor));
    }

    QTreeWidgetItem *vizelet = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Vizelet")));
    sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'vizelet vizsgálat' order by parameter";
    query.exec(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        vizelet->addChild(new QTreeWidgetItem(sor));
    }

    dlg.ui->dateEdit->setDate(QDate::currentDate());
    dlg.trsz = ui->lineEdit->text();
    dlg.doki = ui->comboBox_3->currentText();
    dlg.ui->comboBox_2->addItem("");
    sql = QString("Select distinct alpha.datum "
        "From alpha Inner Join blabor On alpha.az = blabor.alphaaz "
        "Where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(ui->lineEdit->text());
    query.exec(sql);
    while (query.next()) {
        QString datum = query.value(0).toString();
        dlg.ui->comboBox_2->addItem(datum);
    }

    dlg.betolt("", "");

    if(dlg.exec()==QDialog::Accepted){
//        for (int row=0; row!=dlg.ui->tableView->model()->rowCount(); row++){
//            QString val = QString("%1;%2;%3")
//                .arg(frm->model->itemData(frm->model->index(row,0)).value(0).toString())
//                .arg(frm->model->itemData(frm->model->index(row,1)).value(0).toString())
//                .arg(frm->model->itemData(frm->model->index(row,2)).value(0).toString());
//        }
    }
    db.close();
}



void frmMain::laborLap(QString datum){
    if(kontroll()!=0){
        return;
    }

    db.open();
    frmLabor dlg(this);
    dlg.setWindowTitle("Laborvizsgálatok");

    QStringList cimkek;
    cimkek << "Típus" << "Paraméter" << "Mértékegység" << "Kutya" << "Macska" << "id";
    dlg.ui->treeWidget->setColumnCount(5);
    dlg.ui->treeWidget->setHeaderLabels(cimkek);

    QTreeWidgetItem *bio = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Biokémia")));
    QString sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'Biokémia' order by parameter";
    QSqlQuery query(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        bio->addChild(new QTreeWidgetItem(sor));
    }

    QTreeWidgetItem *ver = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Vérkép")));
    sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'Vérkép' order by parameter";
    query.exec(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        ver->addChild(new QTreeWidgetItem(sor));
    }

    QTreeWidgetItem *belsar = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Bélsár")));
    sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'bélsár vizsgálat' order by parameter";
    query.exec(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        belsar->addChild(new QTreeWidgetItem(sor));
    }

    QTreeWidgetItem *borkaparek = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Bőrkaparék")));
    sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'bőrkaparék vizsgálat' order by parameter";
    query.exec(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        borkaparek->addChild(new QTreeWidgetItem(sor));
    }

    QTreeWidgetItem *szerologia = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Szerológia")));
    sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'szerológia' order by parameter";
    query.exec(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        szerologia->addChild(new QTreeWidgetItem(sor));
    }

    QTreeWidgetItem *testuri = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Testűri folyadék")));
    sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'testűri folyadék vizsgálata' order by parameter";
    query.exec(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        testuri->addChild(new QTreeWidgetItem(sor));
    }

    QTreeWidgetItem *vizelet = new QTreeWidgetItem(dlg.ui->treeWidget, QStringList(QObject::tr("Vizelet")));
    sql = "select parameter, mertekegyseg, kutya, macska, az from xblabor where csoport = 'vizelet vizsgálat' order by parameter";
    query.exec(sql);
    while (query.next()) {
        QStringList sor;
        sor << "" << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        vizelet->addChild(new QTreeWidgetItem(sor));
    }


    dlg.ui->dateEdit->setDate(QDate::currentDate());
    dlg.trsz = ui->lineEdit->text();
    dlg.doki = ui->comboBox_3->currentText();
    dlg.ui->comboBox_2->addItem("");
    sql = QString("Select distinct alpha.datum "
        "From alpha Inner Join blabor On alpha.az = blabor.alphaaz "
        "Where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(ui->lineEdit->text());
    query.exec(sql);
    while (query.next()) {
        dlg.ui->comboBox_2->addItem(query.value(0).toString());
    }

    dlg.betolt(ui->lineEdit->text(), datum);
    dlg.ui->comboBox_2->setCurrentIndex(dlg.ui->comboBox_2->findText(datum, Qt::MatchExactly));

    if(dlg.exec()==QDialog::Accepted){

    }
    db.close();
}


void frmMain::idTulAllbol(){
    disconnect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(AllatBetoltoTrsz()));
    disconnect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(TrszDel(QString)));
    if(ui->comboBox_2->currentText()!=""){
        db.open();

        QString sql = QString("Select min(yallat.torzsszam) "
            "From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos "
            "where ytulajdonos.nev = '%1' and yallat.hivonev = '%2' and yallat.torzsszam<9000000")
                .arg(ui->comboBox->currentText())
                .arg(ui->comboBox_2->currentText());
        QSqlQuery query(sql);
        query.first();
        ui->lineEdit->setText(query.value(0).toString());

        db.close();

        AllatBetoltoC(ui->lineEdit->text());
        ElozmenyBetolto(ui->lineEdit->text());
    } else {
        UrlapTorloB();
        ui->lineEdit->setText("");
    }
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(AllatBetoltoTrsz()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(TrszDel(QString)));
}


void frmMain::elozmenyFabol(){
    int i = ui->treeWidget_2->selectedItems().count();

    if (i>0)
    {
        QString s = ui->treeWidget_2->currentItem()->text(0);
        if (s != "Kezelések" && s!="Műtétek" && s!="Laborvizsgálatok" && s!="Csatolmányok" && s!="Oltások"){
            if (ui->treeWidget_2->currentItem()->parent()->text(0)=="Kezelések"){
                frmKezelBetolt(s);
            }

            if (ui->treeWidget_2->currentItem()->parent()->text(0)=="Műtétek"){
                SurgBetolt(s);
            }

            if (ui->treeWidget_2->currentItem()->parent()->text(0)=="Laborvizsgálatok"){
                laborLap(s);
            }

            if (ui->treeWidget_2->currentItem()->parent()->text(0)=="Csatolmányok"){
                QApplication::setOverrideCursor( Qt::WaitCursor );

                vtrcodes vc;
                QString datum = s.split(": ")[0];
                QString lab = s.split(": ")[1];

                db.open();
                vc.attachedShow(datum, lab, ui->lineEdit->text());
                db.close();

                QApplication::restoreOverrideCursor();
            }
        }
    }
}


void frmMain::frmDokikBetolt(){
    db.open();
    frmDoki dlg(this);

    if(dlg.exec()==QDialog::Accepted){
        ui->comboBox_3->clear();

        QSqlQuery query("Select doki from xdokik where aktiv='igen' Order By doki");
        QSqlRecord record = query.record();
        while (query.next()) {
            QString doki = query.value(0).toString();
            ui->comboBox_3->addItem(doki);
        }
        ui->comboBox_3->setCurrentIndex(-1);
    }

    db.close();

}


void frmMain::QueryList(){
    db.open();
    frmQuery dlg(this);

    dlg.ui->lineEdit->setText(QString("%1/reports").arg(QApplication::applicationDirPath()));

//    QSqlQuery query("Select doki from xdokik Order By doki");
//    QSqlRecord record = query.record();
//    while (query.next()) {
//        dlg.ui->comboBox->addItem(query.value(0).toString());
//    }

    if( dlg.exec() == QDialog::Accepted ){
        if(dlg.ui->tabWidget->currentIndex()==0){
//            this->setWindowTitle("Veszettsďż˝g");
            QApplication::setOverrideCursor( Qt::WaitCursor );
            db.open();
            vtrcodes vc;
            vc.RabiesReport(dlg.ui->dateEdit->date().toString("yyyy-MM-dd"),dlg.ui->dateEdit_2->date().toString("yyyy-MM-dd"),dlg.ui->lineEdit->text());
            db.close();
            QApplication::restoreOverrideCursor();
//            sd = "2004-05-01";
//            ed = "2004-12-31";
        } else {
//            this->setWindowTitle("Lejďż˝rďż˝k");
        }
    }

    db.close();
}




int frmMain::kontroll(){
    int res = 0;
    if(ui->comboBox_3->currentText()=="")
    {
        QMessageBox::information(0,
            tr("Figyelmezzünk!"),
            tr("Meg kell adni az állatorvos nevét"),
            QMessageBox::Ok);
        res=1;
    }

    if(ui->lineEdit->text()=="")
    {
        QMessageBox::information(0,
            tr("Figyelmezzünk!"),
            tr("Meg kell adni az állat azonosítóját"),
            QMessageBox::Ok);
        res=1;
    }
    return res;
}




void frmMain::frmKezelBetolt(){
    if(kontroll()!=0){
        return;
    }

    QDate date = QDate::currentDate();

    db.open();
    frmKezel dlg(this);
    dlg.typ = "new";
    dlg.doki = ui->comboBox_3->currentText();
    dlg.allat_az = ui->lineEdit->text();
    dlg.m_ui->radioButton->setChecked(true);
    dlg.ListaBetolto();
    dlg.m_ui->dateEdit->setDate(date);

    QString sql = QString("Select alpha.datum "
        "From alpha Inner Join bgyogykezeles On alpha.az = bgyogykezeles.alphaaz "
        "Where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(ui->lineEdit->text());
    QSqlQuery query(sql);
    dlg.m_ui->comboBox->addItem("");
    while (query.next()) {
        dlg.m_ui->comboBox->addItem(query.value(0).toString());
    }

    dlg.attachlist("", ui->lineEdit->text(), "kezel");

    if( dlg.exec() == QDialog::Accepted ){
        db.transaction();

        QString datum ="", alphaID="";
        vtrcodes vc;
        if (dlg.typ=="new"){
            datum = dlg.m_ui->dateEdit->date().toString("yyyy-MM-dd");
            alphaID = vc.alphaIDentify(ui->comboBox_3->currentText(), ui->lineEdit->text(), datum);
            vc.KezelRec(alphaID, dlg.m_ui->textEdit->toPlainText(), dlg.m_ui->textEdit_2->toPlainText(), dlg.m_ui->textEdit_3->toPlainText(), dlg.m_ui->textEdit_4->toPlainText(), dlg.m_ui->textEdit_5->toPlainText());
        } else if (dlg.typ=="edit"){
            datum = dlg.m_ui->comboBox->currentText();
            alphaID = vc.alphaIDentify(ui->comboBox_3->currentText(), ui->lineEdit->text(), datum);
            vc.KezelMod(alphaID, dlg.m_ui->textEdit->toPlainText(), dlg.m_ui->textEdit_2->toPlainText(), dlg.m_ui->textEdit_3->toPlainText(), dlg.m_ui->textEdit_4->toPlainText(), dlg.m_ui->textEdit_5->toPlainText());
            if (dlg.m_ui->dateEdit->date().toString("yyyy-MM-dd")!=datum){
                //
            }
        }
        db.commit();
    }
    db.close();

    QString allatID = ui->lineEdit->text();
    ElozmenyBetolto(allatID);
}

void frmMain::frmKezelBetolt(QString idopont){
    if(kontroll()!=0){
        return;
    }

    QDate date = QDate::currentDate();

    db.open();
    frmKezel dlg(this);
    dlg.typ = "new";
    dlg.doki = ui->comboBox_3->currentText();
    dlg.allat_az = ui->lineEdit->text();
    dlg.m_ui->radioButton->setChecked(true);
    dlg.ListaBetolto();
    dlg.m_ui->dateEdit->setDate(date);

    QString sql = QString("Select alpha.datum "
        "From alpha Inner Join bgyogykezeles On alpha.az = bgyogykezeles.alphaaz "
        "Where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(ui->lineEdit->text());
    QSqlQuery query(sql);
    dlg.m_ui->comboBox->addItem("");
    while (query.next()) {
        dlg.m_ui->comboBox->addItem(query.value(0).toString());
    }
    dlg.m_ui->comboBox->setCurrentIndex(dlg.m_ui->comboBox->findText(idopont, Qt::MatchExactly));

    dlg.attachlist(idopont, ui->lineEdit->text(), "kezel");

    if( dlg.exec() == QDialog::Accepted ){
        db.transaction();

        QString datum ="", alphaID="";
        vtrcodes vc;
        if (dlg.typ=="new"){
            datum = dlg.m_ui->dateEdit->date().toString("yyyy-MM-dd");
            alphaID = vc.alphaIDentify(ui->comboBox_3->currentText(), ui->lineEdit->text(), datum);
            vc.KezelRec(alphaID, dlg.m_ui->textEdit->toPlainText(), dlg.m_ui->textEdit_2->toPlainText(), dlg.m_ui->textEdit_3->toPlainText(), dlg.m_ui->textEdit_4->toPlainText(), dlg.m_ui->textEdit_5->toPlainText());
        } else if (dlg.typ=="edit"){
            datum = dlg.m_ui->comboBox->currentText();
            alphaID = vc.alphaIDentify(ui->comboBox_3->currentText(), ui->lineEdit->text(), datum);
            vc.KezelMod(alphaID, dlg.m_ui->textEdit->toPlainText(), dlg.m_ui->textEdit_2->toPlainText(), dlg.m_ui->textEdit_3->toPlainText(), dlg.m_ui->textEdit_4->toPlainText(), dlg.m_ui->textEdit_5->toPlainText());
            if (dlg.m_ui->dateEdit->date().toString("yyyy-MM-dd")!=datum){
                //
            }
        }
        db.commit();

//        QString allatID = ui->lineEdit->text();
//        ElozmenyBetolto(allatID);
    }
    db.close();
}


void frmMain::SurgBetolt(){
    if(kontroll()!=0){
        return;
    }

    QDate date = QDate::currentDate();

    db.open();
    frmSurg dlg(this);
    dlg.typ = "new";
    dlg.doki = ui->comboBox_3->currentText();
    dlg.allat_az = ui->lineEdit->text();
    dlg.m_ui->radioButton->setChecked(true);
    dlg.ListaBetolto();
    dlg.m_ui->dateEdit->setDate(date);

    QString sql = QString("Select alpha.datum "
        "From alpha Inner Join bmutet On alpha.az = bmutet.alphaaz "
        "Where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(ui->lineEdit->text());
    QSqlQuery query(sql);
    dlg.m_ui->comboBox->addItem("");
    while (query.next()) {
        dlg.m_ui->comboBox->addItem(query.value(0).toString());
    }
//
    if( dlg.exec() == QDialog::Accepted ){
        QString datum ="", alphaID="";
        vtrcodes vc;
        if (dlg.typ=="new"){
            datum = dlg.m_ui->dateEdit->date().toString("yyyy-MM-dd");
            alphaID = vc.alphaIDentify(ui->comboBox_3->currentText(), ui->lineEdit->text(), datum);
            vc.SurgRec(alphaID, dlg.m_ui->textEdit->toPlainText(), dlg.m_ui->textEdit_2->toPlainText(), dlg.m_ui->textEdit_3->toPlainText(), dlg.m_ui->textEdit_4->toPlainText(), dlg.m_ui->textEdit_5->toPlainText());
        } else if (dlg.typ=="edit"){
            datum = dlg.m_ui->comboBox->currentText();
            alphaID = vc.alphaIDentify(ui->comboBox_3->currentText(), ui->lineEdit->text(), datum);
            vc.SurgMod(alphaID, dlg.m_ui->textEdit->toPlainText(), dlg.m_ui->textEdit_2->toPlainText(), dlg.m_ui->textEdit_3->toPlainText(), dlg.m_ui->textEdit_4->toPlainText(), dlg.m_ui->textEdit_5->toPlainText());
            if (dlg.m_ui->dateEdit->date().toString("yyyy-MM-dd")!=datum){
                //ha megvďż˝ltoztatja a kezelďż˝s dďż˝tumďż˝t is
            }
        }
    }
    db.close();

    QString allatID = ui->lineEdit->text();
    ElozmenyBetolto(allatID);
}

void frmMain::SurgBetolt(QString idopont){
    if(kontroll()!=0){
        return;
    }

    QDate date = QDate::currentDate();

    db.open();
    frmSurg dlg(this);
    dlg.typ = "new";
    dlg.doki = ui->comboBox_3->currentText();
    dlg.allat_az = ui->lineEdit->text();
    dlg.m_ui->radioButton->setChecked(true);
    dlg.ListaBetolto();
    dlg.m_ui->dateEdit->setDate(date);

    QString sql = QString("Select alpha.datum "
        "From alpha Inner Join bmutet On alpha.az = bmutet.alphaaz "
        "Where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(ui->lineEdit->text());
    QSqlQuery query(sql);
    dlg.m_ui->comboBox->addItem("");
    while (query.next()) {
        dlg.m_ui->comboBox->addItem(query.value(0).toString());
    }

    dlg.m_ui->comboBox->setCurrentIndex(dlg.m_ui->comboBox->findText(idopont, Qt::MatchExactly));

    dlg.attachlist(idopont, ui->lineEdit->text(), "mutet");

    if( dlg.exec() == QDialog::Accepted ){
        QString datum ="", alphaID="";
        vtrcodes vc;
        if (dlg.typ=="new"){
            datum = dlg.m_ui->dateEdit->date().toString("yyyy-MM-dd");
            alphaID = vc.alphaIDentify(ui->comboBox_3->currentText(), ui->lineEdit->text(), datum);
            vc.SurgRec(alphaID, dlg.m_ui->textEdit->toPlainText(), dlg.m_ui->textEdit_2->toPlainText(), dlg.m_ui->textEdit_3->toPlainText(), dlg.m_ui->textEdit_4->toPlainText(), dlg.m_ui->textEdit_5->toPlainText());
        } else if (dlg.typ=="edit"){
            datum = dlg.m_ui->comboBox->currentText();
            alphaID = vc.alphaIDentify(ui->comboBox_3->currentText(), ui->lineEdit->text(), datum);
            vc.SurgMod(alphaID, dlg.m_ui->textEdit->toPlainText(), dlg.m_ui->textEdit_2->toPlainText(), dlg.m_ui->textEdit_3->toPlainText(), dlg.m_ui->textEdit_4->toPlainText(), dlg.m_ui->textEdit_5->toPlainText());
            if (dlg.m_ui->dateEdit->date().toString("yyyy-MM-dd")!=datum){
                //ha megvďż˝ltoztatja a kezelďż˝s dďż˝tumďż˝t is
            }
        }
    }
    db.close();
}


void frmMain::frmVaccBetolt(){
    if(kontroll()!=0){
        return;
    }

    db.open();
    frmVacc dlg("ghg", this);
    dlg.doki = ui->comboBox_3->currentText();
    dlg.TabBetolt(ui->lineEdit->text());
    dlg.allat_az = ui->lineEdit->text();

    if( dlg.exec() == QDialog::Accepted )
    {
        ElozmenyBetolto(ui->lineEdit->text());
    }
    db.close();
}



void frmMain::modositTulajAllat(){
    db.open();
    frmTulAll dlg(this);

    QString trsz;

    dlg.m_ui->comboBox->setCurrentIndex(dlg.m_ui->comboBox->findText(ui->lineEdit_4->text(), Qt::MatchExactly));
    dlg.m_ui->comboBox_2->setCurrentIndex(dlg.m_ui->comboBox_2->findText(ui->lineEdit_5->text(), Qt::MatchExactly));
    dlg.m_ui->comboBox_3->setCurrentIndex(dlg.m_ui->comboBox_3->findText(ui->lineEdit_6->text(), Qt::MatchExactly));
    dlg.m_ui->comboBox_4->setCurrentIndex(dlg.m_ui->comboBox_4->findText(ui->lineEdit_7->text(), Qt::MatchExactly));
    dlg.m_ui->comboBox_5->setCurrentIndex(dlg.m_ui->comboBox_5->findText(ui->lineEdit_8->text(), Qt::MatchExactly));
    dlg.m_ui->comboBox_6->setCurrentIndex(dlg.m_ui->comboBox_6->findText(ui->lineEdit_9->text(), Qt::MatchExactly));
    dlg.m_ui->comboBox_7->setCurrentIndex(dlg.m_ui->comboBox_7->findText(ui->lineEdit_10->text(), Qt::MatchExactly));

    dlg.m_ui->lineEdit->setText(ui->lineEdit_2->text());
    dlg.m_ui->lineEdit_2->setText(ui->lineEdit_3->text());
    dlg.m_ui->lineEdit_3->setText(ui->lineEdit_14->text());

    dlg.m_ui->dateEdit->setDate(QDate::fromString(ui->lineEdit_11->text(), "yyyy-MM-dd"));

    dlg.m_ui->lineEdit_4->setText(ui->lineEdit_12->text());
    dlg.m_ui->lineEdit_5->setText(ui->lineEdit_13->text());

    QString beerk = ui->lineEdit_11->text();
    QString Shivo = ui->lineEdit_6->text();
    QString Sszin = ui->lineEdit_9->text();
    QString Sivar = ui->lineEdit_10->text();
    QString Sfaj = ui->lineEdit_7->text();
    QString Sfajta = ui->lineEdit_8->text();
    QString Snev = ui->lineEdit_2->text();
    QString Sisz = ui->lineEdit_3->text();
    QString Shely = ui->lineEdit_4->text();
    QString Sutca = ui->lineEdit_5->text();
    QString Shea = ui->lineEdit_14->text();
    QString chip = ui->lineEdit_12->text();
    QString booknum = ui->lineEdit_13->text();

    if(dlg.exec() == QDialog::Accepted){

        vtrcodes vc;

        QString sql = QString("Select yallat.az, ytulajdonos.az "
            "From yallat Inner Join ytulajdonos On ytulajdonos.az = yallat.tulajdonos Inner Join xtutca On xtutca.az = ytulajdonos.utca Inner Join xtisz On xtisz.az = ytulajdonos.helyseg Inner Join xttelepules On xttelepules.az = xtisz.telepules Inner Join xafajta On xafajta.az = yallat.fajta Inner Join xafaj On xafaj.az = xafajta.faj Inner Join xaivar On xaivar.az = yallat.ivar Inner Join xaszin On xaszin.az = yallat.szin "
            "Where xttelepules.telepules = '%1' And "
            "ytulajdonos.hea = '%2' And xtisz.isz = '%3' And "
            "xtutca.utca = '%4' And xafaj.faj = '%5' And "
            "xafajta.fajta = '%6' And xaivar.ivar = '%7' And "
            "xaszin.szin = '%8' And yallat.szuletett = '%9' And "
            "yallat.hivonev = '%10' And ytulajdonos.nev = '%11'")
            .arg(Shely).arg(Shea).arg(Sisz).arg(Sutca).arg(Sfaj).arg(Sfajta).arg(Sivar).arg(Sszin).arg(beerk).arg(Shivo).arg(Snev);

        QSqlQuery query;
        query.exec(sql);
        query.first();
        QString allataz = query.value(0).toString();
        QString tulajaz = query.value(1).toString();

        beerk = dlg.m_ui->dateEdit->date().toString("yyyy-MM-dd");
        Shivo = dlg.m_ui->comboBox_3->currentText();
        Sszin = dlg.m_ui->comboBox_6->currentText();
        Sivar = dlg.m_ui->comboBox_7->currentText();
        Sfaj = dlg.m_ui->comboBox_4->currentText();
        Sfajta = dlg.m_ui->comboBox_5->currentText();
        Snev = dlg.m_ui->lineEdit->text();
        Sisz = dlg.m_ui->lineEdit_2->text();
        Shely = dlg.m_ui->comboBox->currentText();
        Sutca = dlg.m_ui->comboBox_2->currentText();
        Shea = dlg.m_ui->lineEdit_3->text();
        chip = dlg.m_ui->lineEdit_4->text();
        booknum = dlg.m_ui->lineEdit_5->text();

        db.transaction();
        vc.tulajallatmod(tulajaz, allataz, beerk, Shivo, Sszin, Sivar, Sfaj, Sfajta, Snev, Sisz, Shely, Sutca, Shea, chip, booknum);
        db.commit();

        sql = QString("Select yallat.torzsszam "
            "From yallat Inner Join ytulajdonos On ytulajdonos.az = yallat.tulajdonos Inner Join xtutca On xtutca.az = ytulajdonos.utca Inner Join xtisz On xtisz.az = ytulajdonos.helyseg Inner Join xttelepules On xttelepules.az = xtisz.telepules Inner Join xafajta On xafajta.az = yallat.fajta Inner Join xafaj On xafaj.az = xafajta.faj Inner Join xaivar On xaivar.az = yallat.ivar Inner Join xaszin On xaszin.az = yallat.szin "
            "Where xttelepules.telepules = '%1' And "
            "ytulajdonos.hea = '%2' And xtisz.isz = '%3' And "
            "xtutca.utca = '%4' And xafaj.faj = '%5' And "
            "xafajta.fajta = '%6' And xaivar.ivar = '%7' And "
            "xaszin.szin = '%8' And yallat.szuletett = '%9' And "
            "yallat.hivonev = '%10' And ytulajdonos.nev = '%11'")
            .arg(Shely).arg(Shea).arg(Sisz).arg(Sutca).arg(Sfaj).arg(Sfajta).arg(Sivar).arg(Sszin).arg(beerk).arg(Shivo).arg(Snev);

        query.exec(sql);
        query.first();
        trsz = query.value(0).toString();

        ui->comboBox->clear();
        ui->comboBox->addItem("");
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem("");

        balFa();

        ui->lineEdit->setText(trsz);
        AllatBetoltoC(trsz);

    }
    db.close();
}


void frmMain::balFa(){
    db.open();

    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel(tr("Tallózó"));

    QTreeWidgetItem *tulaj = new QTreeWidgetItem(ui->treeWidget, QStringList(QObject::tr("Tulajdonos")));
    QTreeWidgetItem *hivo = new QTreeWidgetItem(ui->treeWidget, QStringList(QObject::tr("Hívónév")));
    QTreeWidgetItem *utca = new QTreeWidgetItem(ui->treeWidget, QStringList(QObject::tr("Utca")));
    QTreeWidgetItem *datum = new QTreeWidgetItem(ui->treeWidget, QStringList(QObject::tr("Utolsó kezelések")));
    QTreeWidgetItem *chipid = new QTreeWidgetItem(ui->treeWidget, QStringList(QObject::tr("Mikrochip id")));
    QTreeWidgetItem *bookid = new QTreeWidgetItem(ui->treeWidget, QStringList(QObject::tr("Könyv száma")));

    QSqlQuery query;
    QString sql;

    sql = "select distinct nev from ytulajdonos order by nev";
    query.exec(sql);
    while (query.next()) {
        QString nev = query.value(0).toString();
        ui->comboBox->addItem(nev);
        tulaj->addChild(new QTreeWidgetItem(QStringList(nev)));
    }

    sql = "select distinct hivonev from yallat order by hivonev";
    query.exec(sql);
    while (query.next()) {
        QString hivonev = query.value(0).toString();
        hivo->addChild(new QTreeWidgetItem(QStringList(hivonev)));
    }

    int datumlimit = 15;
    sql = QString("select distinct datum from alpha order by datum desc limit %1").arg(datumlimit);
    query.exec(sql);
    while (query.next()) {
        datum->addChild(new QTreeWidgetItem(QStringList(query.value(0).toString())));
    }

    sql = "Select distinct xtutca.utca From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos Inner Join xtutca On xtutca.az = ytulajdonos.utca order by xtutca.utca";
    query.exec(sql);
    while (query.next()) {
        utca->addChild(new QTreeWidgetItem(QStringList(query.value(0).toString())));
    }

    sql = "select distinct chip from yallat order by chip";
    query.exec(sql);
    while (query.next()) {
        QString chip = query.value(0).toString();
        chipid->addChild(new QTreeWidgetItem(QStringList(chip)));
    }

    sql = "select distinct booknum from yallat order by booknum";
    query.exec(sql);
    while (query.next()) {
        QString booknum = query.value(0).toString();
        bookid->addChild(new QTreeWidgetItem(QStringList(booknum)));
    }

    db.close();
}


void frmMain::TulajAllatmodosit(){
    disconnect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(idTulAllbol()));
    modositTulajAllat();
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(idTulAllbol()));
}



void frmMain::UjAllatTulajhoz(){
    db.open();
    frmTulAll dlg(this);
    QString trsz;

    dlg.m_ui->comboBox->setCurrentIndex(dlg.m_ui->comboBox->findText(ui->lineEdit_4->text(), Qt::MatchExactly));
    dlg.m_ui->comboBox_2->setCurrentIndex(dlg.m_ui->comboBox_2->findText(ui->lineEdit_5->text(), Qt::MatchExactly));
    dlg.m_ui->lineEdit->setText(ui->lineEdit_2->text());
    dlg.m_ui->lineEdit_2->setText(ui->lineEdit_3->text());
    dlg.m_ui->lineEdit_3->setText(ui->lineEdit_14->text());


    dlg.m_ui->lineEdit->setEnabled(false);
    dlg.m_ui->lineEdit_2->setEnabled(false);
    dlg.m_ui->lineEdit_3->setEnabled(false);
    dlg.m_ui->comboBox->setEnabled(false);
    dlg.m_ui->comboBox_2->setEnabled(false);

    if(dlg.exec() == QDialog::Accepted){
        vtrcodes vc;

        QString beerk = dlg.m_ui->dateEdit->date().toString("yyyy-MM-dd");
        QString Shivo = dlg.m_ui->comboBox_3->currentText();
        QString Sszin = dlg.m_ui->comboBox_6->currentText();
        QString Sivar = dlg.m_ui->comboBox_7->currentText();
        QString Sfaj = dlg.m_ui->comboBox_4->currentText();
        QString Sfajta = dlg.m_ui->comboBox_5->currentText();
        QString Snev = dlg.m_ui->lineEdit->text();
        QString Sisz = dlg.m_ui->lineEdit_2->text();
        QString Shely = dlg.m_ui->comboBox->currentText();
        QString Sutca = dlg.m_ui->comboBox_2->currentText();
        QString Shea = dlg.m_ui->lineEdit_3->text();
        QString chip = dlg.m_ui->lineEdit_4->text();
        QString booknum = dlg.m_ui->lineEdit_5->text();

        db.transaction();
        QString telaz = vc.telepazonosito(Sisz, Shely);
        QString utcaz = vc.utcazonosit(Sutca);
        QString tulaz = vc.tulajazonosito(Snev, telaz, utcaz, Shea);

        QString fajfajtaz = vc.fajfajtazonosit(Sfaj, Sfajta);
        QString szinaz = vc.szinazonosit(Sszin);
        QString ivaraz = vc.ivarazonosit(Sivar);
        vc.allatrec(tulaz, Shivo, beerk, ivaraz, fajfajtaz, szinaz, chip, booknum);
        db.commit();

        QString sql = QString("Select yallat.torzsszam "
            "From yallat Inner Join ytulajdonos On ytulajdonos.az = yallat.tulajdonos Inner Join xtutca On xtutca.az = ytulajdonos.utca Inner Join xtisz On xtisz.az = ytulajdonos.helyseg Inner Join xttelepules On xttelepules.az = xtisz.telepules Inner Join xafajta On xafajta.az = yallat.fajta Inner Join xafaj On xafaj.az = xafajta.faj Inner Join xaivar On xaivar.az = yallat.ivar Inner Join xaszin On xaszin.az = yallat.szin "
            "Where xttelepules.telepules = '%1' And "
            "ytulajdonos.hea = '%2' And xtisz.isz = '%3' And "
            "xtutca.utca = '%4' And xafaj.faj = '%5' And "
            "xafajta.fajta = '%6' And xaivar.ivar = '%7' And "
            "xaszin.szin = '%8' And yallat.szuletett = '%9' And "
            "yallat.hivonev = '%10' And ytulajdonos.nev = '%11'")
            .arg(Shely).arg(Shea).arg(Sisz).arg(Sutca).arg(Sfaj).arg(Sfajta).arg(Sivar).arg(Sszin).arg(beerk).arg(Shivo).arg(Snev);

        QSqlQuery query;
        query.exec(sql);
        query.first();
        trsz = query.value(0).toString();

        ui->comboBox->clear();
        ui->comboBox->addItem("");
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem("");

        balFa();

        ui->lineEdit->setText(trsz);
        AllatBetoltoC(trsz);
        ElozmenyBetolto(trsz);
    }
    db.close();
}

void frmMain::TulajhozAllat(){
    disconnect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(idTulAllbol()));
    UjAllatTulajhoz();
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(idTulAllbol()));
}


void frmMain::frmTulAllBetolt()
{
    db.open();
    frmTulAll dlg(this);
    QString trsz;

    if(dlg.exec() == QDialog::Accepted)
    {
        vtrcodes vc;

        QString beerk = dlg.m_ui->dateEdit->date().toString("yyyy-MM-dd");
        QString Shivo = dlg.m_ui->comboBox_3->currentText();
        QString Sszin = dlg.m_ui->comboBox_6->currentText();
        QString Sivar = dlg.m_ui->comboBox_7->currentText();
        QString Sfaj = dlg.m_ui->comboBox_4->currentText();
        QString Sfajta = dlg.m_ui->comboBox_5->currentText();
        QString Snev = dlg.m_ui->lineEdit->text();
        QString Sisz = dlg.m_ui->lineEdit_2->text();
        QString Shely = dlg.m_ui->comboBox->currentText();
        QString Sutca = dlg.m_ui->comboBox_2->currentText();
        QString Shea = dlg.m_ui->lineEdit_3->text();
        QString chip = dlg.m_ui->lineEdit_4->text();
        QString booknum = dlg.m_ui->lineEdit_5->text();

        db.transaction();
        trsz = vc.tulajallatrec(beerk, Shivo, Sszin, Sivar, Sfaj, Sfajta, Snev, Sisz, Shely, Sutca, Shea, chip, booknum);
        db.commit();

        ui->comboBox->clear();
        ui->comboBox->addItem("");
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem("");

        balFa();

        ui->lineEdit->setText(trsz);
        AllatBetoltoC(trsz);
        ElozmenyBetolto(trsz);
    }
    db.close();
}

void frmMain::ujTulajAllat(){
    disconnect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(idTulAllbol()));
    frmTulAllBetolt();
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(idTulAllbol()));
}


void frmMain::EditorNyit(){
    TextEdit *te = new TextEdit;
    te->textEdit->setText("");
    te->show();
}

void frmMain::kiir(){
    QMenu* contextMenu = new QMenu(this);
//    Q_CHECK_PTR(contextMenu);


    int i = ui->treeWidget->selectedItems().count();

    if (i>0)
    {
        QString s = ui->treeWidget->currentItem()->text(0);
        if (s != "Tulajdonos" && s!="Hívónév" && s!="Utca" && s!="Utolsó kezelések" && s!="Mikrochip id" && s!="Könyv száma")
        {
            db.open();
            QSignalMapper *mapper = new QSignalMapper(this);

            if (ui->treeWidget->currentItem()->parent()->text(0)=="Tulajdonos")
            {
                QString sql = QString("Select distinct yallat.hivonev, yallat.torzsszam "
                    "From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos "
                    "Where ytulajdonos.nev = '%1' and yallat.torzsszam<9000000 Order by hivonev").arg(s);

                QSqlQuery query(sql);
                QSqlRecord record = query.record();
                while (query.next()) {
                    QString hivonev = query.value(record.indexOf("hivonev")).toString();
                    QString torzsszam = query.value(record.indexOf("torzsszam")).toString();
                    QString lab = QString("%1 %2").arg(hivonev).arg(torzsszam);
                    QAction *a = contextMenu->addAction(lab);
                    connect(a, SIGNAL(triggered()), mapper, SLOT(map()));
                    mapper->setMapping(a, lab);
                }
            }

            if (ui->treeWidget->currentItem()->parent()->text(0)=="Hívónév")
            {
                QString sql = QString("Select distinct ytulajdonos.nev, yallat.torzsszam "
                    "From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos "
                    "where yallat.hivonev = '%1' and yallat.torzsszam<9000000 Order by nev").arg(s);
                QSqlQuery query(sql);
                QSqlRecord record = query.record();
                while (query.next()) {
                    QString nev = query.value(record.indexOf("nev")).toString();
                    QString torzsszam = query.value(record.indexOf("torzsszam")).toString();
                    QString lab = QString("%1 %2").arg(nev).arg(torzsszam);
                    QAction *a = contextMenu->addAction(lab);
                    connect(a, SIGNAL(triggered()), mapper, SLOT(map()));
                    mapper->setMapping(a, lab);
                }
            }

            if (ui->treeWidget->currentItem()->parent()->text(0)=="Utca")
            {
                QString sql = QString("Select distinct yallat.hivonev, yallat.torzsszam "
                    "From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos Inner Join xtutca On xtutca.az = ytulajdonos.utca "
                    "where xtutca.utca = '%1' and yallat.torzsszam<9000000 order by yallat.hivonev").arg(s);
                QSqlQuery query(sql);
                QSqlRecord record = query.record();
                while (query.next()) {
                    QString hivonev = query.value(record.indexOf("hivonev")).toString();
                    QString torzsszam = query.value(record.indexOf("torzsszam")).toString();
                    QString lab = QString("%1 %2").arg(hivonev).arg(torzsszam);
                    QAction *a = contextMenu->addAction(lab);
                    connect(a, SIGNAL(triggered()), mapper, SLOT(map()));
                    mapper->setMapping(a, lab);
                }
            }

            if (ui->treeWidget->currentItem()->parent()->text(0)=="Utolsó kezelések")
            {
                QString sql = QString("Select distinct yallat.hivonev, yallat.torzsszam "
                    "From alpha Inner Join yallat On yallat.torzsszam = alpha.torzsszam "
                    "where alpha.datum = '%1' and yallat.torzsszam<9000000").arg(s);
                QSqlQuery query(sql);
                QSqlRecord record = query.record();
                while (query.next()) {
                    QString hivonev = query.value(record.indexOf("hivonev")).toString();
                    QString torzsszam = query.value(record.indexOf("torzsszam")).toString();
                    QString lab = QString("%1 %2").arg(hivonev).arg(torzsszam);
                    QAction *a = contextMenu->addAction(lab);
                    connect(a, SIGNAL(triggered()), mapper, SLOT(map()));
                    mapper->setMapping(a, lab);
                }
            }

            if (ui->treeWidget->currentItem()->parent()->text(0)=="Mikrochip id")
            {
                QString sql = QString("Select distinct ytulajdonos.nev, yallat.torzsszam "
                    "From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos "
                    "where yallat.chip = '%1' and yallat.torzsszam<9000000 Order by nev").arg(s);
                QSqlQuery query(sql);
                QSqlRecord record = query.record();
                while (query.next()) {
                    QString nev = query.value(record.indexOf("nev")).toString();
                    QString torzsszam = query.value(record.indexOf("torzsszam")).toString();
                    QString lab = QString("%1 %2").arg(nev).arg(torzsszam);
                    QAction *a = contextMenu->addAction(lab);
                    connect(a, SIGNAL(triggered()), mapper, SLOT(map()));
                    mapper->setMapping(a, lab);
                }
            }

            if (ui->treeWidget->currentItem()->parent()->text(0)=="Könyv száma")
            {
                QString sql = QString("Select distinct ytulajdonos.nev, yallat.torzsszam "
                    "From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos "
                    "where yallat.booknum = '%1' and yallat.torzsszam<9000000 Order by nev").arg(s);
                QSqlQuery query(sql);
                QSqlRecord record = query.record();
                while (query.next()) {
                    QString nev = query.value(record.indexOf("nev")).toString();
                    QString torzsszam = query.value(record.indexOf("torzsszam")).toString();
                    QString lab = QString("%1 %2").arg(nev).arg(torzsszam);
                    QAction *a = contextMenu->addAction(lab);
                    connect(a, SIGNAL(triggered()), mapper, SLOT(map()));
                    mapper->setMapping(a, lab);
                }
            }

            connect(mapper, SIGNAL(mapped(QString)), SLOT(AllatBetoltoA(QString)));

            contextMenu->popup(QCursor::pos());
            contextMenu->exec();
            delete contextMenu;
            contextMenu = 0;
            db.close();
        }
    }
}

void frmMain::ElozmenyBetolto(const QString& id)
{
    ui->treeWidget_2->clear();
    QTreeWidgetItem *oltasok = new QTreeWidgetItem(ui->treeWidget_2, QStringList(QObject::tr("Oltások")));
    QTreeWidgetItem *kezelesek = new QTreeWidgetItem(ui->treeWidget_2, QStringList(QObject::tr("Kezelések")));
    QTreeWidgetItem *mutetek = new QTreeWidgetItem(ui->treeWidget_2, QStringList(QObject::tr("Műtétek")));
    QTreeWidgetItem *laborok = new QTreeWidgetItem(ui->treeWidget_2, QStringList(QObject::tr("Laborvizsgálatok")));
    QTreeWidgetItem *csatoltak = new QTreeWidgetItem(ui->treeWidget_2, QStringList(QObject::tr("Csatolmányok")));

    db.open();

    QString sql = QString("Select alpha.datum "
        "From alpha Inner Join bvakcinazas On alpha.az = bvakcinazas.alphaaz "
        "Where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(id);
    QSqlQuery query(sql);
    while (query.next()) {
        QString datum = query.value(0).toString();
        oltasok->addChild(new QTreeWidgetItem(QStringList(datum)));
    }

    sql = QString("Select alpha.datum "
        "From alpha Inner Join bgyogykezeles On alpha.az = bgyogykezeles.alphaaz "
        "Where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(id);
    query.exec(sql);
    while (query.next()) {
        QString datum = query.value(0).toString();
        kezelesek->addChild(new QTreeWidgetItem(QStringList(datum)));
    }

    sql = QString("Select alpha.datum "
        "From alpha Inner Join bmutet On alpha.az = bmutet.alphaaz "
        "Where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(id);
    query.exec(sql);
    while (query.next()) {
        QString datum = query.value(0).toString();
        mutetek->addChild(new QTreeWidgetItem(QStringList(datum)));
    }

    sql = QString("Select distinct alpha.datum "
        "From alpha Inner Join blabor On alpha.az = blabor.alphaaz "
        "Where alpha.torzsszam = %1 Order By alpha.datum Desc").arg(id);
    query.exec(sql);
    while (query.next()) {
        QString datum = query.value(0).toString();
        laborok->addChild(new QTreeWidgetItem(QStringList(datum)));
    }

    sql = QString("Select alpha.datum, lattach.lab "
        "From lattach Inner Join alpha On alpha.az = lattach.alphaz "
        "Where alpha.torzsszam = %1 "
        "order by alpha.datum, lattach.lab ").arg(id);
    query.exec(sql);
    while (query.next()) {
        QString csstr = QString("%1: %2").arg(query.value(0).toString()).arg(query.value(1).toString());
        csatoltak->addChild(new QTreeWidgetItem(QStringList(csstr)));
    }

    db.close();

    ui->treeWidget_2->expandAll();


}

void frmMain::AllatBetoltoTrsz()
{
    disconnect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(idTulAllbol()));
    QString allatID = ui->lineEdit->text();
    AllatBetoltoB(allatID);
    ElozmenyBetolto(allatID);
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(idTulAllbol()));
}

void frmMain::TrszDel(const QString& trsz)
{
    if (trsz=="")
    {
        UrlapTorlo();
    }
}

void frmMain::TulajAllatai(const QString& tulaj)
{
    ui->comboBox_2->clear();
    QString sql = QString("Select distinct yallat.hivonev "
        "From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos "
        "Where ytulajdonos.nev = '%1' and yallat.torzsszam<9000000 Order by hivonev").arg(tulaj);

    db.open();

    ui->comboBox_2->addItem("");

    QSqlQuery query(sql);
//    QSqlRecord record = query.record();
    int i = 0;
    QString hivo = "";
    while (query.next()) {
        hivo = query.value(0).toString();
        ui->comboBox_2->addItem(hivo);
        i++;
    }

    db.close();

    if (i==1){
        ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(hivo, Qt::MatchExactly));
    } else {
        ui->comboBox_2->setCurrentIndex(0);
    }

}

void frmMain::AllatBetoltoA(const QString& az)
{
    disconnect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(idTulAllbol()));
    QString allatID = az.split(" ").last();
    ui->lineEdit->setText(allatID);
    AllatBetoltoB(allatID);
    ElozmenyBetolto(allatID);
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(idTulAllbol()));
}

void frmMain::AllatBetoltoB(const QString& id)
{
    UrlapTorlo();

    QString sql = QString("Select "
        "ytulajdonos.nev, "
        "yallat.hivonev, "
        "xtisz.isz, "
        "xttelepules.telepules, "
        "xtutca.utca, "
        "ytulajdonos.hea, "
        "yallat.szuletett, "
        "xafaj.faj, "
        "xafajta.fajta, "
        "xaivar.ivar, "
        "xaszin.szin, yallat.chip , yallat.booknum "
        "From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos Inner Join xtutca On xtutca.az = ytulajdonos.utca Inner Join xtisz On xtisz.az = ytulajdonos.helyseg Inner Join xttelepules On xttelepules.az = xtisz.telepules Inner Join xafajta On xafajta.az = yallat.fajta Inner Join xafaj On xafaj.az = xafajta.faj Inner Join xaivar On xaivar.az = yallat.ivar Inner Join xaszin On xaszin.az = yallat.szin "
        "Where yallat.torzsszam = %1").arg(id);

    db.open();

    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    query.first();
//    while (query.next()) {
    ui->lineEdit_2->setText(query.value(record.indexOf("nev")).toString());
    ui->lineEdit_3->setText(query.value(record.indexOf("isz")).toString());
    ui->lineEdit_4->setText(query.value(record.indexOf("telepules")).toString());
    ui->lineEdit_5->setText(query.value(record.indexOf("utca")).toString());
    ui->lineEdit_14->setText(query.value(record.indexOf("hea")).toString());

    ui->lineEdit_6->setText(query.value(record.indexOf("hivonev")).toString());
    ui->lineEdit_7->setText(query.value(record.indexOf("faj")).toString());
    ui->lineEdit_8->setText(query.value(record.indexOf("fajta")).toString());
    ui->lineEdit_9->setText(query.value(record.indexOf("szin")).toString());
    ui->lineEdit_10->setText(query.value(record.indexOf("ivar")).toString());
    ui->lineEdit_11->setText(query.value(record.indexOf("szuletett")).toString());
    ui->lineEdit_12->setText(query.value(record.indexOf("chip")).toString());
    ui->lineEdit_13->setText(query.value(record.indexOf("booknum")).toString());

//    }

    db.close();

    ui->comboBox->setCurrentIndex(ui->comboBox->findText(ui->lineEdit_2->text(), Qt::MatchExactly));
    ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(ui->lineEdit_6->text(), Qt::MatchExactly));

}


void frmMain::AllatBetoltoC(const QString& id)
{
    QString sql = QString("Select "
        "ytulajdonos.nev, "
        "yallat.hivonev, "
        "xtisz.isz, "
        "xttelepules.telepules, "
        "xtutca.utca, "
        "ytulajdonos.hea, "
        "yallat.szuletett, "
        "xafaj.faj, "
        "xafajta.fajta, "
        "xaivar.ivar, "
        "xaszin.szin, yallat.chip , yallat.booknum "
        "From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos Inner Join xtutca On xtutca.az = ytulajdonos.utca Inner Join xtisz On xtisz.az = ytulajdonos.helyseg Inner Join xttelepules On xttelepules.az = xtisz.telepules Inner Join xafajta On xafajta.az = yallat.fajta Inner Join xafaj On xafaj.az = xafajta.faj Inner Join xaivar On xaivar.az = yallat.ivar Inner Join xaszin On xaszin.az = yallat.szin "
        "Where yallat.torzsszam = %1").arg(id);

    db.open();

    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    query.first();
//    while (query.next()) {
    ui->lineEdit_2->setText(query.value(record.indexOf("nev")).toString());
    ui->lineEdit_3->setText(query.value(record.indexOf("isz")).toString());
    ui->lineEdit_4->setText(query.value(record.indexOf("telepules")).toString());
    ui->lineEdit_5->setText(query.value(record.indexOf("utca")).toString());
    ui->lineEdit_14->setText(query.value(record.indexOf("hea")).toString());

    ui->lineEdit_6->setText(query.value(record.indexOf("hivonev")).toString());
    ui->lineEdit_7->setText(query.value(record.indexOf("faj")).toString());
    ui->lineEdit_8->setText(query.value(record.indexOf("fajta")).toString());
    ui->lineEdit_9->setText(query.value(record.indexOf("szin")).toString());
    ui->lineEdit_10->setText(query.value(record.indexOf("ivar")).toString());
    ui->lineEdit_11->setText(query.value(record.indexOf("szuletett")).toString());
    ui->lineEdit_12->setText(query.value(record.indexOf("chip")).toString());
    ui->lineEdit_13->setText(query.value(record.indexOf("booknum")).toString());

//    }

    db.close();

    ui->comboBox->setCurrentIndex(ui->comboBox->findText(ui->lineEdit_2->text(), Qt::MatchExactly));
    ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(ui->lineEdit_6->text(), Qt::MatchExactly));
}


void frmMain::UrlapTorlo()
{
    ui->comboBox->setCurrentIndex(-1);
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit_7->setText("");
    ui->lineEdit_8->setText("");
    ui->lineEdit_9->setText("");
    ui->lineEdit_10->setText("");
    ui->lineEdit_11->setText("");
    ui->lineEdit_12->setText("");
    ui->lineEdit_13->setText("");
    ui->lineEdit_14->setText("");
    ui->treeWidget_2->clear();
}

void frmMain::UrlapTorloB()
{
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit_7->setText("");
    ui->lineEdit_8->setText("");
    ui->lineEdit_9->setText("");
    ui->lineEdit_10->setText("");
    ui->lineEdit_11->setText("");
    ui->lineEdit_12->setText("");
    ui->lineEdit_13->setText("");
    ui->lineEdit_14->setText("");
    ui->treeWidget_2->clear();
}

void frmMain::betolt01()
{
    ui->comboBox->clear();
    ui->comboBox_3->clear();
    ui->treeWidget->clear();
    ui->treeWidget_2->clear();

    ui->comboBox->addItem("");
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel(tr("Tallózó"));
    ui->treeWidget_2->setColumnCount(1);
    ui->treeWidget_2->setHeaderLabel("Előzmények");

    QTreeWidgetItem *tulaj = new QTreeWidgetItem(ui->treeWidget, QStringList(QObject::tr("Tulajdonos")));
    QTreeWidgetItem *hivo = new QTreeWidgetItem(ui->treeWidget, QStringList(QObject::tr("Hívónev")));
    QTreeWidgetItem *utca = new QTreeWidgetItem(ui->treeWidget, QStringList(QObject::tr("Utca")));
    QTreeWidgetItem *datum = new QTreeWidgetItem(ui->treeWidget, QStringList(QObject::tr("Utolsó kezelések")));
    QTreeWidgetItem *chipid = new QTreeWidgetItem(ui->treeWidget, QStringList(QObject::tr("Mikrochip id")));
    QTreeWidgetItem *bookid = new QTreeWidgetItem(ui->treeWidget, QStringList(QObject::tr("Könyv szama")));

    db.open();


    QSqlQuery query("Select distinct ytulajdonos.nev "
        "From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos "
        "where yallat.torzsszam<9000000 Order by ytulajdonos.nev");
    QSqlRecord record = query.record();
    while (query.next()) {
        QString nev = query.value(record.indexOf("nev")).toString();
        ui->comboBox->addItem(nev);
        tulaj->addChild(new QTreeWidgetItem(QStringList(nev)));
    }

    query.exec("select distinct hivonev from yallat where torzsszam<9000000 order by hivonev");
    record = query.record();
    while (query.next()) {
        QString hivonev = query.value(record.indexOf("hivonev")).toString();
        hivo->addChild(new QTreeWidgetItem(QStringList(hivonev)));
    }

//    int datumlimit = 15;
    QString sql = QString("select distinct datum from alpha where torzsszam<9000000 order by datum desc limit %1").arg(kezelnapok);
    query.exec(sql);
    while (query.next()) {
        datum->addChild(new QTreeWidgetItem(QStringList(query.value(0).toString())));
    }

    sql = "Select distinct xtutca.utca From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos Inner Join xtutca On xtutca.az = ytulajdonos.utca where yallat.torzsszam<9000000 order by xtutca.utca";
    query.exec(sql);
    while (query.next()) {
        utca->addChild(new QTreeWidgetItem(QStringList(query.value(0).toString())));
    }

    query.exec("Select doki from xdokik where aktiv='igen' Order By doki");
    record = query.record();
    while (query.next()) {
        QString doki = query.value(record.indexOf("doki")).toString();
        ui->comboBox_3->addItem(doki);
    }

    query.exec("select distinct chip from yallat where torzsszam<9000000 order by chip");
    record = query.record();
    while (query.next()) {
        QString chip = query.value(record.indexOf("chip")).toString();
        chipid->addChild(new QTreeWidgetItem(QStringList(chip)));
    }

    query.exec("select distinct booknum from yallat where torzsszam<9000000 order by booknum");
    record = query.record();
    while (query.next()) {
        QString booknum = query.value(record.indexOf("booknum")).toString();
        bookid->addChild(new QTreeWidgetItem(QStringList(booknum)));
    }

    db.close();
    ui->comboBox_3->setCurrentIndex(-1);
}


void frmMain::About(){
    xAbout dlg(this);
    dlg.m_ui->plainTextEdit->appendPlainText(QString("\nVerzió: %1").arg(QApplication::applicationVersion()));

    if(dlg.exec() == QDialog::Accepted)
    {

    }
}

frmMain::~frmMain(){
    delete ui;
}

