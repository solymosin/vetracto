#ifndef XATTACH_H
#define XATTACH_H

#include <QDialog>

namespace Ui {
    class xAttach;
}

class xAttach : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(xAttach)
public:
    explicit xAttach(QWidget *parent = 0);
    virtual ~xAttach();
    Ui::xAttach *m_ui;

protected:
    virtual void changeEvent(QEvent *e);


public slots:
    void browse();

};

#endif // XATTACH_H
