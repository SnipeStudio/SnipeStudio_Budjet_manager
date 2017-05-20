#ifndef LOGGER_H
#define LOGGER_H
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QTime>
#include "../datamanager/datamanager.h"

class logger {
public:
  logger();
  void close();
  void Info(QString infoMessage);
  void Debug(QString debugMessage);
  enum logLevel { off = 0, info = 1, debug = 2 };
  void Error(QString errorMessage);
  void Warning(QString warningMessage);

private:
  QFile log;
  QString timeFormat;
  dataManager *data;
};

#endif // LOGGER_H
