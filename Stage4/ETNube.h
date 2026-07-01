#ifndef ETNUBE_H
#define ETNUBE_H
#include <QMap>
#include <QPointF>

class ETNube
{
public:
    ETNube();
    void uploadData(QString name, QString itemName, bool isTag, double x, double y);
    std::pair<QMap<QString, QPointF>, QMap<QString, QPointF>> downloadData(const QString& user);
    std::pair<QMap<QString, QMap<QString, QPointF>>, QMap<QString, QMap<QString, QPointF>>> downloadAllData(){return std::make_pair(m_smartDeviceData, m_tagData);}
private:
    QMap<QString, QMap<QString, QPointF>> m_tagData;
    QMap<QString, QMap<QString, QPointF>> m_smartDeviceData;
};

#endif // ETNUBE_H
