#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include <QCommandLineParser>
#include <iostream>
#include <QApplication>
#include <QList>
#include <QString>
#include <QDebug>
#include "app_info.h"
#include "export/export.h"
#include "sqlman/sqlman.h"

#ifdef COMMANDLINE_H
class commandLine;
#endif

class commandLine {
public:
  commandLine(int argc, char *argv[], sqlMan *database);
  bool IsHelp();
  bool IsVersion();
  bool IsExport();
  bool IsImport();
  bool IsProfit();
  bool IsExpence();
  bool IsList();
  bool IsClean();

  bool cLine;

private:
  QCommandLineParser *parser;
  bool isHelp;
  bool isVersion;
  bool isExport;
  bool isImport;
  bool isProfit;
  bool isExpence;
  dataManager *data;
  QCommandLineOption *helpOption;
  QCommandLineOption *versionOption;
  QCommandLineOption *exportOption;
  QCommandLineOption *importOption;
  QCommandLineOption *profitOption;
  QCommandLineOption *expenceOption;
  QCommandLineOption *listOption;
  QCommandLineOption *cleanOption;
  void initDatabase(sqlMan *db);
  QStringList arguments;
  sqlMan *db;
  QSqlTableModel *model;
  bool exportConsole(QString path);
  bool importConsole(QString path);
  bool profitConsole(double summ, QString comment, QString dateTime);
  bool expenceConsole(double summ, QString comment, QString dateTime);
  bool writeOperations();
  bool cleanDatabase();
};

#endif // COMMANDLINE_H
