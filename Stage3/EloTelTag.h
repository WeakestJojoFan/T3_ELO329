#ifndef ELOTELTAG_H
#define ELOTELTAG_H
#include "EquipoPasivo.h"
#include <QDebug>


class EloTelTag : public EquipoPasivo
{
    Q_OBJECT
public:
    EloTelTag(QString name, QString itemName, double x, double y, double speed, double angle, double deltaAngle);
};

#endif // ELOTELTAG_H
