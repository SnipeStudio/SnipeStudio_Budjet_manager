#include "settings.h"

settings::settings(QWidget *parent) :
    QWidget(parent)
{
    dataManager* data=new dataManager();
    params=new QVBoxLayout();
    element_data=new QHBoxLayout();
    element_cur=new QHBoxLayout();
    DataPath=new QLabel();
    DataPath->setText("Data Path:");
    DataPathLine=new QLineEdit();
    Currency=new QLabel("Currency");
    CurrencyLine=new QLineEdit();
    element_data->addWidget(DataPath);
    element_data->addWidget(DataPathLine);
    params->addLayout(element_data);
    element_cur->addWidget(Currency);
    element_cur->addWidget(CurrencyLine);
    params->addLayout(element_cur);
    ok=new QPushButton("Ok");
    DataPathLine->setText(data->getPath());
    CurrencyLine->setText(data->GetCurrency());
    params->addWidget(ok);
    this->setLayout(params);
    this->setWindowTitle("Settings");
    connect(ok,SIGNAL(clicked()),this,SLOT(close()));
    connect(ok,SIGNAL(clicked()),this,SLOT(okSlot()));
    delete data;
}

void settings::okSlot()
{
   dataManager* data=new dataManager();
   data->setPath(DataPathLine->text());
   data->setCurrency(CurrencyLine->text());
   delete data;
   QMessageBox* a=new QMessageBox(this);
   a->setText(tr("Your settings saved. \n Visual changes will be applied after program restart or press load"));
   a->setWindowTitle(QString::fromStdString("Data saved"));
   connect(a,SIGNAL(buttonClicked(QAbstractButton*)),a,SLOT(close()));
   a->show();
   close();
}
