#include "widget.h"
#include "app_info.h"
#include "logger/logger.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    dataManager* data=new dataManager();
    logger* loging=new logger();
    loging->setVerbosity(data->getVerbosity());
    loging->writeLog("Loading translation");
    translator.load(QDir::toNativeSeparators("translation/ssbm_"+data->getTranslation()));
    qApp->installTranslator(&translator);
    loging->writeLog("Translation loaded");
    delete data;
    a.setWindowIcon(QIcon(":/icon/ico.png"));
    a.setApplicationName(VER_PRODUCTNAME_STR);
    a.setApplicationVersion(VER_FILEVERSION_STR);
    Widget* w = new Widget(0,loging);
    w->show();
    return a.exec();
}
