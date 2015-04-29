#include "frmolt.h"
#include "ui_frmolt.h"

frmOlt::frmOlt(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::frmOlt)
{
    m_ui->setupUi(this);
    connect(m_ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_ui->pushButton_2, SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_ui->checkBox, SIGNAL(clicked()), this, SLOT(EbVeszettseg()));
}

frmOlt::~frmOlt()
{
    delete m_ui;
}

void frmOlt::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void frmOlt::EbVeszettseg()
{
    if(m_ui->label_2->isVisible()==true)
    {
        m_ui->label_2->setVisible(false);
        m_ui->lineEdit->setVisible(false);
    }else{
        m_ui->label_2->setVisible(true);
        m_ui->lineEdit->setVisible(true);
    }
}


