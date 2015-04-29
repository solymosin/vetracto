#include <QApplication>
#include <QtSql>
#include <QDesktopServices>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextTableCell>
#include <QTextEdit>

#include "vtrcodes.h"

vtrcodes::vtrcodes()
{
}

//kommunikacio
void vtrcodes::kommRec(QString tulaj, QString tool, QString cim){
    QSqlQuery query;
    QString sql = "insert into ykommunikacio (tulajdonos, eszkoz, cim) "
        "VALUES (?, ?, ?)";

    query.prepare(sql);
    query.addBindValue(tulaj);
    query.addBindValue(tool);
    query.addBindValue(cim);
    query.exec();
}

void vtrcodes::kommMod(QString id, QString tool, QString cim){
    QString sql = QString("update ykommunikacio set eszkoz='%1', cim='%2' where az=%3").arg(tool).arg(cim).arg(id);
    QSqlQuery query(sql);
}

void vtrcodes::kommDel(QString id){
    QString sql = QString("delete from ykommunikacio where az=%1;").arg(id);
    QSqlQuery query(sql);
}

//DB
void vtrcodes::itemEdit(QString sql){
    QSqlQuery query(sql);
}


void vtrcodes::fajCleaner(){

    QString sql1 = "select faj, count(az) as db from xafaj group by faj;";
    QSqlQuery query1(sql1);

    while (query1.next()){
        if (query1.value(1).toInt()>1){
            QString sql2 = QString("select faj, az from xafaj where faj='%1';").arg(query1.value(0).toString());
            QSqlQuery query2(sql2);
            query2.first();
            QString nID = query2.value(1).toString();
            while (query2.next()){
                QString oID = query2.value(1).toString();
                QString sql3 = QString("update xafajta set faj=%1 where faj=%2;").arg(nID).arg(oID);
                QSqlQuery query3(sql3);
                QString sql4 = QString("delete from xafaj where az=%1;").arg(oID);
                QSqlQuery query4(sql4);
            }
        }
    }
}

void vtrcodes::fajtaCleaner(){

    QString sql1 = "select fajta, count(az) as db from xafajta group by fajta;";
    QSqlQuery query1(sql1);

    while (query1.next()){
        if (query1.value(1).toInt()>1){
            QString sql2 = QString("select fajta, az from xafajta where fajta='%1';").arg(query1.value(0).toString());
            QSqlQuery query2(sql2);
            query2.first();
            QString nID = query2.value(1).toString();
            while (query2.next()){
                QString oID = query2.value(1).toString();
                QString sql3 = QString("update yallat set fajta=%1 where fajta=%2;").arg(nID).arg(oID);
                QSqlQuery query3(sql3);
                QString sql4 = QString("delete from xafajta where az=%1;").arg(oID);
                QSqlQuery query4(sql4);
            }
        }
    }
}

void vtrcodes::szinCleaner(){

    QString sql1 = "select szin, count(az) as db from xaszin group by szin;";
    QSqlQuery query1(sql1);

    while (query1.next()){
        if (query1.value(1).toInt()>1){
            QString sql2 = QString("select szin, az from xaszin where szin='%1';").arg(query1.value(0).toString());
            QSqlQuery query2(sql2);
            query2.first();
            QString nID = query2.value(1).toString();
            while (query2.next()){
                QString oID = query2.value(1).toString();
                QString sql3 = QString("update yallat set szin=%1 where szin=%2;").arg(nID).arg(oID);
                QSqlQuery query3(sql3);
                QString sql4 = QString("delete from xaszin where az=%1;").arg(oID);
                QSqlQuery query4(sql4);
            }
        }
    }
}

void vtrcodes::ivarCleaner(){

    QString sql1 = "select ivar, count(az) as db from xaivar group by ivar;";
    QSqlQuery query1(sql1);

    while (query1.next()){
        if (query1.value(1).toInt()>1){
            QString sql2 = QString("select ivar, az from xaivar where ivar='%1';").arg(query1.value(0).toString());
            QSqlQuery query2(sql2);
            query2.first();
            QString nID = query2.value(1).toString();
            while (query2.next()){
                QString oID = query2.value(1).toString();
                QString sql3 = QString("update yallat set ivar=%1 where ivar=%2;").arg(nID).arg(oID);
                QSqlQuery query3(sql3);
                QString sql4 = QString("delete from xaivar where az=%1;").arg(oID);
                QSqlQuery query4(sql4);
            }
        }
    }
}

void vtrcodes::archivalMind(QString ut){
    QString archut = QString("%1/vtrarch%2").arg(ut).arg(QDate::currentDate().toString("yyyyMMdd"));
    QString attfsut = QString("%1/attfs").arg(QApplication::applicationDirPath());
    QDir attfsdir(attfsut);
    QDir archdir(archut);
    if(!archdir.exists()){
        archdir.mkdir(archut);
    }
    QString forrasf = QString("%1/vtrdb.db").arg(QApplication::applicationDirPath());
    QString celf = QString("%1/vtrdb.db").arg(archut);
    QFile file(forrasf);
    file.copy(celf);

    archut.append("/attfs");
    QDir attfs(archut);
    if(!attfs.exists()){
        attfs.mkdir(archut);
    }

    QStringList flist = attfsdir.entryList(QDir::Files, QDir::Name);
    for(int i=0; i!=flist.count(); i++){
        forrasf = QString("%1/%2").arg(attfsut).arg(flist[i]);
        celf = QString("%1/%2").arg(archut).arg(flist[i]);
        file.setFileName(forrasf);
        file.copy(celf);
    }
}

void vtrcodes::dbkontroll(){
    QString sql = QString("Select * from yallat");
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    int n = record.indexOf("booknum");

    if (n==-1){
        sql = "ALTER TABLE yallat ADD booknum NUMERIC";
        query.exec(sql);
    }

//    n = record.indexOf("elo");
//
//    if (n==-1){
//        sql = "ALTER TABLE yallat ADD elo NUMERIC";
//        query.exec(sql);
//        sql = "update yallat set elo=1";
//        query.exec(sql);
//    }
//    9000000
}

void vtrcodes::dbclean(){
    QString sql = "select max(xttelepules.az) as maz from xtisz inner join xttelepules on xtisz.telepules=xttelepules.az";
    QSqlQuery query(sql);
    query.first();
    QString maxid = query.value(0).toString();
    sql = QString("delete from xttelepules where az>%1;").arg(maxid);
    query.exec(sql);
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx01 ON alpha (az);");
    query.exec("CREATE INDEX IF NOT EXISTS idx02 ON alpha (datum);");
    query.exec("CREATE INDEX IF NOT EXISTS idx03 ON alpha (torzsszam);");
    query.exec("CREATE INDEX IF NOT EXISTS idx04 ON alpha (allatorvos);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx05 ON bfereghajtas (az);");
    query.exec("CREATE INDEX IF NOT EXISTS idx06 ON bfereghajtas (alphaaz);");
    query.exec("CREATE INDEX IF NOT EXISTS idx07 ON bfereghajtas (fereghajto);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx08 ON bgyogykezeles (az);");
    query.exec("CREATE INDEX IF NOT EXISTS idx09 ON bgyogykezeles (alphaaz);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx10 ON blabor (az);");
    query.exec("CREATE INDEX IF NOT EXISTS idx11 ON blabor (alphaaz);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx12 ON bmutet (az);");
    query.exec("CREATE INDEX IF NOT EXISTS idx13 ON bmutet (alphaaz);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx14 ON brtg (az);");
    query.exec("CREATE INDEX IF NOT EXISTS idx15 ON brtg (alphaaz);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx16 ON bvakcinazas (az);");
    query.exec("CREATE INDEX IF NOT EXISTS idx17 ON bvakcinazas (alphaaz);");
    query.exec("CREATE INDEX IF NOT EXISTS idx18 ON bvakcinazas (vakcina);");
    query.exec("CREATE INDEX IF NOT EXISTS idx19 ON bvakcinazas (tipus);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx20 ON laltatas (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx21 ON lanamnesis (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx22 ON lattach (id);");
    query.exec("CREATE INDEX IF NOT EXISTS idx23 ON lattach (alphaz);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx24 ON lbeavatkozasaltalanos (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx25 ON ldiagnosisaltalanos (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx26 ON ldiagnozismutet (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx27 ON lleirasmutet (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx28 ON lpanel (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx29 ON ltunetekaltalanos (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx30 ON xafaj (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx31 ON xafajta (az);");
    query.exec("CREATE INDEX IF NOT EXISTS idx32 ON xafajta (faj);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx33 ON xaivar (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx34 ON xaszin (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx35 ON xbfereghajtok (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx36 ON xblabor (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx37 ON xbvakcinak (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx38 ON xdokik (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx39 ON xsettings (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx40 ON xtisz (az);");
    query.exec("CREATE INDEX IF NOT EXISTS idx41 ON xtisz (telepules);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx42 ON xtkerulet (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx43 ON xttelepules (az);");
    query.exec("CREATE INDEX IF NOT EXISTS idx44 ON xttelepules (telepules);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx45 ON xtutca (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx46 ON yallat (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx47 ON yallat (torzsszam);");
    query.exec("CREATE INDEX IF NOT EXISTS idx48 ON yallat (tulajdonos);");
    query.exec("CREATE INDEX IF NOT EXISTS idx49 ON yallat (ivar);");
    query.exec("CREATE INDEX IF NOT EXISTS idx50 ON yallat (fajta);");
    query.exec("CREATE INDEX IF NOT EXISTS idx51 ON yallat (szin);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx52 ON yamegjegyzes (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx53 ON yamegjegyzes (torzsszam);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx54 ON ykommunikacio (az);");
    query.exec("CREATE INDEX IF NOT EXISTS idx55 ON ykommunikacio (tulajdonos);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx56 ON ytmegjegyzes (az);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx57 ON ytmegjegyzes (tulajszam);");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx58 ON ytulajdonos (az);");
    query.exec("CREATE INDEX IF NOT EXISTS idx59 ON ytulajdonos (helyseg);");
    query.exec("CREATE INDEX IF NOT EXISTS idx60 ON ytulajdonos (utca);");

    ivarCleaner();
    szinCleaner();
    fajtaCleaner();
    fajCleaner();


}


//DOKIK
void vtrcodes::dokiRec(QString nev, QString tel, QString aktiv){
    QSqlQuery query;
    QString sql = "insert into xdokik (doki, telefon, aktiv) "
        "VALUES (?, ?, ?)";

    query.prepare(sql);
    query.addBindValue(nev);
    query.addBindValue(tel);
    query.addBindValue(aktiv);
    query.exec();
}

void vtrcodes::dokiMod(QString nev, QString tel, QString aktiv, QString id){
    QString sql = QString(
       "update xdokik set doki = '%1', telefon = '%2', aktiv = '%3' where az = %4"
        ).arg(nev).arg(tel).arg(aktiv).arg(id);
    QSqlQuery query(sql);
}



//QUERIES
int vtrcodes::vaccNumer(QString sql){
    QSqlQuery queryN(sql);
    int rows = 0;
    while (queryN.next()) {
        rows++;
    }
    return rows;
}


void vtrcodes::reporter01(int rows, QString doki, QString sd, QString ed, QString isz, QString hely, QString path){
    QString telepules = "Budapest";
    QString tsd = sd;
    QString ted = ed;

    QTextEdit *text = new QTextEdit;
    text->clear();

    QTextCursor cursor(text->textCursor());
    cursor.movePosition(QTextCursor::Start);

    QTextCharFormat textFormat;
    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    QTextCharFormat italicFormat;
    italicFormat.setFontItalic(true);
    QTextCharFormat cellFormat;
    cellFormat.setFontPointSize(7);

    QString sql02 = QString("Select bvakcinazas.sorszama, alpha.datum, ytulajdonos.nev, xtisz.isz, xttelepules.telepules, "
        "xtutca.utca, ytulajdonos.hea, xafajta.fajta, xaszin.szin, yallat.hivonev, xaivar.ivar, "
        "yallat.szuletett, xbvakcinak.oltoanyag, yallat.chip, yallat.booknum "
        "From bvakcinazas Inner Join alpha On alpha.az = bvakcinazas.alphaaz Inner Join xdokik On xdokik.az = alpha.allatorvos Inner Join yallat On yallat.torzsszam = alpha.torzsszam Inner Join ytulajdonos On ytulajdonos.az = yallat.tulajdonos Inner Join xtisz On xtisz.az = ytulajdonos.helyseg Inner Join xttelepules On xttelepules.az = xtisz.telepules Inner Join xbvakcinak On xbvakcinak.az = bvakcinazas.vakcina Inner Join xtutca On xtutca.az = ytulajdonos.utca Inner Join xafajta On xafajta.az = yallat.fajta Inner Join xaszin On xaszin.az = yallat.szin Inner Join xaivar On xaivar.az = yallat.ivar "
        "Where (bvakcinazas.tipus = 1) "
        "And (xdokik.doki = '%1') "
        "And (alpha.datum between '%2' and '%3') "
        "And (substr(xtisz.isz,2,2) = '%4') "
        "And (xttelepules.telepules = '%5') "
        "Order By bvakcinazas.sorszama").arg(doki).arg(sd).arg(ed).arg(isz).arg(hely);
    QSqlQuery query02(sql02);

    if (hely == "Budapest"){
        hely = qDistrict(hely, isz);
    }

    text->setAlignment(Qt::AlignCenter);
    cursor.insertText("Veszettség elleni védőoltások", boldFormat);
    cursor.insertBlock();
    cursor.insertText(QString("%1, %2. - %3.").arg(hely).arg(tsd.replace("-",".")).arg(ted.replace("-",".")), boldFormat);
    cursor.insertBlock();

    text->setAlignment(Qt::AlignLeft);

    QTextTableFormat tableFormat;
    tableFormat.setBorder(0);
    tableFormat.setCellPadding(2);
    tableFormat.setAlignment(Qt::AlignLeft);
    tableFormat.setHeaderRowCount(1);

    QStringList headers;
    QTextCharFormat tableHeaderFormat;
    tableHeaderFormat.setBackground( QColor( "#DADADA" ) );

    headers << "Sorszám" << "Dátum" << "Könyv" << "Chip"
            << "Tulajdonos neve és az állat tartási helye" << "Fajta"
            << "Szín" << "Hívónév" << "Ivar" << "Született" << "Oltóanyag";

    const int columns = headers.count();

    QTextTable* textTable = cursor.insertTable( rows+1, columns, tableFormat );

    int row=0;
    for(int column = 0; column < columns; column++ ){
        QTextTableCell cell = textTable->cellAt( row, column );
        Q_ASSERT( cell.isValid() );
        cell.setFormat( tableHeaderFormat );
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.insertText( headers[column] );
    }
    row++;

    while (query02.next()){
                QStringList fields;
                fields << QString("%1.").arg(query02.value(0).toString())
                       << QString("%1.").arg(query02.value(1).toString().replace("-","."))
                       << QString("%1.").arg(query02.value(14).toString())
                       << QString("%1.").arg(query02.value(13).toString())
                       << QString("%1, %2 %3, %4 %5")
                               .arg(query02.value(2).toString())
                               .arg(query02.value(3).toString())
                               .arg(query02.value(4).toString())
                               .arg(query02.value(5).toString())
                               .arg(query02.value(6).toString())
                       << QString("%1").arg(query02.value(7).toString())
                       << QString("%1").arg(query02.value(8).toString())
                       << QString("%1").arg(query02.value(9).toString())
                       << QString("%1").arg(query02.value(10).toString())
                       << QString("%1.").arg(query02.value(11).toString().replace("-","."))
                       << QString("%1").arg(query02.value(12).toString());

                for(int column = 0; column < fields.count(); column++ ){
                    QTextTableCell cell = textTable->cellAt(row, column);
                    Q_ASSERT(cell.isValid());
                    QTextCursor cellCursor = cell.firstCursorPosition();
                    cellCursor.insertText(fields[column], cellFormat);
                }
                row++;
//        QString sor = QString("%1;%2;%3, %4 %5, %6 %7;%8;%9;%10;%11;%12;%13")
//        .arg(query02.value(0).toString())
//        .arg(query02.value(1).toString())
//        .arg(query02.value(2).toString())
//        .arg(query02.value(3).toString())
//        .arg(query02.value(4).toString())
//        .arg(query02.value(5).toString())
//        .arg(query02.value(6).toString())
//        .arg(query02.value(7).toString())
//        .arg(query02.value(8).toString())
//        .arg(query02.value(9).toString())
//        .arg(query02.value(10).toString())
//        .arg(query02.value(11).toString())
//        .arg(query02.value(12).toString());
//        qDebug() << sor;
    }
//            qDebug() << row;

    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertText(QString("Ebek száma: %1").arg(rows), boldFormat);
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertText(QString("%1, %2").arg(telepules).arg(QDate::currentDate().toString("yyyy.MM.dd.")), boldFormat);
    cursor.insertBlock();
    text->setAlignment(Qt::AlignRight);
    cursor.insertText(QString("%1").arg(doki), italicFormat);

    QTextDocument *report = text->document();

    QDir reportsdir(path);
    if(!reportsdir.exists()){
        reportsdir.mkdir(path);
//        return;
    }

    QString repfile = QString("%1/%2_%3.pdf").arg(reportsdir.absolutePath()).arg(doki).arg(hely);

    QPrinter printer;
//    printer.setPageMargins(50,20,20,20,QPrinter::Inch);
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFileName(repfile);
    printer.setFullPage(true);
    report->print(&printer);
}


void vtrcodes::RabiesReport(QString sd, QString ed, QString path){
    QString sql = QString("Select count(xttelepules.telepules) "
        "From bvakcinazas Inner Join alpha On alpha.az = bvakcinazas.alphaaz Inner Join xdokik On xdokik.az = alpha.allatorvos Inner Join yallat On yallat.torzsszam = alpha.torzsszam Inner Join ytulajdonos On ytulajdonos.az = yallat.tulajdonos Inner Join xtisz On xtisz.az = ytulajdonos.helyseg Inner Join xttelepules On xttelepules.az = xtisz.telepules "
        "Where bvakcinazas.tipus = 1 And alpha.datum between '%1' and '%2'").arg(sd).arg(ed);
    QSqlQuery query(sql);
    query.first();
    int helysegszam = query.value(0).toInt();
    if (helysegszam != 0){
        QString sql01 = "";
//        QString sql02 = "";
        QString doki = "";
        QString isz = "";
        QString hely = "";

        sql01 = QString("Select distinct xdokik.doki, substr(xtisz.isz,2,2), xttelepules.telepules "
            "From bvakcinazas Inner Join alpha On alpha.az = bvakcinazas.alphaaz Inner Join xdokik On xdokik.az = alpha.allatorvos Inner Join yallat On yallat.torzsszam = alpha.torzsszam Inner Join ytulajdonos On ytulajdonos.az = yallat.tulajdonos Inner Join xtisz On xtisz.az = ytulajdonos.helyseg Inner Join xttelepules On xttelepules.az = xtisz.telepules "
            "Where bvakcinazas.tipus = 1 And alpha.datum between '%1' and '%2' "
            "order by xdokik.doki, xttelepules.telepules, substr(xtisz.isz,2,2)").arg(sd).arg(ed);
//        qDebug() << sql01;
        QSqlQuery query01(sql01);

        while (query01.next()) {
            doki = query01.value(0).toString();
            isz = query01.value(1).toString();
            hely = query01.value(2).toString();

            QString sqlN = QString("Select bvakcinazas.sorszama "
                "From bvakcinazas Inner Join alpha On alpha.az = bvakcinazas.alphaaz Inner Join xdokik On xdokik.az = alpha.allatorvos Inner Join yallat On yallat.torzsszam = alpha.torzsszam Inner Join ytulajdonos On ytulajdonos.az = yallat.tulajdonos Inner Join xtisz On xtisz.az = ytulajdonos.helyseg Inner Join xttelepules On xttelepules.az = xtisz.telepules Inner Join xbvakcinak On xbvakcinak.az = bvakcinazas.vakcina Inner Join xtutca On xtutca.az = ytulajdonos.utca Inner Join xafajta On xafajta.az = yallat.fajta Inner Join xaszin On xaszin.az = yallat.szin Inner Join xaivar On xaivar.az = yallat.ivar "
                "Where (bvakcinazas.tipus = 1) "
                "And (xdokik.doki = '%1') "
                "And (alpha.datum between '%2' and '%3') "
                "And (substr(xtisz.isz,2,2) = '%4') "
                "And (xttelepules.telepules = '%5') "
                "Order By bvakcinazas.sorszama").arg(doki).arg(sd).arg(ed).arg(isz).arg(hely);

//            qDebug() << sqlN;

            int rows = vaccNumer(sqlN);
//            qDebug() << rows;
            if (rows>0){
                reporter01(rows, doki, sd, ed, isz, hely, path);
            }
        }
    }
}





QString vtrcodes::qDistrict(QString hely, QString isz){
    switch(isz.toInt()){
    case 1:
        hely = hely + " I. kerület";
        break;
    case 2:
        hely = hely + " II. kerület";
        break;
    case 3:
        hely = hely + " III. kerület";
        break;
    case 4:
        hely = hely + " IV. kerület";
        break;
    case 5:
        hely = hely + " V. kerület";
        break;
    case 6:
        hely = hely + " VI. kerület";
        break;
    case 7:
        hely = hely + " VII. kerület";
        break;
    case 8:
        hely = hely + " VIII. kerület";
        break;
    case 9:
        hely = hely + " IX. kerület";
        break;
    case 10:
        hely = hely + " X. kerület";
        break;
    case 11:
        hely = hely + " XI. kerület";
        break;
    case 12:
        hely = hely + " XII. kerület";
        break;
    case 13:
        hely = hely + " XIII. kerület";
        break;
    case 14:
        hely = hely + " XIV. kerület";
        break;
    case 15:
        hely = hely + " XV. kerület";
        break;
    case 16:
        hely = hely + " XVI. kerület";
        break;
    case 17:
        hely = hely + " XVII. kerület";
        break;
    case 18:
        hely = hely + " XVIII. kerület";
        break;
    case 19:
        hely = hely + " XIX. kerület";
        break;
    case 20:
        hely = hely + " XX. kerület";
        break;
    case 21:
        hely = hely + " XXI. kerület";
        break;
    case 22:
        hely = hely + " XXII. kerület";
        break;
    case 23:
        hely = hely + " XXIII. kerület";
        break;
    }
    return hely;
}



// FÉREGHAJTÁS
QString vtrcodes::fereghajtoIDentify(const QString& fereghajto){

    QString ID;
    QString sql = QString("Select count(az) as n from xbfereghajtok where fereghajto = '%1'").arg(fereghajto);
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    query.first();
    int n = query.value(record.indexOf("n")).toInt();

    if (n==0){
        fereghajtoRec(fereghajto);
    }

    ID = fereghajtoIDkeres(fereghajto);

    return ID;
}

QString vtrcodes::fereghajtoIDkeres(const QString& fereghajto){

    QString sql = QString("Select az from xbfereghajtok where fereghajto = '%1'").arg(fereghajto);
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    query.first();
    QString ID = query.value(record.indexOf("az")).toString();

    return ID;
}

void vtrcodes::fereghajtoRec(const QString& fereghajto){

    QSqlQuery query;
    QString sql = "insert into xbfereghajtok (fereghajto,aktiv) "
        "VALUES (?, 1)";

    query.prepare(sql);
    query.addBindValue(fereghajto);
    query.exec();

}

void vtrcodes::fereghajtasRec(const QString& alphaID, const QString& fereghajtoID){

    QSqlQuery query;
    QString sql = "insert into bfereghajtas (alphaaz, fereghajto) "
        "VALUES (?, ?)";

    query.prepare(sql);
    query.addBindValue(alphaID);
    query.addBindValue(fereghajtoID);
    query.exec();

}


// VAKCINÁZÁS
QString vtrcodes::vakcinaIDentify(const QString& vakcina){

    QString ID;
    QString sql = QString("Select count(az) as n from xbvakcinak where oltoanyag = '%1'").arg(vakcina);
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    query.first();
    int n = query.value(record.indexOf("n")).toInt();

    if (n==0){
        vakcinaRec(vakcina);
    }

    ID = vakcinaIDkeres(vakcina);

    return ID;
}

QString vtrcodes::vakcinaIDkeres(const QString& vakcina){

    QString sql = QString("Select az from xbvakcinak where oltoanyag = '%1'").arg(vakcina);
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    query.first();
    QString ID = query.value(record.indexOf("az")).toString();

    return ID;
}

void vtrcodes::vakcinaRec(const QString& vakcina){

    QSqlQuery query;
    QString sql = "insert into xbvakcinak (oltoanyag,aktiv) "
        "VALUES (?, 1)";

    query.prepare(sql);
    query.addBindValue(vakcina);
    query.exec();

}

void vtrcodes::vakcinazasRec(const QString& alphaID, const QString& vakcinaID, const int vakcinatipus, const int sorszam){

    QSqlQuery query;
    QString sql = "insert into bvakcinazas (alphaaz,vakcina,tipus,sorszama) "
        "VALUES (?, ?, ?, ?)";

    query.prepare(sql);
    query.addBindValue(alphaID);
    query.addBindValue(vakcinaID);
    query.addBindValue(vakcinatipus);
    query.addBindValue(sorszam);
    query.exec();

}

//attachment
void vtrcodes::attachFile(QString path, QString datum, QString lab, QString typ, QString allat_az, QString doki){
    QFile file( path );
    if(!file.exists()){
        return;
    }

    QString csatf = QString("%1/attfs").arg(QApplication::applicationDirPath());
    QDir attdir(csatf);
    if(!attdir.exists()){
        attdir.mkdir(csatf);
//        return;
    }

    QFileInfo fi(path);

    QString alphaz = alphaIDentify2(doki, allat_az, datum);

    QSqlQuery query;
    QString sql = "insert into lattach (alphaz, lab, typ) values(?, ?, ?)";

    query.prepare(sql);
    query.addBindValue(alphaz);
    query.addBindValue(lab);
    query.addBindValue(typ);
    query.exec();

    sql = "select max(id) from lattach";
    query.exec(sql);
    query.first();
    QString attid = query.value(0).toString();
    QString newf = QString("%1.%2").arg(attid).arg(fi.completeSuffix());
    QString npath = QString("%1/%2").arg(attdir.absolutePath()).arg(newf);
    file.copy(npath);

    sql = QString("update lattach set filen = '%1' where id = %2").arg(newf).arg(attid);
    query.exec(sql);
}


void vtrcodes::attachedShow(QString datum, QString lab, QString typ, QString allat_az){
    QString csatf = QString("%1/attfs").arg(QApplication::applicationDirPath());
    QDir attdir(csatf);
    if(!attdir.exists()){
        attdir.mkdir(csatf);
    }

    QString sql = QString("Select lattach.filen "
        "From lattach Inner Join alpha On alpha.az = lattach.alphaz "
        "Where lattach.typ = '%1' And "
        "alpha.datum = '%2' And "
        "lattach.lab = '%3' And "
        "alpha.torzsszam = %4").arg(typ).arg(datum).arg(lab).arg(allat_az);

    QSqlQuery query(sql);
    query.first();

//    QString attachment = QString("file://%1/%2").arg(attdir.absolutePath()).arg(query.value(0).toString());
    QString attachment = QString("%1/%2").arg(attdir.absolutePath()).arg(query.value(0).toString());
    QUrl url = QUrl::fromLocalFile(attachment);
    QDesktopServices::openUrl(url);
//    QDesktopServices::openUrl(QUrl(attachment, QUrl::TolerantMode));
}

void vtrcodes::attachedShow(QString datum, QString lab, QString allat_az){
    QString csatf = QString("%1/attfs").arg(QApplication::applicationDirPath());
    QDir attdir(csatf);
    if(!attdir.exists()){
        attdir.mkdir(csatf);
    }

    QString sql = QString("Select lattach.filen "
        "From lattach Inner Join alpha On alpha.az = lattach.alphaz "
        "Where alpha.datum = '%1' And "
        "lattach.lab = '%2' And "
        "alpha.torzsszam = %3").arg(datum).arg(lab).arg(allat_az);

    QSqlQuery query(sql);
    query.first();

    QString attachment = QString("%1/%2").arg(attdir.absolutePath()).arg(query.value(0).toString());
    QUrl url = QUrl::fromLocalFile(attachment);
    QDesktopServices::openUrl(url);
}



// ALPHA
QString vtrcodes::alphaIDentify(const QString& doki, const QString& allatID, const QString& datum){
    QString alphaID;
    QString sql = QString(
        "Select count(alpha.az) as n "
        "From alpha Inner Join xdokik On xdokik.az = alpha.allatorvos "
        "Where alpha.datum = '%1' And alpha.torzsszam = %2 And xdokik.doki = '%3'"
        ).arg(datum).arg(allatID).arg(doki);
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    query.first();
    int n = query.value(record.indexOf("n")).toInt();

    if (n==0){
        alphaRec(doki, allatID, datum);
    }

    alphaID = alphaIDkeres(doki, allatID, datum);

    return alphaID;
}

QString vtrcodes::alphaIDkeres(const QString& doki, const QString& allatID, const QString& datum){
    QString alphaID;
    QString sql = QString(
        "Select alpha.az "
        "From alpha Inner Join xdokik On xdokik.az = alpha.allatorvos "
        "Where alpha.datum = '%1' And alpha.torzsszam = %2 And xdokik.doki = '%3'"
        ).arg(datum).arg(allatID).arg(doki);
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    query.first();
    alphaID = query.value(record.indexOf("az")).toString();

    return alphaID;
}

void vtrcodes::alphaRec(const QString& doki, const QString& allatID, const QString& datum){
    QString sql = QString(
        "select az from xdokik where doki ='%1'"
        ).arg(doki);
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    query.first();
    int dokiaz = query.value(record.indexOf("az")).toInt();

    sql = "insert into alpha (datum,torzsszam,allatorvos) values(?,?,?)";
    query.prepare(sql);
    query.addBindValue(datum);
    query.addBindValue(allatID);
    query.addBindValue(dokiaz);
    query.exec();
}

QString vtrcodes::alphaIDentify2(const QString& doki, const QString& allatID, const QString& datum){
    QString alphaID;
    QString sql = QString(
        "Select count(az) as n From alpha Where datum = '%1' And torzsszam = %2"
        ).arg(datum).arg(allatID);
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    query.first();
    int n = query.value(record.indexOf("n")).toInt();

    if (n==0){
        alphaRec(doki, allatID, datum);
    }

    alphaID = alphaIDkeres2(allatID, datum);

    return alphaID;
}

QString vtrcodes::alphaIDkeres2(const QString& allatID, const QString& datum){
    QString alphaID;
    QString sql = QString(
        "Select az From alpha Where datum = '%1' And torzsszam = %2"
        ).arg(datum).arg(allatID);
    QSqlQuery query(sql);
    query.first();
    alphaID = query.value(0).toString();

    return alphaID;
}

//MEGJEGYZES
void vtrcodes::allatMegjegyzRec(const QString& trsz, const QString& megjegyzes){
    QString sql = QString("select count(az) from yamegjegyzes where torzsszam=%1").arg(trsz);
    QSqlQuery query(sql);
    query.first();
    int van = query.value(0).toInt();

    switch(van){
        case 0:
            sql = "insert into yamegjegyzes (torzsszam, megjegyzes) values(?, ?)";
            query.prepare(sql);
            query.addBindValue(trsz);
            query.addBindValue(megjegyzes);
            query.exec();
            break;
        case 1:
            sql = QString("update yamegjegyzes set megjegyzes='%1' where torzsszam=%2").arg(megjegyzes).arg(trsz);
            query.exec(sql);
            break;
    }
}

void vtrcodes::tulajMegjegyzRec(const QString& tsz, const QString& megjegyzes){
    QString sql = QString("select count(az) from ytmegjegyzes where tulajszam=%1").arg(tsz);
//    qDebug() << sql;
    QSqlQuery query(sql);
    query.first();
    int van = query.value(0).toInt();

    switch(van){
        case 0:
            sql = "insert into ytmegjegyzes (tulajszam, megjegyzes) values(?, ?)";
            query.prepare(sql);
            query.addBindValue(tsz);
            query.addBindValue(megjegyzes);
            query.exec();
            break;
        case 1:
            sql = QString("update ytmegjegyzes set megjegyzes='%1' where tulajszam=%2").arg(megjegyzes).arg(tsz);
            query.exec(sql);
            break;
    }
}


//PANEL
void vtrcodes::PanelRec(const QString& ek, const QString& nev, const QString& leiras){
    QSqlQuery query;
    QString sql = "insert into lpanel (ek, panel, descr) values(?, ?, ?)";

    query.prepare(sql);
    query.addBindValue(ek);
    query.addBindValue(nev);
    query.addBindValue(leiras);
    query.exec();
}

void vtrcodes::PanelMod(const QString& ek, const QString& onev, const QString& nev, const QString& leiras){
    QString sql = QString(
        "update lpanel set panel='%1', descr='%2' where ek='%3' and panel='%4'"
        ).arg(nev).arg(leiras).arg(ek).arg(onev);
    QSqlQuery query(sql);
}

//LABOR
void vtrcodes::laborRec(const QString& alphaID, const QString& pid, const QString& ertek){

    QSqlQuery query;
    QString sql = "insert into blabor (alphaaz,vizsgalat,ertek) "
        "VALUES (?, ?, ?)";

    query.prepare(sql);
    query.addBindValue(alphaID);
    query.addBindValue(pid);
    query.addBindValue(ertek);
    query.exec();
}

void vtrcodes::laborDel(const QString& rid){
    QSqlQuery query;
    QString sql = QString("delete from blabor where az = %1").arg(rid);
    query.exec(sql);
//    qDebug() << sql;
}

//KEZELÉS
void vtrcodes::KezelRec(const QString& alphaID, const QString& anamnesis, const QString& jelenallapot, const QString& diagnosis, const QString& gyogyszer, const QString& beavatkozas){

    QSqlQuery query;
    QString sql = "insert into bgyogykezeles (alphaaz,anamnesis,jelenallapot,diagnosis,gyogyszer,beavatkozas) "
        "VALUES (?, ?, ?, ?, ?, ? )";

    query.prepare(sql);
    query.addBindValue(alphaID);
    query.addBindValue(anamnesis);
    query.addBindValue(jelenallapot);
    query.addBindValue(diagnosis);
    query.addBindValue(gyogyszer);
    query.addBindValue(beavatkozas);
    query.exec();

}

void vtrcodes::KezelMod(const QString& alphaID, const QString& anamnesis, const QString& jelenallapot, const QString& diagnosis, const QString& gyogyszer, const QString& beavatkozas){

    QString sql = QString("update bgyogykezeles set anamnesis = '%1', "
        "jelenallapot = '%2', "
        "diagnosis = '%3', "
        "gyogyszer = '%4', "
        "beavatkozas = '%5' where alphaaz = %6").arg(anamnesis).arg(jelenallapot).arg(diagnosis).arg(gyogyszer).arg(beavatkozas).arg(alphaID);
    QSqlQuery query(sql);
}

//SEBÉSZET
void vtrcodes::SurgRec(const QString& alphaID, const QString& anamnesis, const QString& jelenallapot, const QString& diagnosis, const QString& gyogyszer, const QString& beavatkozas){

    QSqlQuery query;
    QString sql = "insert into bmutet (alphaaz, anamnesis, jelenallapot, diagnosis, leirasa, altatas) "
        "VALUES (?, ?, ?, ?, ?, ? )";

    query.prepare(sql);
    query.addBindValue(alphaID);
    query.addBindValue(anamnesis);
    query.addBindValue(jelenallapot);
    query.addBindValue(diagnosis);
    query.addBindValue(gyogyszer);
    query.addBindValue(beavatkozas);
    query.exec();

}

void vtrcodes::SurgMod(const QString& alphaID, const QString& anamnesis, const QString& jelenallapot, const QString& diagnosis, const QString& gyogyszer, const QString& beavatkozas){

    QString sql = QString("update bmutet set anamnesis = '%1', "
        "jelenallapot = '%2', "
        "diagnosis = '%3', "
        "leirasa = '%4', "
        "altatas = '%5' where alphaaz = %6").arg(anamnesis).arg(jelenallapot).arg(diagnosis).arg(gyogyszer).arg(beavatkozas).arg(alphaID);
    QSqlQuery query(sql);
}



//tulaj, allat adatai
QString vtrcodes::tulajallatrec(const QString& beerk, const QString& Shivo, const QString& Sszin, const QString& Sivar, const QString& Sfaj, const QString& Sfajta,
        const QString& Snev, const QString& Sisz, const QString& Shely, const QString& Sutca, const QString& Shea, const QString& chip, const QString& booknum){

    QString sql = "";
    QString helyvan = "";
    QString helyaz = "";
    QString telaz = "";
    QString utcaz = "";

    //tulajdonos
    sql = QString("Select count(xtisz.az) as num "
        "From xtisz Inner Join xttelepules On xttelepules.az = xtisz.telepules "
        "Where xtisz.isz = %1"
        " And xttelepules.telepules = '%2'").arg(Sisz).arg(Shely);

//    qDebug() << sql;

    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    query.first();
    helyvan = query.value(0).toString();

//    qDebug() << helyvan;

    if (helyvan == "0"){
        helyaz = helykontr(Shely);
        QString isz = Sisz;
        teleprec(helyaz, isz);
        telaz = telepazonosito(Sisz, Shely);
//        qDebug() << telaz;
    } else {
        telaz = telepazonosito(Sisz, Shely);
    }

    utcaz = utcakontr(Sutca);
    tulajrec(Snev, telaz, utcaz, Shea);

    QString tulajaz = tulajazonosito(Snev, telaz, utcaz, Shea);

    //állat
    QString szinaz = szinazonosit(Sszin);
    QString ivaraz = ivarazonosit(Sivar);
    QString fajfajtaz = fajfajtazonosit(Sfaj, Sfajta);
    QString torzsszam = allatrec(tulajaz, Shivo, beerk, ivaraz, fajfajtaz, szinaz, chip, booknum);
    return(torzsszam);
}

QString vtrcodes::allatrec(QString tulajdonos, QString hivonev, QString szuletett, QString ivar, QString fajta, QString szin, QString chip, QString booknum){
    QString sql = "";
    QString torzsszam = "";

    sql = "select max(torzsszam)+1 from yallat where torzsszam<9000000";
    QSqlQuery query(sql);
    query.first();
    torzsszam = query.value(0).toString();

    if (torzsszam == ""){
        torzsszam = "1";
    }

    sql = "insert into yallat (torzsszam, tulajdonos, hivonev, szuletett, ivar, fajta, szin, chip, booknum) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";

    query.prepare(sql);
    query.addBindValue(torzsszam);
    query.addBindValue(tulajdonos);
    query.addBindValue(hivonev);
    query.addBindValue(szuletett);
    query.addBindValue(ivar);
    query.addBindValue(fajta);
    query.addBindValue(szin);
    query.addBindValue(chip);
    query.addBindValue(booknum);
    query.exec();

    return(torzsszam);
}

QString vtrcodes::fajfajtazonosit(QString faj, QString fajta){
    QString sql = "";
    QString fajfajtaszam = "";
    QString fajfajtaz = "";

    sql = QString("Select count(xafajta.az) "
        "From xafajta Inner Join xafaj On xafaj.az = xafajta.faj "
        "Where xafaj.faj = '%1' And xafajta.fajta = '%2'").arg(faj).arg(fajta);
    QSqlQuery query(sql);
    query.first();
    fajfajtaszam = query.value(0).toString();

    if (fajfajtaszam == "0"){
        fajfajtarec(faj, fajta);
        fajfajtaz = fajfajtakeres(faj, fajta);
    } else {
        fajfajtaz = fajfajtakeres(faj, fajta);
    }

    return fajfajtaz;
}

void vtrcodes::fajfajtarec(QString faj, QString fajta){
    QString fajaz = "";

    fajaz = fajazonosit(faj);

    QSqlQuery query;
    QString sql = "insert into xafajta (faj, fajta) VALUES (?,?)";

    query.prepare(sql);
    query.addBindValue(fajaz);
    query.addBindValue(fajta);
    query.exec();
}

QString vtrcodes::fajfajtakeres(QString faj, QString fajta){
    QString sql = "";
    QString fajfajtaz = "";

    sql = QString("Select xafajta.az "
        "From xafajta Inner Join xafaj On xafaj.az = xafajta.faj "
        "Where xafaj.faj = '%1' And xafajta.fajta = '%2'").arg(faj).arg(fajta);
    QSqlQuery query(sql);
    query.first();
    fajfajtaz = query.value(0).toString();

    return fajfajtaz;
}

QString vtrcodes::fajazonosit(QString faj){
    QString sql = "";
    QString fajszam = "";
    QString fajaz = "";

    sql = QString("select count(az) from xafaj where faj ='%1'").arg(faj);
    QSqlQuery query(sql);
    query.first();
    fajszam = query.value(0).toString();

    if (fajszam == "0")
    {
        fajrec(faj);
        fajaz = fajkeres(faj);
    }
    else
    {
        fajaz = fajkeres(faj);
    }

    return fajaz;
}

void vtrcodes::fajrec(QString faj){
    QSqlQuery query;
    QString sql = "insert into xafaj (faj) "
        "VALUES (?)";

    query.prepare(sql);
    query.addBindValue(faj);
    query.exec();
}

QString vtrcodes::fajkeres(QString faj){
    QString sql = "";
    QString fajaz = "";
    sql = QString("select az from xafaj where faj ='%1'").arg(faj);
    QSqlQuery query(sql);
    query.first();
    fajaz = query.value(0).toString();

    return fajaz;
}

QString vtrcodes::ivarazonosit(QString ivar){
    QString ivaraz = "";
    QString ivarszam = "";
    QString sql = "";

    sql = QString("select count(az) from xaivar where ivar='%1'").arg(ivar);
    QSqlQuery query(sql);
    query.first();
    ivarszam = query.value(0).toString();

    if (ivarszam == "0")
    {
        ivarrec(ivar);
        ivaraz = ivarkeres(ivar);
    }
    else
    {
        ivaraz = ivarkeres(ivar);
    }

    return ivaraz;
}

void vtrcodes::ivarrec(QString ivar){
    QSqlQuery query;
    QString sql = "insert into xaivar (ivar) "
        "VALUES (?)";

    query.prepare(sql);
    query.addBindValue(ivar);
    query.exec();
}

QString vtrcodes::ivarkeres(QString ivar){
    QString ivaraz = "";
    QString sql = "";

    sql = QString("select az from xaivar where ivar='%1'").arg(ivar);
    QSqlQuery query(sql);
    query.first();
    ivaraz = query.value(0).toString();

    return ivaraz;
}

QString vtrcodes::szinazonosit(QString szin){
    QString szinaz = "";
    QString szinszam = "";
    QString sql = "";

    sql = QString("select count(az) from xaszin where szin='%1'").arg(szin);
    QSqlQuery query(sql);
    query.first();
    szinszam = query.value(0).toString();

    if (szinszam == "0")
    {
        szinrec(szin);
        szinaz = szinkeres(szin);
    }
    else
    {
        szinaz = szinkeres(szin);
    }

    return szinaz;
}

void vtrcodes::szinrec(QString szin){
    QSqlQuery query;
    QString sql = "insert into xaszin (szin) "
        "VALUES (?)";

    query.prepare(sql);
    query.addBindValue(szin);
    query.exec();
}

QString vtrcodes::szinkeres(QString szin){
    QString szinaz = "";
    QString sql = "";

    sql = QString("select az from xaszin where szin='%1'").arg(szin);
    QSqlQuery query(sql);
    query.first();
    szinaz = query.value(0).toString();

    return szinaz;
}

QString vtrcodes::tulajazonosito(QString nev, QString helyseg, QString utca, QString hea){
    QString tulajaz = "";
    QString sql = "";

    sql = QString("select az from ytulajdonos "
        "where nev='%1' and "
        "helyseg = %2 and "
        "utca = %3 and "
        "hea = '%4'").arg(nev).arg(helyseg).arg(utca).arg(hea);
    QSqlQuery query(sql);
    query.first();
    tulajaz = query.value(0).toString();

    return tulajaz;
}

void vtrcodes::tulajrec(QString nev, QString helyseg, QString utca, QString hea){
    QSqlQuery query;
    QString sql = "insert into ytulajdonos (nev, helyseg, utca, hea) VALUES (?,?,?,?)";

    query.prepare(sql);
    query.addBindValue(nev);
    query.addBindValue(helyseg);
    query.addBindValue(utca);
    query.addBindValue(hea);
    query.exec();
}

QString vtrcodes::utcakontr(QString utca){
    QString sql = "";
    QString utcaszam = "";
    QString utcaz = "";

    sql = QString("select count(az) from xtutca where utca ='%1'").arg(utca);
    QSqlQuery query(sql);
    query.first();
    utcaszam = query.value(0).toString();

    if (utcaszam == "0"){
        utcarec(utca);
        utcaz = utcazonosit(utca);
    } else {
        utcaz = utcazonosit(utca);
    }

    return utcaz;
}

void vtrcodes::utcarec(QString utca){
    QSqlQuery query;
    QString sql = "insert into xtutca (utca) VALUES (?)";

    query.prepare(sql);
    query.addBindValue(utca);
    query.exec();
}


QString vtrcodes::utcazonosit(QString utca){
    QString sql = "";
    QString utcaz = "";

    sql = QString("select az from xtutca where utca ='%1'").arg(utca);
    QSqlQuery query(sql);
    query.first();
    utcaz = query.value(0).toString();

    return utcaz;
}

QString vtrcodes::helykontr(QString hely){
    QString sql = "";
    QString helyaz = "";
    QString helyvan = "";

    sql = QString("select count(az) as num from xttelepules where telepules='%1'").arg(hely);
    qDebug() << sql;
    QSqlQuery query(sql);
//    QSqlRecord record = query.record();
    query.first();
    helyvan = query.value(0).toString();
    if (helyvan == "0"){
//        qDebug() << "itt";
        helyrec(hely);
        helyaz = helyazonosito(hely);
    } else {
//        qDebug() << "itt";
        helyaz = helyazonosito(hely);
    }

    return helyaz;
}


QString vtrcodes::helyazonosito(QString hely){

    QString sql = "";
    QString helyaz = "";

    sql = QString("select az from xttelepules where telepules='%1'").arg(hely);
    QSqlQuery query(sql);
    query.first();
    helyaz = query.value(0).toString();

    return helyaz;
}

void vtrcodes::helyrec(QString hely){
    QSqlQuery query;
    QString sql = "insert into xttelepules (telepules, aktiv) VALUES (?, 1)";

    query.prepare(sql);
    query.addBindValue(hely);
//    query.addBindValue("1");
    query.exec();
//    qDebug() << query.executedQuery();
}


void vtrcodes::teleprec(QString helyaz, QString isz){
    QSqlQuery query;
    QString sql = "insert into xtisz (telepules, isz) VALUES (?, ?)";

    query.prepare(sql);
    query.addBindValue(helyaz);
    query.addBindValue(isz);
    query.exec();
}

QString vtrcodes::telepazonosito(QString isz, QString hely){
    QString az = "";
    QString sql = "";

    sql = QString("Select xtisz.az "
        "From xtisz Inner Join xttelepules On xttelepules.az = xtisz.telepules "
        "Where xtisz.isz = %1 And xttelepules.telepules = '%2'").arg(isz).arg(hely) ;

    QSqlQuery query(sql);
    query.first();
    az = query.value(0).toString();

    return az;
}


void vtrcodes::tulajallatmod(QString tulaz, QString allataz, QString beerk, QString Shivo, QString Sszin, QString Sivar, QString Sfaj, QString Sfajta, QString Snev, QString Sisz, QString Shely, QString Sutca, QString Shea, QString chip, QString booknum){
    QString sql = "";
    QString helyvan = "";
    QString helyaz = "";
    QString telaz = "";
    QString utcaz = "";

    sql = QString("Select count(xtisz.az) "
        "From xtisz Inner Join xttelepules On xttelepules.az = xtisz.telepules "
        "Where xtisz.isz = %1 And xttelepules.telepules = '%2'").arg(Sisz).arg(Shely);
    QSqlQuery query(sql);
    query.first();
    helyvan = query.value(0).toString();

    if (helyvan == "0"){
        helyaz = helykontr(Shely);
        QString isz = Sisz;
        teleprec(helyaz, isz);
        telaz = telepazonosito(Sisz, Shely);
    } else {
        telaz = telepazonosito(Sisz, Shely);
    }

    utcaz = utcakontr(Sutca);
    tulajmod(tulaz, Snev, telaz, utcaz, Shea);

    //allat
    QString szinaz = szinazonosit(Sszin);
    QString ivaraz = ivarazonosit(Sivar);
    QString fajfajtaz = fajfajtazonosit(Sfaj, Sfajta);
    allatmod(allataz, tulaz, Shivo, beerk, ivaraz, fajfajtaz, szinaz, chip, booknum);

}

void vtrcodes::tulajmod(QString tulaz, QString nev, QString helyseg, QString utca, QString hea){
    QString sql = QString("update ytulajdonos set nev = '%1', "
        "helyseg = '%2', "
        "utca = '%3', "
        "hea = '%4' "
        "where az = %5").arg(nev).arg(helyseg).arg(utca).arg(hea).arg(tulaz);
    QSqlQuery query(sql);
//    qDebug() << sql;
}

void vtrcodes::allatmod(QString allataz, QString tulajdonos, QString hivonev, QString szuletett, QString ivar, QString fajta, QString szin, QString chip, QString booknum){
    QString sql = QString("update yallat set tulajdonos = '%1', "
        "hivonev = '%2', "
        "szuletett = '%3', "
        "ivar = '%4', "
        "fajta = '%5', "
        "szin = '%6', "
        "chip = '%7', "
        "booknum = '%8' "
        "where az = %9").arg(tulajdonos).arg(hivonev).arg(szuletett).arg(ivar).arg(fajta).arg(szin).arg(chip).arg(booknum).arg(allataz);
    QSqlQuery query(sql);
//    qDebug() << sql;
}

void vtrcodes::delAllat(QString id){
    int did = id.toInt() + 9000000;
    QString sql = QString("update yallat set torzsszam=%1 where torzsszam=%2").arg(did).arg(id);
    QSqlQuery query(sql);

    sql = QString("update yamegjegyzes set torzsszam=%1 where torzsszam=%2").arg(did).arg(id);
    query.exec(sql);

    sql = QString("update alpha set torzsszam=%1 where torzsszam=%2").arg(did).arg(id);
    query.exec(sql);
}

//report
QString vtrcodes::Nationale(const QString& allat_az){
    QString tab = "<table border='0' cellpadding='2' align='left' width='70%'>"
        "<tr>"
            "<td><b>Tulajdonos:</b></td>"
            "<td>%1</td>"
        "</tr>"
        "<tr>"
            "<td><b>Tartási hely:</b></td>"
            "<td>%2</td>"
        "</tr>"
        "<tr>"
            "<td></td>"
            "<td>%3</td>"
        "</tr>"
        "<tr>"
            "<td></td>"
            "<td></td>"
        "</tr>"
        "<tr>"
            "<td><b>Hívónév:</b></td>"
            "<td>%4</td>"
        "</tr>"
        "<tr>"
            "<td><b>Faj:</b></td>"
            "<td>%5</td>"
        "</tr>"
        "<tr>"
            "<td><b>Fajta:</b></td>"
            "<td>%6</td>"
        "</tr>"
        "<tr>"
            "<td><b>Szín:</b></td>"
            "<td>%7</td>"
        "</tr>"
        "<tr>"
            "<td><b>Ivar:</b></td>"
            "<td>%8</td>"
        "</tr>"
        "<tr>"
            "<td><b>Születés dátuma:</b></td>"
            "<td>%9</td>"
        "</tr>"
        "<tr>"
            "<td><b>Mikrochip azonosító:</b></td>"
            "<td>%10</td>"
        "</tr>"
        "<tr>"
            "<td><b>Könyv azonosító:</b></td>"
            "<td>%11</td>"
        "</tr>"
        "</table>";

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
        "xaszin.szin, yallat.chip, yallat.booknum "
        "From ytulajdonos Inner Join yallat On ytulajdonos.az = yallat.tulajdonos Inner Join xtutca On xtutca.az = ytulajdonos.utca Inner Join xtisz On xtisz.az = ytulajdonos.helyseg Inner Join xttelepules On xttelepules.az = xtisz.telepules Inner Join xafajta On xafajta.az = yallat.fajta Inner Join xafaj On xafaj.az = xafajta.faj Inner Join xaivar On xaivar.az = yallat.ivar Inner Join xaszin On xaszin.az = yallat.szin "
        "Where yallat.torzsszam = %1").arg(allat_az);

    QSqlQuery query(sql);
    QSqlRecord record = query.record();

    query.first();

    QString hely = QString("%1 %2").arg(query.value(record.indexOf("isz")).toString()).arg(query.value(record.indexOf("telepules")).toString());
    QString cim = QString("%1 %2").arg(query.value(record.indexOf("utca")).toString()).arg(query.value(record.indexOf("hea")).toString());

    QString nationale = QString(tab)
        .arg(query.value(record.indexOf("nev")).toString())
        .arg(hely)
        .arg(cim)
        .arg(query.value(record.indexOf("hivonev")).toString())
        .arg(query.value(record.indexOf("faj")).toString())
        .arg(query.value(record.indexOf("fajta")).toString())
        .arg(query.value(record.indexOf("szin")).toString())
        .arg(query.value(record.indexOf("ivar")).toString())
        .arg(query.value(record.indexOf("szuletett")).toString())
        .arg(query.value(record.indexOf("chip")).toString())
        .arg(query.value(record.indexOf("booknum")).toString());

//        ui->lineEdit_13->setText(query.value(record.indexOf("")).toString());

    return nationale;
}



