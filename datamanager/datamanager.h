#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <QtCore/QFile>
#include <QTextCodec>
#include <QMessageBox>
#include <sqlman/sqlman.h>


class dataManager : public QObject
{
    Q_OBJECT
public:
    dataManager()
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
                {
                    dataPath=result.at(1);
                }
                if(result.at(0)=="Currency")
                {
                    Currency=result.at(1);
                }
                if(result.at(0)!="Currency"&&result.at(0)!="DataPath")
                {break;}
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
            }

        }
        file.close();
    }
    QString getPath()
    {
        return dataPath;
    }

    QString GetCurrency()
    {
        return Currency;
    }

    ~dataManager()
    {
        QString fileNameSettings=tr("settings.cfg");
        QFile file(fileNameSettings);
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            out.setCodec("UTF-8");

            out<<tr("DataPath=%1\n").arg(dataPath);
            out<<tr("Currency=%1\n").arg(Currency);
        }
        file.close();

    }

signals:

public slots:
    void setPath(QString data)
    {
        dataPath=data;
    }
    void setCurrency(QString currency)
    {
        Currency=currency;
    }
private:
    QString dataPath;
    QString configPath;
    QString Currency;
};

#endif // DATAMANAGER_H
