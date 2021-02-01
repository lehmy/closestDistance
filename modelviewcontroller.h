#ifndef MODELVIEWCONTROLLER_H
#define MODELVIEWCONTROLLER_H
#include <QObject>
#include <QPointF>

class ModelViewController : public QObject
{
    Q_OBJECT


public:
    ModelViewController(QList<QPointF> & model, QObject *parent = nullptr): m_model(QList<QPointF>())
    {
        m_model = model;
    }
    Q_INVOKABLE int count()
    {
        return m_model.count();
    }
    Q_INVOKABLE QPointF get(int index)
    {
        return m_model[index];
    }

signals:
    void itemsChanged();
private:
    QList<QPointF> m_model;
};

#endif // MODELVIEWCONTROLLER_H
