#ifndef LOGAPI_H
#define LOGAPI_H

#include <QObject>

class logApi : public QObject
{
    Q_OBJECT
public:
    explicit logApi(QObject *parent = 0);

signals:

public slots:

};

#endif // LOGAPI_H
