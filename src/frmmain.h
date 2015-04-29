#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <QtSql>
#include <QTreeWidget>
#include <QSignalMapper>

namespace Ui
{
    class frmMainClass;
}

class frmMain : public QMainWindow
{
    Q_OBJECT

public:
    frmMain(QWidget *parent = 0);
    ~frmMain();
    QSqlDatabase db;
    QString u;
    QSignalMapper mapper;
    int kezelnapok;

private:
    Ui::frmMainClass *ui;
    QSignalMapper *mppr;

private slots:
    void kiir();
    void betolt01();
    void frmKezelBetolt();
    void frmTulAllBetolt();
    void frmKezelBetolt(QString idopont);
    void UjAllatTulajhoz();
    void TulajhozAllat();
    void modositTulajAllat();
    void TulajAllatmodosit();
    void ujTulajAllat();
    void frmVaccBetolt();
    void UrlapTorlo();
    void UrlapTorloB();
    void AllatBetoltoA(const QString&);
    void AllatBetoltoB(const QString&);
    void AllatBetoltoC(const QString&);
    void ElozmenyBetolto(const QString&);
    void AllatBetoltoTrsz();
    void TulajAllatai(const QString&);
    void TrszDel(const QString&);
    void EditorNyit();
    void SurgBetolt();
    void SurgBetolt(QString idopont);
    void About();    
    int kontroll();
    void QueryList();
    void frmDokikBetolt();
    void elozmenyFabol();
    void idTulAllbol();
    void balFa();
    void laborLap();
    void laborLap(QString dd);
    void tulajPopUp();
    void allatPopUp();
    void tulajMegjegyz();
    void allatMegjegyz();
    void vtrSettings();
    void norberger();
    void tpa();
    void comtan();
    void MySQLimporter();
    void dbCleaner();
    void archival();
    void tulajKomm();
    void dataKorr1(QAction *action);
    void allatDel();
    void sendEmail();
    void telepKorr();
//    void dataKorr2(QAction *action);

signals:
    void decChanged(const QString& newValue);

};

#endif // FRMMAIN_H
