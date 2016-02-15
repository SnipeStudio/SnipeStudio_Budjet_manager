#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::settings)
{

  ui->setupUi(this);
  connect(ui->clear,SIGNAL(clicked()),this,SLOT(cleanData()));
  connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(close()));
  connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(okSlot()));
  ui->TranslationSelect->addItem(tr("English"));
  ui->TranslationSelect->addItem(tr("Russian"));
  ui->TranslationSelect->addItem(tr("German"));
  ui->TranslationSelect->addItem(tr("Dutch"));
  dataManager* data=new dataManager();
  ui->TranslationSelect->setCurrentIndex(ui->TranslationSelect->findText(data->getMenuTranslation()));
  delete data;
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
