#include "Cellular.h"
#include <QDebug>

Cellular::Cellular(QString name, double x, double y, double speed, double angle, double deltaAngle): Equipo(name, x, y, speed, angle, deltaAngle){
    m_itemName = QString("Telefono");
}