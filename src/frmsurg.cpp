#include <QtGui>
#include <QtSql>
#include <QDate>
#include <QMenu>
#include <QMessageBox>

#include "frmsurg.h"
#include "ui_frmsurg.h"

#include "xpanel.h"
#include "ui_xpanel.h"
#include "xattach.h"
#include "ui_xattach.h"

#include "textedit.h"
#include "vtrcodes.h"

frmSurg::frmSurg(QWidget *parent) : QDialog(parent), m_ui(new Ui::frmSurg)
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

void frmSurg::listaPopUp(){
    QMenu* contextMenu = new QMenu(this);
    QString lab = QString("Listaelem törlése");
    QAction *a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(leDel()));

    contextMenu->popup(QCursor::pos());
    contextMenu->exec();
    delete contextMenu;
    contextMenu = 0;
}

void frmSurg::leDel(){
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
            sql = QString("delete from ldiagnozismutet where diagnosis='%1'").arg(litem);
        } else if (m_ui->radioButton_4->isChecked()==true){
            sql = QString("delete from lleirasmutet where leiras='%1'").arg(litem);
        } else if (m_ui->radioButton_5->isChecked()==true){
            sql = QString("delete from laltatas where altatas='%1'").arg(litem);
        }
        query.exec(sql);
        ListaBetolto();
    }
}

frmSurg::~frmSurg()
{
    delete m_ui;
}

void frmSurg::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void frmSurg::createToolbars()
{
//    QToolBar *toolbar;
//
//    toolbar = addToolBar( tr("File") );
//    toolbar->addAction( newAction );
}


void frmSurg::Csatolmany(){
    if (m_ui->comboBox_2->currentText()!=""){
        if (m_ui->comboBox_2->currentText()=="Új csatolmány"){
            Csatol();
        } else {
            attached();
        }
    }
}

QString frmSurg::datumozo(){
    QString datum = "";
    if (m_ui->comboBox->currentText()==""){
        datum = m_ui->dateEdit->date().toString("yyyy-MM-dd");
    } else {
        datum = m_ui->comboBox->currentText();
    }
    return datum;
}

void frmSurg::attached(){
    vtrcodes vc;
    QString datum = datumozo();
    QString lab = m_ui->comboBox_2->currentText();
    QString typ = "seb";

    vc.attachedShow(datum, lab, typ, allat_az);
}


void frmSurg::Csatol(){
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
        QString typ = "seb";

        vtrcodes vc;

        vc.attachFile(path, datum, lab, typ, allat_az, doki);

        attachlist(datum, allat_az, typ);
    }
}



void frmSurg::attachlist(const QString& datum, const QString& aisz, const QString& typ){

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


void frmSurg::EditorNyit()
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
        "<b>Műtét leírása:</b><br>%4<br><br>"
        "<b>Altatás:</b><br>%5<br>").arg(
        m_ui->textEdit->toHtml()  ).arg(
        m_ui->textEdit_2->toHtml()).arg(
        m_ui->textEdit_3->toHtml()).arg(
        m_ui->textEdit_4->toHtml()).arg(
        m_ui->textEdit_5->toHtml()
    );

    QString dd = QString("<p align='right' style='margin-right: 25px;'> %1").arg(doki);

    te->textEdit->append(
        QString("%1<br><br><b>Beavatkozás időpontja: </b>%2<br><br>%3<br><br>%4<br><br>%5").arg(vc.Nationale(allat_az)).arg(m_ui->dateEdit->date().toString("yyyy.MM.dd.")).arg(sz).arg(QDate::currentDate().toString("yyyy.MM.dd.")).arg(dd)
    );

    te->show();
}


void frmSurg::ListaBetolto(){
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
        sql1 = "select diagnosis, az from ldiagnozismutet order by diagnosis";
        sql2 = "select panel from lpanel where ek='mdiag' order by panel";

        model1->setQuery(sql1);
        m_ui->listView->setModel(model1);
        model2->setQuery(sql2);
        m_ui->listView_2->setModel(model2);

        m_ui->textEdit_3->setFocus();

    } else if (m_ui->radioButton_4->isChecked()==true){
        sql1 = "select leiras, az from lleirasmutet order by leiras";
        sql2 = "select panel from lpanel where ek='mutet' order by panel";

        model1->setQuery(sql1);
        m_ui->listView->setModel(model1);
        model2->setQuery(sql2);
        m_ui->listView_2->setModel(model2);

        m_ui->textEdit_4->setFocus();

    } else if (m_ui->radioButton_5->isChecked()==true){
        sql1 = "select altatas, az from laltatas order by altatas";
        sql2 = "select panel from lpanel where ek='maltat' order by panel";

        model1->setQuery(sql1);
        m_ui->listView->setModel(model1);
        model2->setQuery(sql2);
        m_ui->listView_2->setModel(model2);

        m_ui->textEdit_5->setFocus();

    }

}

void frmSurg::ListatoPlain(){
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

void frmSurg::TextboLista(){
    QMenu* contextMenu = new QMenu(this);
    QString lab = QString("Hozzáad a listához");
    QAction *a = contextMenu->addAction(lab);
    connect(a, SIGNAL(triggered()), this, SLOT(UjListaElem()));
    contextMenu->popup(QCursor::pos());
    contextMenu->exec();
    delete contextMenu;
    contextMenu = 0;
}

void frmSurg::UjListaElem(){
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
        sql = "insert into ldiagnozismutet (diagnosis) values(?)";

    } else if (kulcs == "plainTextEdit_4"){
        m_ui->radioButton_4->setChecked(true);
        m_ui->textEdit_4->copy();
        sql = "insert into lleirasmutet (leiras) values(?)";

    } else if (kulcs == "plainTextEdit_5"){
        m_ui->radioButton_5->setChecked(true);
        m_ui->textEdit_5->copy();
        sql = "insert into laltatas (altatas) values(?)";
    }

    QString elem = clpb->text();
    if (elem!=""){
        query.prepare(sql);
        query.addBindValue(elem);
        query.exec();
    }

    ListaBetolto();

}


void frmSurg::ElozmenyMutat(){

    if (m_ui->comboBox->currentText()!=""){
        QString sql = QString("Select anamnesis, jelenallapot, diagnosis, leirasa, altatas "
            "From alpha Inner Join bmutet On bmutet.alphaaz = alpha.az "
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

void frmSurg::Felszab(){
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

void frmSurg::TisztaLap(){
    Felszab();

    m_ui->textEdit->setPlainText("");
    m_ui->textEdit_2->setPlainText("");
    m_ui->textEdit_3->setPlainText("");
    m_ui->textEdit_4->setPlainText("");
    m_ui->textEdit_5->setPlainText("");
}


void frmSurg::UjKezeles(){
    TisztaLap();

    QDate date = QDate::currentDate();
    m_ui->dateEdit->setDate(date);

    typ = "new";
    m_ui->comboBox->setCurrentIndex(0);
    m_ui->comboBox->setEnabled(true);
}


void frmSurg::Modosit(){
    if (m_ui->comboBox->currentText()!=""){
        Felszab();
        m_ui->comboBox->setEnabled(false);
        typ = "edit";
    }
}


void frmSurg::PanelPopUp(){
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


void frmSurg::PanelRec(){
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
            ek = "mdiag";
            vc.PanelRec(ek, dlg.m_ui->lineEdit->text(), dlg.m_ui->plainTextEdit->toPlainText());
        } else if (m_ui->radioButton_4->isChecked()==true){
            ek = "mutet";
            vc.PanelRec(ek, dlg.m_ui->lineEdit->text(), dlg.m_ui->plainTextEdit->toPlainText());
        } else if (m_ui->radioButton_5->isChecked()==true){
            ek = "maltat";
            vc.PanelRec(ek, dlg.m_ui->lineEdit->text(), dlg.m_ui->plainTextEdit->toPlainText());
        }

        ListaBetolto();
    }
}

void frmSurg::PanelMod(){
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
        ek = "mdiag";
    } else if (m_ui->radioButton_4->isChecked()==true){
        ek = "mutet";
    } else if (m_ui->radioButton_5->isChecked()==true){
        ek = "maltat";
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

void frmSurg::PanelMutat(){
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
        sql = QString("select descr from lpanel where panel = '%1' and ek='mdiag'").arg(litem);
        query.exec(sql);
        query.first();
        m_ui->textEdit_3->setPlainText(query.value(0).toString());
    } else if (m_ui->radioButton_4->isChecked()==true){
        sql = QString("select descr from lpanel where panel = '%1' and ek='mutet'").arg(litem);
        query.exec(sql);
        query.first();
        m_ui->textEdit_4->setPlainText(query.value(0).toString());
    } else if (m_ui->radioButton_5->isChecked()==true){
        sql = QString("select descr from lpanel where panel = '%1' and ek='maltat'").arg(litem);
        query.exec(sql);
        query.first();
        m_ui->textEdit_5->setPlainText(query.value(0).toString());
    }
}


