#ifndef SETTINGS_H
#define SETTINGS_H

#include "datamanager/datamanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
<<<<<<< HEAD
#include "ui_widget.h"

class settings : public QWidget
=======
#ifdef WIDGET_H
#include "widget.h"
#endif
class settings:public QWidget
>>>>>>> origin/linux_maste
{
    Q_OBJECT
public:
    settings(Widget::Widget baseWindow);
private:
    QVBoxLayout* params;
    QHBoxLayout* element_data;
    QHBoxLayout* element_cur;
    QHBoxLayout* element_clean;
    QLabel* DataPath;
    QLineEdit* DataPathLine;
    QLabel* Currency;
    QLineEdit* CurrencyLine;
    QPushButton* clear;
    QPushButton* ok;
signals:

public slots:
    void okSlot();
    void cleanData();
    void cleanDataOk();
};

#endif // SETTINGS_H
