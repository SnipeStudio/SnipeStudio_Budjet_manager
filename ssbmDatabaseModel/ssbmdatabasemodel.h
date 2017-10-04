#ifndef SSBMDATABASEMODEL_H
#define SSBMDATABASEMODEL_H

#include <QBrush>
#include <QColor>
#include <QSqlRecord>
#include <QSqlTableModel>

class ssbmDatabaseModel : public QSqlTableModel {
  Q_OBJECT
public:
  explicit ssbmDatabaseModel(QObject *parent = Q_NULLPTR,
                             QSqlDatabase db = QSqlDatabase());
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QColor calculateColorForRow(int row);

signals:

public slots:
private:
};

#endif // SSBMDATABASEMODEL_H
