#ifndef FRMIMPORTER_H
#define FRMIMPORTER_H

#include <QDialog>

namespace Ui {
    class frmImporter;
}

class frmImporter : public QDialog {
    Q_OBJECT
public:
    frmImporter(QWidget *parent = 0);
    ~frmImporter();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::frmImporter *ui;

public slots:
    void sourcePath();
    void destPath();
    void importer();
};

#endif // FRMIMPORTER_H
