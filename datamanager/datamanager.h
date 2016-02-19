#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <QtCore/QFile>
#include <QTextCodec>
#include <sqlman/sqlman.h>


class dataManager : public QObject
{
    Q_OBJECT
public:
    dataManager();
    ~dataManager();

    QString getPath();
    QString GetCurrency();
    QString getTranslation();
    QString getMenuTranslation();
    QString getDefaultUser();
    int getLoglevel();

signals:
public slots:
    void setPath(QString data);
    void setCurrency(QString currency);
    void setTranslation(QString translation);
    void setDefaultUser(QString DefaultUser);
    void setLogLevel(int lLevel);


private:
    QString dataPath;
    QString configPath;
    QString Currency;
    QString Translation;
    QString DefUser;
    int Loglevel;
    enum logLevelenum{
        off=0,
        info=1,
        debug=2
    };
};

#endif // DATAMANAGER_H
