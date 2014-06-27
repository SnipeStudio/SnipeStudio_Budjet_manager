#include "sqlman.h"

sqlMan::sqlMan(QString dbname)
{
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("ssbm.db");
    if (!sdb.open()) {
           qDebug()<<"ERROR OCCURED";
    }
    else
    {


    QSqlQuery* query=new QSqlQuery(sdb);
query->exec("CREATE TABLE  IF NOT EXISTS \"operations\" (\"id\" INTEGER PRIMARY KEY  NOT NULL ,\"time\" DATETIME DEFAULT (CURRENT_TIMESTAMP) ,\"summ\" double NOT NULL  DEFAULT (null) ,\"comment\"  NOT NULL ,\"catid\" INTEGER DEFAULT (null) ,\"side\" BOOL DEFAULT (0) )");
    QSqlTableModel* model=new QSqlTableModel;
    model->setTable("operations");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    }
}

QSqlTableModel& sqlMan::getModel()
{
    return *sqlMan::model;
}
