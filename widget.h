#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMenu>
#include <QAction>
<<<<<<< HEAD

=======
>>>>>>> origin/linux_maste
#include <QTableWidgetItem>
#include <fstream>
#ifndef SETTINGS_H
#include "settings.h"
#endif
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
public slots:
    void closeEvent(QCloseEvent*);
    void help();
    void addOperation();
    void save();
    void load();
<<<<<<< HEAD
=======
    void NextMonth();
    void PrevMonth();
    void showSettings();
>>>>>>> origin/linux_maste
};

#endif // WIDGET_H
