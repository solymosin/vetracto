#include "xabout.h"
#include "ui_xabout.h"

xAbout::xAbout(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::xAbout)
{
    m_ui->setupUi(this);
}

xAbout::~xAbout()
{
    delete m_ui;
}

void xAbout::changeEvent(QEvent *e)
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
