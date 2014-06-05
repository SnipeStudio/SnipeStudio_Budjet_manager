#ifndef WIDGET_H
#define WIDGET_H
#include "settings.h"
#ifdef SETTINGS_H
class settings;
#endif
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QTableWidgetItem>
#include <QDialogButtonBox>
#include <fstream>
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
public slots:
    void closeEvent(QCloseEvent*);
    void help();
    void addOperation();
    void save();
    void load();
    void NextMonth();
    void PrevMonth();
    void showSettings();
    void updLoad(bool);
};

#endif // WIDGET_H
