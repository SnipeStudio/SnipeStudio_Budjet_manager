#include "commandline.h"

commandLine::commandLine(int argc, char* argv[])
{
    for(int i = 1; i < argc; i++)
    {
        QString str = QString((argv[i]));
        arguments.push_front(str);
    }

    parser = new QCommandLineParser();

    console = new QCommandLineOption(QStringList() << "c" << "console",
            QCoreApplication::translate("main", "Allows use console variables."));
    parser->addOption(*console);

    helpOption = new QCommandLineOption(parser->addHelpOption());
    versionOption = new QCommandLineOption(parser->addVersionOption());
    parser->parse(arguments);
}

bool commandLine::IsCommandLine()
{
    isCommandLine = parser->isSet(*console);

    if(isCommandLine)
    {
        QTextStream(stdout) << "Console Mode Activated" << endl;
    }
    return isCommandLine;
}

bool commandLine::IsHelp()
{
    isCommandLine = parser->isSet(*helpOption);


    if(isHelp)
    {
         QTextStream(stdout) << parser->helpText() << endl;
    }
    return isHelp;
}

bool commandLine::IsVersion()
{
    isVersion = parser->isSet(*versionOption);
    QTextStream(stdout) << isVersion << endl;

    if(isVersion)
    {
        parser->showVersion();
    }
    return isVersion;
}
