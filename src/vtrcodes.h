#ifndef VTRCODES_H
#define VTRCODES_H

#include <QObject>

class vtrcodes : public QObject
{
public:
    vtrcodes();

public slots:
    QString alphaIDentify(const QString& doki, const QString& allatID, const QString& datum);
    QString alphaIDkeres(const QString& doki, const QString& allatID, const QString& datum);
    void alphaRec(const QString& doki, const QString& allatID, const QString& datum);
    QString alphaIDentify2(const QString& doki, const QString& allatID, const QString& datum);
    QString alphaIDkeres2(const QString& allatID, const QString& datum);

    QString fereghajtoIDentify(const QString& fereghajto);
    QString fereghajtoIDkeres(const QString& fereghajto);
    void fereghajtoRec(const QString& fereghajto);
    void fereghajtasRec(const QString& alphaID, const QString& fereghajtoID);

    QString vakcinaIDentify(const QString& vakcina);
    QString vakcinaIDkeres(const QString& vakcina);
    void vakcinaRec(const QString& vakcina);
    void vakcinazasRec(const QString& alphaID, const QString& vakcinaID, const int vakcinatipus, const int sorszam);

    void PanelRec(const QString& ek, const QString& nev, const QString& leiras);
    void PanelMod(const QString& ek, const QString& onev, const QString& nev, const QString& leiras);

    void KezelRec(const QString& alphaID, const QString& anamnesis, const QString& jelenallapot, const QString& diagnosis, const QString& gyogyszer, const QString& beavatkozas);
    void KezelMod(const QString& alphaID, const QString& anamnesis, const QString& jelenallapot, const QString& diagnosis, const QString& gyogyszer, const QString& beavatkozas);

    void SurgRec(const QString& alphaID, const QString& anamnesis, const QString& jelenallapot, const QString& diagnosis, const QString& gyogyszer, const QString& beavatkozas);
    void SurgMod(const QString& alphaID, const QString& anamnesis, const QString& jelenallapot, const QString& diagnosis, const QString& gyogyszer, const QString& beavatkozas);


    QString tulajallatrec(const QString& beerk, const QString& Shivo, const QString& Sszin, const QString& Sivar, const QString& Sfaj,
            const QString& Sfajta, const QString& Snev, const QString& Sisz, const QString& Shely, const QString& Sutca,
            const QString& Shea, const QString& chip, const QString& booknum);
    QString helykontr(QString hely);
    QString helyazonosito(QString hely);
    void helyrec(QString hely);
    void teleprec(QString helyaz, QString isz);
    QString telepazonosito(QString isz, QString hely);
    QString utcakontr(QString utca);
    void utcarec(QString utca);
    QString utcazonosit(QString utca);
    void tulajrec(QString nev, QString helyseg, QString utca, QString hea);
    QString tulajazonosito(QString nev, QString helyseg, QString utca, QString hea);
    QString szinazonosit(QString szin);
    void szinrec(QString szin);
    QString szinkeres(QString szin);
    QString ivarkeres(QString ivar);
    void ivarrec(QString ivar);
    QString ivarazonosit(QString ivar);
    QString fajfajtazonosit(QString faj, QString fajta);
    void fajfajtarec(QString faj, QString fajta);
    QString fajfajtakeres(QString faj, QString fajta);
    QString fajazonosit(QString faj);
    void fajrec(QString faj);
    QString fajkeres(QString faj);
    QString allatrec(QString tulajdonos, QString hivonev, QString szuletett, QString ivar, QString fajta, QString szin, QString chip, QString booknum);

    void attachFile(QString path, QString datum, QString lab, QString typ, QString allat_az, QString doki);
    void attachedShow(QString datum, QString lab, QString typ, QString allat_az);
    void attachedShow(QString datum, QString lab, QString allat_az);

    void tulajallatmod(QString tulaz, QString allataz, QString beerk, QString Shivo, QString Sszin, QString Sivar, QString Sfaj, QString Sfajta, QString Snev, QString Sisz, QString Shely, QString Sutca, QString Shea, QString chip, QString booknum);
    void tulajmod(QString tulaz, QString nev, QString helyseg, QString utca, QString hea);
    void allatmod(QString allataz, QString tulajdonos, QString hivonev, QString szuletett, QString ivar, QString fajta, QString szin, QString chip, QString booknum);

    void RabiesReport(QString sd, QString ed, QString path);
    QString qDistrict(QString hely, QString isz);

    int vaccNumer(QString sql);
    void reporter01(int rows, QString doki, QString sd, QString ed, QString isz, QString hely, QString path);

    void dokiRec(QString nev, QString tel, QString aktiv);
    void dokiMod(QString nev, QString tel, QString aktiv, QString id);

    QString Nationale(const QString& allat_az);

    void dbkontroll();

    void laborRec(const QString& alphaID, const QString& pid, const QString& ertek);
    void laborDel(const QString& rid);
    void allatMegjegyzRec(const QString& trsz, const QString& megjegyzes);
    void tulajMegjegyzRec(const QString& tsz, const QString& megjegyzes);

    void dbclean();
    void archivalMind(QString ut);
    void kommRec(QString tulaj, QString tool, QString cim);
    void kommMod(QString id, QString tool, QString cim);
    void kommDel(QString id);
    void itemEdit(QString sql);
    void ivarCleaner();
    void szinCleaner();
    void fajtaCleaner();
    void fajCleaner();
    void delAllat(QString id);
};

#endif // VTRCODES_H
