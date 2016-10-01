#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include <QCommandLineParser>
#include <QApplication>
#include <QList>
#include <QString>
#include <QDebug>
#include "app_info.h"

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

private:
    QCommandLineParser* parser;
    bool isCommandLine;
    bool isHelp;
    bool isVersion;
    QCommandLineOption* console;
    QCommandLineOption* helpOption;
    QCommandLineOption* versionOption;

    QStringList arguments;
};

#endif // COMMANDLINE_H
