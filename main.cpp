#ifndef
#include "widget.h"
#endif
#ifndef SETTINGS_H
#endif
#ifndef
#endif
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/ico.png"));
    a.setApplicationName("Snipe Studio Budget Manager");
<<<<<<< HEAD
    a.setApplicationVersion("14.04-beta(0.0.2.7)");
=======
    a.setApplicationVersion("14.05-beta(0.0.3.3)");
>>>>>>> origin/linux_maste
    Widget* w=new Widget(0);
    w->setProperty("Version",a.applicationVersion());
    w->show();
    return a.exec();
}
