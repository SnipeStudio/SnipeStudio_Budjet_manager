#include "widget.h"
#include "app_info.h"
#include "logger/logger.h"
#include "commandline/commandline.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    commandLine* cLine = new commandLine(argc, argv);
    if(cLine->cLine)
    {
        exit(0);
    }

    delete cLine;

    logger* loging = new logger();
    dataManager* data = new dataManager();
    QTranslator translator;
    QString translationPath = QDir::toNativeSeparators(QString("%1/translations/ssbm_%2.qm").arg(data->getPath()).arg(data->getTranslation()));
    loging->infoM(QString("Loading translation from %1").arg(translationPath));
    translator.load(translationPath);
    qApp->installTranslator(&translator);
    loging->debugM("Translation loaded");
    a.setWindowIcon(QIcon(":/icon/ico.png"));
    loging->infoM(QString("Version of application set to %1").arg(VER_PRODUCTVERSION_STR));
    a.setApplicationName(VER_PRODUCTNAME_STR);
    a.setApplicationVersion(VER_PRODUCTVERSION_STR);
    loging->infoM(QString("Version of file set to %1").arg(VER_PRODUCTVERSION_STR));
    a.addLibraryPath(QDir::toNativeSeparators("./"));
    loging->infoM(QString("Initializing of %1").arg(VER_PRODUCTNAME_STR));
    Widget* w = new Widget(0, loging);
    w->show();

    /// TODO: Fix this mess
    /// or it's ok, IDK really
    int exitCode = a.exec();
    delete w;
    return exitCode;
}
