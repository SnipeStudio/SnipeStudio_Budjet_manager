#ifndef WIDGET_H
#define WIDGET_H
#include "settings/settings.h"
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QShortcut>
#include <fstream>
#include <QTableView>
#include "datamanager/datamanager.h"
#include "sqlman/sqlman.h"
#include "app_info.h"
#include "logger/logger.h"
#include "editentry/editentry.h"
#include "addentry/addentry.h"

#ifdef SETTINGS_H
class settings;
#endif
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0, logger *log_ptr = 0);
    ~Widget();

private:
  void initDatabase(sqlMan *db);
    Ui::Widget *ui;
    QString tmp;
    QString version;
    settings* set;
    bool fLoad;
    unsigned long idLoaded;
    sqlMan* db;
    logger* loging;
    editentry* editdialog;
    QShortcut* keyEnter;
    QShortcut* keyDelete;
    bool lockBool;

public slots:
    void help();
    void addOperation(bool side);
    void load();
    void showSettings();
    void resetTime();
    void editTrigger(QModelIndex index);
    void updateDatabase();
    void deleteEntry();
    void addProfit();
    void addExpence();
    void enableWindow();
protected:
     void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_H
