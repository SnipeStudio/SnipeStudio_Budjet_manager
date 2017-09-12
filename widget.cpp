#include "widget.h"

Widget::Widget(QWidget *parent, logger *log_ptr)
    : QWidget(parent), ui(new Ui::Widget) {
  db = new sqlMan();
  this->setAttribute(Qt::WA_DeleteOnClose);
  if (log_ptr != 0) {
    loging = log_ptr;
  } else {
    loging = new logger();
  }
  dataManager *dataMan = new dataManager();
  if (QFile::exists(
          QDir::toNativeSeparators(dataMan->getPath() + "lockfile"))) {
    delete dataMan;
    exit(-1);
  } else {
    QFile lock(QDir::toNativeSeparators(dataMan->getPath() + "lockfile"));
    lock.open(QIODevice::Append);
    lock.close();
  }
  fLoad = false;
  idLoaded = 0;
  version = VER_FILEVERSION_STR;
  loging->Debug("Initialize user interface");
  ui->setupUi(this);
  QString path = dataMan->getPath() + "bal.ssff";
  loging->Debug(QString("Setting DataPath:%1").arg(dataMan->getPath()));
  ui->currency->setText(dataMan->GetCurrency());
  loging->Debug(QString("Setting Currency:%1").arg(dataMan->GetCurrency()));
  loging->Debug("Processing balance");
  loging->Debug("Done");
  delete dataMan;
  this->setWindowTitle("Snipe Studio Budget Manager");
  loging->Debug("Activating Slots");
  connect(ui->about, SIGNAL(clicked()), this, SLOT(help()));
  connect(ui->profit, SIGNAL(clicked()), this, SLOT(addProfit()));
  connect(ui->expence, SIGNAL(clicked()), this, SLOT(addExpence()));
  connect(ui->settings, SIGNAL(clicked()), this, SLOT(showSettings()));
  connect(ui->view, SIGNAL(doubleClicked(QModelIndex)), this,
          SLOT(editTrigger(QModelIndex)));
  loging->Debug("Done");
  loging->Debug("Activating shortcuts");
  keyDelete = new QShortcut(this);
  keyDelete->setKey(Qt::Key_Delete);
  keyPlus = new QShortcut(this);
  keyPlus->setKey(Qt::Key_Plus);
  keyMinus = new QShortcut(this);
  keyMinus->setKey(Qt::Key_Minus);
  connect(keyPlus, SIGNAL(activated()), this, SLOT(addProfit()));
  connect(keyMinus, SIGNAL(activated()), this, SLOT(addExpence()));
  connect(keyDelete, SIGNAL(activated()), this, SLOT(deleteEntry()));
  loging->Debug("Done");
  updateDatabase();
}

Widget::~Widget() {
  delete db;
  this->closeEvent();
}

void Widget::initDatabase(sqlMan *db) {
  loging->Debug("Get into database initialization");
  QSqlTableModel *model = db->getModel();
  model->setTable("operations");
  if (db->dbIsOpen()) {
    QMessageBox *dbOpenError = new QMessageBox(this);
    loging->Error("Error in Db Loading. There are some shit happens during "
                  "database loading");
    dbOpenError->warning(this, "Error in Db Loading",
                         "There are some shit happens during database loading");
    dbOpenError->exec();
  }

  updateDatabase();
  loging->Debug("Database initialized succesfully");
}

void Widget::help() {
  loging->Debug("About message called");
  QMessageBox helpMb(this);
  helpMb.about(this, "About SSBM",
               QString("Snipe Studio Budget Manager v.%1\nUsing QT5\n%2\n%3")
                   .arg(this->version)
                   .arg(VER_LEGALCOPYRIGHT_STR)
                   .arg(VER_LEGALTRADEMARKS1_STR));
  helpMb.close();
}

void Widget::addProfit() { addOperation(true); }

void Widget::addExpence() { addOperation(false); }

void Widget::addOperation(bool side) {
  addEntry *AddEntryWidget = new addEntry(side, db);
  connect(AddEntryWidget, SIGNAL(finished(int)), this, SLOT(updateDatabase()));
  connect(AddEntryWidget, SIGNAL(finished(int)), this, SLOT(enableWindow()));
  AddEntryWidget->show();
  this->setEnabled(false);
}

void Widget::load() {
  loging->Debug("load called");
  QTranslator translator;
  dataManager *data = new dataManager();
  translator.load(QDir::toNativeSeparators("translations/ssbm_" +
                                           data->getTranslation() + ".qm"));
  qApp->installTranslator(&translator);
  ui->retranslateUi(this);
  delete data;
}

void Widget::showSettings() {
  loging->Debug("showSettings called");
  this->setEnabled(false);
  if (set != NULL)
    set = new settings(this, loging, db);
  connect(set, SIGNAL(finished(int)), this, SLOT(updateDatabase()));
  connect(set, SIGNAL(finished(int)), this, SLOT(enableWindow()));
  connect(set, SIGNAL(finished(int)), this, SLOT(closeSettings()));
  set->show();
}

void Widget::closeSettings() {
  dataManager *data = new dataManager();
  data->reloadTranslator();
  ui->retranslateUi(this);
  set->hide();
  set->close();
  delete data;
}

void Widget::editTrigger(QModelIndex index) {
  QVector<QString> data;
  int col_count = ui->view->model()->columnCount();
  for (int i = 0; i < col_count; i++) {
    data.push_back(ui->view->model()->index(index.row(), i).data().toString());
  }

  editdialog = new editentry(this, loging, &data, db);
  connect(editdialog, SIGNAL(finished(int)), this, SLOT(updateDatabase()));
  editdialog->show();
}

void Widget::updateDatabase() {
  QSqlTableModel *model = db->getModel();
  ui->view->setModel(model);
  ui->view->hideColumn(0);
  ui->view->hideColumn(4);
  ui->view->hideColumn(5);
  ui->view->resizeColumnsToContents();
  ui->view->sortByColumn(0, Qt::DescendingOrder);
  ui->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->view->horizontalHeader()->setStretchLastSection(true);
  ui->view->show();
  ui->view->selectRow(0);
  ui->balance->setText(QString::number(db->getBalance(), 'f', 2));
  QPalette *palette = new QPalette();
  if (db->getBalance() == 0) {
    palette->setColor(QPalette::WindowText, Qt::black);
  } else if (db->getBalance() > 0) {
    palette->setColor(QPalette::WindowText, Qt::darkGreen);
  } else {
    palette->setColor(QPalette::WindowText, Qt::darkRed);
  }

  ui->balance->setPalette(*palette);
  dataManager *data = new dataManager();
  ui->currency->setText(data->GetCurrency());
  delete data;
}

void Widget::enableWindow() { this->setEnabled(true); }

void Widget::deleteEntry() {
  int selectedIndex = ui->view->model()
                          ->index(ui->view->currentIndex().row(), 0)
                          .data()
                          .toInt();
  db->deleteOperation(selectedIndex);
  updateDatabase();
}

void Widget::closeEvent() {
  dataManager *data = new dataManager();
  while (!QDir().remove(QDir().absoluteFilePath(
      QDir::toNativeSeparators(data->getPath() + "lockfile"))))
    ;
  loging->Info(QString("Deinitialization of %1").arg(VER_PRODUCTNAME_STR));
  loging->Debug("Closing SSBM");
  delete data;
  delete ui;
  delete loging;
  exit(0);
}
