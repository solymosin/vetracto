#include <QtGui>
#include <QtSql>
#include <QDate>
#include <QFile>
#include <QDir>
#include <QMenu>
#include <QMessageBox>

#include "frmkezel.h"
#include "ui_frmkezel.h"

#include "xpanel.h"
#include "ui_xpanel.h"
#include "xattach.h"
#include "ui_xattach.h"

#include "textedit.h"
#include "vtrcodes.h"

frmKezel::frmKezel(QWidget *parent) : QDialog(parent), m_ui(new Ui::frmKezel)
{
    m_ui->setupUi(this);
    connect(m_ui->toolButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(m_ui->toolButton_5, SIGNAL(clicked()), this, SLOT(EditorNyit()));

    connect(m_ui->radioButton, SIGNAL(clicked()), this, SLOT(ListaBetolto()));
    connect(m_ui->radioButton_2, SIGNAL(clicked()), this, SLOT(ListaBetolto()));
    connect(m_ui->radioButton_3, SIGNAL(clicked()), this, SLOT(ListaBetolto()));
    connect(m_ui->radioButton_4, SIGNAL(clicked()), this, SLOT(ListaBetolto()));
    connect(m_ui->radioButton_5, SIGNAL(clicked()), this, SLOT(ListaBetolto()));

    connect(m_ui->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ListatoPlain()));
    connect(m_ui->textEdit, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(TextboLista()));
    connect(m_ui->textEdit_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(TextboLista()));
    connect(m_ui->textEdit_3, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(TextboLista()));
    connect(m_ui->textEdit_4, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(TextboLista()));
    connect(m_ui->textEdit_5, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(TextboLista()));

    connect(m_ui->listView_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(PanelPopUp()));
    connect(m_ui->listView_2, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(PanelMutat()));

    connect(m_ui->toolButton_3, SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ElozmenyMutat()));
    connect(m_ui->toolButton_2, SIGNAL(clicked()), this, SLOT(UjKezeles()));
    connect(m_ui->toolButton_4, SIGNAL(clicked()), this, SLOT(Modosit()));

    connect(m_ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(Csatolmany()));
    connect(m_ui->listView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(listaPopUp()));


}

frmKezel::~frmKezel()
{
    delete m_ui;
}

void frmKezel::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void frmKezel::createToolbars()
{
//    QToolBar *toolbar;
//
//    toolbar = addToolBar( tr("File") );
//    toolbar->addAction( newAction );
}



void frmKezel::Csatolmany(){
    if (m_ui->comboBox_2->currentText()!=""){
        if (m_ui->comboBox_2->currentText()=="Új csatolmány"){
            Csatol();
        } else {
            attached();
        }
    }
}

QString frmKezel::datumozo(){
    QString datum = "";
    if (m_ui->comboBox->currentText()==""){
        datum = m_ui->dateEdit->date().toString("yyyy-MM-dd");
    } else {
        datum = m_ui->comboBox->currentText();
    }
    return datum;
}

void frmKezel::attached(){
    QApplication::setOverrideCursor( Qt::WaitCursor );

    vtrcodes vc;
    QString datum = datumozo();
    QString lab = m_ui->comboBox_2->currentText();
    QString typ = "kezel";

    vc.attachedShow(datum, lab, typ, allat_az);

    QApplication::restoreOverrideCursor();
}


void frmKezel::Csatol(){
    xAttach dlg(this);

    QString sql = "Select distinct lab From lattach Order By lab";
    QSqlQuery query(sql);
    dlg.m_ui->comboBox->addItem("");
    while (query.next()) {
        dlg.m_ui->comboBox->addItem(query.value(0).toString());
    }

    if( dlg.exec() == QDialog::Accepted )
    {
        QString path = dlg.m_ui->lineEdit->text();
        QString datum = datumozo();
        QString lab = dlg.m_ui->comboBox->currentText();
        QString typ = "kezel";

        vtrcodes vc;

        vc.attachFile(path, datum, lab, typ, allat_az, doki);

        attachlist(datum, allat_az, typ);
    }
}



void frmKezel::attachlist(const QString& datum, const QString& aisz, const QString& typ){

    m_ui->comboBox_2->clear();
    m_ui->comboBox_2->addItem("");

    QString sql = QString("Select lattach.lab "
        "From lattach Inner Join alpha On alpha.az = lattach.alphaz "
        "Where alpha.datum = '%1' "
        "And alpha.torzsszam = '%2' "
        "And lattach.typ = '%3' Order By lattach.lab").arg(datum).arg(aisz).arg(typ);
    QSqlQuery query(sql);
    while (query.next()) {
        m_ui->comboBox_2->addItem(query.value(0).toString());
    }

    m_ui->comboBox_2->addItem("Új csatolmány");

}



void frmKezel::EditorNyit()
{
    vtrcodes vc;

    TextEdit *te = new TextEdit(this);

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "vetracto", "qvtr");

    settings.beginGroup("vtr");
    settings.beginGroup("rendelo");

    QString fejlec = QString(
        "<p align='center'><b>Kórlap</b></span></p>"
        "<p align='center'><b>%1</b></span></p>"
        "<p align='center'><b>%2</b></span></p>"
        "<p align='center'><b>%3</b></span></p>"
        "<p align='center'><b></b></span></p>")
            .arg(settings.value("neve").toString())
            .arg(settings.value("cime").toString())
            .arg(settings.value("www").toString());

    settings.endGroup();
    settings.endGroup();

    te->textEdit->append(fejlec);

    QString sz = QString(
        "<b>Kórelőzmény:</b><br>%1<br><br>"
        "<b>Jelen állapot:</b><br>%2<br><br>"
        "<b>Kórisme:</b><br>%3<br><br>"
        "<b>Kezelés:</b><br>%4<br><br>"
        "<b>Gyógyszer:</b><br>%5<br>").arg(
        m_ui->textEdit->toHtml() ).arg(
        m_ui->textEdit_2->toHtml()).arg(
        m_ui->textEdit_3->toHtml()).arg(
        m_ui->textEdit_4->toHtml()).arg(
        m_ui->textEdit_5->toHtml()
    );

    QString dd = QString("<p align='right' style='margin-right: 25px;'> %1").arg(doki);

    QString datum = "";
    if(m_ui->comboBox->currentText()==""){
        datum = m_ui->dateEdit->date().toString("yyyy.MM.dd.");
    } else {
        datum = QString("%1.").arg(m_ui->comboBox->currentText().replace("-","."));
    }
//    te->textEdit->setText(

    te->textEdit->append(
        QString("%1<br><br><b>Vizsgálat időpontja: </b>%2<br><br>%3<br><br>%4<br><br>%5").arg(vc.Nationale(allat_az)).arg(datum).arg(sz).arg(QDate::currentDate().toString("yyyy.MM.dd.")).arg(dd)
    );

    te->show();
}


void frmKezel::ListaBetolto(){
    QSqlQueryModel *model1 = new QSqlQueryModel();
    QSqlQueryModel *model2 = new QSqlQueryModel();
    QString sql1 = "", sql2 = "";

    if (m_ui->radioButton->isChecked()==true){
        sql1 = "select anamnesis, az from lanamnesis order by anamnesis";
        sql2 = "select panel from lpanel where ek='anam' order by panel";

        model1->setQuery(sql1);
        m_ui->listView->setModel(model1);
        model2->setQuery(sql2);
        m_ui->listView_2->setModel(model2);

        m_ui->textEdit->setFocus();

    } else if (m_ui->radioButton_2->isChecked()==true){
        sql1 = "select tunetek, az from ltunetekaltalanos order by tunetek";
        sql2 = "select panel from lpanel where ek='pres' order by panel";

        model1->setQuery(sql1);
        m_ui->listView->setModel(model1);
        model2->setQuery(sql2);
        m_ui->listView_2->setModel(model2);

        m_ui->textEdit_2->setFocus();

    } else if (m_ui->radioButton_3->isChecked()==true){
        sql1 = "select diagnosis, az from ldiagnosisaltalanos order by diagnosis";
        sql2 = "select panel from lpanel where ek='diag' order by panel";

        model1->setQuery(sql1);
        m_ui->listView->setModel(model1);
        model2->setQuery(sql2);
        m_ui->listView_2->setModel(model2);

        m_ui->textEdit_3->setFocus();

    } else if (m_ui->radioButton_4->isChecked()==true){
        sql1 = "select beavatkozas, az from lbeavatkozasaltalanos order by beavatkozas";
        sql2 = "select panel from lpanel where ek='treat' order by panel";

        model1->setQuery(sql1);
        m_ui->listView->setModel(model1);
        model2->setQuery(sql2);
        m_ui->listView_2->setModel(model2);

        m_ui->textEdit_4->setFocus();

    } else if (m_ui->radioButton_5->isChecked()==true){
        sql1 = "select gyogyszer, az from agyogyofo order by gyogyszer";
        sql2 = "select panel from lpanel where ek='pharm' order by panel";

        model1->setQuery(sql1);
        m_ui->listView->setModel(model1);
        model2->setQuery(sql2);
        m_ui->listView_2->setModel(model2);

        m_ui->textEdit_5->setFocus();

    }

}

void frmKezel::ListatoPlain(){
    QModelIndex idx;

    idx = m_ui->listView->selectionModel()->currentIndex();
    QString litem = m_ui->listView->model()->data(idx.sibling(idx.row(),0)).toString();

    if (m_ui->radioButton->isChecked()==true){
        m_ui->textEdit->insertPlainText(litem);
    } else if (m_ui->radioButton_2->isChecked()==true){
        m_ui->textEdit_2->insertPlainText(litem);
    } else if (m_ui->radioButton_3->isChecked()==true){
        m_ui->textEdit_3->insertPlainText(litem);
    } else if (m_ui->radioButton_4->isChecked()==true){
        m_ui->textEdit_4->insertPlainText(litem);
    } else if (m_ui->radioButton_5->isChecked()==true){
        m_ui->textEdit_5->insertPlainText(litem);
    }

}

void frmKezel::TextboLista(){
    QMenu* contextMenu = new QMenu(this);
    QString lab = QString("Hozzáad a listához");
    QAction *a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(UjListaElem()));
    contextMenu->popup(QCursor::pos());
    contextMenu->exec();
    delete contextMenu;
    contextMenu = 0;
}

void frmKezel::UjListaElem(){
    QClipboard *clpb = QApplication::clipboard();
    QString sql = "";
    QSqlQuery query;

    QString kulcs = this->focusWidget()->objectName();

    if (kulcs == "plainTextEdit"){
        m_ui->radioButton->setChecked(true);
        m_ui->textEdit->copy();
        sql = "insert into lanamnesis (anamnesis) values(?)";

    } else if (kulcs == "plainTextEdit_2"){
        m_ui->radioButton_2->setChecked(true);
        m_ui->textEdit_2->copy();
        sql = "insert into ltunetekaltalanos (tunetek) values(?)";

    } else if (kulcs == "plainTextEdit_3"){
        m_ui->radioButton_3->setChecked(true);
        m_ui->textEdit_3->copy();
        sql = "insert into ldiagnosisaltalanos (diagnosis) values(?)";

    } else if (kulcs == "plainTextEdit_4"){
        m_ui->radioButton_4->setChecked(true);
        m_ui->textEdit_4->copy();
        sql = "insert into lbeavatkozasaltalanos (beavatkozas) values(?)";

    } else if (kulcs == "plainTextEdit_5"){
        m_ui->radioButton_5->setChecked(true);
        m_ui->textEdit_5->copy();
        sql = "insert into agyogyofo (gyogyszer) values(?)";
    }

    QString elem = clpb->text();
    if (elem!=""){
        query.prepare(sql);
        query.addBindValue(elem);
        query.exec();
    }

    ListaBetolto();

}


void frmKezel::ElozmenyMutat(){

    attachlist(m_ui->comboBox->currentText(), allat_az, "kezel");

    if (m_ui->comboBox->currentText()!=""){
        QString sql = QString("Select bgyogykezeles.anamnesis, bgyogykezeles.jelenallapot, bgyogykezeles.diagnosis, bgyogykezeles.gyogyszer, bgyogykezeles.beavatkozas "
            "From alpha Inner Join bgyogykezeles On alpha.az = bgyogykezeles.alphaaz "
            "Where alpha.datum = '%1' And alpha.torzsszam = %2").arg(m_ui->comboBox->currentText()).arg(allat_az);

        QSqlQuery query(sql);
        query.first();
        m_ui->textEdit->setReadOnly(true);
        m_ui->textEdit_2->setReadOnly(true);
        m_ui->textEdit_3->setReadOnly(true);
        m_ui->textEdit_4->setReadOnly(true);
        m_ui->textEdit_5->setReadOnly(true);
//        m_ui->plainTextEdit->setEnabled(false);
//        m_ui->plainTextEdit_2->setEnabled(false);
//        m_ui->plainTextEdit_3->setEnabled(false);
//        m_ui->plainTextEdit_4->setEnabled(false);
//        m_ui->plainTextEdit_5->setEnabled(false);

        m_ui->listView->setEnabled(false);
        m_ui->listView_2->setEnabled(false);

        m_ui->textEdit->setPlainText(query.value(0).toString());
        m_ui->textEdit_2->setPlainText(query.value(1).toString());
        m_ui->textEdit_3->setPlainText(query.value(2).toString());
        m_ui->textEdit_4->setPlainText(query.value(3).toString());
        m_ui->textEdit_5->setPlainText(query.value(4).toString());
    } else {
        TisztaLap();
    }
}

void frmKezel::Felszab(){
    m_ui->textEdit->setReadOnly(false);
    m_ui->textEdit_2->setReadOnly(false);
    m_ui->textEdit_3->setReadOnly(false);
    m_ui->textEdit_4->setReadOnly(false);
    m_ui->textEdit_5->setReadOnly(false);
//    m_ui->plainTextEdit->setEnabled(true);
//    m_ui->plainTextEdit_2->setEnabled(true);
//    m_ui->plainTextEdit_3->setEnabled(true);
//    m_ui->plainTextEdit_4->setEnabled(true);
//    m_ui->plainTextEdit_5->setEnabled(true);

    m_ui->listView->setEnabled(true);
    m_ui->listView_2->setEnabled(true);
}

void frmKezel::TisztaLap(){
    Felszab();

    m_ui->textEdit->setPlainText("");
    m_ui->textEdit_2->setPlainText("");
    m_ui->textEdit_3->setPlainText("");
    m_ui->textEdit_4->setPlainText("");
    m_ui->textEdit_5->setPlainText("");
}


void frmKezel::UjKezeles(){
    TisztaLap();

    QDate date = QDate::currentDate();
    m_ui->dateEdit->setDate(date);

    typ = "new";
    m_ui->comboBox->setCurrentIndex(0);
    m_ui->comboBox->setEnabled(true);
}


void frmKezel::Modosit(){
    if (m_ui->comboBox->currentText()!=""){
        Felszab();
        m_ui->comboBox->setEnabled(false);
        typ = "edit";
    }
}

void frmKezel::listaPopUp(){
    QMenu* contextMenu = new QMenu(this);
    QString lab = QString("Listaelem törlése");
    QAction *a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(leDel()));

    contextMenu->popup(QCursor::pos());
    contextMenu->exec();
    delete contextMenu;
    contextMenu = 0;
}

void frmKezel::leDel(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("Figyelmezzünk!");
    msgBox.setInformativeText("Valóban töröljük a kijelölt elemet?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes){
        QModelIndex idx;
        QString sql = "";
        QSqlQuery query;

        idx = m_ui->listView->selectionModel()->currentIndex();
        QString litem = m_ui->listView->model()->data(idx.sibling(idx.row(),0)).toString();
        if (m_ui->radioButton->isChecked()==true){
            sql = QString("delete from lanamnesis where anamnesis='%1'").arg(litem);
        } else if (m_ui->radioButton_2->isChecked()==true){
            sql = QString("delete from ltunetekaltalanos where tunetek='%1'").arg(litem);
        } else if (m_ui->radioButton_3->isChecked()==true){
            sql = QString("delete from ldiagnosisaltalanos where diagnosis='%1'").arg(litem);
        } else if (m_ui->radioButton_4->isChecked()==true){
            sql = QString("delete from lbeavatkozasaltalanos where beavatkozas='%1'").arg(litem);
        } else if (m_ui->radioButton_5->isChecked()==true){
            sql = QString("delete from agyogyofo where gyogyszer='%1'").arg(litem);
        }

        query.exec(sql);
        ListaBetolto();
    }
}



void frmKezel::PanelPopUp(){
    QMenu* contextMenu = new QMenu(this);
    QString lab = QString("Új panel rögzítése");
    QAction *a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(PanelRec()));
    lab = QString("Panel módosítása");
    a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(PanelMod()));
    contextMenu->popup(QCursor::pos());
    contextMenu->exec();
    delete contextMenu;
    contextMenu = 0;
}


void frmKezel::PanelRec(){
    xPanel dlg(this);

    if( dlg.exec() == QDialog::Accepted )
    {
        vtrcodes vc;
        QString ek = "";
        if (m_ui->radioButton->isChecked()==true){
            ek = "anam";
            vc.PanelRec(ek, dlg.m_ui->lineEdit->text(), dlg.m_ui->plainTextEdit->toPlainText());
        } else if (m_ui->radioButton_2->isChecked()==true){
            ek = "pres";
            vc.PanelRec(ek, dlg.m_ui->lineEdit->text(), dlg.m_ui->plainTextEdit->toPlainText());
        } else if (m_ui->radioButton_3->isChecked()==true){
            ek = "diag";
            vc.PanelRec(ek, dlg.m_ui->lineEdit->text(), dlg.m_ui->plainTextEdit->toPlainText());
        } else if (m_ui->radioButton_4->isChecked()==true){
            ek = "treat";
            vc.PanelRec(ek, dlg.m_ui->lineEdit->text(), dlg.m_ui->plainTextEdit->toPlainText());
        } else if (m_ui->radioButton_5->isChecked()==true){
            ek = "pharm";
            vc.PanelRec(ek, dlg.m_ui->lineEdit->text(), dlg.m_ui->plainTextEdit->toPlainText());
        }

        ListaBetolto();
    }
}

void frmKezel::PanelMod(){
    xPanel dlg(this);
    dlg.setWindowTitle("Panel módisítása");

    QModelIndex idx;
    QString sql = "", litem = "", ek = "";

    idx = m_ui->listView_2->selectionModel()->currentIndex();
    litem = m_ui->listView_2->model()->data(idx.sibling(idx.row(),0)).toString();

    if (m_ui->radioButton->isChecked()==true){
        ek = "anam";
    } else if (m_ui->radioButton_2->isChecked()==true){
        ek = "pres";
    } else if (m_ui->radioButton_3->isChecked()==true){
        ek = "diag";
    } else if (m_ui->radioButton_4->isChecked()==true){
        ek = "treat";
    } else if (m_ui->radioButton_5->isChecked()==true){
        ek = "pharm";
    }

    sql = QString("select descr from lpanel where panel = '%1' and ek='%2'").arg(litem).arg(ek);
    QSqlQuery query(sql);
    query.first();
    dlg.m_ui->lineEdit->setText(litem);
    dlg.m_ui->plainTextEdit->setPlainText(query.value(0).toString());

    if( dlg.exec() == QDialog::Accepted )
    {
        vtrcodes vc;
        vc.PanelMod(ek, litem, dlg.m_ui->lineEdit->text(), dlg.m_ui->plainTextEdit->toPlainText());
        ListaBetolto();
    }
}

void frmKezel::PanelMutat(){
    QModelIndex idx;
    QString sql = "", litem = "", ek = "";
    QSqlQuery query;

    idx = m_ui->listView_2->selectionModel()->currentIndex();
    litem = m_ui->listView_2->model()->data(idx.sibling(idx.row(),0)).toString();

    if (m_ui->radioButton->isChecked()==true){
        sql = QString("select descr from lpanel where panel = '%1' and ek='anam'").arg(litem);
        query.exec(sql);
        query.first();
        m_ui->textEdit->setPlainText(query.value(0).toString());
    } else if (m_ui->radioButton_2->isChecked()==true){
        sql = QString("select descr from lpanel where panel = '%1' and ek='pres'").arg(litem);
        query.exec(sql);
        query.first();
        m_ui->textEdit_2->setPlainText(query.value(0).toString());
    } else if (m_ui->radioButton_3->isChecked()==true){
        sql = QString("select descr from lpanel where panel = '%1' and ek='diag'").arg(litem);
        query.exec(sql);
        query.first();
        m_ui->textEdit_3->setPlainText(query.value(0).toString());
    } else if (m_ui->radioButton_4->isChecked()==true){
        sql = QString("select descr from lpanel where panel = '%1' and ek='treat'").arg(litem);
        query.exec(sql);
        query.first();
        m_ui->textEdit_4->setPlainText(query.value(0).toString());
    } else if (m_ui->radioButton_5->isChecked()==true){
        sql = QString("select descr from lpanel where panel = '%1' and ek='pharm'").arg(litem);
        query.exec(sql);
        query.first();
        m_ui->textEdit_5->setPlainText(query.value(0).toString());
    }

}

