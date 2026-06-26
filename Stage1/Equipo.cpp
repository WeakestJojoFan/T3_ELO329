#include "Equipo.h"
#include <QDebug>

Equipo::Equipo(QString name, double x, double y, double speed, double angle, double deltaAngle):
    m_name(name),
    m_x(x),
    m_y(y),
    m_speed(speed),
    m_angle(angle),
    m_deltaAngle(deltaAngle)
{}

QString Equipo::getName() const{
    return m_name;
}
double Equipo::getX() const{
    return m_x;
}

double Equipo::getY() const{
    return m_y;
}