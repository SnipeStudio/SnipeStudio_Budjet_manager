#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/ico.png"));
    a.setApplicationName("Snipe Studio Budget Manager");
    a.setApplicationVersion("0.0.2.0");
    a.addLibraryPath("qwindows.dll");
    Widget w;
    w.setProperty("Version",a.applicationVersion());
    w.show();

    return a.exec();
}
