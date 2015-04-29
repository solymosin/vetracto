#ifndef XABOUT_H
#define XABOUT_H

#include <QDialog>

namespace Ui {
    class xAbout;
}

class xAbout : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(xAbout)
public:
    explicit xAbout(QWidget *parent = 0);
    virtual ~xAbout();
    Ui::xAbout *m_ui;

protected:
    virtual void changeEvent(QEvent *e);



};

#endif // XABOUT_H
