#include "ETNube.h"
#include "EloTelTag.h"

ETNube::ETNube() {}

void ETNube::uploadData(Equipo* device, double x, double y){
    QString name = device->getName();
    QString itemName = device->getItemName();
    if (qobject_cast<EloTelTag*>(device) != nullptr){
        m_tagData[name][itemName] = QPointF(x,y);
    }else{
        qDebug() << "Subiendo ubicacion smart Device";
        m_smartDeviceData[name][itemName] = QPointF(x,y);
    }
}

std::pair<QMap<QString, QPointF>, QMap<QString, QPointF>> ETNube::downloadData(const QString& user){
    return std::make_pair(m_smartDeviceData[user], m_tagData[user]);
}