#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <QSettings>
#include <QTextCodec>
#include <QtCore/QFile>
#include <sqlman/sqlman.h>

class dataManager : public QObject {
  Q_OBJECT
public:
  dataManager();
  ~dataManager();
  void loadTranslator();
  void reloadTranslator();
  QString getPath();
  QString GetCurrency();
  QString getTranslation();
  QString getMenuTranslation();
  QString getDefaultUser();
  int getLoglevel();
  void reloadSettings();

signals:
public slots:
  void setPath(QString data);
  void setCurrency(QString currency);
  void setTranslation(QString translation);
  void setDefaultUser(QString DefaultUser);
  void setLogLevel(int lLevel);

private:
  QTranslator translator;
  QString dataPath;
  QString configPath;
  QString Currency;
  QString Translation;
  QString DefUser;
  int Loglevel;
  QSettings *set;
  void writeSettings();
};

#endif // DATAMANAGER_H
