#include "settingwizard.h"
#include "ui_settingwizard.h"

settingWizard::settingWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::settingWizard)
{
    ui->setupUi(this);
}

settingWizard::~settingWizard()
{
    delete ui;
}

void settingWizard::changeEvent(QEvent *e)
{
    QWizard::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
