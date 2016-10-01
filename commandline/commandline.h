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

class commandLine
{
public:
    commandLine(int argc, char *argv[]);
    bool IsCommandLine();
    bool IsHelp();
    bool IsVersion();
    bool IsExport();

private:
    QCommandLineParser* parser;
    bool isCommandLine;
    bool isHelp;
    bool isVersion;
    bool isExport;
    dataManager* data;
    QCommandLineOption* console;
    QCommandLineOption* helpOption;
    QCommandLineOption* versionOption;
    QCommandLineOption* exportOption;
    void initDatabase(sqlMan* db);
    QStringList arguments;
    sqlMan* db;
    QSqlTableModel* model;
    bool exportConsole(QString path);
};

#endif // COMMANDLINE_H
