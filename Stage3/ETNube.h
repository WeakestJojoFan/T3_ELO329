#ifndef ETNUBE_H
#define ETNUBE_H
#include <QMap>
#include <QPointF>
#include "Equipo.h"

class ETNube
{
public:
    ETNube();
    void uploadData(Equipo* device, double x, double y);
    std::pair<QMap<QString, QPointF>, QMap<QString, QPointF>> downloadData(const QString& user);
private:
    QMap<QString, QMap<QString, QPointF>> m_tagData;
    QMap<QString, QMap<QString, QPointF>> m_smartDeviceData;
};

#endif // ETNUBE_H
