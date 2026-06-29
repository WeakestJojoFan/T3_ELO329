#include "Cellular.h"
#include "ETNube.h"
#include <QDebug>
#include <QTimer>

Cellular::Cellular(QString name, ETNube* cloud, double x, double y, double speed, double angle, double deltaAngle): Equipo(name, x, y, speed, angle, deltaAngle){
    m_itemName = QString("Telefono");
    m_cloud = cloud;
    m_timeSinceLastReport = 0.0;
}

void Cellular::reportPosition(){
    m_cloud->uploadData(this, m_x, m_y);
}

void Cellular::reportItemPos(Equipo* device){
    m_cloud->uploadData(device, m_x, m_y);
}

void Cellular::updatePosition(double deltaTime){
    Equipo::updatePosition(deltaTime);

    m_timeSinceLastReport += deltaTime;

    if (m_timeSinceLastReport >= 4.0){
        reportPosition();

        m_timeSinceLastReport -= 4.0;
    }
}