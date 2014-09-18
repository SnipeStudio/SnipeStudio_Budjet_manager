#include "widget.h"

settings::settings(Widget* baseWindow) :
    QWidget()
{

    dataManager* data=new dataManager();
    params=new QVBoxLayout();
    element_data=new QHBoxLayout();
    element_cur=new QHBoxLayout();
    element_clean=new QHBoxLayout();
    DataPath=new QLabel();
    DataPath->setText(tr("Data Path:"));
    DataPathLine=new QLineEdit();
    Currency=new QLabel(tr("Currency"));
    CurrencyLine=new QLineEdit();
    Translation=new QLabel(tr("Translation"));
    TranslationSelect=new QComboBox();
    TranslationSelect->addItem(tr("English"));
    TranslationSelect->addItem(tr("Russian"));
    TranslationSelect->addItem(tr("German"));
    TranslationSelect->addItem(tr("Dutch"));
    TranslationSelect->setCurrentIndex(TranslationSelect->findText(data->getMenuTranslation()));
    clear=new QPushButton(tr("Clean data"));
    element_data->addWidget(DataPath);
    element_data->addWidget(DataPathLine);
    params->addLayout(element_data);
    element_cur->addWidget(Currency);
    element_cur->addWidget(CurrencyLine);
    element_cur->addWidget(Translation);
    element_cur->addWidget(TranslationSelect);
    element_clean->addWidget(clear);
    params->addLayout(element_cur);
    params->addLayout(element_clean);
    ok=new QPushButton(tr("Ok"));
    baseWindowAddr=baseWindow;
    DataPathLine->setText(data->getPath());
    CurrencyLine->setText(data->GetCurrency());
    params->addWidget(ok);
    this->setLayout(params);
    this->setWindowTitle(tr("Settings"));
    connect(clear,SIGNAL(clicked()),this,SLOT(cleanData()));
    connect(ok,SIGNAL(clicked()),this,SLOT(close()));
    connect(ok,SIGNAL(clicked()),this,SLOT(okSlot()));
    connect(this,SIGNAL(destroyed()),baseWindow,SLOT(load()));
    delete data;
}


void settings::okSlot()
{
   dataManager* data=new dataManager();
   if(DataPathLine->text()!=data->getPath())
     {
       data->setPath((QDir::fromNativeSeparators(DataPathLine->text())));
     }

   data->setCurrency(CurrencyLine->text());
   data->setTranslation(TranslationSelect->currentText());
   delete data;
   baseWindowAddr->load();
   close();
   baseWindowAddr->closeSettings();


}

void settings::cleanData()
{
  QMessageBox* a=new QMessageBox(this);
  a->setText(tr("All data will be cleaned. Use at your own risk. Don't forgot to click load"));
  a->addButton(tr("cancel"),a->RejectRole);
  a->addButton(tr("ok"),a->AcceptRole);
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
