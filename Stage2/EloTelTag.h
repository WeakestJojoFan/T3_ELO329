#ifndef ELOTELTAG_H
#define ELOTELTAG_H
#include "Equipo.h"
#include <QDebug>


class EloTelTag : public Equipo
{
public:
    EloTelTag(QString name, QString itemName, double x, double y, double speed, double angle, double deltaAngle);
};

#endif // ELOTELTAG_H
