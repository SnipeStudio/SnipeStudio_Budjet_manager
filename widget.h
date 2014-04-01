#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMenu>
#include <QAction>

#include <QTableWidgetItem>
#include "settings.h"
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
public slots:
    void closeEvent(QCloseEvent*);
    void help();
    void addOperation();
    void save();
};

#endif // WIDGET_H
