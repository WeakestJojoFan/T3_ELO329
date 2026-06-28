#include "Equipo.h"
#include <QDebug>
#include <cmath>
#include <random>

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

QString Equipo::getItemName() const{
    return m_itemName;
}
double Equipo::getX() const{
    return m_x;
}
double Equipo::getY() const{
    return m_y;
}

void Equipo::updatePosition(double deltaTime){
    static std::random_device rd;

    static std::mt19937 gen(rd());

    std::uniform_real_distribution<double> dis(-m_deltaAngle, m_deltaAngle);

    m_angle += dis(gen);

    double angleRad = m_angle * (M_PI / 180.0);

    double deltaX = m_speed * std::cos(angleRad) * deltaTime;
    double deltaY = m_speed * std::sin(angleRad) * deltaTime;

    m_x += deltaX;
    m_y += deltaY;
}

void Equipo::reboteX(){
    m_angle = 180.0 - m_angle;
}

void Equipo::reboteY(){
    m_angle = -m_angle;
}