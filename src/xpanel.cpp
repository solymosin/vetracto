#include "xpanel.h"
#include "ui_xpanel.h"

xPanel::xPanel(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::xPanel)
{
    m_ui->setupUi(this);

    connect(m_ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

xPanel::~xPanel()
{
    delete m_ui;
}

void xPanel::changeEvent(QEvent *e)
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
