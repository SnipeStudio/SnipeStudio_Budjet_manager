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
    QHBoxLayout* element;
    QLabel* DataPath;
    QLineEdit* DataPathLine;
    QPushButton* ok;
signals:

public slots:
    void changePath();
};

#endif // SETTINGS_H
