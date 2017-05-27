#include "logger.h"

logger::logger() {
  data = new dataManager();
  log.setFileName(QDir::toNativeSeparators(data->getPath() + "ssbm.log"));
  log.open(QIODevice::Append);
  timeFormat = "hh:mm:ss.zzz";
  delete data;
}

void logger::close() { log.close(); }

void logger::Info(QString infoMessage) {
  data = new dataManager();
  if (data->getLoglevel() > 0) {
    QTextStream fout(&log);
    fout << QTime::currentTime().toString(timeFormat) << ",I,"
         << infoMessage + "\n";
  }

  delete data;
}

void logger::Debug(QString debugMessage) {
  data = new dataManager();
  if (data->getLoglevel() > 1) {
    QTextStream fout(&log);
    fout << QTime::currentTime().toString(timeFormat) << ",D, "
         << debugMessage + "\n";
  }

  delete data;
}

void logger::Error(QString errorMessage) {
  data = new dataManager();
  if (data->getLoglevel() > 0) {
    QTextStream fout(&log);
    fout << QTime::currentTime().toString(timeFormat) << ",E,"
         << errorMessage + "\n";
  }

  delete data;
}

void logger::Warning(QString warningMessage) {
  data = new dataManager();
  if (data->getLoglevel() > 1) {
    QTextStream fout(&log);
    fout << QTime::currentTime().toString(timeFormat) << ",W,"
         << warningMessage + "\n";
  }

  delete data;
}
