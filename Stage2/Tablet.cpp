#include "Tablet.h"
#include "Equipo.h"
#include <QDebug>

Tablet::Tablet(QString name, double x, double y, double speed, double angle, double deltaAngle): Equipo(name, x, y, speed, angle, deltaAngle){
    m_itemName = QString("Tablet");
}