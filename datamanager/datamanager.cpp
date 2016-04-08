#include "datamanager.h"

dataManager::dataManager()
{
    QString fileNameSettings=tr("settings.cfg");
    QFile file(fileNameSettings);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
 in.setCodec(QTextCodec::codecForName("UTF-8"));
        QString line = in.readLine();
        QStringList result;
        while (!line.isNull())
        {
            result.append(line.split(QString('=')));
            line.remove(QRegExp("//[\\W\\w]{0,}"));
            if(result.at(0)=="DataPath")
            dataPath=QDir::toNativeSeparators(result.at(1));
            if(result.at(0)=="Currency")
                Currency=result.at(1);
            if(result.at(0)=="Translation")
                Translation=result.at(1);
            if(result.at(0)=="DefaultUser")
                DefUser=result.at(1);
            if(result.at(0)=="Loglevel")
                Loglevel=result.at(1).toInt();;

            line = in.readLine();
            result.clear();
        }
    }
    else
    {
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            out.setCodec("UTF-8");
            out<<"DataPath=\n";
            out<<"Currency=\n";
            out<<"Translation=\n";
            out<<"DefaultUser=\n";
            out<<"LogLevel=0";
        }

    }
    file.close();
    QDir dataDir(dataPath);
    if(!dataDir.exists())
    {
        dataDir.mkpath(".");
    }
}

dataManager::~dataManager()
{
    QString fileNameSettings=tr("settings.cfg");
    QFile file(fileNameSettings);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out<<tr("DataPath=%1\n").arg(dataPath);
        out<<tr("Currency=%1\n").arg(Currency);
        out<<tr("Translation=%1\n").arg(Translation);
        out<<tr("DefaultUser=%1\n").arg(DefUser);
        out<<tr("Loglevel=%1\n").arg(Loglevel);
    }
    file.close();
}

QString dataManager::getPath()
{
    if(dataPath=="")
    {
        return "./";
    }
    return dataPath;
}

QString dataManager::GetCurrency()
{
    return Currency;
}

QString dataManager::getTranslation()
{
    if(Translation=="")
    {
        return "en";
    }
    return Translation;
}

QString dataManager::getMenuTranslation()
{
    if(Translation=="ru")
    {
       return tr("Russian");
    }
    if(Translation=="en")
    {
       return tr("English");
    }
    if(Translation=="de")
    {
      return tr("German");
    }
    if(Translation=="nl")
    {
       return "Dutch";
    }
    return tr("English");
}

QString dataManager::getDefaultUser()
{
    return DefUser;
}

int dataManager::getLoglevel()
{
    return Loglevel;
}

void dataManager::setPath(QString data)
{
    dataPath=data;
}

void dataManager::setCurrency(QString currency)
{
    Currency=currency;
}

// need make this more flexible, probably using switch...case statement
void dataManager::setTranslation(QString translation)
{
    Translation=translation;
    if(Translation==tr("Russian"))
    {
       Translation="ru";
    }
    if(Translation==tr("English"))
    {
       Translation="en";
    }
    if(Translation==tr("German"))
    {
       Translation="de";
    }
    if(Translation==tr("Dutch"))
    {
       Translation="nl";
    }

}

// for future use
void dataManager::setDefaultUser(QString DefaultUser)
{
    DefUser=DefaultUser;
}

// sets log level
void dataManager::setLogLevel(int lLevel)
{
    Loglevel=lLevel;
}

