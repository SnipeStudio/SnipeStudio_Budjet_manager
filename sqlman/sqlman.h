#ifndef SQLMAN_H
#define SQLMAN_H
#include <QtSql>
#include <QDir>

#include <QDebug>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>
#include "ui_widget.h"
<<<<<<< HEAD
#include "datamanager/datamanager.h"
=======
#include "../datamanager/datamanager.h"
#ifdef _MBOX
#define _MBOX
#include <QMessageBox>
#endif
>>>>>>> 2c960d380d2b93a4173da806a30346556ce8a103
namespace Ui {
class sqlMan;
}
class sqlMan
{
public:
    sqlMan();
    void addOperation(sqlMan* db,double summ,QString comment,bool side);
    double getBalance();
    void init();
    QString getDBName();
    QSqlTableModel* getModel();
    QSqlDatabase* getDataBase();
    bool dbIsOpen();
private:
    QString databaseName;
    QSqlQuery* query;
    QSqlTableModel* model;
    QSqlDatabase sdb;
<<<<<<< HEAD

=======
    int init();
>>>>>>> 2c960d380d2b93a4173da806a30346556ce8a103




};

#endif // SQLMAN_H
