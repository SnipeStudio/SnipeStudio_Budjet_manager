#ifndef WIDGET_H
#define WIDGET_H
#include "settings/settings.h"
#ifdef SETTINGS_H
class settings;
#endif


#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <fstream>
#include <QTableView>
#include "datamanager/datamanager.h"
#include "sqlman/sqlman.h"
#include "app_info.h"
#include "logger/logger.h"
#include "editentry/editentry.h"
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
  bool initDatabase(sqlMan *db);
    Ui::Widget *ui;
    QString tmp;
    QString version;
    settings* set;
    bool fLoad;
    unsigned long idLoaded;
    sqlMan* db;
    logger* loging;
    editentry* editdialog;

public slots:
    void help();
    void addOperation();
    void load();
    void showSettings();
    void closeSettings();
    void editTrigger(QModelIndex index);

    void updateDatabase();
    //void editEntry();

};

#endif // WIDGET_H
