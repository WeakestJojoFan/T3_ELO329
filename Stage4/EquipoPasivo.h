#ifndef EQUIPOPASIVO_H
#define EQUIPOPASIVO_H
#include "Equipo.h"
#include "Cellular.h"
#include <QVector>

class EquipoPasivo: public Equipo
{
    Q_OBJECT
public:
    EquipoPasivo(QString name, double x, double y, double speed, double angle, double deltaAngle);

    void findNearbyPhone(const QVector<Cellular*>& cells);
    void updatePosition(double deltaTime, const QVector<Cellular*>& cells);
protected:
    double m_timeSinceLastScan;
    double m_bipTime;
signals:
    void scanAnimation();
};

#endif // EQUIPOPASIVO_H
