#include <QtGui>
#include <QFileDialog>

#include "xattach.h"
#include "ui_xattach.h"

xAttach::xAttach(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::xAttach)
{
    m_ui->setupUi(this);

    connect(m_ui->toolButton, SIGNAL(clicked()), this, SLOT(browse()));

}

xAttach::~xAttach()
{
    delete m_ui;
}

void xAttach::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



void xAttach::browse(){
     QString fn = QFileDialog::getOpenFileName(this,
        tr("Csatolmány keresése"),
        QDir::currentPath(),
        tr("Minden fájl (*.*)"));
     m_ui->lineEdit->setText(fn);
 }

