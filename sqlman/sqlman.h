#ifndef SQLMAN_H
#define SQLMAN_H
#include <QtSql>
#include <QDebug>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>
#include "ui_widget.h"
namespace Ui {
class sqlMan;
}
class sqlMan
{
public:
    sqlMan(QString dbname);
    void addOperation(double summ,QString comment,bool side);
    double getBalance();
    QSqlTableModel &getModel();
    QSqlQuery query;
    QSqlTableModel* model;
    QSqlDatabase sdb;



};

#endif // SQLMAN_H
