#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>
#include <QTextCodec>
#include <QDebug>

class dataManager : public QObject
{
    Q_OBJECT
public:
    dataManager(QObject *parent=0)
    {
        QString fileNameSettings=tr("settings.cfg");
        QFile file(fileNameSettings);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            in.setCodec(QTextCodec::codecForName("UTF-8"));
            QString line = in.readLine();
            qDebug()<<line;
            QStringList result;
            while (!line.isNull())
            {
                line.remove(QRegExp("//[\\W\\w]{0,}"));
                result.append(line.split(QString('=')));
                if(result.at(0)=="DataPath")
                {
                    dataPath=result.at(1);
                    qDebug()<<dataPath;
                    break;
                }
            }
        }
        else
        {
            if(file.open(QIODevice::WriteOnly))
            {
                QTextStream out(&file);
                out.setCodec("UTF-8");
                out<<"DataPath=\n";
            }

        }
        file.close();
    }
    QString getPath()
    {
        return dataPath;
    }
signals:

public slots:
private:
    QString dataPath;
    QString configPath;
};

#endif // DATAMANAGER_H
