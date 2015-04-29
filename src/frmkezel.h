#ifndef FRMKEZEL_H
#define FRMKEZEL_H

#include <QDialog>

namespace Ui {
    class frmKezel;
}

class frmKezel : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(frmKezel)

public:
    explicit frmKezel(QWidget *parent = 0);
    virtual ~frmKezel();
    QString doki, allat_az, typ;
    Ui::frmKezel *m_ui;

protected:
    virtual void changeEvent(QEvent *e);

//private:
//    Ui::frmKezel *m_ui;

private slots:
    void createToolbars();

public slots:
    void EditorNyit();
    void ListaBetolto();
    void ListatoPlain();
    void TextboLista();
    void UjListaElem();
    void PanelPopUp();
    void PanelRec();
    void PanelMod();
    void PanelMutat();
//    QString Nationale();
    void ElozmenyMutat();
    void TisztaLap();
    void UjKezeles();
    void Modosit();
    void Felszab();
    void Csatolmany();
    void Csatol();
    void attachlist(const QString& datum, const QString& aisz, const QString& typ);
    void attached();
    QString datumozo();
    void listaPopUp();
    void leDel();
};

#endif // FRMKEZEL_H
