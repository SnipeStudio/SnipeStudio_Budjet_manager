#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent,logger *loging) :
  QDialog(parent),
  ui(new Ui::settings)
{
    loging->debugM("Initializing settings menu");
  ui->setupUi(this);
  loging->debugM("Enabling slots");
  connect(ui->clear,SIGNAL(clicked()),this,SLOT(cleanData()));
  connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(close()));
  connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(okSlot()));
  loging->debugM("Enabling slots: Done");
  dataManager* data=new dataManager();
  loging->debugM(QString("Set translations to: %1").arg(data->getMenuTranslation()));
  ui->TranslationSelect->setCurrentIndex(ui->TranslationSelect->findText(data->getMenuTranslation()));
  loging->debugM("Set DataPath to:" + data->getPath());
  ui->DataPathLine->setText(data->getPath());
  loging->debugM("Set Currency to:" + data->GetCurrency());
  ui->CurrencyLine->setText(data->GetCurrency());
  int loglevel = data->getLoglevel();
  if(loglevel<0 || loglevel>2)
  {
      data->setLogLevel(2);
      loging->debugM(QString("Change log level to debug due to:%1").arg(loglevel));
  }
  loging->debugM(QString("Set Log Level to: %1").arg(data->getLoglevel()));
  ui->verbositySelect->setCurrentIndex(data->getLoglevel());
  delete data;
  loging->debugM("Initializing settings menu: Done");
}

settings::~settings()
{
  delete ui;
}

void settings::okSlot()
{
   dataManager* data=new dataManager();
   if(ui->DataPathLine->text()!=data->getPath())
     {
       data->setPath((QDir::fromNativeSeparators(ui->DataPathLine->text())));
     }

   data->setCurrency(ui->CurrencyLine->text());
   data->setTranslation(ui->TranslationSelect->currentText());
   switch (ui->verbositySelect->currentIndex()) {
   case 0:
       data->setLogLevel(0);
       break;
   case 1:
       data->setLogLevel(1);
       break;
   case 2:
       data->setLogLevel(2);
       break;
   default:
       data->setLogLevel(2);
       break;
   }
   delete data;
   close();


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
  sqlMan* sql=new sqlMan();
  sql->clean();
  delete sql;
  delete data;
}
