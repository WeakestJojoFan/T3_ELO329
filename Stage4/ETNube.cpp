#include "ETNube.h"

ETNube::ETNube() {}

void ETNube::uploadData(QString name, QString itemName, bool isTag, double x, double y){
    if (isTag){
        m_tagData[name][itemName] = QPointF(x,y);
    }else{
        m_smartDeviceData[name][itemName] = QPointF(x,y);
    }
}

std::pair<QMap<QString, QPointF>, QMap<QString, QPointF>> ETNube::downloadData(const QString& user){
    return std::make_pair(m_smartDeviceData[user], m_tagData[user]);
}