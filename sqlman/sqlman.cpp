#include "sqlman.h"

sqlMan::sqlMan()
{
    dataManager* data=new dataManager();
    QString databaseName=QDir::toNativeSeparators(data->getPath()+"/ssbm.db");
    delete data;
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(databaseName);
    if (sdb.open())
        this->init();
    dirty = false;
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
       return 0.0;
   }
    return this->query->value(0).toDouble();
}

QString sqlMan::getDBName()
{
    return databaseName;
}

bool sqlMan::dbIsOpen()
{
    return sdb.isOpen();
}

void sqlMan::init()
{
    QSqlQuery* query=new QSqlQuery(sdb);
    if(!query->exec("CREATE TABLE  IF NOT EXISTS \"operations\" (\"id\" INTEGER PRIMARY KEY  NOT NULL ,\"time\" DATETIME DEFAULT (CURRENT_TIMESTAMP) ,\"summ\" NOT NULL  DEFAULT (null) ,\"comment\"  NOT NULL ,\"catid\" INTEGER DEFAULT (null) ,\"side\" BOOL DEFAULT (0) )"))
    {
        return;
    }
    model=new QSqlTableModel(0,sdb);
    model->setTable("operations");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
}

void sqlMan::addOperation(double summ, QString comment, bool side,QDateTime time)
{
    if(dirty)
    {
        dirty = false;
        return;
    }
    this->query=new QSqlQuery(this->sdb);
    this->query->prepare("INSERT INTO operations (summ, comment, side,time) VALUES (:summ, :comment, :side,:time)");
         this->query->bindValue(":summ", QString::number(summ,'f',2));
         this->query->bindValue(":comment", comment);
    if(side)
    {
       this->query->bindValue(":side", 1);
    }
    else
    {
        this->query->bindValue(":side", 0);
    }
    this->query->bindValue(":time", time.toString("dd-MM-yyyy hh:mm:ss"));
    this->query->exec();
    dirty = true;
    delete query;
}

void sqlMan::updateEntry(sqlMan *db,int index, double summ, QString comment, bool side,QDateTime time)
{
    this->query=new QSqlQuery(this->sdb);
    this->query->prepare("UPDATE operations set summ = :summ, comment = :comment,side = :side, time = :time  where id=:index;");
         this->query->bindValue(":summ",  QString::number(summ,'f',2));
         this->query->bindValue(":comment", comment);
         this->query->bindValue(":side", side);
    this->query->bindValue(":time", time.toString("dd-MM-yyyy hh:mm:ss"));
    this->query->bindValue(":index", index);
    this->query->exec();
    delete query;
}

void sqlMan::deleteOperation(int index)
{
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
    sdb.isOpen();
    QFile::remove(databaseName);
    sdb.open();
    this->init();
}

