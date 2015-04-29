#ifndef XPANEL_H
#define XPANEL_H

#include <QDialog>

namespace Ui {
    class xPanel;
}

class xPanel : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(xPanel)
public:
    explicit xPanel(QWidget *parent = 0);
    virtual ~xPanel();
    Ui::xPanel *m_ui;

protected:
    virtual void changeEvent(QEvent *e);


};

#endif // XPANEL_H
