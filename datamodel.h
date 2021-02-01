#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QPointF>

class DataModel : public QAbstractListModel
{
    Q_OBJECT

private:
    QVector<QPointF> myList {QPointF(0.0f, 0.9f)};

public:

    explicit DataModel(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
    }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        if (parent.isValid())
            return 0;
        return myList.length();
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (!index.isValid())
            return QVariant();
        if(index.row() >= 0 && index.row() < rowCount())
            return QVariant::fromValue(myList[index.row()]);
        return QVariant();
    }

};

#endif // DATAMODEL_H
