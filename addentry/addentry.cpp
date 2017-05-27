#include "addentry.h"
#include "ui_addentry.h"

addEntry::addEntry(bool side, sqlMan *sqlOut, QWidget *parent)
    : QDialog(parent), ui(new Ui::addEntry) {
  sql = sqlOut;
  ui->setupUi(this);
  dataManager *data = new dataManager();
  data->reloadTranslator();
  ui->retranslateUi(this);
  delete data;
  this->side = side;

  // TODO: Probably i should define it somehow another way
  if (side) {
    ui->Side->setText("+");
  } else {
    ui->Side->setText("-");
  }

  ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

addEntry::~addEntry() { delete ui; }

void addEntry::on_cancel_clicked() {
  ui->confirmChanges->setEnabled(false);
  this->close();
}

void addEntry::on_confirmChanges_clicked() {
  ui->confirmChanges->setEnabled(false);
  const QChar delimiter = (uchar)'.';
  bool summDigits = true;
  short dots = 0;
  if (!ui->lineSumm->text().isEmpty()) {
    for (int i = 0; i < ui->lineSumm->text().length(); i++) {
      if (!ui->lineSumm->text().at(i).isDigit() &&
          !(ui->lineSumm->text().at(i) == '.') &&
          !(ui->lineSumm->text().at(i) == ',')) {
        summDigits = false;
      }

      if ((ui->lineSumm->text().at(i) == '.') ||
          (ui->lineSumm->text().at(i) == ',')) {
        ui->lineSumm->setText(ui->lineSumm->text().replace(i, 1, delimiter));
        dots++;
      }
    }
  }

  if ((ui->lineEditComment->text().isEmpty() &&
       ui->lineSumm->text().isEmpty()) ||
      !summDigits || dots > 1) {
    this->setEnabled(false);
    QMessageBox a(this);
    a.setText(tr("Invalid summ value"));
    a.show();
    connect(&a, SIGNAL(finished(int)), this, SLOT(enable()));
    return;
  }

  if (ui->lineEditComment->text().isEmpty()) {
    ui->lineEditComment->setText("Default");
  }

  summ = ui->lineSumm->text().toDouble();
  if (!side) {
    summ = -summ;
  }

  QDateTime time = ui->dateTimeEdit->dateTime();
  sql->addOperation(summ, ui->lineEditComment->text(), side,
                    ui->dateTimeEdit->dateTime());
  this->close();
}

void addEntry::enable() {
  this->setEnabled(true);
  this->ui->confirmChanges->setEnabled(true);
}
