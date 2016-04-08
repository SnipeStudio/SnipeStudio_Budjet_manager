#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "datamanager/datamanager.h"
#include "widget.h"
#include "sqlman/sqlman.h"
#include "logger/logger.h"

namespace Ui {
  class settings;
}

class settings : public QDialog
{
  Q_OBJECT

public:
  explicit settings(QWidget *parent, logger *log_ptr, sqlMan *sql=0);
  ~settings();

public slots:
   void okSlot();
    void cleanData();
    void cleanDataOk();
   // void showUserControl();

private:
  Ui::settings *ui;
  logger* loging;
  sqlMan* sqlManager;


};

#endif // SETTINGS_H
