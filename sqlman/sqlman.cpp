#include "sqlman.h"

sqlMan::sqlMan()
{
    dataManager* man=new dataManager();
    QString databaseName=man->getPath()+"ssbm.db";
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(databaseName);
    if (!sdb.open()) {
           qDebug()<<"ERROR OCCURED";
    }
    else
    {
        this->init();
    }
}

QSqlTableModel* sqlMan::getModel()
{
    return this->model;
}

int sqlMan::init()
{
    QSqlQuery* query=new QSqlQuery(sdb);
    if(!query->exec("CREATE TABLE  IF NOT EXISTS \"operations\" (\"id\" INTEGER PRIMARY KEY  NOT NULL ,\"time\" DATETIME DEFAULT (CURRENT_TIMESTAMP) ,\"summ\" double NOT NULL  DEFAULT (null) ,\"comment\"  NOT NULL ,\"catid\" INTEGER DEFAULT (null) ,\"side\" BOOL DEFAULT (0) )"))
    {
        return 2;
    }
    this->model=new QSqlTableModel(0,this->sdb);
    this->model->setTable("operations");
    if(!this->model->select())
    {
        return 1;
    }
    return 0;
}


void sqlMan::addOperation(sqlMan *db, double summ, QString comment, bool side)
{
    if(!side)
    {
        summ*=-1;
    }
    this->query=new QSqlQuery(this->sdb);
    this->query->prepare("INSERT INTO operations (summ, comment, side) VALUES (:summ, :comment, :side)");
         this->query->bindValue(":summ", summ);
         this->query->bindValue(":comment", comment);
         this->query->bindValue(":side", side);
    if(this->query->exec())
    {
        qDebug()<<"OK";
    }
    else
    {
        qDebug()<<"ERROR";
    }
    db->model=new QSqlTableModel(0,db->sdb);
    db->model->setTable("operations");

    if(db->model->select())
    {
        qDebug()<<"Model is OK";
    }
    db->model->setEditStrategy(QSqlTableModel::OnFieldChange);

}


double sqlMan::getBalance()
{

    query=new QSqlQuery(sdb);
    this->query->exec("Select sum(summ) from operations;");
    query->next();
   if(this->query->value(0).isNull())
   {
       qDebug()<<"UPS";
       return 0.0;
   }
    qDebug()<<"Balance is: "+ this->query->value(0).toString();
    return this->query->value(0).toDouble();

}
