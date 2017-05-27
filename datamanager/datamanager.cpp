#include "datamanager.h"

dataManager::dataManager() {
  QString dataFolder = QDir::homePath() + "/ssbm/";
  QString fileNameSettings = dataFolder + "settings.cfg";
  QFile file(fileNameSettings);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    in.setCodec(QTextCodec::codecForName("UTF-8"));
    QString line = in.readLine();
    QStringList result;
    while (!line.isNull()) {
      result.append(line.split(QString('=')));
      line.remove(QRegExp("//[\\W\\w]{0,}"));
      if (result.at(0) == "Currency") {
        Currency = result.at(1);
      }

      if (result.at(0) == "Translation") {
        Translation = result.at(1);
      }

      if (result.at(0) == "DefaultUser") {
        DefUser = result.at(1);
      }

      if (result.at(0) == "Loglevel") {
        Loglevel = result.at(1).toInt();
      }

      line = in.readLine();
      result.clear();
    }
  } else {
    if (file.open(QIODevice::WriteOnly)) {
      QTextStream out(&file);
      out.setCodec("UTF-8");
      out << "DataPath=" << dataFolder << "\n";
      out << "Currency=\n";
      out << "Translation=en\n";
      out << "DefaultUser=\n";
      out << "LogLevel=0\n";
    }
    dataPath = dataFolder;
  }

  file.close();
  QDir dataDir(dataPath);
  if (!dataDir.exists()) {
    dataDir.mkpath(dataPath);
  }
}

dataManager::~dataManager() {
  // for correctly load settings file
  QString dataFolder = QDir().homePath() + "/ssbm/";
  QString fileNameSettings = dataFolder + "settings.cfg";
  QFile file(fileNameSettings);
  if (file.open(QIODevice::WriteOnly)) {
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << QString("DataPath=%1\n").arg(dataPath);
    out << QString("Currency=%1\n").arg(Currency);
    out << QString("Translation=%1\n").arg(Translation);
    out << QString("DefaultUser=%1\n").arg(DefUser);
    out << QString("Loglevel=%1\n").arg(Loglevel);
  }
  file.close();
}

QString dataManager::getPath() {
  if (dataPath == "") {
    return QDir::homePath() + "/ssbm/";
  }

  return dataPath;
}

QString dataManager::GetCurrency() { return Currency; }

QString dataManager::getTranslation() {
  if (Translation == "") {
    return "en";
  }

  return Translation;
}

QString dataManager::getMenuTranslation() {
  if (Translation == "ru") {
    return tr("ru");
  }

  if (Translation == "de") {
    return tr("de");
  }
  if (Translation == "nl") {
    return tr("nl");
  }
  if (Translation == "fr") {
    return tr("fr");
  }

  return tr("en");
}

QString dataManager::getDefaultUser() { return DefUser; }

int dataManager::getLoglevel() { return Loglevel; }

void dataManager::setPath(QString data) { dataPath = data; }

void dataManager::setCurrency(QString currency) { Currency = currency; }

void dataManager::setTranslation(QString translation) {
  Translation = translation;
  if (Translation == tr("ru")) {
    Translation = "ru";
  } else if (Translation == tr("de")) {
    Translation = "de";
  } else if (Translation == tr("nl")) {
    Translation = "nl";
  } else if (Translation == tr("fr")) {
    Translation = "fr";
  } else {
    Translation = "en";
  }
}

// for future use
void dataManager::setDefaultUser(QString DefaultUser) { DefUser = DefaultUser; }

// sets log level
void dataManager::setLogLevel(int lLevel) { Loglevel = lLevel; }
void dataManager::loadTranslator() {
  QString translationPath =
      QDir::toNativeSeparators(QString("%1/translations/ssbm_%2.qm")
                                   .arg(this->getPath())
                                   .arg(this->getTranslation()));
  translator.load(translationPath);
  if (qApp->installTranslator(&translator)) {
  }
}

void dataManager::reloadTranslator() {
  qApp->removeTranslator(&translator);
  this->loadTranslator();
}
