#ifndef IMPORT_H
#define IMPORT_H

#include <QDialog>

#include <QFileDialog>
#include "sqlman/sqlman.h"

namespace Ui {
class Import;
}

class Import : public QDialog
{
    Q_OBJECT

public:
    explicit Import(QWidget *parent = 0, sqlMan *sqlManOut = 0);
    ~Import();

public slots:
    void saveData();
    void selectFile();

private:
    Ui::Import *ui;
    sqlMan* sqlManager;
};

#endif // IMPORT_H
