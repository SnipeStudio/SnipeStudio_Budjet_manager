#include "settings.h"

settings::settings(Widget baseWindow) :
    QWidget()
{
    dataManager* data=new dataManager();
    params=new QVBoxLayout();
    element_data=new QHBoxLayout();
    element_cur=new QHBoxLayout();
    element_clean=new QHBoxLayout();
    DataPath=new QLabel();
    DataPath->setText("Data Path:");
    DataPathLine=new QLineEdit();
    Currency=new QLabel("Currency");
    CurrencyLine=new QLineEdit();
    clear=new QPushButton("Clean data");
    element_data->addWidget(DataPath);
    element_data->addWidget(DataPathLine);
    params->addLayout(element_data);
    element_cur->addWidget(Currency);
    element_cur->addWidget(CurrencyLine);
    element_clean->addWidget(clear);
    params->addLayout(element_cur);
    params->addLayout(element_clean);
    ok=new QPushButton("Ok");

    DataPathLine->setText(data->getPath());
    CurrencyLine->setText(data->GetCurrency());
    params->addWidget(ok);
    this->setLayout(params);
    this->setWindowTitle("Settings");
    connect(clear,SIGNAL(clicked()),this,SLOT(cleanData()));
    connect(ok,SIGNAL(clicked()),this,SLOT(close()));
    connect(ok,SIGNAL(clicked()),this,SLOT(okSlot()));
    connect(ok,SIGNAL(clicked()),baseWindow,SLOT(load));
    delete data;
}

void settings::okSlot()
{
  QMessageBox* a=new QMessageBox(this);
   dataManager* data=new dataManager();
   if(DataPathLine->text()!=data->getPath())
     {
       data->setPath(DataPathLine->text());
       connect(a,SIGNAL(accepted()),
     }

   data->setCurrency(CurrencyLine->text());
   delete data;
   a->setText(tr("Your settings saved. \n Visual changes will be applied after program restart or press load"));
   a->setWindowTitle(tr("Data saved"));
   connect(a,SIGNAL(buttonClicked(QAbstractButton*)),a,SLOT(close()));
   a->show();
   close();
}

void settings::cleanData()
{
  QMessageBox* a=new QMessageBox(this);
  a->setText(tr("All data will be cleaned. Use at your own risk. Don't forgot to click load"));
  a->addButton("cancel",a->RejectRole);
  a->addButton("ok",a->AcceptRole);
  a->show();
  connect(a,SIGNAL(accepted()),this,SLOT(cleanDataOk()));
  connect(a,SIGNAL(rejected()),a,SLOT(close()));
      connect(a,SIGNAL(accepted()),a,SLOT(close()));
  }

void settings::cleanDataOk()
{
  dataManager* data=new dataManager();
  if(!data->getPath().isEmpty())
  {
    QFile::remove(data->getPath());
  }
  delete data;
}
