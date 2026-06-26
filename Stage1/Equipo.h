#ifndef EQUIPO_H
#define EQUIPO_H
#include <QDebug>

class Equipo {
protected:
    QString m_name;
    double m_x;
    double m_y;
    double m_speed;
    double m_angle;
    double m_deltaAngle;

public:
    Equipo(QString name, double x, double y, double speed, double angle, double deltaAngle);

    QString getName() const;
    double getX() const;
    double getY() const;
};

#endif // EQUIPO_H
