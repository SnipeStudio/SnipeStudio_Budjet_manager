#include "commandline.h"

commandLine::commandLine(int argc, char *argv[], sqlMan *database) {

  for (int i = 0; i < argc; i++) {
    QString str = QString((argv[i]));
    arguments.push_back(str);
  }
  parser = new QCommandLineParser();
  exportOption = new QCommandLineOption(
      QStringList() << "e"
                    << "export",
      QCoreApplication::translate("main", "Exporting database to <file>."),
      QCoreApplication::translate("main", "file"));
  parser->addOption(*exportOption);
  importOption = new QCommandLineOption(
      QStringList() << "i"
                    << "import",
      QCoreApplication::translate("main", "Importing database from <file>"),
      QCoreApplication::translate("main", "file"));
  parser->addOption(*importOption);
  profitOption = new QCommandLineOption(
      QStringList() << "p"
                    << "plus",
      QCoreApplication::translate("main",
                                  "Add Profit with parameters. \n"
                                  "Format of data is \"ddMMyyyy_hhmmss\".\n"
                                  " Arguments sent in \"\" symbol between\n"),
      QCoreApplication::translate("main", "summ;comment;data"));
  parser->addOption(*profitOption);

  expenceOption = new QCommandLineOption(
      QStringList() << "m"
                    << "minus",
      QCoreApplication::translate("main",
                                  "Add Expence with parameters. \n"
                                  "Format of data is \"ddMMyyyy_hhmm\".\n"
                                  " Arguments sent with \"\" symbol between\n"),
      QCoreApplication::translate("main", "summ;comment;data"));
  parser->addOption(*expenceOption);
  listOption = new QCommandLineOption(
      QStringList() << "l"
                    << "list",
      QCoreApplication::translate("main",
                                  "Print list of operations from database"));
  parser->addOption(*listOption);
  cleanOption = new QCommandLineOption(
      QStringList() << "c"
                    << "clean",
      QCoreApplication::translate("main", "Clean database of all data"));
  parser->addOption(*cleanOption);
  helpOption = new QCommandLineOption(parser->addHelpOption());
  versionOption = new QCommandLineOption(parser->addVersionOption());
  parser->parse(arguments);
  cLine = false;
  db = database;
  IsClean();
  IsHelp();
  IsVersion();
  IsExport();
  IsImport();
  IsProfit();
  IsList();
}

void commandLine::initDatabase(sqlMan *db) {
  model = db->getModel();
  model->setTable("operations");
  if (!db->dbIsOpen()) {
    qDebug().noquote() << "Error in Db Loading. There are some shit happens "
                          "during database loading";
  }

  qDebug().noquote() << "Database initialized succesfully";
}

bool commandLine::IsHelp() {
  if (parser->isSet(*helpOption)) {
    cLine = true;
    qDebug().noquote() << parser->helpText();
  }

  return false;
}

bool commandLine::IsVersion() {
  if (parser->isSet(*versionOption)) {
    qDebug().noquote() << VER_PRODUCTNAME_STR << VER_FILEVERSION_STR;
    cLine = true;
    ;
  }

  return false;
}

bool commandLine::IsExport() {
  isExport = parser->isSet(*exportOption);
  if (isExport) {
    model = db->getModel();
    qDebug().noquote() << "Exporting mode On";
    if (!exportConsole(parser->value(*exportOption))) {
      qDebug() << "Succesfully exported to " + parser->value(*exportOption);
      cLine = true;
      ;

    } else {
      qDebug().noquote() << "Failed to export " << parser->value(*exportOption);
      cLine = true;
      ;
    }
  }

  return isExport;
}

bool commandLine::IsImport() {
  isImport = parser->isSet(*importOption);
  if (isImport) {
    db = new sqlMan();
    initDatabase(db);
    model = db->getModel();
    qDebug().noquote() << "Import mode On";
    cLine = true;
    ;

    if (!importConsole(parser->value(*importOption))) {
      qDebug() << "Succesfully imported to " + parser->value(*importOption);

    } else {
      qDebug().noquote() << "Failed to import " << parser->value(*importOption);
    }
  }

  return isImport;
}

bool commandLine::IsProfit() {
  if (!parser->isSet(*profitOption)) {
    return false;
  }

  cLine = true;
  ;
  qDebug().noquote() << "Add profit mode";

  QStringList list = parser->value(*profitOption).split(";");

  if (profitConsole(list[0].toDouble(), list[1], list[2])) {
    qDebug().noquote() << "Successfully add PROFIT OPERATION";
    return true;
  } else {
    qDebug().noquote() << "Failed to add PROFIT OPERATION";
    return false;
  }
}

bool commandLine::IsExpence() {
  if (!parser->isSet(*expenceOption)) {
    return false;
  }

  cLine = true;
  ;
  qDebug().noquote() << "Add expence mode";

  QStringList list = parser->value(*profitOption).split(";");

  if (expenceConsole(list[0].toDouble(), list[1], list[2])) {
    qDebug().noquote() << "Successfully add Expence OPERATION";
    return true;

  } else {
    qDebug().noquote() << "Failed to add Expence OPERATION";
    return false;
  }
}

bool commandLine::IsList() {
  if (!parser->isSet(*listOption)) {
    return false;
  }

  cLine = true;
  ;

  if (!this->writeOperations()) {
    return false;
  }
  return true;
}

bool commandLine::IsClean() {
  if (!parser->isSet(*cleanOption)) {
    return false;
  }

  cLine = true;
  ;

  if (!this->cleanDatabase()) {
    return false;
  }
  return true;
}

bool commandLine::exportConsole(QString path) {
  QFile *file;
  try {
    int columns = model->columnCount();
    QString filename = QDir::toNativeSeparators(path);
    file = new QFile(filename);
    file->open(QIODevice::Append);
    do {
      model->fetchMore();
    } while (model->canFetchMore());

    int rows = model->rowCount();
    QTextStream fout(file);
    fout << rows << "\n";
    for (long row = 0; row < rows; row++) {
      QString line = "";
      for (int column = 0; column < columns; column++) {
        QModelIndex index = model->index(row, column);
        line += model->data(index).toString() + ";";
      }

      fout << line << "\n";
    }
    file->close();
    return false;
  } catch (QException) {
    if (file) {
      file->close();
    }
    return true;
  }
}

bool commandLine::importConsole(QString path) {
  try {
    QString filename = QDir::toNativeSeparators(path);
    QFile *file = new QFile(filename);
    file->open(QIODevice::ReadOnly);
    QTextStream fin(file);
    int rows = 0;
    int row = 0;
    fin >> rows;
    while (!fin.atEnd()) {
      QString line = fin.readLine();
      if (line.isEmpty()) {
        continue;
      }

      QStringList list = line.split(';');
      QDateTime dateTime =
          QDateTime::fromString(list[1], "dd-MM-yyyy hh:mm:ss");
      double summ = list[2].toDouble();
      QString comment = list[3];
      bool side = list.at(5).toInt();
      db->addOperation(summ, comment, side, dateTime);
      db->addOperation(summ, comment, side, dateTime);
      row++;
    }

    file->close();
  } catch (QException) {
    return false;
  }
  return true;
}

bool commandLine::profitConsole(double summ, QString comment,
                                QString dateTime) {
  QDateTime dateTime_data = QDateTime::fromString(dateTime, "ddMMyyyy_hhmm");
  db->addOperation(summ, comment, true, dateTime_data);
  return true;
}

bool commandLine::expenceConsole(double summ, QString comment,
                                 QString dateTime) {
  QDateTime dateTime_data = QDateTime::fromString(dateTime, "ddMMyyyy_hhmm");
  db->addOperation(summ, comment, false, dateTime_data);
  return true;
}

bool commandLine::writeOperations() {
  try {
    data = new dataManager();
    qDebug().noquote() << db->getListOfOperations(' ');
    qDebug().noquote() << "Total is :" << db->getBalance() << " "
                       << data->GetCurrency();
    delete data;
  } catch (QException) {
    return false;
  }

  return true;
}

bool commandLine::cleanDatabase() {
  try {
    this->db->clean();
    return true;
  } catch (QException) {
    return false;
  }
}
