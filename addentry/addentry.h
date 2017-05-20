#ifndef ADDENTRY_H
#define ADDENTRY_H

#include <QDialog>
#include <QDateTime>
#include "logger/logger.h"
#include "sqlman/sqlman.h"
#include <qvector.h>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class addEntry;
}

class addEntry : public QDialog {
  Q_OBJECT

public:
  explicit addEntry(bool side, sqlMan *sqlOut, QWidget *parent = 0);
  ~addEntry();

private:
  Ui::addEntry *ui;
  sqlMan *sql;
  bool side;
  double summ;

public slots:
  void on_cancel_clicked();
  void on_confirmChanges_clicked();
  void enable();
};

#endif // ADDENTRY_H
