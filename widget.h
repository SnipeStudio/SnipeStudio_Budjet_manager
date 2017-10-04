#ifndef WIDGET_H
#define WIDGET_H
#include "addentry/addentry.h"
#include "app_info.h"
#include "datamanager/datamanager.h"
#include "editentry/editentry.h"
#include "logger/logger.h"
#include "settings/settings.h"
#include "sqlman/sqlman.h"
#include <QAction>
#include <QDialogButtonBox>
#include <QMenu>
#include <QMessageBox>
#include <QShortcut>
#include <QTableView>
#include <QWidget>
#include <fstream>

#ifdef SETTINGS_H
class settings;
#endif
namespace Ui {
class Widget;
}

class Widget : public QWidget {
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0, logger *log_ptr = 0,
                  dataManager *dataMan = 0);
  ~Widget();

private:
  void initDatabase(sqlMan *db);
  dataManager *data;
  Ui::Widget *ui;
  QString tmp;
  QString version;
  settings *set = NULL;
  bool fLoad;
  unsigned long idLoaded;
  sqlMan *db;
  logger *loging;
  editentry *editdialog;
  QShortcut *keyEnter;
  QShortcut *keyDelete;
  QShortcut *keyPlus;
  QShortcut *keyMinus;
  bool lockBool;

public slots:
  void help();
  void addOperation(bool side);
  void load();
  void showSettings();
  void closeSettings();
  void editTrigger(QModelIndex index);
  void updateDatabase();
  void deleteEntry();
  void addProfit();
  void addExpence();
  void enableWindow();
  void closeEvent();
};

#endif // WIDGET_H
