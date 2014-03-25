#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QTableWidgetItem>

#include "datamanager/datamanager.h"
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
public slots:
    void closeEvent(QCloseEvent*);
    void help();
    void addOperation();
};

#endif // WIDGET_H
