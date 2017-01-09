#ifndef EXPORT_H
#define EXPORT_H

#include <QWidget>
#include <QFileDialog>
#include "sqlman/sqlman.h"

namespace Ui {
class Export;
}

class Export : public QWidget
{
    Q_OBJECT

public:
    explicit Export(QWidget *parent = 0, QSqlTableModel *modelOut = NULL);
    ~Export();

private:
    QSqlTableModel *model;
    Ui::Export *ui;

public slots:
    void saveData();
    void selectPath();

};

#endif // EXPORT_H
