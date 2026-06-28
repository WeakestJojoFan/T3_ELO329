#ifndef CELLULAR_H
#define CELLULAR_H

#include <QDebug>
#include "Equipo.h"

class Cellular: public Equipo
{
public:
    Cellular(QString name, double x, double y, double speed, double angle, double deltaAngle);
};

#endif // CELLULAR_H