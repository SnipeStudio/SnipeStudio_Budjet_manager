#include "logger.h"

logger::logger()
{

    log.setFileName("ssbm.log");
    log.open(QIODevice::Append);
}

void logger::close()
{
    log.close();
}

void logger::info(QString infoMessage)
{
    QTextStream fout(&log);
    fout<<infoMessage+"\n";
}

void logger::verbose(QString verboseMessage)
{
    QTextStream fout(&log);
    fout<<verboseMessage+"\n";
}

void logger::debug(QString debugMessage)
{
    QTextStream fout(&log);
    fout<<debugMessage+"\n";
}

void logger::setVerbosity(int logLevel)
{
    switch(logLevel)
    {
    case 0:
        verbosity=0;
        break;
    case 1:
        verbosity=1;
        break;
    case 2:
        verbosity=2;
        break;
    default:
        verbosity=0;
    }
}

void logger::writeLog(QString message, int logLevel)
{
    switch(logLevel)
    {
    case 0:
        info(message);
        break;
    case 1:
        verbose(message);
        break;
    case 2:
        debug(message);
        break;
    default:
        info(message);
    }
}

void logger::writeLog(QString message)
{
    switch(verbosity)
    {
    case 0:
        info(message);
        break;
    case 1:
        verbose(message);
        break;
    case 2:
        debug(message);
        break;
    default:
        info(message);
    }
}


