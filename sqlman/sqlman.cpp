#include "sqlman.h"

sqlMan::sqlMan()
{
    dataManager* data=new dataManager();
    QString databaseName=QDir::toNativeSeparators(data->getPath()+"/ssbm.db");
    delete data;
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
    this->init();
    return model;
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
QString sqlMan::getDBName()
{
    return databaseName;
}
//QSqlDatabase* sqlMan::getDataBase()
//{
//    return &sdb;
//}
bool sqlMan::dbIsOpen()
{
    sdb.open();
    return sdb.isOpen();
}

void sqlMan::init()
{
    QSqlQuery* query=new QSqlQuery(sdb);
    if(!query->exec("CREATE TABLE  IF NOT EXISTS \"operations\" (\"id\" INTEGER PRIMARY KEY  NOT NULL ,\"time\" DATETIME DEFAULT (CURRENT_TIMESTAMP) ,\"summ\" double NOT NULL  DEFAULT (null) ,\"comment\"  NOT NULL ,\"catid\" INTEGER DEFAULT (null) ,\"side\" BOOL DEFAULT (0) )"))
    {
        return;
    }
    model=new QSqlTableModel(0,sdb);
    model->setTable("operations");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
}

void sqlMan::addOperation(sqlMan *db, double summ, QString comment, bool side,QDateTime time)
{
    qDebug()<<"Side:"<<side;
    qDebug()<<"Summ:"<<summ;
    this->query=new QSqlQuery(this->sdb);
    this->query->prepare("INSERT INTO operations (summ, comment, side,time) VALUES (:summ, :comment, :side,:time)");
         this->query->bindValue(":summ", summ);
         this->query->bindValue(":comment", comment);
         this->query->bindValue(":side", side);
    this->query->bindValue(":time", time.toString("dd-MM-yyyy hh:mm:ss"));
    this->query->exec();
    delete query;

}

void sqlMan::updateEntry(sqlMan *db,int index, double summ, QString comment, bool side,QDateTime time)
{
    qDebug()<<"Side:"<<side;
    qDebug()<<"Summ:"<<summ;
    this->query=new QSqlQuery(this->sdb);
    //  qry.prepare( "UPDATE names SET lastname = 'Johnson' WHERE firstname = 'Jane'" );
    // UPDATE operations set summ = :summ, comment = :comment,side = :side, time = :time  where id=:index;
    this->query->prepare("UPDATE operations set summ = :summ, comment = :comment,side = :side, time = :time  where id=:index;");
         this->query->bindValue(":summ", summ);
         this->query->bindValue(":comment", comment);
         this->query->bindValue(":side", side);
    this->query->bindValue(":time", time.toString("dd-MM-yyyy hh:mm:ss"));
    this->query->bindValue(":index", index);
    this->query->exec();
    delete query;

}

void sqlMan::deleteOperation(int index)
{
    qDebug()<<"DO YOU WANT A FRYING NAILS?";
    this->query=new QSqlQuery(this->sdb);
    this->query->prepare("DELETE FROM operations WHERE id = :index" );
    this->query->bindValue(":index", index);
    this->query->exec();
}

int sqlMan::clean(sqlMan *db)
{
    sdb.close();
    dataManager* data=new dataManager();
    QString databaseName=QDir::toNativeSeparators(data->getPath()+"/ssbm.db");
    delete data;
    qDebug() << sdb.isOpen();
    qDebug() << QFile::remove(databaseName);
    sdb.open();
    this->init();
}

