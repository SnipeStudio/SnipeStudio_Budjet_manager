#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent, logger *log_ptr, sqlMan* sql) :
  QDialog(parent),
  ui(new Ui::settings)
{
  ui->setupUi(this);
  loging=log_ptr;
  sqlManager=sql;
  loging->debugM("Initializing settings menu");
  loging->debugM("Enabling slots");
  connect(ui->clear,SIGNAL(clicked()),this,SLOT(cleanData()));
  connect(ui->okButton,SIGNAL(clicked()),this,SLOT(okSlot()));
  connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(close()));
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
  loging->debugM("Initializing settings menu: Done");
   delete data;
}

settings::~settings()
{
    delete ui;
}

void settings::cleanData()
{
  QMessageBox* a=new QMessageBox(this);
  a->setText(tr("All data will be cleaned. Use at your own risk."));
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
  sqlManager->clean(sqlManager);
  delete data;
}

//void settings::showUserControl()
//{

//}

void settings::okSlot()
{
    loging->debugM("OK");
    dataManager* data=new dataManager();
    loging->debugM("data init");
    if(ui->DataPathLine->text()!=data->getPath())
      {
        data->setPath((QDir::fromNativeSeparators(ui->DataPathLine->text())));
      }

    data->setCurrency(ui->CurrencyLine->text());
    loging->debugM(data->GetCurrency());
    data->setTranslation(ui->TranslationSelect->currentText());

    if(ui->verbositySelect->currentText()=="off")
    {
        data->setLogLevel(loging->off);
    }
    if(ui->verbositySelect->currentText()=="info")
    {
        data->setLogLevel(loging->info);
    }
    if(ui->verbositySelect->currentText()=="debug")
    {
        data->setLogLevel(loging->debug);
    }

    loging->debugM("settings saved");
    delete data;
    close();
    loging->debugM("done");
}
