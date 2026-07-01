#include "Cellular.h"
#include "ETNube.h"
#include "EloTelTag.h"
#include <QDebug>
#include <QTimer>
#include<QRandomGenerator>

Cellular::Cellular(QString name, ETNube* cloud, double x, double y, double speed, double angle, double deltaAngle): Equipo(name, x, y, speed, angle, deltaAngle){
    m_itemName = QString("Telefono");
    m_cloud = cloud;
    m_reportTime = 4.0;
    m_timeSinceLastReport = QRandomGenerator::global()->generateDouble() * m_reportTime;
}

void Cellular::reportPosition(){
    m_cloud->uploadData(this->getName(), m_itemName, false, m_x, m_y);
}

void Cellular::reportItemPos(Equipo* device){
    bool isTag = false;
    if (qobject_cast<EloTelTag*>(device) != nullptr){isTag = true;}
    m_cloud->uploadData(device->getName(),device->getItemName(), isTag, m_x, m_y);
}

void Cellular::updatePosition(double deltaTime){
    Equipo::updatePosition(deltaTime);

    m_timeSinceLastReport += deltaTime;

    if (m_timeSinceLastReport >= m_reportTime){
        reportPosition();

        m_timeSinceLastReport -= m_reportTime;
    }
}