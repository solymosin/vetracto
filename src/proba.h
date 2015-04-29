#ifndef PROBA_H
#define PROBA_H

#include <QtGui/QMainWindow>

namespace Ui {
    class proba;
}

class proba : public QMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY(proba)
public:
    explicit proba(QWidget *parent = 0);
    virtual ~proba();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::proba *m_ui;
};

#endif // PROBA_H
