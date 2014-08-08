#ifndef WIDGET_H
#define WIDGET_H
#include "settings.h"
#ifdef SETTINGS_H
class settings;
#endif


#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QDialogButtonBox>
#include <fstream>
#include <QTableView>
#include "datamanager/datamanager.h"
#include "sqlman/sqlman.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QString tmp;
    QString version;
    settings* set;
    short monthSelected;
    short yearSelected;
    bool fLoad;
    unsigned long idLoaded;
    sqlMan db;
public slots:
    void updLoad(bool);
    void closeEvent(QCloseEvent*);
    void help();
    void addOperation();
    void save();
    void load();
    void NextMonth();
    void PrevMonth();
    void showSettings();
};

#endif // WIDGET_H
