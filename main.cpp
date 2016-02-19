#include "widget.h"
#include "app_info.h"
#include "logger/logger.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    logger* loging=new logger();
    dataManager* data=new dataManager();
    loging->debugM("Loading translation");
    translator.load(QDir::toNativeSeparators("translation/ssbm_"+data->getTranslation()));
    qApp->installTranslator(&translator);
    loging->debugM("Translation loaded");
    delete data;
    a.setWindowIcon(QIcon(":/icon/ico.png"));
    loging->infoM(QString("Version of application set to ").arg(VER_PRODUCTNAME_STR));
    a.setApplicationName(VER_PRODUCTNAME_STR);
    loging->infoM(QString("Version of file set to %1").arg(VER_FILEVERSION_STR));
    a.setApplicationVersion(VER_FILEVERSION_STR);
    a.addLibraryPath("./");
    loging->infoM(QString("Initializing of %1").arg(VER_PRODUCTNAME_STR));
    Widget* w = new Widget(0,loging);
    w->show();
    return a.exec();
}
