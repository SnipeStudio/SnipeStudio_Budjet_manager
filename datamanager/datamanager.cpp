#include "datamanager.h"

dataManager::dataManager() {
  QString dataFolder = QDir::homePath() + "/ssbm/";
  QDir dataDir(dataPath);
  if (!dataDir.exists()) {
    dataDir.mkpath(dataPath);
  }
  QString fileNameSettings = dataFolder + "settings.cfg";
  set = new QSettings(fileNameSettings, QSettings::IniFormat);
  reloadSettings();
}

void dataManager::writeSettings() {
  set->setValue("Currency", Currency);
  set->setValue("Translation", Translation);
  set->setValue("DefaultUser", DefUser);
  set->setValue("Loglevel", Loglevel);
}

dataManager::~dataManager() {
  writeSettings();
  delete set;
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

void dataManager::reloadSettings() {
  set->sync();
  Currency = set->value("Currency").toString();
  Translation = set->value("Translation").toString();
  DefUser = set->value("DefaultUser").toString();
  Loglevel = set->value("Loglevel").toInt();
}

void dataManager::setPath(QString data) {
  dataPath = data;
  reloadSettings();
}

void dataManager::setCurrency(QString currency) {
  Currency = currency;
  writeSettings();
  reloadSettings();
}

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

  writeSettings();
  reloadSettings();
}

// for future use
void dataManager::setDefaultUser(QString DefaultUser) {
  DefUser = DefaultUser;

  writeSettings();
  reloadSettings();
}

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

  writeSettings();
  reloadSettings();
}
