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
  connect(ui->cleanButton,SIGNAL(clicked()),this,SLOT(cleanData()));
  connect(ui->okButton,SIGNAL(clicked()),this,SLOT(okSlot()));
  connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(close()));
  connect(ui->exportButton,SIGNAL(clicked()), this, SLOT(showExport()));
  connect(ui->importButton,SIGNAL(clicked()), this, SLOT(showImport()));
  connect(ui->select, SIGNAL(clicked()), this, SLOT(selectFolder()));
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
  }

void settings::cleanDataOk()
{
  sqlManager->clean();
}

//void settings::showUserControl()
//{

//}

void settings::okSlot()
{
    bool updatedLanguage = false;
    loging->debugM("OK");
    dataManager* data=new dataManager();
    loging->debugM("data init");
    if(ui->DataPathLine->text()!=data->getPath())
      {
        data->setPath((QDir::fromNativeSeparators(ui->DataPathLine->text())));
      }

    data->setCurrency(ui->CurrencyLine->text());
    loging->debugM(data->GetCurrency());
    if(ui->TranslationSelect->currentText() != data->getMenuTranslation())
    {
        updatedLanguage = true;
    }
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
    if(updatedLanguage)
    {
        QMessageBox* a = new QMessageBox(this);
        a->setText(tr("You need to restart application to language settings will be applied"));
        connect(a,SIGNAL(accepted()),a,SLOT(close()));
        a->show();
    }
    else
    {

        close();
        loging->debugM("done");
    }
}

void settings::showExport()
{
    loging->debugM("showExport called");
    Export* ex = new Export(0, sqlManager->getModel());
    connect(ex,SIGNAL(finished(int)),this,SLOT(updateDatabase()));
    ex->show();
}

void settings::showImport()
{
    loging->debugM("showImport called");
    Import* ex = new Import(0, sqlManager);
    connect(ex,SIGNAL(finished(int)),this,SLOT(updateDatabase()));
    ex->show();
}

void settings::selectFolder()
{
    dataManager* data = new dataManager();
    QFileDialog* selectFolderDialog = new QFileDialog(this);
    selectFolderDialog->setOption(QFileDialog::DontUseNativeDialog);
    selectFolderDialog->setFileMode(QFileDialog::Directory);
    selectFolderDialog->setOption(QFileDialog::ShowDirsOnly);
    selectFolderDialog->setDirectory(data->getPath());
    if(selectFolderDialog->exec())
    {
        QString directory = selectFolderDialog->selectedFiles()[0];
        ui->DataPathLine->setText(directory);
    }
    delete data;
}



