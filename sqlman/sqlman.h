#ifndef SQLMAN_H
#define SQLMAN_H
#include <QtSql>
#include <QDir>

#include <QDebug>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>
#include "ui_widget.h"
#include "datamanager/datamanager.h"
namespace Ui {
class sqlMan;
}
class sqlMan
{
public:
    sqlMan();
    void addOperation(sqlMan* db, double summ, QString comment, bool side, QDateTime time);
    double getBalance();
    void init();
    int clean();
    QString getDBName();
    QSqlTableModel* getModel();
    QSqlDatabase* getDataBase();
    bool dbIsOpen();
private:
    QString databaseName;
    QSqlQuery* query;
    QSqlTableModel* model;
    QSqlDatabase sdb;



};

#endif // SQLMAN_H
