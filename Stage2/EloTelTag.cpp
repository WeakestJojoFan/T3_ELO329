#include "EloTelTag.h"

EloTelTag::EloTelTag(QString name, QString itemName, double x, double y, double speed, double angle, double deltaAngle): Equipo(name, x, y, speed, angle, deltaAngle){
    m_itemName = itemName;
}