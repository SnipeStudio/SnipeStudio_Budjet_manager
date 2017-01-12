#include "commandline.h"

commandLine::commandLine(int argc, char* argv[])
{
    for(int i = 0; i < argc; i++)
    {
        QString str = QString((argv[i]));
        arguments.push_back(str);
    }

    parser = new QCommandLineParser();

    // TODO: Probably this is unesessary (IDK)
    console = new QCommandLineOption(QStringList() << "c" << "console",
                                     QCoreApplication::translate("main", "Allows use console variables."));
    parser->addOption(*console);
    exportOption = new QCommandLineOption(QStringList() << "e" << "export",
                                          QCoreApplication::translate("main", "Exporting database to <file>."),
                                          QCoreApplication::translate("main", "file"));
    parser->addOption(*exportOption);
    helpOption = new QCommandLineOption(parser->addHelpOption());
    versionOption = new QCommandLineOption(parser->addVersionOption());
    parser->parse(arguments);
    if(isCommandLine)
    {
        std::cout << "Command mode activated" << std::endl;
    }

    IsHelp();
    IsVersion();
    IsExport();
}

void commandLine::initDatabase(sqlMan* db)
{
    model = db->getModel();
    model->setTable("operations");
    if(!db->dbIsOpen())
    {
        std::cerr << "Error in Db Loading. There are some shit happens during database loading"<< std::endl;
        exit (1);
    }

    std::cout << "Database initialized succesfully"<< std::endl;
}

bool commandLine::IsCommandLine()
{
    isCommandLine = parser->isSet(*console);
    return isCommandLine;
}

bool commandLine::IsHelp()
{
    isHelp = parser->isSet(*helpOption);
    if(isHelp)
    {
        std::cout << parser->helpText().toStdString() << std::endl;
    }

    return isHelp;
}

bool commandLine::IsVersion()
{
    isVersion = parser->isSet(*versionOption);
    if(isVersion)
    {
        std::cout << VER_FILEVERSION_STR << std::endl;
    }

    return isVersion;
}

bool commandLine::IsExport()
{
    isExport = parser->isSet(*exportOption);
    if(isExport)
    {
        db = new sqlMan();
        initDatabase(db);
        model = db->getModel();
        std::cout << "Exporting mode On" << std::endl;
        if(!exportConsole(parser->value(*exportOption)))
        {
            std::cout << "Succesfully exported to " << parser->value(*exportOption).toStdString() << std::endl;
        }
        else
        {
            std::cerr << "Failed to export " << parser->value(*exportOption).toStdString() << std::endl;
        }
    }

    return isVersion;
}

bool commandLine::exportConsole(QString path)
{
    QFile* file;
    try{
        int columns = model->columnCount();
        QString filename = QDir::toNativeSeparators(path);
        file = new QFile(filename);
        file->open(QIODevice::Append);
        do
        {
            model->fetchMore();
        } while(model->canFetchMore());

        int rows = model->rowCount();
        QTextStream fout(file);
        fout << rows << "\n";
        for(long row = 0; row < rows; row++)
        {
            QString line = "";
            for (int column = 0; column < columns; column++)
            {
                QModelIndex index = model->index(row, column);
                line+= model->data(index).toString() + ";";
            }

            fout<<line<<"\n";
        }
        file->close();
        return 0;
    }
    catch(QException)
    {
        if(file)
        {
            file->close();
        }
        return 1;
    }
}
