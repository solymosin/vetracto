#include <QtGui>
#include <QTextStream>
#include <qtextcodec.h>
#include <QMessageBox>
#include <QFileDialog>

#include "frmimporter.h"
#include "ui_frmimporter.h"

frmImporter::frmImporter(QWidget *parent): QDialog(parent), ui(new Ui::frmImporter){
    ui->setupUi(this);
    connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(sourcePath()));
    connect(ui->toolButton_2, SIGNAL(clicked()), this, SLOT(destPath()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(importer()));
}

void frmImporter::importer(){
    QApplication::setOverrideCursor( Qt::WaitCursor );

    QString sif = ui->lineEdit->text();
    QString sof = ui->lineEdit_2->text();
    QString sql = "";

    QFile sqlitef(sof);
    if (!sqlitef.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
        tr("Cannot write file %1:\n%2.").arg(sof).arg(sqlitef.errorString()));
        return;
    }

    QTextStream out(&sqlitef);

    sql = QString(
        "delete from agyogyofo;\n"
        "delete from aind;\n"
        "delete from alpha;\n"
        "delete from bfereghajtas;\n"
        "delete from bgyogykezeles;\n"
        "delete from blabor;\n"
        "delete from bmutet;\n"
        "delete from brtg;\n"
        "delete from bvakcinazas;\n"
        "delete from laltatas;\n"
        "delete from lanamnesis;\n"
        "delete from lattach;\n"
        "delete from lbeavatkozasaltalanos;\n"
        "delete from ldiagnosisaltalanos;\n"
        "delete from ldiagnozismutet;\n"
        "delete from lleirasmutet;\n"
//        "delete from lpanel;\n"
        "delete from ltunetekaltalanos;\n"
        "delete from xafaj;\n"
        "delete from xafajta;\n"
        "delete from xaivar;\n"
        "delete from xaszin;\n"
        "delete from xbfereghajtok;\n"
        "delete from xblabor;\n"
        "delete from xbvakcinak;\n"
        "delete from xdokik;\n"
        "delete from xsettings;\n"
        "delete from xtisz;\n"
        "delete from xtkerulet;\n"
        "delete from xttelepules;\n"
        "delete from xtutca;\n"
        "delete from yallat;\n"
        "delete from yamegjegyzes;\n"
        "delete from ykommunikacio;\n"
        "delete from ytmegjegyzes;\n"
        "delete from ytulajdonos;\n"
        );
    out << sql;

    QFile mysql(sif);
    if (mysql.open(QFile::ReadOnly)) {
        QTextStream stream(&mysql);
        stream.setCodec("ISO8859-2");
        QString line;
        QRegExp rx("\\b(LOCK TABLES)\\b");
        QRegExp rx1("\\t");

        QString tabla = "";

        int i = 1;
        do {
            line = stream.readLine();
            if(rx.indexIn(line)==0){
                line.replace("LOCK TABLES", "");
                line.replace("WRITE", "");
                line.replace(";", "");
                line.replace(" ", "");
                line.replace("á", "a");
                line.replace("é", "e");
                line.replace("í", "i");
                line.replace("ó", "o");
                line.replace("ü", "u");
                line.replace("ű", "u");
                tabla = line.replace("`", "");
                if (tabla.left(2) =="bm"){
                    tabla = "bmutet";
                } else if (tabla.left(11) =="ldiagnozism"){
                    tabla = "ldiagnozismutet";
                } else if (tabla.left(8) =="lleirasm"){
                    tabla = "lleirasmutet";
                }

                qDebug() << tabla;
            }
            if (tabla=="alpha"){
                QString l2 = "";
                if (line.contains("VALUES (")){
                    QStringList sl = line.split("VALUES ");
                    l2 = sl[1];
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    l2.replace(" 00:00:00","");
                    sql = QString("insert into alpha values %1;\n").arg(l2);
                    out << sql;
                } else if (rx1.indexIn(line)==0){
                    l2 = line;
                    l2.replace("\t", "");
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    l2.replace(" 00:00:00","");
                    sql = QString("insert into alpha values %1;\n").arg(l2);
                    out << sql;
                }
            }
            if (tabla=="bfereghajtas"){
                QString l2 = "";
                if (line.contains("VALUES (")){
                    QStringList sl = line.split("VALUES ");
                    l2 = sl[1];
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                } else if (rx1.indexIn(line)==0){
                    l2 = line;
                    l2.replace("\t", "");
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                }
            }
            if (tabla=="bgyogykezeles"){
                QString l2 = "";
                if (line.contains("VALUES (")){
                    QStringList sl = line.split("VALUES ");
                    l2 = sl[1];
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                } else if (rx1.indexIn(line)==0){
                    l2 = line;
                    l2.replace("\t", "");
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                }
            }
            if (tabla=="blabor"){
                QString l2 = "";
                if (line.contains("VALUES (")){
                    QStringList sl = line.split("VALUES ");
                    l2 = sl[1];
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                } else if (rx1.indexIn(line)==0){
                    l2 = line;
                    l2.replace("\t", "");
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                }
            }
            if (tabla =="bmutet"){
                QString l2 = "";
                if (line.contains("VALUES (")){
                    QStringList sl = line.split("VALUES ");
                    l2 = sl[1];
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                } else if (rx1.indexIn(line)==0){
                    l2 = line;
                    l2.replace("\t", "");
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                }
            }
            if (tabla=="brtg"){
                QString l2 = "";
                if (line.contains("VALUES (")){
                    QStringList sl = line.split("VALUES ");
                    l2 = sl[1];
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                } else if (rx1.indexIn(line)==0){
                    l2 = line;
                    l2.replace("\t", "");
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                }
            }
            if (tabla=="bvakcinazas"){
                QString l2 = "";
                if (line.contains("VALUES (")){
                    QStringList sl = line.split("VALUES ");
                    l2 = sl[1];
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                } else if (rx1.indexIn(line)==0){
                    l2 = line;
                    l2.replace("\t", "");
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                }
            }
            if (tabla=="laltatas" or tabla=="lanamnesis" or
                tabla=="lbeavatkozasaltalanos" or tabla=="ldiagnosisaltalanos" or
                tabla=="ldiagnozismutet" or tabla=="lleirasmutet" or tabla=="ltunetekaltalanos"){
                QString l2 = "";
                if (line.contains("VALUES (")){
                    QStringList sl = line.split("VALUES ");
                    l2 = sl[1];
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                } else if (rx1.indexIn(line)==0){
                    l2 = line;
                    l2.replace("\t", "");
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                }
            }
            if (tabla=="xbfereghajtok" or tabla=="xbvakcinak" or tabla=="xttelepules" or
                tabla=="xafaj" or tabla=="xafajta" or tabla=="xaivar" or tabla=="xaszin"){
                QString l2 = "";
                if (line.contains("VALUES (")){
                    QStringList sl = line.split("VALUES ");
                    l2 = sl[1];
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    l2.replace("(", "(1,");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                } else if (rx1.indexIn(line)==0){
                    l2 = line;
                    l2.replace("\t", "");
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    l2.replace("(", "(1,");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                }
            }
            if (tabla=="xblabor" or tabla=="xdokik" or tabla=="xtisz" or tabla=="xtkerulet" or tabla=="xtutca" or
                tabla=="ykommunikacio" or tabla=="ytmegjegyzes" or tabla=="ytulajdonos" or tabla=="yamegjegyzes"){
                QString l2 = "";
                if (line.contains("VALUES (")){
                    QStringList sl = line.split("VALUES ");
                    l2 = sl[1];
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                } else if (rx1.indexIn(line)==0){
                    l2 = line;
                    l2.replace("\t", "");
                    l2.replace("),", ")");
                    l2.replace(");", ")");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    out << sql;
                }
            }
            if (tabla=="yallat"){
                QString l2 = "";
                if (line.contains("VALUES (")){
                    QStringList sl = line.split("VALUES ");
                    l2 = sl[1];
                    l2.replace(" 00:00:00","");
                    l2.replace("),", ")");
                    //l2.replace(");", ",)");
                    l2.replace("(", "('',");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    sql.replace(");", ",'');");
                    out << sql;
                } else if (rx1.indexIn(line)==0){
                    l2 = line;
                    l2.replace(" 00:00:00","");
                    l2.replace("\t", "");
                    l2.replace("),", ")");
                    //l2.replace(");", ",)");
                    l2.replace("(", "('',");
                    sql = QString("insert into %1 values %2;\n").arg(tabla).arg(l2);
                    sql.replace(");", ",'');");
                    out << sql;
                }
            }
            i++;
        } while (!line.isNull());
    }
    mysql.close();


    QApplication::restoreOverrideCursor();
}

void frmImporter::sourcePath(){
    QString fn = QFileDialog::getOpenFileName(this, tr("Forrás"), QDir::currentPath(), tr("Minden fájl (*.*)"));
    ui->lineEdit->setText(fn);
}

void frmImporter::destPath(){
    QString fn = QFileDialog::getOpenFileName(this, tr("Cél"), QDir::currentPath(), tr("Minden fájl (*.*)"));
    ui->lineEdit_2->setText(fn);
}


frmImporter::~frmImporter()
{
    delete ui;
}

void frmImporter::changeEvent(QEvent *e)
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
