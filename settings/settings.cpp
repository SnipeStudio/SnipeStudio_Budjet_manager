#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent, logger *log_ptr, sqlMan *sql)
    : QDialog(parent), ui(new Ui::settings) {
  ui->setupUi(this);
  loging = log_ptr;
  sqlManager = sql;
  loging->Debug("Initializing settings menu");
  loging->Debug("Enabling slots");
  connect(ui->cleanButton, SIGNAL(clicked()), this, SLOT(cleanData()));
  connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okSlot()));
  connect(ui->Cancel, SIGNAL(clicked()), this, SLOT(close()));
  connect(ui->exportButton, SIGNAL(clicked()), this, SLOT(showExport()));
  connect(ui->importButton, SIGNAL(clicked()), this, SLOT(showImport()));
  connect(ui->select, SIGNAL(clicked()), this, SLOT(selectFolder()));
  loging->Debug("Enabling slots: Done");
  dataManager *data = new dataManager();
  data->reloadTranslator();
  ui->retranslateUi(this);
  loging->Debug(
      QString("Set translations to: %1").arg(data->getMenuTranslation()));
  ui->TranslationSelect->setCurrentIndex(
      ui->TranslationSelect->findText(data->getMenuTranslation()));
  loging->Debug("Set DataPath to:" + data->getPath());
  ui->DataPathLine->setText(data->getPath());
  loging->Debug("Set Currency to:" + data->GetCurrency());
  ui->CurrencyLine->setText(data->GetCurrency());
  int loglevel = data->getLoglevel();
  if (loglevel < 0 || loglevel > 2) {
    data->setLogLevel(2);
    loging->Debug(QString("Change log level to debug due to:%1").arg(loglevel));
  }

  loging->Debug(QString("Set Log Level to: %1").arg(data->getLoglevel()));
  ui->verbositySelect->setCurrentIndex(data->getLoglevel());
  loging->Debug("Initializing settings menu: Done");
  delete data;
}

settings::~settings() { delete ui; }

void settings::cleanData() {
  QMessageBox *a = new QMessageBox(this);
  a->setText(tr("All data will be cleaned. Use at your own risk."));
  a->addButton(tr("cancel"), a->RejectRole);
  a->addButton(tr("ok"), a->AcceptRole);
  a->show();
  connect(a, SIGNAL(accepted()), this, SLOT(cleanDataOk()));
  connect(a, SIGNAL(rejected()), a, SLOT(close()));
}

void settings::cleanDataOk() { sqlManager->clean(); }

void settings::okSlot() {
  bool updatedLanguage = false;
  loging->Debug("OK");
  dataManager *data = new dataManager();
  loging->Debug("data init");
  if (ui->DataPathLine->text() != data->getPath()) {
    data->setPath((QDir::fromNativeSeparators(ui->DataPathLine->text())));
  }

  data->setCurrency(ui->CurrencyLine->text());
  loging->Debug(data->GetCurrency());
  if (ui->TranslationSelect->currentText() != data->getMenuTranslation()) {
    updatedLanguage = true;
  }

  data->setTranslation(ui->TranslationSelect->currentText());

  if (ui->verbositySelect->currentText() == "off") {
    data->setLogLevel(loging->off);
  } else if (ui->verbositySelect->currentText() == "info") {
    data->setLogLevel(loging->info);
  } else if (ui->verbositySelect->currentText() == "debug") {
    data->setLogLevel(loging->debug);
  } else {
    data->setLogLevel(loging->debug);
  }

  loging->Debug("settings saved");
  delete data;
  loging->Debug("done");
  this->close();
}

void settings::enableWindow() { this->setEnabled(true); }

void settings::showExport() {
  loging->Debug("showExport called");
  Export *exportWindow = new Export(0, sqlManager->getModel());
  connect(exportWindow, SIGNAL(finished(int)), this, SLOT(updateDatabase()));
  exportWindow->show();
}

void settings::showImport() {
  loging->Debug("showImport called");
  Import *import = new Import(0, sqlManager);
  connect(import, SIGNAL(finished(int)), this, SLOT(updateDatabase()));
  import->show();
}

void settings::selectFolder() {
  dataManager *data = new dataManager();
  QFileDialog *selectFolderDialog = new QFileDialog(this);
  selectFolderDialog->setOption(QFileDialog::DontUseNativeDialog);
  selectFolderDialog->setFileMode(QFileDialog::Directory);
  selectFolderDialog->setOption(QFileDialog::ShowDirsOnly);
  selectFolderDialog->setDirectory(data->getPath());
  if (selectFolderDialog->exec()) {
    QString directory = selectFolderDialog->selectedFiles()[0];
    ui->DataPathLine->setText(directory);
  }

  delete data;
}
