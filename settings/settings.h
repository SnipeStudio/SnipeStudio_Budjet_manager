#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "datamanager/datamanager.h"
#include "widget.h"
#include "sqlman/sqlman.h"

namespace Ui {
  class settings;
}

class settings : public QDialog
{
  Q_OBJECT

public:
  explicit settings(QWidget *parent = 0);
  ~settings();

public slots:
    void okSlot();
    void cleanData();
    void cleanDataOk();

private:
  Ui::settings *ui;


};

#endif // SETTINGS_H
