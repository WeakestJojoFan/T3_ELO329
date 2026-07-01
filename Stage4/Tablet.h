#ifndef TABLET_H
#define TABLET_H
#include "EquipoPasivo.h"
#include <QDebug>

class Tablet : public EquipoPasivo
{
public:
    Tablet(QString name, double x, double y, double speed, double angle, double deltaAngle);
};

#endif // TABLET_H
