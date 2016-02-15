#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    dataManager* data=new dataManager();
    translator.load(QDir::toNativeSeparators("translation/ssbm_"+data->getTranslation()));
    qApp->installTranslator(&translator);
    delete data;
    a.setWindowIcon(QIcon(":/icon/ico.png"));
    a.setApplicationName("Snipe Studio Budget Manager");
    a.setApplicationVersion("14.06-pre(0.0.4)");
    Widget* w = new Widget(0);
    w->show();
    return a.exec();
}
