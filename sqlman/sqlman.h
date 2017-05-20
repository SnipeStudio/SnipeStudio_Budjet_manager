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
  QSqlTableModel *getModel();
  // QSqlDatabase* getDataBase();
  bool dbIsOpen();
  void submit();
  QString getListOfOperations(QChar separator);

private:
  QString databaseName;
  QSqlQuery *query;
  QSqlTableModel *model;
  QSqlDatabase sdb;
  bool dirty;
};

#endif // SQLMAN_H
