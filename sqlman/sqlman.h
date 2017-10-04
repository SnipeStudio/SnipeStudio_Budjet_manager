#ifndef SQLMAN_H
#define SQLMAN_H
#include <QDir>
#include <QtSql>

#include "datamanager/datamanager.h"
#include "ssbmDatabaseModel/ssbmdatabasemodel.h"
#include "ui_widget.h"
#include <QDebug>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>
namespace Ui {
class sqlMan;
}
class sqlMan {
public:
  sqlMan();
  void addOperation(double summ, QString comment, bool side, QDateTime time);
  void updateEntry(int index, double summ, QString comment, bool side,
                   QDateTime time);
  void deleteOperation(int index);
  double getBalance();
  void init();
  int clean();
  QString getDBName();
  ssbmDatabaseModel *getModel();
  // QSqlDatabase* getDataBase();
  bool dbIsOpen();
  void submit();
  QString getListOfOperations(QChar separator);

private:
  QString databaseName;
  QSqlQuery *query;
  ssbmDatabaseModel *model;
  QSqlDatabase sdb;
  bool dirty;
};

#endif // SQLMAN_H
