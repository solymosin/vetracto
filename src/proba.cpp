#include "proba.h"
#include "ui_proba.h"

proba::proba(QWidget *parent) :
    QMainWindow(parent)
{
    m_ui->setupUi(this);
}

proba::~proba()
{
    delete m_ui;
}

void proba::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
