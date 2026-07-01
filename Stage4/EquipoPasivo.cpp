#include "EquipoPasivo.h"
#include <cmath>

EquipoPasivo::EquipoPasivo(QString name, double x, double y, double speed, double angle, double deltaAngle): Equipo(name,x,y,speed,angle,deltaAngle){}

void EquipoPasivo::findNearbyPhone(const QVector<Cellular*>& cells){
    for (Cellular* cell : cells) {
        double dist = std::sqrt( std::pow( (cell->getX()-m_x) ,2) + std::pow( (cell->getY() - m_y) , 2));
        if (dist <= 50){
            cell->reportItemPos(this);
            break;
        }
    }
}

void EquipoPasivo::updatePosition(double deltaTime, const QVector<Cellular*>& cells){
    Equipo::updatePosition(deltaTime);

    m_timeSinceLastScan += deltaTime;

    if (m_timeSinceLastScan >= m_bipTime){
        emit scanAnimation();
        findNearbyPhone(cells);
        m_timeSinceLastScan -= m_bipTime;
    }
}