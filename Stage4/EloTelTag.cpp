#include "EloTelTag.h"
#include <QRandomGenerator>

EloTelTag::EloTelTag(QString name, QString itemName, double x, double y, double speed, double angle, double deltaAngle): EquipoPasivo(name, x, y, speed, angle, deltaAngle){
    m_itemName = itemName;
    m_bipTime = 4.0;
    m_timeSinceLastScan = QRandomGenerator::global()->generateDouble() * m_bipTime;
}