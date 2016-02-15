#ifndef LOGGER_H
#define LOGGER_H
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QTime>

class logger
{
public:
    logger();
    void close();
    void info(QString infoMessage);
    void verbose(QString verboseMessage);
    void debug(QString debugMessage);
    void setVerbosity(int logLevel);
    void writeLog(QString message,int logLevel);
    void writeLog(QString message);


private:
    QFile log;
    int verbosity;

};

#endif // LOGGER_H
