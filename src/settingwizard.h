#ifndef SETTINGWIZARD_H
#define SETTINGWIZARD_H

#include <QWizard>

namespace Ui {
    class settingWizard;
}

class settingWizard : public QWizard {
    Q_OBJECT
public:
    settingWizard(QWidget *parent = 0);
    ~settingWizard();
    Ui::settingWizard *ui;

protected:
    void changeEvent(QEvent *e);


};

#endif // SETTINGWIZARD_H
