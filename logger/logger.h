#ifndef LOGGER_H
#define LOGGER_H
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QTime>
#include "../datamanager/datamanager.h"

class logger
{
public:
    logger();
    void close();
    void infoM(QString infoMessage);
    void debugM(QString debugMessage);
    enum logLevel{
        off=0,
        info=1,
        debug=2
    };
    void errorM(QString errorMessage);
    void warningM(QString warningMessage);
private:
    QFile log;
    const QString timeFormat = "hh:mm:ss.zzz";
    dataManager* data;

};

#endif // LOGGER_H
