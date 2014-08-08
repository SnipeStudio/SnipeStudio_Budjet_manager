#ifndef SQLMAN_H
#define SQLMAN_H
#include <QtSql>
#include <QDebug>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>
#include "ui_widget.h"
#include "../datamanager/datamanager.h"
#ifdef _MBOX
#define _MBOX
#include <QMessageBox>
#endif
namespace Ui {
class sqlMan;
}
class sqlMan
{
public:
    sqlMan();
    void addOperation(sqlMan* db,double summ,QString comment,bool side);
    double getBalance();
    double initBal;
    QString databaseName;
    QSqlTableModel *getModel();
    QSqlQuery* query;
    QSqlTableModel* model;
    QSqlDatabase sdb;
    int init();




};

#endif // SQLMAN_H
