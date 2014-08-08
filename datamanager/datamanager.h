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
    dataManager();
    ~dataManager();

    QString getPath();
    QString GetCurrency();
    QString getTranslation();
    QString getMenuTranslation();

signals:
public slots:
    void setPath(QString data);
    void setCurrency(QString currency);
    void setTranslation(QString translation);

private:
    QString dataPath;
    QString configPath;
    QString Currency;
    QString Translation;
};

#endif // DATAMANAGER_H
