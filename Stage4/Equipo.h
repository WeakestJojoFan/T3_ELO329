#ifndef EQUIPO_H
#define EQUIPO_H
#include <QDebug>
#include <QList>
#include <QPointF>
#include <qobject.h>

class Equipo : public QObject{
    Q_OBJECT
protected:
    QString m_name;
    QString m_itemName;
    double m_x;
    double m_y;
    double m_speed;
    double m_angle;
    double m_deltaAngle;
    bool m_trackingActive = false;
    QList<QPointF> m_history;

public:
    Equipo(QString name, double x, double y, double speed, double angle, double deltaAngle);

    QString getName() const;
    QString getItemName() const;
    double getX() const;
    double getY() const;
    void updatePosition(double deltaTime);
    void reboteX();
    void reboteY();

    void setTracking(bool active);
    bool isTrackingActive() const;
    const QList<QPointF>& getHistory() const;
};

#endif // EQUIPO_H
