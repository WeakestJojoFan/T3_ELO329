#ifndef TABLET_H
#define TABLET_H
#include "Equipo.h"
#include <QDebug>

class Tablet : public Equipo
{
public:
    Tablet(QString name, double x, double y, double speed, double angle, double deltaAngle);
};

#endif // TABLET_H
