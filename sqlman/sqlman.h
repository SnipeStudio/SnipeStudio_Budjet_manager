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
    void addOperation(sqlMan* db,double summ,QString comment,bool side);
    double getBalance();
    double initBal;
    QString databaseName;
    QSqlTableModel *getModel();
    QSqlQuery* query;
    QSqlTableModel* model;
    QSqlDatabase sdb;
    void init();




};

#endif // SQLMAN_H
