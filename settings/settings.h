#ifndef SETTINGS_H
#define SETTINGS_H

#include "datamanager/datamanager.h"
#include "export/export.h"
#include "import/import.h"
#include "logger/logger.h"
#include "sqlman/sqlman.h"
#include "widget.h"
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class settings;
}

class settings : public QDialog {
  Q_OBJECT

public:
  settings(QWidget *parent, logger *log_ptr, sqlMan *sql = 0,
           dataManager *dataman = 0);
  ~settings();

public slots:
  void okSlot();
  void cleanData();
  void cleanDataOk();
  void showExport();
  void showImport();
  void selectFolder();
  void enableWindow();
  // void showUserControl();

private:
  Ui::settings *ui;
  logger *loging;
  sqlMan *sqlManager;
  QPushButton *select;
  dataManager *data;
};

#endif // SETTINGS_H
