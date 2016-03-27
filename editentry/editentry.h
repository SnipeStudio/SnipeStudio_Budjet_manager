#ifndef EDITENTRY_H
#define EDITENTRY_H

#include <QDialog>
#include <QDateTime>
#include "logger/logger.h"
#include "sqlman/sqlman.h"
#include <qvector.h>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class editentry;
}

class editentry : public QDialog
{
    Q_OBJECT

public:
    explicit editentry(QWidget *parent = 0, logger* log=0, QVector<QString>* data=0, sqlMan *db=0);
    ~editentry();

private slots:
    void on_cancel_clicked();

    void on_deleteOp_clicked();

    void on_confirmChanges_clicked();

private:
    Ui::editentry *ui;
    logger* log_ptr;
    int index;
    QDateTime dt;
    double summ;
    QString comment;
    bool side;
    sqlMan* database;

};

#endif // EDITENTRY_H
