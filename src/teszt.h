#ifndef TESZT_H
#define TESZT_H

#include <QMainWindow>

namespace Ui {
    class teszt;
}

class teszt : public QMainWindow {
    Q_OBJECT
public:
    teszt(QWidget *parent = 0);
    ~teszt();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::teszt *ui;
};

#endif // TESZT_H
