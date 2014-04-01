#ifndef SETTINGS_H
#define SETTINGS_H

#include "datamanager/datamanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class settings : public QWidget
{
    Q_OBJECT
public:
    settings(QWidget *parent = 0);
private:
    QVBoxLayout* params;
    QHBoxLayout* element_data;
    QHBoxLayout* element_cur;
    QLabel* DataPath;
    QLineEdit* DataPathLine;
    QLabel* Currency;
    QLineEdit* CurrencyLine;
    QPushButton* ok;
signals:

public slots:
    void okSlot();
};

#endif // SETTINGS_H
