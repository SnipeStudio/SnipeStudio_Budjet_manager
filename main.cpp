#include "widget.h"
#include "app_info.h"
#include "logger/logger.h"
#include "commandline/commandline.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  sqlMan *db = new sqlMan();
  commandLine *cLine = new commandLine(argc, argv, db);
  if (cLine->cLine) {
    exit(0);
  }
  delete cLine;
  delete db;
  logger *loging = new logger();
  dataManager *data = new dataManager();
  data->loadTranslator();
  a.setWindowIcon(QIcon(":/icon/ico.png"));
  loging->Info(
      QString("Version of application set to %1").arg(VER_PRODUCTVERSION_STR));
  a.setApplicationName(VER_PRODUCTNAME_STR);
  a.setApplicationVersion(VER_PRODUCTVERSION_STR);
  loging->Info(
      QString("Version of file set to %1").arg(VER_PRODUCTVERSION_STR));
  a.addLibraryPath(QDir::toNativeSeparators("./"));
  loging->Info(QString("Initializing of %1").arg(VER_PRODUCTNAME_STR));
  Widget *w = new Widget(0, loging);
  w->show();

  /// TODO: Fix this mess
  /// or it's ok, IDK really
  int exitCode = a.exec();
  delete w;
  return exitCode;
}
