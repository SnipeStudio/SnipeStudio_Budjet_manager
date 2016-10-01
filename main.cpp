#include "widget.h"
#include "app_info.h"
#include "logger/logger.h"
#include "commandline/commandline.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    commandLine* console = new commandLine(argc, argv);
    logger* loging=new logger();
    dataManager* data=new dataManager();

    if(console->IsCommandLine())
    {
        loging->infoM(QString("Initializing of %1 console app").arg(VER_PRODUCTNAME_STR));
        return 0;
    }
    else
    {
        QApplication a(argc, argv);
        QTranslator translator;
        loging->infoM("Loading translation from " + QDir::toNativeSeparators("translation/ssbm_"+data->getTranslation())+".qm");
        translator.load(QDir::toNativeSeparators("translation/ssbm_"+data->getTranslation()+".qm"));
        qApp->installTranslator(&translator);
        loging->debugM("Translation loaded");
        delete data;
        a.setWindowIcon(QIcon(":/icon/ico.png"));
        loging->infoM(QString("Version of application set to %1").arg(VER_PRODUCTVERSION_STR));
        a.setApplicationName(VER_PRODUCTNAME_STR);
        a.setApplicationVersion(VER_PRODUCTVERSION_STR);
        loging->infoM(QString("Version of file set to %1").arg(VER_PRODUCTVERSION_STR));
        a.addLibraryPath("./");
        loging->infoM(QString("Initializing of %1").arg(VER_PRODUCTNAME_STR));
        Widget* w = new Widget(0,loging);
        w->show();
        return a.exec();
    }
}
