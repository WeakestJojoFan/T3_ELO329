#ifndef CELLULAR_H
#define CELLULAR_H

#include <QDebug>
#include "Equipo.h"
#include "ETNube.h"

class Cellular: public Equipo
{
public:
    Cellular(QString name, ETNube* cloud , double x, double y, double speed, double angle, double deltaAngle);

    void updatePosition(double deltaTime);
    void reportPosition();
    void reportItemPos(Equipo* device);
private:
    ETNube* m_cloud;
    double m_reportTime;
    double m_timeSinceLastReport;
};

#endif // CELLULAR_H