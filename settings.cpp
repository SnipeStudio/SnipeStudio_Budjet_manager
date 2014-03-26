#include "settings.h"

settings::settings(QWidget *parent) :
    QWidget(parent)
{
    dataManager* data=new dataManager();
    params=new QVBoxLayout();
    element=new QHBoxLayout();
    params=new QVBoxLayout();
    element=new QHBoxLayout();
    DataPath=new QLabel();
    DataPath->setText("Data Path:");
    DataPathLine=new QLineEdit();
    element->addWidget(DataPath);
    element->addWidget(DataPathLine);
    params->addLayout(element);
    ok=new QPushButton("Ok");
    DataPathLine->setText(data->getPath());
    params->addWidget(ok);
    this->setLayout(params);
    this->setWindowTitle("Settings");
    connect(ok,SIGNAL(clicked()),this,SLOT(close()));
    connect(ok,SIGNAL(clicked()),this,SLOT(changePath()));
    delete data;
}

void settings::changePath()
{
   dataManager* data=new dataManager();
   data->setPath(DataPathLine->text());
   delete data;
}
