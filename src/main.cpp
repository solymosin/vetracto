#include <QApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTextCodec>

#ifdef Q_OS_WIN
#include <QCleanlooksStyle>
//#include <QGtkStyle>
//#include <QMotifStyle>
//#include <QWindowsStyle>
//#include <QPlastiqueStyle>
//#include <QWindowsXPStyle>
//#include <QWindowsVistaStyle>
#endif

#include "frmmain.h"
//#include "dbconnect.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    #ifdef Q_OS_LINUX
//
//    #endif

    #ifdef Q_OS_WIN
        QApplication::setStyle(new QCleanlooksStyle());
    #endif
//    if (!createConnection())
//        return 1;

//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("vtrdb.db");
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
//    qtTranslator.load("qt_hu_HU", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    //qDebug() << QLocale::system().name();

    QTranslator myapp;
    myapp.load("myapp_" + QLocale::system().name());
//    myapp.load("myapp_hu_HU");
    a.installTranslator(&myapp);
    frmMain w;
    w.show();
    return a.exec();
}


