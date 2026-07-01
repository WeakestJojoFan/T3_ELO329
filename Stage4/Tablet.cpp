#include "Tablet.h"
#include <QDebug>
#include <QRandomGenerator>

Tablet::Tablet(QString name, double x, double y, double speed, double angle, double deltaAngle): EquipoPasivo(name, x, y, speed, angle, deltaAngle){
    m_itemName = QString("Tablet");
    m_bipTime = 5.0;
    m_timeSinceLastScan = QRandomGenerator::global()->generateDouble() * m_bipTime;
}